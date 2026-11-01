#include "rf433/core/key_metadata.hpp"

namespace rf433::core {

bool isUuidV4(const KeyId& id) noexcept {
    constexpr std::uint8_t versionMask = 0xF0;
    constexpr std::uint8_t version4 = 0x40;
    constexpr std::uint8_t variantMask = 0xC0;
    constexpr std::uint8_t rfc4122Variant = 0x80;

    return (id.bytes[6] & versionMask) == version4 &&
           (id.bytes[8] & variantMask) == rfc4122Variant;
}

bool isSupportedFrequencyHz(const std::uint32_t frequencyHz) noexcept {
    constexpr std::uint32_t minimumHz = 387'000'000;
    constexpr std::uint32_t maximumHz = 464'000'000;
    return frequencyHz >= minimumHz && frequencyHz <= maximumHz;
}

} // namespace rf433::core
