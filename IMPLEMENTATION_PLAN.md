# Implementation Plan

## Stage 0 — Replace repository and audit environment
1. Delete the old GitHub repository `aynisej/rf433` without creating a backup. The user explicitly approved this; the old TTL/CH341 prototype is disposable.
2. Create a completely empty replacement repository at the exact same URL: `https://github.com/aynisej/rf433`. Preserve the old repository's visibility if it can be read before deletion; if visibility cannot be determined, stop and ask rather than guessing.
3. Clone the replacement repository to the Mac working environment.
4. Add the approved project documents (`AGENTS.md`, `SPECIFICATION.md`, `IMPLEMENTATION_PLAN.md`, `BUILD_RULES.md`, `DECISIONS.md`, `PROGRESS.md`, `RESOURCE_POLICY_UPDATE.md`) and make/push the initial documentation commit.
5. Audit macOS Apple Silicon tools, record Kali ARMHF on Raspberry Pi Zero 2 W as the primary initial bring-up/test target and Ubuntu 24.04 x86_64/ARM64 as additional Linux targets, pin toolchain/dependency versions, and resolve remaining specification conflicts before implementation.
6. Continue by committing and pushing each coherent, tested milestone directly to this repository.

Do not copy or adapt any old source, tests, CI workflows, package scripts, build configuration or repository history. The replacement starts clean.

## Stage 1 — Kali ARMHF / Pi Zero 2 W initial bring-up
Prioritize an installable Kali ARMHF build for the user's Raspberry Pi Zero 2 W. Establish the Qt Widgets CPU-rendered configuration and package route, then deploy and perform initial software/UI and 512 MB resource checks on the actual Pi before broadening Linux testing to Ubuntu. Keep the CMake/C++20 Core independent of UI, with the approved state, event, key metadata and storage interfaces. No RF hardware test can proceed until a USB-SPI adapter is available and its exact model/revision and timing capabilities are verified. Do not claim on-device checks before they occur.

Mandatory checks: clean configure/build, essential Core tests, package inspection, launch/smoke test, agreement gate, storage/encryption/deletion checks, log policy, no-network/no-telemetry.

## Stage 2 — Pi Zero 2 W / Kali ARMHF radio path
After the initial on-device software checks and once an adapter is available, implement USB-SPI abstraction and exact hardware profiles. Validate the selected adapter's support, especially precise GDO timing. Do not advertise full support if timing capture is inadequate. Implement CC1101 diagnostics and manual-only reinitialization; Scan/capture/dedup/Result Menu/Apply/Correction and fault states. Hardware-independent checks first; record separately what was physically verified on the Pi.

## Stage 3 — Ubuntu 24.04 x86_64 and ARM64
Build Ubuntu 24.04 `.deb` and AppImage artifacts for x86_64 and ARM64. Validate ABI, CPU baseline, Qt software rendering, runtime dependencies and resource use. Keep Pi Zero 2 W compatibility as a separate device profile; do not infer ARM64 compatibility from a generic build.

## Stage 4 — Linux V1 release candidate
Validate the initial Pi Zero 2 W/Kali ARMHF target and the additional Ubuntu 24.04 x86_64/ARM64 targets. Verify agreement, crypto-erasure semantics, hardware fault handling, scan cancellation, sequential operation and logging on each applicable platform. Prepare notes and all artifacts in one release. First public release 1.0.0. Stop before publication and request explicit approval.

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
