# Agent Instructions

Read SPECIFICATION.md, DECISIONS.md, BUILD_RULES.md, IMPLEMENTATION_PLAN.md and PROGRESS.md before coding. These are the approved project contract.

## Non-negotiable rules
- Do not change approved scope, architecture, security, UI, license or release policy without explicit user approval.
- No speculative features, unnecessary abstraction, compatibility layers, telemetry, automatic updates, export/import/backup/restore, or app-initiated network calls.
- Windows and RP2040/Pico are excluded from V1.
- Core stays independent of Qt/LVGL. UI is CPU-only: no OpenGL/Vulkan/Metal dependency.
- Never guess hardware pin maps, adapter capabilities, or electrical measurements.
- No automatic radio reconnect, repair, retry, reinitialization or adapter failover during an operation. Only user-initiated manual Check may diagnose/reinitialize.
- The user has explicitly authorized deleting the old GitHub repository `aynisej/rf433` without a backup and creating a completely new repository at the exact same canonical name and URL. This is an approved destructive action; do not ask for confirmation again for this specific replacement.
- The old repository is disposable prototype code. Do not archive, clone, migrate, cherry-pick, copy, adapt or otherwise reuse its source, tests, build files, issues or history. Do not preserve backward compatibility.
- Create/use a clean local working clone of the replacement repository and push implementation work directly to `aynisej/rf433` through normal Git commits. Do not work only in an uncommitted local sandbox and do not wait until the end to upload a batch of changes.
- Commit coherent, reviewable milestones directly to the replacement repository. Push each approved implementation milestone after its tests pass; keep the repository buildable where practical. Include concise commit messages. Do not force-push, rewrite published history, or delete the replacement repository.
- Repository replacement sequence: delete old `aynisej/rf433`; create a new empty private/public repository at the same name according to the existing repository visibility if discoverable, otherwise stop and ask; clone the new repository; add the approved project documents; make and push the initial documentation commit; then begin implementation. Do not initialize with generated README/license/gitignore if doing so would create unnecessary merge history.
- If GitHub access or permissions prevent deletion, creation, cloning or pushing, stop at that exact step, report the error and provide the single required user action. Do not silently switch to another repository name or URL.

## Agent workflow
- Progress autonomously through approved checkpoints. Do not ask for approval at every checkpoint.
- Ask only for critical unresolved decisions, architecture changes, destructive operations, required user/hardware intervention, insufficient budget, or release publication.
- Stop on a blocker, save exact state in PROGRESS.md, commit and push that progress update when the repository is available, and report the specific intervention required. Do not treat the former 10% Go quota concern as a project constraint; the user has withdrawn that austerity policy.
- The former 10% Go quota concern was withdrawn, but the user's latest instruction (2026-11-01) says about 70% of the Go plan limit remains and asks us to avoid tests that consume quota quickly. Use short, targeted checks; defer token-intensive repeated suites and record what remains. Do not reduce the approved product scope.
- Tell the user before a long-running operation or any extended period that needs no intervention, so they can leave. Do not require the Pi to be powered during documentation or host-side work.
- Initial bring-up and testing must prioritize the user's Raspberry Pi Zero 2 W running Kali ARMHF. Ubuntu 24.04 x86_64/ARM64 remain required Linux V1 targets and follow as additional platforms. Then continue with macOS ARM64, Android ARM64-v8a and ESP32 where technically feasible. Do not silently drop a platform because of an earlier token-saving policy.
- Do not block software, UI, packaging, or resource checks on USB-SPI availability. The adapter is needed only for RF-specific implementation and physical radio validation.
- The project still requires comprehensive validation before release. In the current Go plan budget, avoid test runs that trigger rapid token use; prioritize concise deterministic checks, defer expensive suites and record the remaining validation. Do not claim deferred checks passed.
- Use tokens efficiently: avoid redundant rereading and pointless iterations, but prioritize correctness, maintainability and verified behavior over minimizing token consumption.
- If an actual product/tool limit, technical blocker or missing hardware prevents completion, record the limitation and continue with all work that can be responsibly completed.

## Git and release
- Direct Git commits and pushes to the replacement `aynisej/rf433` are explicitly authorized for this project, including the initial documentation commit and subsequent coherent implementation milestones.
- A GitHub token with commit permission does not authorize publishing a Release.
- Never publish a GitHub Release without explicit user approval.
- First public version is 1.0.0; no public 0.x releases. Use SemVer.
- All artifacts for a version belong in one GitHub Release.
- Distinguish automated validation from physical hardware testing.

## Completion report
State changes, commands, actual test outcomes, produced artifacts, limitations, next checkpoint, commit status and release status. Never claim work or validation that did not happen.
