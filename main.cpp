#include <charconv>
#include <cstdint>
#include <expected>
#include <iostream>
#include <print>
#include <string>
#include <string_view>

enum class ParseError
{
    TOO_SHORT,
    TOO_LONG,
    INVALID_STRING,
    INVALID_VALUE,
    INVALID_RUNWAY_SUFFIX
};

template <> struct std::formatter<ParseError> : std::formatter<std::string>
{
    auto format(ParseError p, format_context& ctx) const
    {
        std::string str;
        switch (p)
        {
            case ParseError::TOO_SHORT:
                str = "PROVIDED STRING TOO_SHORT";
                break;
            case ParseError::TOO_LONG:
                str = "PROVIDED STRING TOO_LONG";
                break;
            case ParseError::INVALID_STRING:
                str = "PROVIDED INVALID_STRING";
                break;
            case ParseError::INVALID_VALUE:
                str = "STRING CONTAINS INVALID_VALUE";
                break;
            case ParseError::INVALID_RUNWAY_SUFFIX:
                str = "STRING CONTAINS INVALID_RUNWAY_SUFFIX";
                break;
            default:
                str = "UNKNOWN";
        }

        return std::formatter<std::string>::format(str, ctx);
    }
};

std::expected<std::uint8_t, ParseError> getHeading(std::string_view str)
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

std::expected<std::string, ParseError> parseInput(std::string_view str)
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

    auto heading = getHeading(str);
    if (not heading.has_value())
    {
        return std::unexpected{heading.error()};
    }

    constexpr std::uint8_t halfwayPoint{18};
    constexpr std::uint8_t maxHeading{36};
    constexpr std::uint8_t nonExistentHeading{0};

    auto oppositeHeading = (*heading + halfwayPoint) % maxHeading;
    oppositeHeading = oppositeHeading == nonExistentHeading ? maxHeading : oppositeHeading;
    auto oppositeHeadingStr = std::to_string(oppositeHeading);

    if (str.length() == expectedMinLength)
    {
        return oppositeHeadingStr;
    }

    auto laneSign = str.back();

    switch (laneSign)
    {
        case 'L':
            return oppositeHeadingStr + 'R';
        case 'R':
            return oppositeHeadingStr + 'L';
        case 'C':
            return oppositeHeadingStr + 'C';
        default:
            return std::unexpected{ParseError::INVALID_RUNWAY_SUFFIX};
    }
}

int main()
{
    std::string input;
    while (true)
    {
        std::print("Provide heading: ");
        std::cin >> input;
        auto newHeading = parseInput(input);

        if (newHeading.has_value())
        {
            std::println("New Heading: {}", *newHeading);
        }
        else
        {
            std::println("Input error: {}", newHeading.error());
        }
    }

    return 0;
}