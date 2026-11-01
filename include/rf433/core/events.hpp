#pragma once

#include "rf433/core/action_policy.hpp"

#include <chrono>
#include <cstdint>
#include <variant>

namespace rf433::core {

enum class RadioCheckStage : std::uint8_t {
    UsbEnumeration,
    AdapterAndSpiLines,
    ElectricalChecks,
    Cc1101Reset,
    IdentifyAndReadRegisters,
    SafeRegisterWriteReadback,
    ConfigurationAndCalibration,
    ReceiveSelfTest,
    TransmitSelfTest,
    RestoreAndSleep,
};

enum class ScanPhase : std::uint8_t {
    Initialization,
    WaitingForSignal,
    SignalDetection,
    SequenceReading,
    BoundaryDetection,
    Deduplication,
    IntegrityCheck,
    ResultGeneration,
};

enum class OperationOutcome : std::uint8_t {
    Completed,
    Interrupted,
    Cancelled,
    InsufficientMemory,
    HardwareFault,
};

struct RadioCheckProgressEvent {
    RadioCheckStage stage{};
    std::chrono::milliseconds stageElapsed{};
    std::chrono::milliseconds totalElapsed{};
};

struct RadioCheckFinishedEvent {
    bool radioReady{};
};

struct ScanProgressEvent {
    ScanPhase phase{};
    std::chrono::milliseconds totalElapsed{};
};

struct OperationFinishedEvent {
    ActiveOperation operation{ActiveOperation::None};
    OperationOutcome outcome{OperationOutcome::Completed};
};

// Value-only progress and outcome messages for delivery to the UI thread.
// RF captures, keys, and other large or sensitive payloads stay in Core.
using CoreEvent = std::variant<RadioCheckProgressEvent,
                               RadioCheckFinishedEvent,
                               ScanProgressEvent,
                               OperationFinishedEvent>;

} // namespace rf433::core
