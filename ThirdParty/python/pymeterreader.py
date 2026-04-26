#!/usr/bin/env python3
"""
pc_meter_reader.py  —  đọc đồng hồ 3 pha từ STM32F411
=======================================================
Kết nối : PC USB-UART  →  USART1 (PA9=TX, PA10=RX)
Giao thức: Modbus RTU, FC03, 115200 8N1, slave ID=1

Cài đặt :
    pip install pymodbus pyserial rich

Chạy    :
    python pc_meter_reader.py                     # tự detect COM port
    python pc_meter_reader.py --port COM3
    python pc_meter_reader.py --port /dev/ttyUSB0
    python pc_meter_reader.py --monitor           # live refresh 1s
    python pc_meter_reader.py --monitor --interval 2
"""

import argparse
import struct
import sys
import time

# ── pymodbus ──────────────────────────────────────────────────
try:
    from pymodbus.client import ModbusSerialClient
    from pymodbus.exceptions import ModbusException
except ImportError:
    sys.exit("Thiếu thư viện: pip install pymodbus pyserial")

# ── rich (tuỳ chọn, nếu có thì hiển thị đẹp hơn) ─────────────
try:
    from rich.console import Console
    from rich.table import Table
    from rich.live import Live
    from rich import box
    _console = Console()
    HAS_RICH = True
except ImportError:
    HAS_RICH = False

# ── Cấu hình (phải khớp firmware) ────────────────────────────
SLAVE_ID  = 1
BAUD_RATE = 115200
TIMEOUT   = 2.0   # giây — giảm vì 115200 nhanh

# ── Register map (khớp meter_registers.h) ────────────────────
# Mỗi entry: (tên, địa_chỉ, đơn_vị)
REGS = [
    # Voltage
    ("Va",        0x0000, "V"),
    ("Vb",        0x0002, "V"),
    ("Vc",        0x0004, "V"),
    ("Vab",       0x0006, "V"),
    ("Vbc",       0x0008, "V"),
    ("Vca",       0x000A, "V"),
    # Current
    ("Ia",        0x000C, "A"),
    ("Ib",        0x000E, "A"),
    ("Ic",        0x0010, "A"),
    ("In",        0x0012, "A"),
    # Active power
    ("Pa",        0x0014, "W"),
    ("Pb",        0x0016, "W"),
    ("Pc",        0x0018, "W"),
    ("P total",   0x001A, "W"),
    # Reactive power
    ("Qa",        0x001C, "VAr"),
    ("Qb",        0x001E, "VAr"),
    ("Qc",        0x0020, "VAr"),
    ("Q total",   0x0022, "VAr"),
    # Apparent power
    ("Sa",        0x0024, "VA"),
    ("Sb",        0x0026, "VA"),
    ("Sc",        0x0028, "VA"),
    ("S total",   0x002A, "VA"),
    # Power factor
    ("PFa",       0x002C, ""),
    ("PFb",       0x002E, ""),
    ("PFc",       0x0030, ""),
    ("PF total",  0x0032, ""),
    # Frequency
    ("Frequency", 0x0034, "Hz"),
    # Energy
    ("kWh import",   0x0036, "kWh"),
    ("kWh export",   0x0038, "kWh"),
    ("kVarh import", 0x003A, "kVarh"),
    ("kVarh export", 0x003C, "kVarh"),
    # THD
    ("THD Va",    0x003E, "%"),
    ("THD Vb",    0x0040, "%"),
    ("THD Vc",    0x0042, "%"),
    ("THD Ia",    0x0044, "%"),
    ("THD Ib",    0x0046, "%"),
    ("THD Ic",    0x0048, "%"),
]

# ── Float decode: big-endian word order ──────────────────────
def regs_to_float(hi: int, lo: int) -> float:
    raw = (hi << 16) | lo
    return struct.unpack(">f", struct.pack(">I", raw))[0]

# ── Đọc tất cả thanh ghi một lần (1 request FC03) ────────────
def read_all(client) -> dict | None:
    """
    Đọc toàn bộ 74 holding registers trong 1 request FC03.
    Trả về dict {tên: giá_trị} hoặc None nếu lỗi.
    """
    try:
        # Flush buffer nhận trước khi gửi
        if hasattr(client, '_transport') and hasattr(client._transport, 'flushInput'):
                client._transport.flushInput()
        resp = client.read_holding_registers(
            address=0x0000, count=74, slave=SLAVE_ID
        )
        if resp.isError():
            return None
    except ModbusException:
        return None

    regs = resp.registers
    result = {}
    for name, addr, unit in REGS:
        hi = regs[addr]
        lo = regs[addr + 1]
        result[name] = (regs_to_float(hi, lo), unit)
    return result

