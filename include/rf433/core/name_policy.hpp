#pragma once

#include <span>
#include <string_view>

namespace rf433::core {

[[nodiscard]] bool isValidRenameBaseName(std::string_view candidate) noexcept;

// existingBaseNames should exclude the key being renamed. System suffixes are
// not part of the base name and are deliberately not considered here.
[[nodiscard]] bool isRenameBaseNameAvailable(
    std::string_view candidate,
    std::span<const std::string_view> existingBaseNames) noexcept;

} // namespace rf433::core
