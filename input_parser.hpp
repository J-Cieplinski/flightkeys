#pragma once

#include <ParseError.hpp>
#include <heading.hpp>

#include <cstdint>
#include <expected>
#include <string>
#include <string_view>

inline std::expected<std::string, ParseError> parseInput(std::string_view str)
{
    constexpr std::uint8_t expectedMaxLength{3};
    constexpr std::uint8_t expectedMinLength{2};

    if (str.length() > expectedMaxLength)
    {
        return std::unexpected{ParseError::TOO_LONG};
    }
    if (str.length() < expectedMinLength)
    {
        return std::unexpected{ParseError::TOO_SHORT};
    }

    auto targetHeadingStr = parseHeading(str);
    if (not targetHeadingStr.has_value())
    {
        return std::unexpected{targetHeadingStr.error()};
    }

    if (str.length() == expectedMinLength)
    {
        return targetHeadingStr;
    }

    auto laneSign = str.back();

    switch (std::toupper(laneSign))
    {
        case 'L':
            return *targetHeadingStr + 'R';
        case 'R':
            return *targetHeadingStr + 'L';
        case 'C':
            return *targetHeadingStr + 'C';
        default:
            return std::unexpected{ParseError::INVALID_RUNWAY_SUFFIX};
    }
}