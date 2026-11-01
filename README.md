# RF433

RF433 is a local RF433 utility for authorized devices. Its approved V1 path is Linux first, with the project scope and constraints recorded in the planning documents in this repository.

## Current implementation status

The repository contains the approved project baseline, a platform-independent Core action-policy library, radio-session state model, UI-facing progress/outcome event types, key metadata types, and key rename-name policy, plus an initial Qt Widgets desktop shell. The shell implements the first-launch agreement and session-only adapter-family selection. No radio driver, saved-key storage backend, or RF operation is implemented yet. In particular, the Core code does not communicate with RF hardware.

A local Kali/Pi ARMHF foundation build now exists as `.deb` and AppImage artifacts under the ignored `build/packages/` directory. Qt 6.12.0 was cross-built with XCB enabled and OpenGL/Vulkan disabled; the ARMHF app and Qt dependency set passed ELF dependency inspection. These are unlaunched preview artifacts: they require glibc 2.38 or later, and the actual Raspberry Pi Kali libraries, installation, UI behavior and 512 MiB resource use have not been checked. The artifacts contain only the initial UI shell, not RF functionality.

The Homebrew Qt build used for the initial compile links QtGui to OpenGL and Metal frameworks, which violates the approved strict dependency rule. A reduced Qt 6.12 source configuration still generates a macOS Cocoa platform plugin linked to Metal; that source build was stopped before producing Qt libraries. Neither route provides a compliant macOS app toolchain. See `PROGRESS.md` for the platform-specific blocker.

## Build the platform-independent Core library

Requires CMake 3.28 or later and a C++20 compiler:

```sh
cmake -S . -B build/core -DCMAKE_BUILD_TYPE=Debug
cmake --build build/core --parallel 2
```

The Qt Widgets shell requires Qt 6.12.0 and an approved platform Qt build. The Homebrew QtGui build currently installed on the development Mac does not satisfy the strict graphics dependency rule. `RF433_BUILD_APP` defaults to `OFF`; enable it only with a platform-specific Qt build whose full dependency tree has been audited for the no-OpenGL/Vulkan/Metal rule. The ARMHF preview route is recorded in `PROGRESS.md`; Ubuntu x86_64/ARM64 and macOS still need separate validation.
