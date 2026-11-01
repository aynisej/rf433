# RF433 — Approved Specification

This is the approved planning baseline, not evidence that implementation exists.

## Product and scope
Local general-purpose RF433 utility for authorized devices. V1 uses one EBYTE E07-M1101D-SMA V2.0 CC1101 module for both RX and TX, sequentially (half-duplex). Frequency range 387–464 MHz; SPI, not UART. Do not promise universal cloning: dynamic/rolling-code/authenticated systems may not be replayable.

No telemetry, cloud service, automatic GitHub calls, update checks, export/import, backup, restore or out-of-app key access. Updates are manual from GitHub Releases.

## Platform priority
Linux V1 first:
- x86_64: `.deb` + AppImage
- ARM64: `.deb` + AppImage, including compatibility validation for Raspberry Pi Zero 2 W (512 MB RAM)

macOS ARM64, Android ARM64-v8a and ESP32 are optional later targets only if resources remain after Linux V1. Windows unsupported. No RP2040/Pico in V1. User's physical Pi testing is post-delivery and not a release prerequisite.

## Technology
C++20, CMake, Qt 6 for desktop/mobile, LVGL + ESP-IDF for ESP32. Core independent of UI frameworks. vcpkg for general C++ dependencies. GitHub Actions CI/CD. CPU-only rendering; no OpenGL/Vulkan/Metal. Validate Qt software rendering. Pin toolchain and dependency versions; no automatic dependency upgrades. Minimal repo structure and README.

## Radio hardware
Exact module: EBYTE E07-M1101D-SMA V2.0 (CC1101), 387–464 MHz, SPI.
Pins:
1 GND; 2 VCC 1.8–3.6V; 3 GDO0; 4 CSN; 5 SCK; 6 MOSI; 7 MISO/GDO1; 8 GDO2.

Candidate USB-SPI adapters: FT232H and MCP2210. Common adapter abstraction. FT232H candidate libusb/libftdi; MCP2210 HIDAPI; validate exact support during implementation. Never assume identical vendor pinouts. Profiles map CC1101 functions to adapter functions and exact physical pins for exact model/revision. GPIO 30-pin profiles use board GPIO labels; 40-pin profiles use physical pin number plus GPIO function. Unknown adapters are skipped. Never guess.

Supply module only from adapter if stable 3.3V and adequate current are confirmed; otherwise regulated external supply and common ground. Never claim voltage measurement without a sensor. SPI support alone does not prove precise GDO edge capture capability. RX/TX timing must use hardware capture/timers/interrupts/DMA where available, not software GPIO polling. No separate RX/TX modules.

## Startup and radio readiness
At every launch except Android, show hardware-interface selection. Session-only; ask again next launch; no auto-selection. Android uses USB OTG and no interface selector. No automatic diagnostic at startup.

Main menu exactly:
1. `Check Radio Module Functionality`
2. `Scan`
3. `Saved Keys`

Saved Keys always available. Scan disabled until radio is fully ready. If interface absent/faulty, only Check is active. Manual Check enumerates devices in OS discovery order within selected interface type; try until first fully working adapter, then stop. No automatic interface-type switching.

Manual Check is user-initiated, non-interruptible, with modal stage progress and elapsed time. Final result: `Radio Module Ready` or `Radio Module Check Failed`. Diagnostic chain: USB refresh with timeout; adapter/SPI/CSN/timing/line checks; electrical checks only if supported; CC1101 SRES; read IDs/registers; safe write/readback; config/calibration checks where feasible; RX internal checks; TX FIFO/GDO/completion checks; restore base profile and SLEEP. Missing external test signal alone is not failure. Each stage has its own timeout; USB enumeration has a separate timeout; no global timeout.

Idle CC1101 sleeps, adapter stays connected. Wake and verify before Scan/Apply/Correction. No continuous SPI polling during sleep. During operation check connection at each adapter exchange; use OS attach/detach events, polling every 2 seconds only where unavailable.

