#!/usr/bin/env bash
set -e

APP_NAME="rf433"
APP_TITLE="RF_433_Control"
VERSION="1.0.0"
ARCH="amd64"

ROOT_DIR="$(pwd)"
VENV_DIR="$ROOT_DIR/venv"
DIST_DIR="$ROOT_DIR/dist"
BUILD_DIR="$ROOT_DIR/build"
DEB_DIR="$ROOT_DIR/deb/$APP_NAME"
RELEASE_DIR="$ROOT_DIR/release"

ICON_PNG="$ROOT_DIR/rf433.png"
APPIMAGE_TOOL="$ROOT_DIR/appimagetool-x86_64.AppImage"

echo "[*] RF433 build started"

# ─────────────────────────────────────────────
# 1. Проверки
# ─────────────────────────────────────────────
command -v python3 >/dev/null || { echo "python3 not found"; exit 1; }
command -v dpkg-deb >/dev/null || { echo "dpkg-deb not found"; exit 1; }

if [[ ! -f "$APPIMAGE_TOOL" ]]; then
  echo "[!] appimagetool not found, download it first"
  exit 1
fi

# ─────────────────────────────────────────────
# 2. VENV
# ─────────────────────────────────────────────
if [[ ! -d "$VENV_DIR" ]]; then
  echo "[*] Creating venv"
  python3 -m venv venv
fi

source "$VENV_DIR/bin/activate"
pip install --upgrade pip
pip install pyserial pyinstaller

# ─────────────────────────────────────────────
# 3. PyInstaller
# ─────────────────────────────────────────────
echo "[*] Building binary with PyInstaller"
rm -rf build dist *.spec

pyinstaller \
  --onefile \
  --windowed \
  --name "$APP_NAME" \
  rf_control.py

BIN_PATH="$DIST_DIR/$APP_NAME"

if [[ ! -f "$BIN_PATH" ]]; then
  echo "[!] PyInstaller binary not found"
  exit 1
fi

# ─────────────────────────────────────────────
# 4. AppImage
# ─────────────────────────────────────────────
echo "[*] Building AppImage"

APPDIR="$ROOT_DIR/${APP_NAME}.AppDir"
rm -rf "$APPDIR"

mkdir -p "$APPDIR/usr/bin"
mkdir -p "$APPDIR/usr/share/applications"

cp "$BIN_PATH" "$APPDIR/usr/bin/$APP_NAME"
chmod +x "$APPDIR/usr/bin/$APP_NAME"

cat > "$APPDIR/$APP_NAME.desktop" <<EOF
[Desktop Entry]
Type=Application
Name=RF 433 Control
Exec=$APP_NAME
Icon=$APP_NAME
Terminal=false
Categories=Utility;
EOF

cp "$ICON_PNG" "$APPDIR/$APP_NAME.png"

cat > "$APPDIR/AppRun" <<EOF
#!/bin/sh
HERE="\$(dirname "\$(readlink -f "\$0")")"
exec "\$HERE/usr/bin/$APP_NAME"
EOF

chmod +x "$APPDIR/AppRun"

chmod +x "$APPIMAGE_TOOL"
"$APPIMAGE_TOOL" "$APPDIR"

# ─────────────────────────────────────────────
# 5. DEB
# ─────────────────────────────────────────────
echo "[*] Building .deb package"

rm -rf "$DEB_DIR"
mkdir -p "$DEB_DIR/DEBIAN"
mkdir -p "$DEB_DIR/usr/bin"
mkdir -p "$DEB_DIR/usr/share/applications"
mkdir -p "$DEB_DIR/usr/share/icons/hicolor/256x256/apps"

cp "$BIN_PATH" "$DEB_DIR/usr/bin/$APP_NAME"
chmod 755 "$DEB_DIR/usr/bin/$APP_NAME"

cat > "$DEB_DIR/usr/share/applications/$APP_NAME.desktop" <<EOF
[Desktop Entry]
Type=Application
Name=RF 433 Control
Exec=$APP_NAME
Icon=$APP_NAME
Terminal=false
Categories=Utility;
EOF

cp "$ICON_PNG" "$DEB_DIR/usr/share/icons/hicolor/256x256/apps/$APP_NAME.png"

cat > "$DEB_DIR/DEBIAN/control" <<EOF
Package: $APP_NAME
Version: $VERSION
Section: utils
Priority: optional
Architecture: $ARCH
Maintainer: qweq
Depends: libc6
Description: RF 433 MHz control and sniffer tool
EOF

cat > "$DEB_DIR/DEBIAN/postinst" <<EOF
#!/bin/sh
cat <<RULE >/etc/udev/rules.d/99-rf433-ch341.rules
SUBSYSTEM=="tty", ATTRS{idVendor}=="1a86", ATTRS{idProduct}=="7523", MODE="0666"
RULE
udevadm control --reload
udevadm trigger
exit 0
EOF

chmod 755 "$DEB_DIR/DEBIAN/postinst"

dpkg-deb --build --root-owner-group "$DEB_DIR"

# ─────────────────────────────────────────────
# 6. RELEASE
# ─────────────────────────────────────────────
echo "[*] Preparing release artifacts"

mkdir -p "$RELEASE_DIR"
mv "$APP_TITLE"-x86_64.AppImage "$RELEASE_DIR/"
mv "$ROOT_DIR/deb/$APP_NAME.deb" "$RELEASE_DIR/"

echo "[✓] Build complete"
echo "[✓] Artifacts in ./release/"
