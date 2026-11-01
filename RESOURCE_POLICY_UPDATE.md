# Resource Policy Update

The previous strict token/quota austerity policy was withdrawn, but the latest user instruction on 2026-11-01 sets a temporary validation constraint: about 70% of the Go plan limit remains, and tests that consume quota quickly must not be launched.

- Do not reduce approved implementation scope. Prefer concise, targeted checks; defer repeated, stress, broad resource or other high-token test runs until the plan budget is renewed or the user changes this instruction. Record deferred validation accurately.
- Linux V1 remains first, followed by macOS ARM64, Android ARM64-v8a and ESP32 as specified in the implementation roadmap.
- Comprehensive release validation remains a project requirement, but it must respect the current token-use instruction.
- The previous remaining-10% estimate is no longer current; use the latest approximately-70%-remaining estimate from the user.
- Use resources efficiently, avoiding redundant work, but prioritize correctness, reliability and completion.
- If an actual product limit, technical blocker or unavailable physical hardware prevents a task, document it precisely. Never claim tests or hardware validation that were not performed.
- All other approved architecture, safety, licensing, privacy, release and user-approval constraints remain unchanged.

- The user has authorized direct Git commits and pushes to the clean replacement repository `aynisej/rf433` as implementation proceeds. This does not authorize publishing GitHub Releases.
