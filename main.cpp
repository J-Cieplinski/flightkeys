
#include <input_parser.hpp>

#include <algorithm>
#include <iostream>
#include <print>
#include <string>

int main()
{
    std::string input;
    while (true)
    {
        std::print("Provide heading: ");
        std::getline(std::cin, input);
        std::erase_if(input, isspace);
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