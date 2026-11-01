# Build Rules

- Host: macOS Apple Silicon.
- C++20, CMake, Qt 6; ESP32 only at optional stage with ESP-IDF + LVGL.
- vcpkg for general C++ dependencies; GitHub Actions CI.
- Install missing tools only after implementation authorization.
- Pin compiler, CMake, Qt, vcpkg baseline, ESP-IDF and dependencies. No automatic upgrades.
- Linux V1 artifacts: x86_64 `.deb` + AppImage; ARM64 `.deb` + AppImage.
- Validate ARM64 CPU baseline, ABI, Qt software rendering and runtime compatibility for Pi Zero 2 W; generic ARM64 is not sufficient proof.
- CPU-only rendering. No OpenGL/Vulkan/Metal.
- Keep scripts deterministic and runtime dependencies explicit.
- CI builds and runs mandatory tests for selected stage architectures.

Mandatory validation: clean configure/build; essential Core tests; launch/smoke; package/runtime inspection; agreement gate; storage/encryption and independent Object Key deletion; no plaintext RF data in logs/temp/SQLite journal; hardware fault transitions; no automatic reconnect/retry/reinitialization during operations; exact log policy; no telemetry/network/update behavior.

Run comprehensive relevant tests, including extended, stress, resource, fault-injection, corruption and security tests where practical. Do not skip useful validation merely to conserve tokens. If a test cannot be run because hardware, tooling or an actual product limit is unavailable, record the reason and use the strongest valid substitute without claiming equivalent physical validation.

SemVer; first public version 1.0.0; no public 0.x. All artifacts for a version in one GitHub Release. Never publish without explicit user approval. Release notes must distinguish CI validation from physical hardware tests.


## Repository workflow
- The old `aynisej/rf433` repository is explicitly approved for deletion without backup. It is a disposable prototype and is not a source of reusable implementation.
- Recreate a clean repository at exactly `https://github.com/aynisej/rf433`.
- Commit and push directly to that repository in coherent milestones. Do not accumulate the entire project only locally for a final upload.
- Never force-push or rewrite published history. Never publish a GitHub Release without separate explicit approval.
