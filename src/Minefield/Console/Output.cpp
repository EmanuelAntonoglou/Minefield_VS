#include <Minefield/Console/Output.h>
#include <iomanip>

namespace console
{
    namespace output
    {
        void clearBuffer()
        {
            static char const *const kClearConsoleBufferCommand = "cls";
            system(kClearConsoleBufferCommand);
        }

        void print(const std::string &msg, int w)
        {
            std::cout << std::setw(w) << msg;
        }
    }
}