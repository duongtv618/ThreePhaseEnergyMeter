#!/usr/bin/env python3
"""
pc_calib_tool.py — calibration tool for STM32F411 (dsp_coef_s layout)
======================================================================
Kết nối : PC USB-UART → USART1 (PA9=TX, PA10=RX)
Baud    : 115200  8N1  Slave ID=1

Register layout (khớp calib.h):
  0x0100–0x0119  Phase A/B/C  (5 floats × 3 phases = 30 regs)
  0x011E–0x0129  VLL Vab/Vbc/Vca (2 floats × 3 lines = 12 regs)
  0x012A         CMD save
  0x012C         CMD reset

Cài đặt:
    pip install pymodbus pyserial rich
"""

import argparse
import struct
import sys
import time

try:
    from pymodbus.client import ModbusSerialClient
    from pymodbus.exceptions import ModbusException
except ImportError:
    sys.exit("Thiếu thư viện: pip install pymodbus pyserial")

try:
    from rich.console import Console
    from rich.table import Table
    from rich import box
    _con = Console()
    HAS_RICH = True
except ImportError:
    HAS_RICH = False

# ── Config ────────────────────────────────────────────────────
SLAVE_ID  = 1
BAUD_RATE = 115200
TIMEOUT   = 2

# ── Register map (khớp calib.h) ───────────────────────────────
PHASE_BASE    = 0x0100
VLL_BASE      = 0x011E
CMD_SAVE      = 0x012A
CMD_RESET     = 0x012C
TOTAL_REGS    = 0x012E - PHASE_BASE   # 46 registers

PHASES        = ["Phase A", "Phase B", "Phase C"]
PHASE_FIELDS  = ["v_coef", "i_coef", "i_phase_shift", "v_offset", "i_offset"]
PHASE_LABELS  = ["V coef", "I coef", "I phase shift (°)", "V offset", "I offset"]
PHASE_DEFAULT = [1.0,       1.0,      0.0,                0.0,        0.0]

VLL_FIELDS    = ["vab_coef", "vab_offset", "vbc_coef", "vbc_offset", "vca_coef", "vca_offset"]
VLL_LABELS    = ["Vab coef", "Vab offset", "Vbc coef", "Vbc offset", "Vca coef", "Vca offset"]
VLL_DEFAULT   = [1.0,         0.0,          1.0,         0.0,          1.0,         0.0]

def phase_reg(ph: int, field_idx: int) -> int:
    return PHASE_BASE + ph * 10 + field_idx * 2

def vll_reg(field_idx: int) -> int:
    return VLL_BASE + field_idx * 2

# ── Float helpers ─────────────────────────────────────────────
def f2r(val: float) -> tuple[int, int]:
    raw = struct.unpack(">I", struct.pack(">f", val))[0]
    return (raw >> 16) & 0xFFFF, raw & 0xFFFF

def r2f(hi: int, lo: int) -> float:
    return struct.unpack(">f", struct.pack(">I", (hi << 16) | lo))[0]

# ── Modbus helpers ────────────────────────────────────────────
def read_f32(client, addr: int) -> float | None:
    try:
        r = client.read_holding_registers(addr, count=2, slave=SLAVE_ID)
        return None if r.isError() else r2f(r.registers[0], r.registers[1])
    except ModbusException:
        return None

def write_f32(client, addr: int, val: float) -> bool:
    hi, lo = f2r(val)
    try:
        r = client.write_registers(addr, [hi, lo], slave=SLAVE_ID)
        return not r.isError()
    except ModbusException:
        return False

def write_regs_bulk(client, addr: int, vals: list[float]) -> bool:
    words = []
    for v in vals:
        hi, lo = f2r(v)
        words += [hi, lo]
    try:
        r = client.write_registers(addr, words, slave=SLAVE_ID)
        return not r.isError()
    except ModbusException:
        return False

# ── Read all 46 calib regs in one FC03 request ───────────────
def read_all(client) -> dict | None:
    try:
        r = client.read_holding_registers(
            address=PHASE_BASE, count=TOTAL_REGS, slave=SLAVE_ID
        )
        if r.isError():
            return None
    except ModbusException:
        return None

    regs = r.registers

    def at(addr):
        i = addr - PHASE_BASE
        return r2f(regs[i], regs[i + 1])

    data = {}
    for ph in range(3):
        for fi, field in enumerate(PHASE_FIELDS):
            data[(ph, field)] = at(phase_reg(ph, fi))
    for fi, field in enumerate(VLL_FIELDS):
        data[("vll", field)] = at(vll_reg(fi))

    return data

