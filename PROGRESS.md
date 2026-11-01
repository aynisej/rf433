# Progress

## Current status
Stage 0 repository replacement, initial documentation commit, and macOS environment audit are complete. The former public repository was deleted without backup; a clean public replacement was created at the same canonical URL, cloned to the selected local working folder, and the seven approved planning documents were committed and pushed. No implementation, build, test, package or release has been performed. These documents do not prove any feature exists.

## Stage 0 execution record — 2026-11-01

- Date/time: 2026-11-01 07:06 Europe/Moscow.
- Execution environment: Codex Local on macOS 27.0.1 (build 26A434), Mac14,3, ARM64; 8 GiB RAM. Working directory and read/write access verified at the user's existing /Users/qweq/Desktop/rf433 folder.
- Repository: old aynisej/rf433 visibility was confirmed as public before deletion. It was deleted without backup. New public repository created at the same URL, verified empty before cloning, and cloned in the selected folder. Initial documentation commit 144ccda05c100a858068b391e601c3d512e10aef was pushed to main; GitHub confirmed all seven root documents. The existing .DS_Store was preserved and is not committed.
- Installed host tools: Xcode 27.0; Apple Clang 21.0.0; CMake 4.4.5; Make 3.81; Git 2.56.0; Homebrew 7.0.11; Python 3.15.2; GitHub CLI 2.103.3; pkg-config 3.0.10; SQLite 3.54.0; OpenSSL 4.1.0; libusb 1.0.30.
- Not found: Qt 6, Ninja, vcpkg, libftdi, HIDAPI, ESP-IDF, Java/Android SDK, Docker/Podman, Linux cross-compilers, QEMU, dpkg-deb, AppImage tooling and linuxdeploy. gcc/g++ resolve to Apple Clang, not GNU/Linux compilers.
- Capacity: 12 GiB free on the data volume (94% used). This is a constraint for local Qt/dependency builds and should be considered when selecting the build route.
- USB enumeration: no device names matching FT232/FTDI/MCP2210/CH341/CC1101/USB-SPI were present in system_profiler output. This is only an enumeration result; no adapter pinout, voltage, radio operation or physical hardware behavior was tested.
- Toolchain pin status: observed host versions are not adopted project pins. The official Qt release page identifies Qt 6.12 as the current LTS released on 2026-09-30; the inspected vcpkg baseline commit 9a5dfef5d1a0438a7d24856a85bd60f309d355e9 still carries qtbase 6.11.2. Choose a reproducible Qt acquisition route for x86_64 and ARM64, then lock compiler, CMake, Qt and vcpkg baseline versions before implementation. CMake 4.4.5 is installed on the Mac host; GitHub's Ubuntu 24.04 runner inventory is separately versioned and must not be treated as a fixed image without pinning its tool versions.
- No tools or dependencies were installed. No builds, tests, packages, releases or physical hardware validation were performed.

## Approved scope
Linux V1 first: x86_64 + ARM64 including Raspberry Pi Zero 2 W. Deliver `.deb` and AppImage for both. After Linux V1, continue with macOS ARM64, Android ARM64-v8a and ESP32 according to IMPLEMENTATION_PLAN.md. The former token/quota austerity policy has been withdrawn by the user. Windows and RP2040/Pico excluded. First public version 1.0.0. Release publication requires explicit user approval.

## Approved repository operation
The user explicitly approved deleting the old `aynisej/rf433` repository without a backup and recreating a clean repository at the same name and canonical URL. The old Python/CH341 TTL prototype must not be reused. Commit and push all project work directly to the replacement repository in coherent milestones. GitHub Release publication remains unapproved.

## Blockers before implementation
1. **Object storage representation:** exact physical representation of encrypted payloads and independently destroyable Object Keys is not approved. Select the simplest design satisfying erasure and plaintext-remnant requirements; ask user before locking in.
2. **Hardware profiles:** exact adapter model/revision pin maps and verified GDO timing capability must be established from reliable documentation/hardware. Never guess.
3. **Toolchain pins:** determine and record exact versions during environment audit.

## Next checkpoint
1. Resolve the approved physical representation for per-object keys and encrypted payloads before persistent storage implementation.
2. Establish the exact USB-SPI adapter model/revision, pin map, and supported GDO timing capability from reliable documentation and hardware. Do not infer support from USB/SPI enumeration.
3. Select reproducible compiler, CMake, Qt, vcpkg and dependency pins for Linux x86_64 and ARM64, including a Qt 6 acquisition route compatible with both targets.
4. Begin implementation only after the critical pre-implementation blockers above are resolved. Do not install missing tools before the implementation stage is authorized.

## Progress report template
- Date/time:
- Checkpoint:
- Changes:
- Commands:
- Build/test outcomes:
- Artifacts:
- Known limitations:
- User intervention needed:
- Commit created: yes/no
- Release published: yes/no


## Updated resource policy
The user explicitly withdrew the earlier strict token-saving policy and confirmed access to a usage-limit reset. Do not constrain scope, testing depth or approved platform progression based on the previous remaining-10% estimate. Continue to use resources sensibly, but prioritize quality and completion. Actual technical/product limits and unavailable physical hardware must still be reported honestly.