Any actual radio-chain error during operation immediately aborts, discards temporary data, returns main menu and disables radio controls until manual Check. No automatic reconnect, retry, reinit, repair, driver fix or failover. User-parameter errors or absent external signal are not automatically hardware faults.

## Scan and capture
Modes: `Fixed 433.3 MHz` and `Full Range Scan` 387–464 MHz. One scan = one key. First valid pulse starts capture. Preserve complete pulse/space timing without rounding/smoothing; hardware timestamps edges. End detection uses conservative silence margin, excluded from data. Normalize only leading/trailing silence; internal intervals unchanged.

If a boundary candidate is functionally validated, select it. Otherwise default normalized signal treats gap as end and ignores later waveform. Raw Capture immutable. Retain candidates until validation. Validation requires actual device response or authorized practical test; algorithmic replay alone is not proof. Equally plausible validated variants may remain separate.

Failed capture resumes scan. Five consecutive failed captures at a frequency blacklist it until scan ends; reset blacklist next scan. Auto modulation detection: OOK, ASK, 2-FSK, GFSK, 4-FSK, MSK. Do not claim universal protocol recognition. Store frequency, modulation, all parameters and complete timing.

Quality metrics: integrity, repetition count, verification status. Quality never blocks saving or auto-triggers Correction. Poor/partial captures may be saved for Correction.

Deduplication is exact equality of normalized radio data only; no timing tolerance/rounding; metadata excluded. Exact duplicate is not saved and existing record remains unchanged: `Already exists (%filename%)`. Partial matches remain separate.

Scan phases, numbered with elapsed time: Initialization; Waiting for signal; Signal detection; Sequence reading; Boundary detection; Deduplication; Integrity check; Result generation. Scan continues until first valid result or user interrupt; no scan timeout. Interrupt discards temporary data and returns main menu. If hardware is lost, abort/discard and disable radio controls.

## Keys and compatibility
Compatibility states:
- `Compatible`: functional replay confirmed.
- `Unverified`: capture exists, replay unconfirmed.
- `Incompatible`: strong technical evidence of another mechanism/dynamic code; one failed attempt is insufficient.

Apply transmits exactly one full signal per click; no auto-repeat, no interruption during TX, no repeated Apply while transmitting. Successful TX alone is not compatibility proof. After TX show `Transmission completed`, then `Did the device respond?` Yes/No. Yes => Compatible; No => Unverified; dismissal/crash => Unverified. Apply permits retest. Incompatible never deletes or changes key.

Saved Keys: compact Finder-like one-line rows, name + system suffix only; no dates, metrics, search or pagination. Scroll. A-Z then numeric 1-9; natural sort remains unresolved. Long press opens adjacent context menu, blurred background, selected item focused; tap outside closes.

Actions: Apply, Correction, Delete, Rename. Apply/Correction disabled without module. Correction remains available for Broken if module ready; Apply disabled for Broken. View/Delete/Rename available.

Rename prefilled. Valid base name: 1–32 ASCII Latin letters/digits, no spaces/punctuation/Cyrillic; any allowed character may be first. Case-insensitive uniqueness checks base names only; system suffixes ignored. Save disabled until valid and unique, no error text. `(Broken)` and `(edited)` are immutable system suffixes. Rename preserves suffix.

New key name timestamp `DD/MM/YY-HH:MM:SS`; same-timestamp variants `_01`, `_02` etc. This is exception to rename validation. Correction adds `(edited)` once. Successful confirmed repair removes `(Broken)` and adds `(edited)`.

Delete uses standard OS Cancel/Delete confirmation; permanent delete, list refresh, remain Saved Keys. Cancel ends interaction and returns Saved Keys.

