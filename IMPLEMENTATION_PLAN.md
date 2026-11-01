# Implementation Plan

## Stage 0 — Replace repository and audit environment
1. Delete the old GitHub repository `aynisej/rf433` without creating a backup. The user explicitly approved this; the old TTL/CH341 prototype is disposable.
2. Create a completely empty replacement repository at the exact same URL: `https://github.com/aynisej/rf433`. Preserve the old repository's visibility if it can be read before deletion; if visibility cannot be determined, stop and ask rather than guessing.
3. Clone the replacement repository to the Mac working environment.
4. Add the approved project documents (`AGENTS.md`, `SPECIFICATION.md`, `IMPLEMENTATION_PLAN.md`, `BUILD_RULES.md`, `DECISIONS.md`, `PROGRESS.md`, `RESOURCE_POLICY_UPDATE.md`) and make/push the initial documentation commit.
5. Audit macOS Apple Silicon tools, pin toolchain/dependency versions, and resolve remaining specification conflicts before implementation.
6. Continue by committing and pushing each coherent, tested milestone directly to this repository.

Do not copy or adapt any old source, tests, CI workflows, package scripts, build configuration or repository history. The replacement starts clean.

## Stage 1 — Linux x86_64 foundation
Create minimal CMake/C++20 structure, Core/UI separation, domain model, state machine, event model, storage/hardware interfaces, Qt 6 CPU-rendered UI skeleton and first-launch agreement. Resolve per-object storage representation before persistent storage implementation. Add concise README. Build x86_64 `.deb` and AppImage.

Mandatory checks: clean configure/build, essential Core tests, package inspection, launch/smoke test, agreement gate, storage/encryption/deletion checks, log policy, no-network/no-telemetry.

## Stage 2 — Linux x86_64 radio path
Implement USB-SPI abstraction and exact hardware profiles. Validate FT232H/MCP2210 support, especially precise GDO timing. Do not advertise full support if timing capture is inadequate. Implement CC1101 diagnostics and manual-only reinitialization; Scan/capture/dedup/Result Menu/Apply/Correction and fault states. Hardware-independent tests first. Record what was physically verified.

## Stage 3 — Linux ARM64 / Pi Zero 2 W
Build native ARM64 `.deb` and AppImage. Validate ABI, CPU baseline, Qt software rendering, runtime dependencies and memory use for 512 MB Pi Zero 2 W. Do not assume generic ARM64 compatibility. User physical Pi testing is post-delivery, not release gate.

## Stage 4 — Linux V1 release candidate
Mandatory tests for x86_64 and ARM64. Verify agreement, crypto erasure semantics, hardware fault handling, scan cancellation, sequential operation and logging. Prepare notes and all artifacts in one release. First public release 1.0.0. Stop before publication and request explicit approval.

## Stage 5 — macOS ARM64
Port and validate the approved Core and Qt 6 UI on macOS ARM64. Produce the agreed distributable artifact(s), verify software rendering, storage behavior, permissions, USB-SPI support and launch/update behavior. Run comprehensive platform-specific tests.

## Stage 6 — Android ARM64-v8a
Implement the approved Android USB OTG path, platform storage and UI adaptation. Validate permissions, device enumeration, OTG disconnect behavior, lifecycle/crash handling, software rendering and package installation. Run comprehensive tests on available emulators and physical devices where available.

## Stage 7 — ESP32 DevKit V1
Implement the approved ESP-IDF + LVGL target, LittleFS storage, display/touch profiles, five-button interaction and bounded-memory radio path. Validate each supported controller/profile that can be tested. Do not claim untested display or touch combinations are verified.

## Stage 8 — Cross-platform hardening and release
Run broad regression, stress, resource, corruption, crypto-erasure, fault-injection and packaging tests across all implemented targets. Resolve critical failures before release. Prepare platform artifacts and documentation. Release publication still requires explicit user approval.

No Windows, no RP2040/Pico.

## Checkpoint policy
Commit and push coherent project milestones directly to `aynisej/rf433`; do not defer all commits until completion. Proceed autonomously through approved stages. Pause only for critical unresolved decisions, architecture changes, destructive actions, user/hardware intervention or release approval. Do not pause merely to conserve tokens or because of the previously discussed Go quota estimate. Save exact state in PROGRESS.md on blockers.
