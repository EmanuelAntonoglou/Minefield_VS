#pragma once
#include <iostream>
#include <string>
#include <Minefield/Console/Output.h>

namespace console::input
{
template <typename T, typename... Types>
T readInput(Types... Args)
{
    T input{};
    bool validated = false;

    while (!validated)
    {
        console::output::print("> ");
        if constexpr (sizeof...(Args) > 0)
        {
            console::output::print(Args...);
        }

        std::cin >> input;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            console::output::println("Invalid input, please try again.");
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            validated = true;
        }
    }

    return input;
}

void pressAnyKeyToContinue();
} // namespace console::input