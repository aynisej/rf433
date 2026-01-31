#!/usr/bin/env bash
set -e

echo "[*] RF433 build started"

APP=rf433
APPDIR="$APP.AppDir"
DIST=dist
RELEASE=release

# --- clean ---
rm -rf build dist "$APPDIR" "$RELEASE"
mkdir -p "$RELEASE"

# --- venv ---
if [ ! -d venv ]; then
  python3 -m venv venv
fi
source venv/bin/activate

pip install --upgrade pip
pip install pyserial pyinstaller

# --- build binary ---
echo "[*] Building binary with PyInstaller"
pyinstaller --onefile main.py --name "$APP"

# --- AppDir layout ---
echo "[*] Preparing AppDir"
mkdir -p "$APPDIR/usr/bin"

cp "$DIST/$APP" "$APPDIR/usr/bin/$APP"

# AppRun
cat > "$APPDIR/AppRun" << 'EOF'
#!/bin/sh
HERE="$(dirname "$(readlink -f "$0")")"
exec "$HERE/usr/bin/rf433"
EOF
chmod +x "$APPDIR/AppRun"

# desktop file
cat > "$APPDIR/rf433.desktop" << 'EOF'
[Desktop Entry]
Type=Application
Name=RF433 Control
Exec=rf433
Icon=rf433
Categories=Utility;
Terminal=false
EOF

# icon
if [ ! -f rf433.png ]; then
  echo "[!] rf433.png not found in project root"
  exit 1
fi

cp rf433.png "$APPDIR/rf433.png"

# --- build AppImage ---
echo "[*] Building AppImage"
./appimagetool-x86_64.AppImage "$APPDIR" "$RELEASE/RF_433_Control-x86_64.AppImage"

echo "[✓] AppImage ready"

# --- Debian package ---
echo "[*] Building .deb"
dpkg-deb --build deb/rf433 "$RELEASE/rf433.deb"

echo "[✓] Build finished"
ls -lh "$RELEASE"
