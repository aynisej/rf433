# Decision Register

Settled decisions; do not reopen without new evidence or user request.

1. New implementation replaces old; no backward compatibility.
2. C++20/CMake; Qt 6; ESP32 uses ESP-IDF + LVGL; Core independent of UI.
3. CPU-only UI; no OpenGL/Vulkan/Metal.
4. Linux V1 first: Ubuntu 24.04 LTS baseline for x86_64 and ARM64, including Pi Zero 2 W compatibility; user additionally approved Kali Rolling ARMHF on Pi Zero 2 W.
5. Linux artifacts: `.deb` + AppImage for x86_64 and ARM64, plus `.deb` + AppImage for the Kali ARMHF target. ARMHF is Kali-specific; validate its Qt and AppImage packaging route separately.
6. After Linux V1, continue the approved roadmap: macOS ARM64, Android ARM64-v8a and ESP32, subject only to genuine technical/product blockers or unavailable hardware, not token/quota austerity.
7. Windows unsupported; RP2040/Pico excluded from V1.
8. First public release 1.0.0; no public 0.x.
9. All version artifacts in one GitHub Release; publication needs explicit user approval.
10. Commit permission does not imply release publication permission.
11. Manual updates only; no in-app updater or automatic GitHub calls.
12. No telemetry or app-initiated network calls.
13. English-only UI for first release.
14. One EBYTE E07-M1101D-SMA V2.0 CC1101 module handles RX/TX sequentially.
15. Module is SPI, 387–464 MHz; exact hardware pin maps must be profiled, never guessed.
16. FT232H/MCP2210 are candidate USB-SPI adapters; precise GDO timing must be validated.
17. Interface selected each launch except Android; session-only; no auto-selection.
18. Manual Check is the only user-initiated radio diagnostic/reinitialization path.
19. No auto-recovery/reconnect/retry/reinit/failover during active radio operation.
20. Hardware error aborts, discards temporary data, returns main menu and disables radio functions until manual Check.
21. CC1101 sleeps idle; wake and verify before Scan/Apply/Correction.
22. RX/TX timing uses hardware capture/timers/interrupts/DMA where available.
23. Scan modes: fixed 433.3 MHz and full 387–464 MHz.
24. Preserve original pulse timing; normalize only leading/trailing silence.
25. Dedup exact normalized radio data only; metadata excluded.
26. One Scan = one key; temporary Result Menu.
27. Apply sends one complete transmission per click, no auto-repeat.
28. Compatibility requires functional response; successful TX alone is not proof.
29. Dynamic/rolling-code systems are not promised replayable.
30. Main menu exactly Check, Scan, Saved Keys.
31. No Settings/About/tutorials/heavy effects.
32. Official app has mandatory first-launch lawful-use agreement; forks may remove it.
33. System log is minimal, anonymized, max 10 launch logs, exact event policy in SPECIFICATION.md.
34. SQLite desktop/mobile; LittleFS ESP32; app-internal storage only.
35. AES-256-GCM, SHA-256, UUID v4; no password, Keychain or Keystore.
36. Separate CEK file; independent per-object Object Key; delete object key and encrypted record independently.
37. CEK may be recoverable by skilled reverse engineering; no excessive anti-analysis.
38. Physical overwrite best effort only; crypto-erasure primary; never overclaim.
39. No export/import/backup/restore/history.
40. Corruption is terminal for affected encryption layer; no recovery/regeneration/auto-repair.
41. Approved by user 2026-11-01: desktop/mobile SQLite stores metadata and encrypted payload only; each CEK-wrapped per-object Object Key is in a separate app-internal file. Deleting an object deletes its SQLite record and its key file. No plaintext RF data or raw Object Key in SQLite/journals. Physical overwrite remains best-effort; crypto-erasure is primary.
42. Temp internal only; clean stale temp before UI at startup.
43. No artificial max signal size/scan duration; scan ends on result or manual cancel.
44. Core streams and uses bounded buffers; account for Pi Zero 2 W 512 MB.
45. Three execution areas: Core Worker, Hardware Worker, UI thread.
46. RTC extension point only; no V1 driver/logic.
47. License has exactly two conditions: no commercial use; forks/derivatives link and attribute https://github.com/aynisej/rf433.
48. No additional license restrictions or fork behavior requirements.
49. Approved by the user (2026-11-01): the Raspberry Pi Zero 2 W running Kali ARMHF is the primary initial real-device bring-up and test target. Do not defer its initial software/UI and resource checks until after Ubuntu testing. RF-specific checks wait until a compatible USB-SPI adapter is available and verified.
50. Release validation remains comprehensive. Latest user instruction (2026-11-01): about 70% of the Go plan limit remains; avoid tests that consume quota quickly, favor concise targeted checks, and record deferred high-cost suites without claiming they passed.
51. Agent progresses autonomously between approved checkpoints; pauses only for critical intervention.
52. The former Python/CH341 prototype was validated only in a TTL/programmer-oriented setup and did not establish the intended CC1101-over-SPI operating path. Its build/package success is not evidence of SPI or RF functionality.
53. The old `aynisej/rf433` repository is disposable and explicitly approved for deletion without backup. No code, tests, build configuration or history are to be reused.
54. Create a clean replacement repository at the exact same canonical URL, `https://github.com/aynisej/rf433`.
55. Commit and push project documents and implementation milestones directly to the replacement repository. Git commits/pushes are authorized; GitHub Release publication remains separately approval-gated.
