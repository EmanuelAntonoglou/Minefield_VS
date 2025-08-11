#include <iostream>
#include <Minefield/Console/Input.h>
#include <Minefield/Console/Output.h>
#include <limits>

namespace console
{
    namespace input
    {
        char readChar()
        {
            char input = ' ';
            std::cin.get(input);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return input;
        }

        std::string readString()
        {
            std::string input;
            std::getline(std::cin, input);
            return input;
        }

        int readInt()
        {
            int input = std::stoul(readString());
            return input;
        }

        void pressEnterToContinue()
        {
            console::output::print("> Press enter to continue ");
            readString();
            console::output::clearBuffer();
        }
    }
}