## Result Menu and Correction
After Scan show temporary Result Menu: Record, Correction, Delete.
- Record saves selected key, closes Result Menu and returns main menu; no transmission.
- Correction scans the correct original signal, merges/filters with damaged key, then TX-verifies. Result Menu remains for Record/Delete.
- Delete discards unsaved result and returns main menu.
- Exact duplicate: `Already exists`, no save, return main menu.

Multiple plausible variants appear separately with quality metrics. User tests each via transmitter and selects one or more. Save Selected disabled until selection. One failed variant does not affect others. Selected variants use `_01`, `_02`; Cancel discards all.

Saved-key Correction: user presses original remote once; capture/merge/filter; TX verification. On success `Transmission completed`, then Confirm/Cancel. Confirm permanently replaces sequence, adds `(edited)` once, no history. Cancel discards temp. Both return Saved Keys. No `Correction saved` toast. Failure leaves original unchanged, briefly `Correction failed`; technical reason only in log; context menu restored.

Broken key remains visible, never auto-deleted. Apply disabled; Correction available when module ready. Confirmed successful repair removes `(Broken)` and adds `(edited)`.

## UI and lifecycle
Minimal Finder/iOS/macOS feel; light/dark follows OS, dark default if impossible. No heavy effects/animations, emojis, Settings/About, tutorial or instructional error popups. Concise technical errors only.

One operation at a time, sequential. During operation block navigation/app close/new actions except Interrupt Scan. Manual Check cannot be interrupted. UI responsive for status. Crash/power loss discards temp operations; saved keys unchanged; no resume.

Core/UI independent; UI hang cannot delay radio timing; Core crash stops operation and discards temp. Event-driven UI, no periodic UI polling. Three execution areas: Core Worker (signal/crypto/storage), Hardware Worker (adapter/radio), UI thread. Higher priority only for timing-critical RX/TX sections. Ordinary SPI/crypto/DB/cleanup/UI standard. ESP32 timers/interrupts/DMA. If capture loses timing events, discard that capture and return Scan to waiting.

ESP32 UI mirrors menu adapted to resolution/orientation. Five buttons: Up/Down/Left/Right short; Select short=confirm, long=back; no separate back; ignore simultaneous buttons; minimal debounce; touchscreen if supported; no buzzer. Displays: SSD1306, ST7789, ILI9341, ST7735, GC9A01, SH1106, ILI9488, ST7796. Touch: XPT2046, CST816S, GT911. Detect where possible; SPI display IDs may be unavailable, use known-controller detection + fallback profiles. If multiple displays detected, ask user to leave one; no auto-select. Ready binaries use auto-detection; custom builds configure `config.txt` then rebuild/flash. Pin maps configurable in source config. ESP32 DevKit V1 30-pin DOIT-compatible, ESP32-WROOM-32; avoid boot-strap conflicts; shared SPI with separate CS. Reflash wipes all flash; no OTA.

## First-launch agreement
Official app: mandatory short first-launch agreement. Checkbox acknowledges lawful use and user's legal responsibility; Confirm enabled only after checked; Cancel/window close exits; no main UI before acceptance. Save acceptance; do not show each launch; reset only if app data removed unless changed later. State user responsible for lawful use in their jurisdiction and actions. Developer disclaimer/liability limitation only to extent legally permitted; no absolute immunity claim. Official-app behavior only, not license condition; forks may alter/remove freely.

## System log
Diagnostic-only, short, anonymized. Each record: timestamp, function, result (`OK`, `ERROR`, `CANCELLED` only when meaningful). No parameters, detailed errors, key names, frequencies, modulation, RF data, content, identifiers or activity history. New file each launch, max 10, FIFO delete oldest on 11th. No setting/confirmation. Flush critical records immediately.

Exact policy:
- Radio Check: errors only.
- Scan: errors only.
- Record: never.
- Correction: OK/ERROR/CANCELLED.
- Apply/successful TX: never.
- Delete: never.
- Rename/View/navigation/ordinary cancel/user actions: never.
- Unexpected termination: next launch generic `Application — ERROR`.
No error specifics.

