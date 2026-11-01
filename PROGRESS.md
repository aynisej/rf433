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
- Toolchain pin status: CMake 4.4.5 is installed on the Mac but is only an observed host version. Qt 6.12.0 is the current LTS candidate (standard support through 2031-09-30); its supported-platform matrix lists Ubuntu 24.04 x86_64/ARM64 with GCC 13.x and Debian 12 x86_64/ARM64 with GCC 12. Qt's official Linux binaries are built on Ubuntu 24.04 with glibc 2.39; older glibc targets require a source build. Qt's ARM desktop reference is Raspberry Pi 5 with 8 GiB, so Pi Zero 2 W (512 MiB) remains a separate resource-validation risk. The inspected vcpkg baseline commit 9a5dfef5d1a0438a7d24856a85bd60f309d355e9 carries qtbase 6.11.2, so using Qt 6.12.0 means obtaining Qt separately or waiting for a compatible vcpkg port. Ubuntu 24.04 is now the approved x86_64/ARM64 release baseline; exact compiler, CMake, Qt, vcpkg and dependency pins remain open, as does the separate Kali ARMHF toolchain.
- Primary references checked for the toolchain assessment: [Qt 6.12 release/support table](https://doc.qt.io/qt-6.12/qt-releases.html), [Qt supported platforms and Linux requirements](https://doc.qt.io/qt-6/supported-platforms.html), [inspected vcpkg baseline](https://github.com/microsoft/vcpkg/commit/9a5dfef5d1a0438a7d24856a85bd60f309d355e9), and [CMake 4.4 release notes](https://cmake.org/cmake/help/latest/release/4.4.html).
- User follow-up (2026-11-01): selected Ubuntu 24.04 LTS as the minimum baseline for x86_64/ARM64 release artifacts and explicitly approved adding Kali Rolling ARMHF on Pi Zero 2 W. The existing `.deb` + AppImage artifact rule is applied to this additional target. The user reports that Kali on the Raspberry Pi was last updated about six months ago; its exact model, release, and installed architecture remain unverified. The user said no USB-SPI adapter is available. The user does not need to boot the Pi to continue this documentation work; collect exact OS details at a later device-validation checkpoint.
- Current resource instruction (2026-11-01): the user estimates about 70% of the Go plan limit remains and asks not to launch tests that consume quota rapidly. Use concise targeted checks and defer high-cost suites; notify the user before long-running operations. Approved feature/platform scope is unchanged.
- Official compatibility findings: Qt 6.12's Linux desktop support matrix lists Ubuntu 24.04 for x86_64/ARM64 and does not list ARMHF; the dedicated Kali Pi Zero 2 W image is ARMHF and the board has 512 MB RAM. AppImage's linuxdeploy documentation says its build service does not provide ARM targets; appimagetool documents ARMHF cross-build support, so the ARMHF AppImage path needs separate implementation and validation. Kali's package tracker reports qt6-base 6.11.2+dfsg-5 imported into kali-rolling on 2026-10-21; this is a repository event, not confirmation of the user's installed version.
- Primary references: [Qt 6.12 supported platforms](https://doc.qt.io/qt-6/supported-platforms.html), [Kali Pi Zero 2 W instructions](https://www.kali.org/docs/arm/raspberry-pi-zero-2-w/), [Kali ARM image matrix](https://arm.kali.org/images.html), [Kali qt6-base tracker](https://pkg.kali.org/pkg/qt6-base/news/), [AppImage ARM packaging guidance](https://docs.appimage.org/packaging-guide/from-source/native-binaries.html), and [appimagetool ARMHF build instructions](https://github.com/AppImage/appimagetool).
- No tools or dependencies were installed. No builds, tests, packages, releases or physical hardware validation were performed.

## Approved scope
Linux V1 first: Ubuntu 24.04 LTS x86_64 + ARM64, including Pi Zero 2 W compatibility, plus Kali Rolling ARMHF on Pi Zero 2 W. Deliver `.deb` and AppImage for all three target profiles. After Linux V1, continue with macOS ARM64, Android ARM64-v8a and ESP32 according to IMPLEMENTATION_PLAN.md. The former token/quota austerity policy has been withdrawn by the user. Windows and RP2040/Pico excluded. First public version 1.0.0. Release publication requires explicit user approval.

## Approved repository operation
The user explicitly approved deleting the old `aynisej/rf433` repository without a backup and recreating a clean repository at the same name and canonical URL. The old Python/CH341 TTL prototype must not be reused. Commit and push all project work directly to the replacement repository in coherent milestones. GitHub Release publication remains unapproved.

## Blockers before implementation
1. **ARMHF Qt/package baseline:** Kali ARMHF is now an approved additional target, but Qt 6.12 upstream does not list ARMHF, and the user-installed Kali release/architecture have not been verified. Select and pin a dated Kali/package baseline and compatible Qt toolchain; validate `.deb` and AppImage packaging for ARMHF.
2. **Hardware profiles:** no USB-SPI adapter is currently available. Exact adapter model/revision pin maps and verified GDO timing capability must be established from reliable documentation and hardware. Never guess.
3. **Toolchain pins:** Ubuntu 24.04 is selected for x86_64/ARM64, but exact compatible compiler, CMake, Qt, vcpkg and dependency versions are not recorded. Pin each target toolchain before implementation.

## Next checkpoint
1. Pin reproducible compiler, CMake, Qt, vcpkg and dependency versions for the Ubuntu 24.04 x86_64/ARM64 baseline.
2. Select a dated Kali Rolling ARMHF package baseline, a compatible Qt route and a validated ARMHF AppImage assembly method. Verify the user's installed Pi model/release/architecture when the device can be started; this is not needed for the current documentation update.
3. Select an exact USB-SPI adapter model/revision before hardware integration; verify pin maps and GDO timing from reliable documentation and physical hardware.
4. Begin implementation only after toolchain/package pins and remaining critical pre-implementation blockers are resolved. Do not install missing tools before implementation is authorized.

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
