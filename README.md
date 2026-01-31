# RF433 Control

RF433 Control is a desktop application for working with 433 MHz RF modules via UART.

It allows capturing, analyzing, and replaying RF signals using inexpensive 433 MHz receiver/transmitter modules connected through USB-UART adapters (e.g. CH341).

## Features

- Receive and decode 433 MHz RF signals
- Transmit recorded RF signals
- UART-based communication
- Graphical interface (Tkinter)
- Supports multiple RX/TX devices and serial ports
- Packaged as:
  - AppImage (portable Linux binary)
  - Debian package (.deb)

## Requirements (runtime)

- Linux (tested on Kali Linux)
- USB-UART adapter (CH341 or compatible)
- 433 MHz RX/TX modules
- Access to serial ports (`/dev/ttyUSB*`)

## Installation

### AppImage (recommended)

```bash
chmod +x RF_433_Control-x86_64.AppImage
./RF_433_Control-x86_64.AppImage
