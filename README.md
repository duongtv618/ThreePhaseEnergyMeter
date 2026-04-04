# 3-Phase Energy Meter

A comprehensive STM32-based energy metering system for three-phase electrical installations, providing accurate measurement of voltage, current, power, and energy consumption.

## Features

- **Three-Phase Monitoring**: Real-time measurement of voltage, current, and power on all three phases
- **High Accuracy**: Precision ADC sampling and digital signal processing for accurate measurements
- **Power Calculation**: Active power, reactive power, and apparent power computation
- **Energy Logging**: Cumulative energy consumption tracking
- **Power Factor Analysis**: Real-time power factor calculation for each phase
- **Data Display**: LCD/UART interface for real-time data visualization
- **Energy Billing**: Total energy consumption data for billing purposes
- **Compact Design**: Optimized for integration into standard electrical panels

## Hardware Requirements

- STM32 Microcontroller (F4 or L4 series recommended)
- Current Measurement Modules (CT sensors or Hall effect sensors)
- Voltage Dividers or Sensor Modules
- ADC with sufficient sampling rate (≥ 1 kHz)
- Real-Time Clock (RTC) for timestamp logging
- Optional: EEPROM for data storage

## Software Stack

- STM32CubeIDE / STM32CubeMX
- HAL (Hardware Abstraction Layer)
- Real-time operating system (Optional: FreeRTOS)
- C/C++

## Installation & Setup

1. Clone the repository
2. Open project in STM32CubeIDE
3. Configure hardware peripherals (ADC, UART, RTC)
4. Build and flash to STM32 device

## Usage

The meter continuously monitors three phases and provides:
- Instantaneous voltage and current readings
- Real-time power consumption
- Cumulative energy measurements
- Phase-to-neutral and phase-to-phase relationships

## Communications

- UART: Data transmission to external monitoring systems
- Optional: Ethernet/WiFi module for remote monitoring

## License

MIT License

## Support

For issues or questions, please create an issue in the repository.
