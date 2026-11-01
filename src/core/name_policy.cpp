#include "rf433/core/name_policy.hpp"

namespace rf433::core {

namespace {

constexpr char asciiLower(const char value) noexcept {
    if (value >= 'A' && value <= 'Z') {
        return static_cast<char>(value + ('a' - 'A'));
    }
    return value;
}

bool equalIgnoringAsciiCase(const std::string_view left,
                            const std::string_view right) noexcept {
    if (left.size() != right.size()) {
        return false;
    }

    for (std::size_t index = 0; index < left.size(); ++index) {
        if (asciiLower(left[index]) != asciiLower(right[index])) {
            return false;
        }
    }
    return true;
}

} // namespace

bool isValidRenameBaseName(const std::string_view candidate) noexcept {
    if (candidate.empty() || candidate.size() > 32) {
        return false;
    }

    for (const unsigned char character : candidate) {
        const bool isLatinLetter = (character >= 'A' && character <= 'Z') ||
                                   (character >= 'a' && character <= 'z');
        const bool isDigit = character >= '0' && character <= '9';
        if (!isLatinLetter && !isDigit) {
            return false;
        }
    }
    return true;
}

bool isRenameBaseNameAvailable(
    const std::string_view candidate,
    const std::span<const std::string_view> existingBaseNames) noexcept {
    if (!isValidRenameBaseName(candidate)) {
        return false;
    }

    for (const std::string_view existing : existingBaseNames) {
        if (equalIgnoringAsciiCase(candidate, existing)) {
            return false;
        }
    }
    return true;
}

} // namespace rf433::core