# ── Display ───────────────────────────────────────────────────
def show_table(data: dict):
    if HAS_RICH:
        t = Table(title="[bold cyan]DSP Calibration Coefficients (dsp_coef_s)[/]",
                  box=box.ROUNDED, show_lines=True)
        t.add_column("Channel",        style="cyan",   width=10)
        t.add_column("v_coef",         style="yellow", justify="right", width=11)
        t.add_column("i_coef",         style="yellow", justify="right", width=11)
        t.add_column("i_phase_shift°", style="yellow", justify="right", width=16)
        t.add_column("v_offset",       style="yellow", justify="right", width=11)
        t.add_column("i_offset",       style="yellow", justify="right", width=11)
        for ph, label in enumerate(PHASES):
            t.add_row(label,
                      f"{data[(ph,'v_coef')]:.6f}",
                      f"{data[(ph,'i_coef')]:.6f}",
                      f"{data[(ph,'i_phase_shift')]:.4f}",
                      f"{data[(ph,'v_offset')]:.6f}",
                      f"{data[(ph,'i_offset')]:.6f}")
        _con.print(t)

        t2 = Table(title="[bold cyan]Line-to-Line Voltage Coefficients (vol_line_coef_s)[/]",
                   box=box.ROUNDED, show_lines=True)
        t2.add_column("Line",   style="cyan",   width=8)
        t2.add_column("coef",   style="yellow", justify="right", width=12)
        t2.add_column("offset", style="yellow", justify="right", width=12)
        for line, (cf, of) in enumerate([("vab_coef","vab_offset"),
                                          ("vbc_coef","vbc_offset"),
                                          ("vca_coef","vca_offset")]):
            t2.add_row(f"V{'ab bc ca'.split()[line]}",
                       f"{data[('vll',cf)]:.6f}",
                       f"{data[('vll',of)]:.6f}")
        _con.print(t2)
    else:
        print(f"\n  {'Ch':<9} {'v_coef':>10} {'i_coef':>10} {'i_phase°':>10} {'v_off':>10} {'i_off':>10}")
        print("  " + "─" * 55)
        for ph, label in enumerate(PHASES):
            print(f"  {label:<9} "
                  f"{data[(ph,'v_coef')]:>10.6f} "
                  f"{data[(ph,'i_coef')]:>10.6f} "
                  f"{data[(ph,'i_phase_shift')]:>10.4f} "
                  f"{data[(ph,'v_offset')]:>10.6f} "
                  f"{data[(ph,'i_offset')]:>10.6f}")
        print(f"\n  {'VLL':<9} {'coef':>10} {'offset':>10}")
        print("  " + "─" * 32)
        for line, (cf, of) in enumerate([("vab_coef","vab_offset"),
                                          ("vbc_coef","vbc_offset"),
                                          ("vca_coef","vca_offset")]):
            name = ["Vab","Vbc","Vca"][line]
            print(f"  {name:<9} {data[('vll',cf)]:>10.6f} {data[('vll',of)]:>10.6f}")

# ── Actions ───────────────────────────────────────────────────
def action_read(client):
    data = read_all(client)
    if data is None:
        print("  ✗ Đọc thất bại")
    else:
        show_table(data)

def action_write_phase(client):
    """Ghi toàn bộ 5 hệ số cho một pha."""
    print("\n  [1] Phase A  [2] Phase B  [3] Phase C")
    try:
        ph = int(input("  Chọn pha: ")) - 1
        if ph not in range(3):
            print("  Không hợp lệ"); return
    except (ValueError, KeyboardInterrupt):
        print("  Huỷ"); return

    # Đọc giá trị hiện tại làm default
    data = read_all(client) or {}
    vals = []
    for fi, (field, label, dflt) in enumerate(zip(PHASE_FIELDS, PHASE_LABELS, PHASE_DEFAULT)):
        cur = data.get((ph, field), dflt)
        try:
            s = input(f"  {label:<22} [{cur:.6f}]: ").strip()
            vals.append(float(s) if s else cur)
        except (ValueError, KeyboardInterrupt):
            vals.append(cur)

    if write_regs_bulk(client, phase_reg(ph, 0), vals):
        print(f"  ✓ Đã ghi {PHASES[ph]}")
    else:
        print("  ✗ Ghi thất bại")

def action_write_vll(client):
    """Ghi 6 hệ số VLL (vab/vbc/vca coef + offset)."""
    data = read_all(client) or {}
    vals = []
    print()
    for fi, (field, label, dflt) in enumerate(zip(VLL_FIELDS, VLL_LABELS, VLL_DEFAULT)):
        cur = data.get(("vll", field), dflt)
        try:
            s = input(f"  {label:<22} [{cur:.6f}]: ").strip()
            vals.append(float(s) if s else cur)
        except (ValueError, KeyboardInterrupt):
            vals.append(cur)

    if write_regs_bulk(client, VLL_BASE, vals):
        print("  ✓ Đã ghi VLL coefficients")
    else:
        print("  ✗ Ghi thất bại")

