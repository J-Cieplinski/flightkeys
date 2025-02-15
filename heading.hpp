#pragma once

#include <ParseError.hpp>

#include <charconv>
#include <cstdint>
#include <expected>
#include <string_view>

inline std::expected<std::uint8_t, ParseError> getHeading(std::string_view str)
{
    std::uint8_t heading{0};
    if (std::from_chars(str.data(), str.data() + str.size(), heading).ec
        == std::errc::invalid_argument)
    {
        return std::unexpected{ParseError::INVALID_STRING};
    }
    if (heading < 0 or (heading / 100) > 0)
    {
        return std::unexpected{ParseError::INVALID_VALUE};
    }

    return heading;
}

inline std::expected<std::string, ParseError> parseHeading(std::string_view str)
{
    auto heading = getHeading(str);
    if (not heading.has_value())
    {
        return std::unexpected{heading.error()};
    }

    constexpr std::uint8_t halfwayPoint{18};
    constexpr std::uint8_t maxHeading{36};
    constexpr std::uint8_t nonExistentHeading{0};

    if (*heading > maxHeading or *heading <= nonExistentHeading)
    {
        return std::unexpected{ParseError::INVALID_VALUE};
    }

    auto oppositeHeading = (*heading + halfwayPoint) % maxHeading;
    oppositeHeading = oppositeHeading == nonExistentHeading ? maxHeading : oppositeHeading;
    auto oppositeHeadingStr = std::to_string(oppositeHeading);

    return oppositeHeadingStr;
}