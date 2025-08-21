#pragma once

#include <string>
#include <iostream>
#include <sstream>

namespace console::output
{
void clearBuffer();

template <typename T>
void singlePrint(T const& msg)
{
    std::cout << msg;
}

template <typename... Types>
void print(Types... Args)
{
    (singlePrint(Args), ...);
}

void print(std::string const& msg, int w);

template <typename... Types>
void println(Types... Args)
{
    if constexpr (sizeof...(Args) > 0)
    {
        (singlePrint(Args), ...);
    }
    std::cout << '\n';
}
} // namespace console::output