## Storage and cryptography
Local app-internal storage. SQLite desktop/mobile; LittleFS ESP32. One logical model, platform-specific physical storage. AES-256-GCM, SHA-256, CSPRNG UUID v4. No password, Keychain or Keystore. CEK stored in separate file inside internal app directory. Each object has unique AES-256-GCM Object Key; Object Key is crypto-erasure unit. CEK protects container/wrapped Object Keys and is recoverable by sufficiently skilled reverse engineer; no excessive anti-analysis/obfuscation. Extracting CEK must not recover a deleted Object Key.

Deleting one object destroys only its Object Key and encrypted record; CEK and other objects unchanged. CEK stable, never rotated/deleted on individual delete. Unique nonce per encryption. No Object Key backups, export/import/restore/history. Physical overwrite best effort only if supported; otherwise skip. Never claim it occurred unless verified. Crypto-erasure primary.

Clean plaintext buffers/temp. No plaintext RF data in SQLite journal, logs, crash dumps, swap or temp. One damaged key must not affect others. Broken key remains; no auto-delete. Corrupt DB: no automatic deletion; mark individual Broken if separable. Atomic migrations: prepare/copy/validate/atomic switch; delete old temp only after success; failure preserves old DB. Uninstall deletes app data; reinstall empty. Desktop/mobile updates preserve keys/settings. ESP32 reflash wipes flash.

Exact physical representation of encrypted payloads/Object Keys (DB rows vs separate files) is not yet approved. Choose simplest design satisfying independent Object Key destruction and plaintext-remnant requirements; ask before committing to a material schema decision.

Terminal corruption: CEK loss/corruption => all keys unavailable; Object Key loss/corruption => corresponding key unavailable; container corruption => all keys inaccessible. No recovery, regeneration or automatic repair. Corrupted per-object record remains Broken if separable; never auto-delete. Be honest that SSD/APFS/CoW and external backups prevent absolute physical-erasure guarantees.

## Temporary data and resource limits
Temp files only in app-internal temp. Clear stale temp before UI at startup; clear on normal shutdown after stopping operations and clearing memory. Crash cleanup next launch. No recovery. Active temp excluded from FIFO cleanup. Remove oldest unused temp files FIFO under actual resource pressure; no fixed quantity threshold. Memory uses ownership/lifetime, not arbitrary deletion. No artificial max signal size or scan duration; scan only ends on result or manual cancel. Hardware stage timeouts still apply.

Core streams data; does not load entire container into RAM. Bounded buffers. ESP32 avoids dynamic allocation in critical loops and checks free/contiguous RAM. Insufficient memory aborts operation, shows `Insufficient Memory`, discards temp, leaves saved keys unchanged.

## RTC
Minimal extension point only. No V1 driver, logic, sync, UI or config. Core independent of RTC; not used for radio timing.

## License
Custom non-commercial license with exactly two conditions:
1. No commercial use.
2. Derivatives/forks include link to https://github.com/aynisej/rf433 and attribution/origin indication.
Forking/modification/redistribution allowed subject to these only. No other conditions. Do not draft license text until requested.


## Repository and prototype disposition
The former Python prototype used a CH341 programmer in a TTL-oriented test setup. It was not adapted into, nor validated as, the intended SPI hardware path for the EBYTE CC1101 module. Successful compilation or packaging of that prototype as `.deb`/AppImage did not prove SPI communication, RF capture, timing accuracy or target-hardware operation.

The former repository `aynisej/rf433` is explicitly approved for deletion without backup. It is not a compatibility target or implementation reference. Do not reuse its source code, tests, build scripts, CI workflows or repository history. The new implementation starts from a clean repository at the same canonical URL: `https://github.com/aynisej/rf433`.

All project documents and implementation milestones are to be committed and pushed directly to the replacement repository. GitHub Release publication remains subject to separate explicit user approval.
