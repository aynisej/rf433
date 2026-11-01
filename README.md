# RF433

RF433 is a local RF433 utility for authorized devices. Its approved V1 path is Linux first, with the project scope and constraints recorded in the planning documents in this repository.

## Current implementation status

The repository contains the approved project baseline, a platform-independent Core action-policy library, and an initial Qt Widgets desktop shell. The shell implements the first-launch agreement and session-only adapter-family selection. No radio driver, saved-key storage backend, or RF operation is implemented yet. In particular, the Core policy code does not communicate with RF hardware.

## Build the Core library

Requires CMake 3.28 or later, a C++20 compiler, and Qt 6.12.0 Widgets:

```sh
cmake -S . -B build/app -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH="$(brew --prefix qtbase)"
cmake --build build/app --parallel 2
```

The exact release toolchain and dependency versions are tracked as open preparation items in `PROGRESS.md`.
