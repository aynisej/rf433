#include "rf433/core/action_policy.hpp"

namespace rf433::core {

MainMenuAvailability mainMenuAvailability(
    const RadioReadiness readiness,
    const ActiveOperation operation) noexcept {
    const bool idle = operation == ActiveOperation::None;
    const bool radioReady = readiness == RadioReadiness::Ready;

    return {
        .checkRadio = idle,
        .scan = idle && radioReady,
        .savedKeys = idle,
    };
}

SavedKeyAvailability savedKeyAvailability(
    const RadioReadiness readiness,
    const ActiveOperation operation,
    const SavedKeyHealth health) noexcept {
    const bool idle = operation == ActiveOperation::None;
    const bool radioReady = readiness == RadioReadiness::Ready;

    return {
        .view = idle,
        .apply = idle && radioReady && health == SavedKeyHealth::Healthy,
        .correction = idle && radioReady,
        .remove = idle,
        .rename = idle,
    };
}

bool canInterrupt(const ActiveOperation operation) noexcept {
    return operation == ActiveOperation::Scan;
}

} // namespace rf433::core
