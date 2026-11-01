# Progress

## Current status
Stage 0 repository replacement, initial documentation commit, and macOS environment audit are complete. Stage 1 has begun with a small C++20 Core action-policy library and a Qt Widgets desktop shell. The Core library compiles locally and cross-compiles to ARMHF. A custom Qt 6.12.0 ARMHF QtBase build with XCB and graphics APIs disabled, plus an ARMHF app compile, have succeeded in an isolated Linux VM. ELF dependency inspection found no prohibited GPU libraries. Local `.deb` and AppImage foundation artifacts have now been built for Raspberry Pi Zero 2 W/Kali ARMHF. The user selected a GitHub draft 1.0.0 release; it is not public. The application has not been installed or launched on the Raspberry Pi; Pi UI/resource checks and RF hardware remain outstanding. No test suites or physical hardware validation have been performed.

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
- User follow-up (2026-11-01): selected Ubuntu 24.04 LTS as the minimum baseline for x86_64/ARM64 release artifacts and explicitly approved adding Kali Rolling ARMHF on Pi Zero 2 W. The existing `.deb` + AppImage artifact rule is applied to this additional target. The user reports that Kali on the Raspberry Pi was last updated about six months ago; its exact model, release, and installed architecture remain unverified. The user said no USB-SPI adapter is available. The Pi does not need to be powered for documentation and host-side preparation; it must be available for the prioritized initial on-device testing checkpoint.
- User priority update (2026-11-01): initial real-device bring-up and testing must prioritize the Raspberry Pi Zero 2 W running Kali ARMHF. Ubuntu 24.04 x86_64/ARM64 remain required additional Linux targets and follow the Pi's initial software/UI and resource checks. RF-specific Pi testing remains gated on availability and verification of a USB-SPI adapter.
- User scope update (2026-11-01): proceed with the Pi software/UI/package/resource work without accounting for USB-SPI. Adapter availability blocks only RF-specific implementation and physical radio checks; it must not delay the initial Pi software tests.
- Current resource instruction (2026-11-01): the user estimates about 70% of the Go plan limit remains and asks not to launch tests that consume quota rapidly. Use concise targeted checks and defer high-cost suites; notify the user before long-running operations. Approved feature/platform scope is unchanged.
- Official compatibility findings: Qt 6.12's Linux desktop support matrix lists Ubuntu 24.04 for x86_64/ARM64 and does not list ARMHF; the dedicated Kali Pi Zero 2 W image is ARMHF and the board has 512 MB RAM. AppImage's linuxdeploy documentation says its build service does not provide ARM targets; appimagetool documents ARMHF cross-build support, so the ARMHF AppImage path needs separate implementation and validation. Kali's package tracker reports qt6-base 6.11.2+dfsg-5 imported into kali-rolling on 2026-10-21; this is a repository event, not confirmation of the user's installed version.
- Primary references: [Qt 6.12 supported platforms](https://doc.qt.io/qt-6/supported-platforms.html), [Kali Pi Zero 2 W instructions](https://www.kali.org/docs/arm/raspberry-pi-zero-2-w/), [Kali ARM image matrix](https://arm.kali.org/images.html), [Kali qt6-base tracker](https://pkg.kali.org/pkg/qt6-base/news/), [AppImage ARM packaging guidance](https://docs.appimage.org/packaging-guide/from-source/native-binaries.html), and [appimagetool ARMHF build instructions](https://github.com/AppImage/appimagetool).
- No tools or dependencies were installed. No builds, tests, packages, releases or physical hardware validation were performed.

## Stage 1 initial foundation — 2026-11-01

- Date/time: 2026-11-01 07:39 Europe/Moscow.
- Installed Qt 6.12.0 via Homebrew formula `qtbase` (`6.12.0_2`) without user interaction; only `double-conversion` 3.4.0 and `md4c` 0.6.0 were additional dependencies. The Qt framework bottle is 62.3 MB.
- Added the platform-independent Core action policy and a radio-session state model for serialized operations, readiness gating, scan-only interruption, and immediate hardware-fault state. Added a minimal Qt Widgets shell with the first-launch agreement and session-only FT232H/MCP2210 family selection. The shell visibly marks radio operations and saved-key storage as unimplemented; it does not claim hardware support.
- Local configure/build commands: `cmake -S . -B build/app -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=/opt/homebrew` and `cmake --build build/app --parallel 2`. Both succeeded on macOS 27.0.1 with Apple Clang 21.0.0, CMake 4.4.5 and Qt 6.12.0. This is compile validation only; no test suite or runtime launch was performed.
- Strict graphics rule confirmed by the user (2026-11-01): transitive OpenGL/Vulkan/Metal links are prohibited. The Homebrew QtGui framework used for the initial compile therefore does not satisfy the project rule and must not be used as the compliant app or packaging toolchain. No packaging has been attempted.
- Qt 6.12 source review: `qtbase/src/gui/CMakeLists.txt` links OpenGL only when `QT_FEATURE_opengl` is enabled and adds the Metal graphics-frame-capture source/framework on Apple when `QT_FEATURE_graphicsframecapture` is enabled ([QtGui CMake source](https://github.com/qt/qtbase/blob/6.12/src/gui/CMakeLists.txt)). This did not account for the Cocoa platform plugin's own dependencies; see the follow-up below.
- No test cases were added or run. The latest Go plan instruction remains active: avoid test runs that consume quota quickly and report deferred validation.

## Stage 1 Core follow-up — 2026-11-01

- Date/time: 2026-11-01 07:42 Europe/Moscow.
- Added a Core radio-session state model that allows one operation at a time, gates Scan/Apply/Correction on a successful manual radio check, permits interruption only during Scan, and clears the active operation while faulting radio readiness after a hardware error.
- Added value-only Core progress/outcome event types for the specification's Radio Check stages, Scan phases, and operation endings. Event payloads contain no RF capture, key material, or other large sensitive data.
- Added `RF433_BUILD_APP=OFF` so the platform-independent Core library configures and builds without finding or linking Qt. Clean Core configure and build succeeded with Apple Clang 21.0.0; this is compile validation only.
- A direct C++20 syntax-only compile of `events.hpp` succeeded. No tests or app launch were performed.
- Binary dependency inspection confirms the existing Homebrew QtGui links OpenGL and Metal; the strict project rule makes it non-compliant. The RF433 source files contain no OpenGL, Vulkan, Metal, RHI or Qt Quick API references.
- Qt 6.12 feature flags can disable OpenGL, Vulkan, Metal and graphics-frame capture in QtGui, but this alone does not remove the Cocoa plugin's Metal framework dependency. The completed configure/source inspection is recorded below; no compliant Qt runtime has been produced.

## Qt no-GPU configuration investigation — 2026-11-01

- Date/time: 2026-11-01 07:51 Europe/Moscow.
- Downloaded the official QtBase 6.12.0 source archive into the ignored `build/` directory and verified SHA-256 `a951bd163c7b80fc6b8c88d7668fb56abf91c152373e13c10666763238131307` against Qt Project metalink metadata.
- Configured a Release QtBase build with `-no-opengl -no-feature-graphicsframecapture -nomake examples -nomake tests -- -DFEATURE_metal=OFF`. The configure summary reports OpenGL=no, Vulkan=no, Metal=no, QGraphicsFrameCapture=no; examples and tests were disabled.
- Generated `QCocoaIntegrationPlugin` link flags still include `-framework Metal` and `-framework ScreenCaptureKit`. QtBase 6.12's Cocoa platform CMake file adds those frameworks unconditionally ([Cocoa plugin CMake source](https://github.com/qt/qtbase/blob/6.12/src/plugins/platforms/cocoa/CMakeLists.txt)). Disabling the QtGui graphics features alone therefore does not satisfy the strict no-Metal-link rule on macOS.
- Stopped the QtBase release build at 665/1,729 build steps before completion; no Qt install, RF433 app build, app launch or tests resulted from it. The configured tree and partial build are local generated files under ignored `build/` only.
- This identifies a macOS Qt/Cocoa packaging blocker. Linux V1 can continue independently; before the later macOS stage, either a narrowly patched Qt Cocoa plugin must be assessed or the user must approve a different UI/dependency rule. No architecture change has been made.

## Kali/Pi ARMHF Qt and application cross-build — 2026-11-01

- Date/time: 2026-11-01 08:58 Europe/Moscow.
- Prepared an isolated Colima 0.10.3 Linux VM on the Mac: Ubuntu 24.04.4 ARM64, 2 vCPU, 4 GiB RAM. Installed GCC/G++ 13.3 ARMHF cross-compilers, CMake 3.28.3, Ninja 1.11.1, QEMU/binfmt and ARMHF X11/XCB development dependencies. This setup required no user interaction.
- Built Qt 6.12.0 host tools from the same source version, then configured and built QtBase for ARMHF with `-xcb -no-opengl -no-feature-vulkan -no-feature-graphicsframecapture -nomake tests -nomake examples`. Configuration reports Qt Widgets=yes, XCB=yes, OpenGL/EGL/Vulkan=no, and XCB GLX/EGL integrations=no. The build completed all 1,518 Ninja steps. No Qt test suite was built or run.
- Cross-compiled the RF433 Core and Widgets application with `RF433_BUILD_APP=ON`. The resulting executable is ELF32 ARM, EABI5, hard-float, ARMv7. This is compile validation only; the executable was not launched.
- Inspected the app and all 53 staged Qt shared libraries/plugins, then followed every `DT_NEEDED` dependency: 59 ELF objects resolved across the app, Qt and target sysroot. No EGL, OpenGL, GLX, Vulkan, Metal or `libxcb-glx` dependency was found; there were no unresolved dependency names.
- Build outputs and the generated Qt toolchain are under ignored `build/` or the Colima VM's `/tmp`; no temporary toolchain file or binary is tracked. The first build attempt on the macOS `virtiofs` mount could not rename generated headers; moving the build directory into the VM's native filesystem resolved it without changing project sources.
- This ARMHF SDK uses Ubuntu 24.04 target packages and glibc 2.39; it is a cross-build baseline, not the user's Kali image. The Pi's exact Kali release, libraries, display session and architecture have not been read from the device. Do not claim actual Kali runtime, Pi launch, 512 MiB resource behavior, package install or radio operation from this result.
- No test suites were run. Qt build and application compilation are targeted build checks requested for the Pi software/UI work. No `.deb` or AppImage was produced.

## ARMHF foundation packages — 2026-11-01

- Date/time: 2026-11-01 09:07 Europe/Moscow.
- Built a local `.deb` (`Architecture: armhf`, package version `1.0.0~foundation1`) and an ARMHF AppImage from the foundation UI and the compliant Qt/XCB subset. The `.deb` contains the app, Qt Core/DBus/Gui/Widgets/XcbQpa, the XCB platform plugin, a launcher and icon. The AppImage was generated successfully with AppImage/appimagetool continuous build `9bab981` under QEMU; the downloaded ARMHF tool's SHA-256 was `e074da279b7ce3b1ded5aed6bd2a376f4c6b56da5a1e1d9e07bf9c880607c80f`.
- Package inspection confirms ARMHF, hard-float EABI5. The Qt/app dependency set requires up to `GLIBC_2.38` and `GLIBCXX_3.4.30`; `.deb` declares `libc6 >= 2.38` and X11/XCB/XKB runtime packages. The AppImage bundles Qt libraries but still depends on those system libraries.
- The actual Pi/Kali glibc and installed X11/XCB packages are unknown. Do not install these artifacts on the Pi until the target system meets the package dependencies; the device's Kali release has not been queried. No package install, app launch, Pi resource check, runtime test suite or RF hardware check was performed.
- Artifacts and temporary packaging scripts are under ignored `build/`; no release artifact or helper script was added to the repository. SHA-256 checksums are kept alongside the local artifacts.
- User requested a GitHub release but, when asked about the conflict between a foundation-only app and the full public 1.0.0 policy, explicitly chose a **draft** 1.0.0 release. Do not publish this draft without a later explicit instruction.

## Dependency pin audit — 2026-11-01

- Date/time: 2026-11-01 07:53 Europe/Moscow.
- Verified the current vcpkg `master` baseline at `9a5dfef5d1a0438a7d24856a85bd60f309d355e9`. Its manifest baseline selects OpenSSL `3.6.5#2`, SQLite `3.54.1`, and QtBase `6.11.2` ([vcpkg baseline](https://github.com/microsoft/vcpkg/blob/9a5dfef5d1a0438a7d24856a85bd60f309d355e9/versions/baseline.json)).
- OpenSSL's release policy lists 3.6.5 support only through 2026-11-01, while 3.5.9 is an LTS release supported through 2030-04-08 ([OpenSSL release strategy](https://www.openssl-library.org/policies/releasestrat/), [OpenSSL source releases](https://www.openssl-library.org/source/)). The vcpkg version history currently includes OpenSSL 3.5.4 but not 3.5.9.
- Do not pin vcpkg's current OpenSSL 3.6.5 baseline for RF433. Before implementing encryption, choose a reproducible supported OpenSSL 3.5.9 route (for example, a small vcpkg overlay port) or confirm the security-support status of each target distribution's patched OpenSSL package. The chosen Qt 6.12.0 is also separate from this baseline's QtBase 6.11.2.

## Stage 1 name policy — 2026-11-01

- Date/time: 2026-11-01 07:55 Europe/Moscow.
- Added Core validation for the approved rename rule: one to 32 ASCII Latin letters/digits, with case-insensitive uniqueness against other base names. System suffixes are excluded by the API contract; timestamp-generated names remain an exception handled by creation logic.
- `cmake --build build/core --parallel 2` succeeded with Apple Clang 21.0.0. No tests or UI launch were performed.

## Stage 1 key metadata model — 2026-11-01

- Date/time: 2026-11-01 07:56 Europe/Moscow.
- Added Core metadata types for UUID v4 object IDs, the approved modulation and compatibility states, broken/edited state, capture quality, nominal frequency and CC1101 register values. Added pure checks for UUID v4 bits and the approved 387–464 MHz range.
- `cmake --build build/core --parallel 2` succeeded with Apple Clang 21.0.0. This remains a domain model only: it does not generate IDs, validate hardware register profiles, store payloads, or perform RF operations. No tests or app launch were performed.
- Changed `RF433_BUILD_APP` to default `OFF`; a fresh configure with no application option succeeded and built only the framework-independent Core. No tests or app launch were performed.
- Follow-up check: explicitly reconfigured the existing `build/app` cache with `RF433_BUILD_APP=OFF` and rebuilt `rf433_core` successfully. Removed the previously generated, non-compliant `build/app/rf433_app` binary and verified it is absent. No test suite or app launch was performed.

## Approved scope
Linux V1 includes Kali Rolling ARMHF on Raspberry Pi Zero 2 W as the primary initial bring-up/test target, followed by Ubuntu 24.04 LTS x86_64 and ARM64 as additional targets. Deliver `.deb` and AppImage for all three target profiles. After Linux V1, continue with macOS ARM64, Android ARM64-v8a and ESP32 according to IMPLEMENTATION_PLAN.md. The user withdrew the earlier blanket token-austerity policy, then gave a narrower current instruction: with about 70% of the Go plan limit remaining, avoid tests that consume quota rapidly and notify before long tasks. Windows and RP2040/Pico excluded. First public version 1.0.0. Release publication requires explicit user approval.

## Approved repository operation
The user explicitly approved deleting the old `aynisej/rf433` repository without a backup and recreating a clean repository at the same name and canonical URL. The old Python/CH341 TTL prototype must not be reused. Commit and push all project work directly to the replacement repository in coherent milestones. GitHub Release publication remains unapproved.

## Blockers before subsequent stages
1. **Compliant Qt build:** A custom ARMHF Qt 6.12.0 build with XCB enabled and OpenGL/Vulkan disabled now compiles with the RF433 app. The 59-object dependency closure over the app and all staged Qt libraries/plugins has no prohibited GPU library. This is based on an Ubuntu 24.04 ARMHF sysroot; verify against the user's Kali image and actual Pi. Ubuntu 24.04 x86_64/ARM64 binaries still need equivalent inspection. On macOS, disabling Qt graphics features does not remove the Cocoa plugin's direct Metal framework link; defer app packaging and decide on a compliant Cocoa implementation before the macOS stage.
2. **Toolchain pins:** Ubuntu 24.04 is selected for x86_64/ARM64, but exact Linux compiler, CMake, Qt acquisition and dependency versions are not recorded. The current vcpkg OpenSSL pin is past upstream support; select a supported crypto build before storage implementation.
3. **Primary Pi target:** Local ARMHF `.deb` and AppImage artifacts exist, but Qt upstream does not list ARMHF and the build used Ubuntu 24.04 packages. Their glibc floor is 2.38. Read the Pi's actual Kali release/libraries before installation; UI launch and resource use on the actual Pi remain unverified before broadening initial testing to Ubuntu.
4. **Hardware profiles:** no USB-SPI adapter is currently available. Exact adapter model/revision pin maps and verified GDO timing capability must be established from reliable documentation and hardware. Never guess.

## Next checkpoint
1. Create the selected private-to-publication GitHub draft with both ARMHF artifacts and prominent foundation-only/runtime-baseline notes; leave it unpublished.
2. When the Pi is available, capture its model, Kali release, architecture, display session and installed runtime library versions; install and launch only if they meet the package ABI requirements, then measure resource use on the 512 MB device.
3. Pin reproducible compiler, CMake, Qt and cryptographic dependency versions, prioritizing the Kali ARMHF toolchain and then Ubuntu 24.04 x86_64/ARM64.
4. Continue target-independent Core work while the Pi software toolchain is prepared. Begin Pi radio integration only after an exact USB-SPI adapter model/revision is available and its pin map and GDO timing can be verified.

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
The earlier remaining-10% estimate and blanket token-saving policy were withdrawn. The current instruction is to avoid test runs that consume quota rapidly while about 70% remains and to notify the user before long tasks. This does not reduce approved scope or platform progression. Use targeted checks for current prep work; accurately report any validation deferred by this instruction, along with actual technical limits and unavailable physical hardware.
