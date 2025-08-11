#pragma once

#include <string>

namespace console
{
    namespace input
    {
        char readChar();
        std::string readString();
        int readInt();
        void pressEnterToContinue();
    }
}