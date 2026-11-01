# RF433

RF433 is a local RF433 utility for authorized devices. Its approved V1 path is Linux first, with the project scope and constraints recorded in the planning documents in this repository.

## Current implementation status

The repository contains the approved project baseline, a platform-independent Core action-policy library and radio-session state model, and an initial Qt Widgets desktop shell. The shell implements the first-launch agreement and session-only adapter-family selection. No radio driver, saved-key storage backend, or RF operation is implemented yet. In particular, the Core code does not communicate with RF hardware.

The Homebrew Qt build used for the initial compile links QtGui to OpenGL and Metal frameworks, which violates the approved strict dependency rule. A reduced Qt 6.12 source configuration still generates a macOS Cocoa platform plugin linked to Metal; that source build was stopped before producing Qt libraries. Neither route provides a compliant macOS app toolchain. See `PROGRESS.md` for the platform-specific blocker.

## Build the platform-independent Core library

Requires CMake 3.28 or later and a C++20 compiler:

```sh
cmake -S . -B build/core -DRF433_BUILD_APP=OFF -DCMAKE_BUILD_TYPE=Debug
cmake --build build/core --parallel 2
```

The Qt Widgets shell requires Qt 6.12.0. The Homebrew QtGui build currently installed on the development Mac does not satisfy the approved strict graphics dependency rule. The C++ Core library can be built independently with `RF433_BUILD_APP=OFF`. Toolchain pins and compliant platform-specific Qt routes are tracked in `PROGRESS.md`.
