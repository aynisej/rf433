#pragma once

namespace rf433::core {

enum class RadioReadiness {
    Unknown,
    Ready,
    Faulted,
};

enum class ActiveOperation {
    None,
    ManualCheck,
    Scan,
    Apply,
    Correction,
};

enum class SavedKeyHealth {
    Healthy,
    Broken,
};

struct MainMenuAvailability {
    bool checkRadio{};
    bool scan{};
    bool savedKeys{};
};

struct SavedKeyAvailability {
    bool view{};
    bool apply{};
    bool correction{};
    bool remove{};
    bool rename{};
};

[[nodiscard]] MainMenuAvailability mainMenuAvailability(
    RadioReadiness readiness,
    ActiveOperation operation) noexcept;

[[nodiscard]] SavedKeyAvailability savedKeyAvailability(
    RadioReadiness readiness,
    ActiveOperation operation,
    SavedKeyHealth health) noexcept;

[[nodiscard]] bool canInterrupt(ActiveOperation operation) noexcept;

} // namespace rf433::core
