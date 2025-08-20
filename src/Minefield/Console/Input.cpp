#include <iostream>
#include <Minefield/Console/Input.h>
#include <limits>
#include <windows.h>

namespace console::input
{
void pressAnyKeyToContinue()
{
    console::output::print("> Press any key to continue ");

    #ifdef _WIN32
        _getwch();
    #endif

    console::output::clearBuffer();
}
} // namespace console::input