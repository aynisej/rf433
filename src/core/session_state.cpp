#include "rf433/core/session_state.hpp"

namespace rf433::core {

RadioSessionSnapshot RadioSession::snapshot() const noexcept {
    return state_;
}

SessionTransitionError RadioSession::begin(const ActiveOperation operation) noexcept {
    if (operation == ActiveOperation::None) {
        return SessionTransitionError::InvalidOperation;
    }
    if (state_.activeOperation != ActiveOperation::None) {
        return SessionTransitionError::OperationAlreadyActive;
    }
    if (operation != ActiveOperation::ManualCheck &&
        state_.readiness != RadioReadiness::Ready) {
        return SessionTransitionError::RadioNotReady;
    }

    state_.activeOperation = operation;
    return SessionTransitionError::None;
}

SessionTransitionError RadioSession::completeManualCheck(const bool radioReady) noexcept {
    if (state_.activeOperation != ActiveOperation::ManualCheck) {
        return SessionTransitionError::WrongOperation;
    }

    state_.readiness = radioReady ? RadioReadiness::Ready : RadioReadiness::Faulted;
    state_.activeOperation = ActiveOperation::None;
    return SessionTransitionError::None;
}

SessionTransitionError RadioSession::complete(const ActiveOperation operation) noexcept {
    if (operation == ActiveOperation::None || operation == ActiveOperation::ManualCheck ||
        state_.activeOperation != operation) {
        return SessionTransitionError::WrongOperation;
    }

    state_.activeOperation = ActiveOperation::None;
    return SessionTransitionError::None;
}

SessionTransitionError RadioSession::interruptScan() noexcept {
    if (!canInterrupt(state_.activeOperation)) {
        return SessionTransitionError::OperationNotInterruptible;
    }

    state_.activeOperation = ActiveOperation::None;
    return SessionTransitionError::None;
}

void RadioSession::reportHardwareFault() noexcept {
    state_.readiness = RadioReadiness::Faulted;
    state_.activeOperation = ActiveOperation::None;
}

} // namespace rf433::core