def action_write_field(client):
    """Ghi một trường đơn lẻ."""
    print("\n  Phase [1-3] hoặc VLL [4]:")
    try:
        sel = int(input("  Chọn: "))
    except (ValueError, KeyboardInterrupt):
        print("  Huỷ"); return

    if 1 <= sel <= 3:
        ph = sel - 1
        print(f"  Trường của {PHASES[ph]}:")
        for i, label in enumerate(PHASE_LABELS):
            print(f"    [{i+1}] {label}")
        try:
            fi = int(input("  Chọn: ")) - 1
            val = float(input(f"  Giá trị: "))
        except (ValueError, KeyboardInterrupt):
            print("  Huỷ"); return
        addr = phase_reg(ph, fi)
        label = f"{PHASES[ph]}.{PHASE_FIELDS[fi]}"
    elif sel == 4:
        for i, label in enumerate(VLL_LABELS):
            print(f"    [{i+1}] {label}")
        try:
            fi = int(input("  Chọn: ")) - 1
            val = float(input(f"  Giá trị: "))
        except (ValueError, KeyboardInterrupt):
            print("  Huỷ"); return
        addr = vll_reg(fi)
        label = f"VLL.{VLL_FIELDS[fi]}"
    else:
        print("  Không hợp lệ"); return

    if write_f32(client, addr, val):
        print(f"  ✓ {label} = {val:.6f}  (addr=0x{addr:04X})")
    else:
        print("  ✗ Ghi thất bại")

def action_save(client):
    if input("  Lưu Flash? [y/N]: ").strip().lower() != "y":
        print("  Huỷ"); return
    if write_f32(client, CMD_SAVE, 1.0):
        time.sleep(0.6)
        print("  ✓ Đã lưu Flash")
    else:
        print("  ✗ Thất bại")

def action_reset(client):
    if input("  Reset về default? [y/N]: ").strip().lower() != "y":
        print("  Huỷ"); return
    if write_f32(client, CMD_RESET, 1.0):
        time.sleep(0.3)
        print("  ✓ Reset xong")
        action_read(client)
    else:
        print("  ✗ Thất bại")

# ── Menu ──────────────────────────────────────────────────────
MENU = """
┌──────────────────────────────────────────────────┐
│   STM32F411 DSP Calibration Tool (dsp_coef_s)    │
├──────┬───────────────────────────────────────────┤
│  [1] │ Đọc tất cả hệ số                          │
│  [2] │ Ghi toàn bộ hệ số cho một pha             │
│  [3] │ Ghi VLL coefficients (Vab/Vbc/Vca)        │
│  [4] │ Ghi một trường đơn lẻ                     │
│  [5] │ Lưu vào Flash                             │
│  [6] │ Reset về factory default                  │
│  [0] │ Thoát                                     │
└──────┴───────────────────────────────────────────┘"""

def run(client):
    while True:
        print(MENU)
        try:
            c = input("  Chọn: ").strip()
        except KeyboardInterrupt:
            break
        if   c == "1": action_read(client)
        elif c == "2": action_write_phase(client)
        elif c == "3": action_write_vll(client)
        elif c == "4": action_write_field(client)
        elif c == "5": action_save(client)
        elif c == "6": action_reset(client)
        elif c == "0": break
        else:          print("  Không hợp lệ")

# ── Entry point ───────────────────────────────────────────────
def pick_port(requested):
    try:
        import serial.tools.list_ports
        ports = sorted(p.device for p in serial.tools.list_ports.comports())
    except ImportError:
        ports = []
    if requested:
        return requested
    if not ports:
        sys.exit("Không tìm thấy serial port")
    if len(ports) == 1:
        print(f"  Auto-detected: {ports[0]}")
        return ports[0]
    for i, p in enumerate(ports):
        print(f"  [{i+1}] {p}")
    try:
        return ports[int(input("  Chọn port: ")) - 1]
    except (ValueError, IndexError):
        sys.exit("Không hợp lệ")

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--port",  default=None)
    ap.add_argument("--baud",  type=int, default=BAUD_RATE)
    ap.add_argument("--slave", type=int, default=SLAVE_ID)
    args = ap.parse_args()

    port = pick_port(args.port)
    print(f"\n  Port={port}  Baud={args.baud}  Slave={args.slave}\n")

    client = ModbusSerialClient(
        port=port, baudrate=args.baud,
        bytesize=8, parity="N", stopbits=1, timeout=TIMEOUT,
    )
    if not client.connect():
        sys.exit(f"Không mở được {port}")

    test = read_f32(client, PHASE_BASE)
    if test is None:
        print("  ⚠  Không nhận phản hồi — kiểm tra kết nối / NVIC")
    else:
        print(f"  ✓ OK  (Phase A v_coef = {test:.6f})")

    try:
        run(client)
    finally:
        client.close()
        print("  Đóng kết nối.")

if __name__ == "__main__":
    main()