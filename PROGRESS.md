# Progress

## Current status
Planning package prepared and updated for clean repository replacement. No GitHub repository has yet been deleted or created; no implementation, build, test, commit or release has been performed. These documents do not prove any feature exists.

## Approved scope
Linux V1 first: x86_64 + ARM64 including Raspberry Pi Zero 2 W. Deliver `.deb` and AppImage for both. After Linux V1, continue with macOS ARM64, Android ARM64-v8a and ESP32 according to IMPLEMENTATION_PLAN.md. The former token/quota austerity policy has been withdrawn by the user. Windows and RP2040/Pico excluded. First public version 1.0.0. Release publication requires explicit user approval.

## Approved repository operation
The user explicitly approved deleting the old `aynisej/rf433` repository without a backup and recreating a clean repository at the same name and canonical URL. The old Python/CH341 TTL prototype must not be reused. Commit and push all project work directly to the replacement repository in coherent milestones. GitHub Release publication remains unapproved.

## Blockers before implementation
1. **Object storage representation:** exact physical representation of encrypted payloads and independently destroyable Object Keys is not approved. Select the simplest design satisfying erasure and plaintext-remnant requirements; ask user before locking in.
2. **Hardware profiles:** exact adapter model/revision pin maps and verified GDO timing capability must be established from reliable documentation/hardware. Never guess.
3. **Toolchain pins:** determine and record exact versions during environment audit.

## Next checkpoint
Next actions:
1. Delete old GitHub repository `aynisej/rf433` without backup.
2. Create a clean replacement repository at the same URL and clone it locally.
3. Add these approved documents and push the initial documentation commit.
4. Audit macOS build environment.
3. Resolve object-storage representation.
4. Pin toolchain/dependencies.
5. Start Stage 1 in IMPLEMENTATION_PLAN.md and proceed through the full approved roadmap, using comprehensive testing and refinement.

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
