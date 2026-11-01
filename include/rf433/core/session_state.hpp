#pragma once

#include "rf433/core/action_policy.hpp"

namespace rf433::core {

enum class SessionTransitionError {
    None,
    InvalidOperation,
    OperationAlreadyActive,
    RadioNotReady,
    WrongOperation,
    OperationNotInterruptible,
};

struct RadioSessionSnapshot {
    RadioReadiness readiness{RadioReadiness::Unknown};
    ActiveOperation activeOperation{ActiveOperation::None};
};

class RadioSession final {
public:
    [[nodiscard]] RadioSessionSnapshot snapshot() const noexcept;

    [[nodiscard]] SessionTransitionError begin(ActiveOperation operation) noexcept;
    [[nodiscard]] SessionTransitionError completeManualCheck(bool radioReady) noexcept;
    [[nodiscard]] SessionTransitionError complete(ActiveOperation operation) noexcept;
    [[nodiscard]] SessionTransitionError interruptScan() noexcept;

    void reportHardwareFault() noexcept;

private:
    RadioSessionSnapshot state_{};
};

} // namespace rf433::core
