# Changelog

All notable changes to this project are documented in this file.

The format is based on *Keep a Changelog*  
and this project follows *Semantic Versioning*.

---

## [1.0.0] – Initial Release

### Added
- 433 MHz RF signal capture via USB-UART adapters
- RF signal transmission and replay functionality
- Pulse and bit sequence analysis
- Graphical user interface (Tkinter)
- Support for CH341, CP210x, and FTDI USB-UART adapters
- AppImage distribution for portable usage
- Debian (.deb) package for system-wide installation
- Automatic udev rule installation for serial device access
- Unified build script (`build.sh`)

### Notes
- Initial public release
- Tested on Kali Linux (x86_64)

## [1.0.1] – Maintenance Release

### Changed
- Improved serial port detection and error handling
- Clearer user feedback when no devices are available
- Minor GUI layout adjustments
- Internal code cleanup without behavior changes

### Fixed
- Application startup issues when no UART devices are present
- Incorrect handling of unavailable serial ports

---

## [Unreleased]

### Planned
- RX/TX device separation improvements
- Advanced protocol analysis
- Logging and debug mode
### Planned
- Improved serial port auto-detection
- Better error handling and logging
- RX/TX device separation improvements
- Codebase refactoring for maintainability
