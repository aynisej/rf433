#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace rf433::core {

struct KeyId {
    std::array<std::uint8_t, 16> bytes{};

    friend bool operator==(const KeyId&, const KeyId&) = default;
};

enum class Modulation : std::uint8_t {
    Ook,
    Ask,
    Fsk2,
    Gfsk,
    Fsk4,
    Msk,
};

enum class Compatibility : std::uint8_t {
    Compatible,
    Unverified,
    Incompatible,
};

enum class KeyHealth : std::uint8_t {
    Healthy,
    Broken,
};

enum class CaptureIntegrity : std::uint8_t {
    Unknown,
    Complete,
    Partial,
};

struct Cc1101RegisterValue {
    std::uint8_t address{};
    std::uint8_t value{};

    friend bool operator==(const Cc1101RegisterValue&, const Cc1101RegisterValue&) = default;
};

struct RadioConfiguration {
    std::uint32_t frequencyHz{};
    Modulation modulation{Modulation::Ook};
    std::vector<Cc1101RegisterValue> cc1101Registers;
};

struct CaptureQuality {
    CaptureIntegrity integrity{CaptureIntegrity::Unknown};
    std::uint32_t repetitionCount{};
};

struct KeyMetadata {
    KeyId id;
    std::string baseName;
    RadioConfiguration radio;
    CaptureQuality capture;
    Compatibility compatibility{Compatibility::Unverified};
    KeyHealth health{KeyHealth::Healthy};
    bool edited{};
};

[[nodiscard]] bool isUuidV4(const KeyId& id) noexcept;
[[nodiscard]] bool isSupportedFrequencyHz(std::uint32_t frequencyHz) noexcept;

} // namespace rf433::core
