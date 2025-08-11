#pragma once

#include <string>
#include <iostream>

namespace console
{
    namespace output
    {
        void clearBuffer();

        template<typename T>
        void singlePrint(const T& msg)
        {
            std::cout << msg;
        }

        template<typename... Types>
        void print(Types... Args)
        {
            (singlePrint(Args), ...);
        }

        void print(const std::string &msg, int w);

        template<typename... Types>
        void println(Types... Args)
        {
            if constexpr (sizeof...(Args) > 0) 
            {
                (singlePrint(Args), ...);
            }
            std::cout << std::endl;
        }
    }
}