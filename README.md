# RF433 Control

RF433 Control is a Linux desktop application for receiving, analyzing, and transmitting
433 MHz RF signals using USB-UART adapters.

The tool is designed for research, learning, and working with your own RF devices.
It supports inexpensive 433 MHz RF receiver/transmitter modules connected via
USB-UART adapters such as CH341, CP210x, or FTDI.

The project targets Kali Linux and Debian-based distributions, but should work on
most modern Linux systems.

---

## ✨ Features

- Receive 433 MHz RF signals (OOK / simple protocols)
- Analyze pulses and bit sequences
- Replay and transmit captured RF codes
- UART-based communication (`/dev/ttyUSB*`)
- Graphical user interface (Tkinter)
- No Python installation required for end users
- Portable distribution formats

---

## 🔌 Supported Hardware

- 433 MHz RF receiver modules (e.g. XY-MK, RXB series)
- 433 MHz RF transmitter modules (e.g. FS1000A)
- USB-UART adapters:
  - CH341
  - CP210x
  - FTDI

---

## 🖥 Supported Systems

- Kali Linux
- Debian / Ubuntu and derivatives
- Linux x86_64

---

## 📦 Installation

### AppImage (Recommended)

Portable option that does not require installation or root privileges.

```bash
chmod +x RF_433_Control-x86_64.AppImage
./RF_433_Control-x86_64.AppImage

Debian / Kali (.deb package)

Recommended for system-wide installation on Debian-based systems.

sudo dpkg -i rf433.deb

During installation, a udev rule is automatically installed to allow access to
serial devices (/dev/ttyUSB*) without running the application as root.

⸻

▶️ Usage
 1. Connect the RF receiver and/or transmitter to a USB-UART adapter
 2. Plug the adapter into the system
 3. Launch RF433 Control
 4. Select the correct serial port
 5. Capture RF signals or transmit saved codes
 6. Save captured signals for later reuse

⸻

🔐 Permissions and udev

When installed via .deb, a udev rule is automatically added for CH341 devices.

If you are running the AppImage and encounter permission issues, ensure that:
 • Your user belongs to the dialout group
 • The device node /dev/ttyUSB* is accessible

sudo usermod -aG dialout $USER

Log out and log back in after changing group membership.

⸻

🛠 Build from Source (Developers)

The project includes a single build script that produces all artifacts:
 • standalone binary
 • AppImage
 • Debian (.deb) package

To build everything:

./build.sh

The script automatically:
 • creates a Python virtual environment
 • installs required dependencies
 • builds a binary using PyInstaller
 • packages an AppImage
 • packages a Debian .deb

No manual build steps are required.

⸻

📤 Release Artifacts

Each release provides:
 • RF_433_Control-x86_64.AppImage
 • rf433.deb

These files can be found on the GitHub Releases page.

⸻

🧪 Troubleshooting

Application does not see serial ports
 • Check that the USB-UART adapter is detected (ls /dev/ttyUSB*)
 • Verify permissions on the device node
 • Ensure udev rules are applied

Permission denied on /dev/ttyUSB*
 • Confirm group membership (dialout)
 • Re-login after adding the user to the group

No RF data received
 • Verify wiring (GND, VCC, DATA)
 • Confirm correct baud rate
 • Ensure correct RX/TX module orientation

⸻

⚠️ Security Notice

This software is intended only for:
 • educational purposes
 • research
 • interaction with devices you own or are authorized to test

Do not use this tool to interact with third-party systems or devices
without explicit permission.

⸻

📄 License

This project is licensed under the MIT License.
See the LICENSE file for details.