# ── Hiển thị bảng ─────────────────────────────────────────────
def print_rich_table(data: dict, timestamp: str):
    table = Table(
        title=f"[bold cyan]3-Phase Power Meter[/]  {timestamp}",
        box=box.ROUNDED,
        show_lines=False,
        padding=(0, 1),
    )
    table.add_column("Parameter",  style="cyan",    width=14)
    table.add_column("Value",      style="yellow",  justify="right", width=12)
    table.add_column("Unit",       style="dim",     width=6)

    for name, (val, unit) in data.items():
        table.add_row(name, f"{val:.3f}", unit)

    _console.print(table)

def print_plain_table(data: dict, timestamp: str):
    print(f"\n{'─'*38}  {timestamp}")
    print(f"  {'Parameter':<16} {'Value':>10}  Unit")
    print(f"{'─'*38}")
    for name, (val, unit) in data.items():
        print(f"  {name:<16} {val:>10.3f}  {unit}")

def show_table(data: dict):
    ts = time.strftime("%H:%M:%S")
    if HAS_RICH:
        print_rich_table(data, ts)
    else:
        print_plain_table(data, ts)

# ── Auto-detect serial port ───────────────────────────────────
def pick_port(requested: str | None) -> str:
    try:
        import serial.tools.list_ports
        ports = sorted(p.device for p in serial.tools.list_ports.comports())
    except ImportError:
        ports = []

    if requested:
        return requested

    if not ports:
        sys.exit("Không tìm thấy serial port nào.")

    if len(ports) == 1:
        print(f"  Auto-detected: {ports[0]}")
        return ports[0]

    print("  Các serial port tìm thấy:")
    for i, p in enumerate(ports):
        print(f"    [{i+1}] {p}")
    try:
        idx = int(input("  Chọn: ")) - 1
        return ports[idx]
    except (ValueError, IndexError):
        sys.exit("Lựa chọn không hợp lệ")

# ── Entry point ───────────────────────────────────────────────
def main():
    parser = argparse.ArgumentParser(
        description="Đọc đồng hồ 3 pha STM32F411 qua Modbus RTU"
    )
    parser.add_argument("--port",     default=None,
                        help="Serial port (COM3 hoặc /dev/ttyUSB0)")
    parser.add_argument("--baud",     type=int, default=BAUD_RATE,
                        help=f"Baud rate (mặc định {BAUD_RATE})")
    parser.add_argument("--slave",    type=int, default=SLAVE_ID,
                        help=f"Slave ID (mặc định {SLAVE_ID})")
    parser.add_argument("--monitor",  action="store_true",
                        help="Live monitor — tự cập nhật liên tục")
    parser.add_argument("--interval", type=float, default=1.0,
                        help="Khoảng thời gian cập nhật (giây, mặc định 1.0)")
    args = parser.parse_args()

    port = pick_port(args.port)

    print(f"\n  Port  : {port}")
    print(f"  Baud  : {args.baud}  8N1")
    print(f"  Slave : {args.slave}\n")

    client = ModbusSerialClient(
        port=port,
        baudrate=args.baud,
        bytesize=8,
        parity="N",
        stopbits=1,
        timeout=TIMEOUT,
    )

    if not client.connect():
        sys.exit(f"Không thể mở {port}")

    try:
        if args.monitor:
            # ── Live monitor ──────────────────────────────────
            print("  Live monitor — Ctrl+C để thoát\n")
            while True:
                data = read_all(client)
                if data is None:
                    print("  [WARN] Không nhận được phản hồi, thử lại...")
                else:
                    if HAS_RICH:
                        _console.clear()
                    show_table(data)
                time.sleep(args.interval)
        else:
            # ── Đọc một lần ──────────────────────────────────
            data = read_all(client)
            if data is None:
                print("  LỖI: Không nhận được dữ liệu.")
                print("  Kiểm tra:")
                print("    • Đúng COM port và baud rate 115200?")
                print("    • PA9 (TX) → RX converter, PA10 (RX) → TX converter")
                print("    • GND chung?")
                print("    • NVIC đã bật USART1 + DMA2_Stream2 + DMA2_Stream7?")
            else:
                show_table(data)
    except KeyboardInterrupt:
        print("\n  Dừng.")
    finally:
        client.close()


if __name__ == "__main__":
    main()