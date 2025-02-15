#pragma once

#include <format>

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