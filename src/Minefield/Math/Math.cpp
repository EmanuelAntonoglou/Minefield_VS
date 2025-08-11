#include <Minefield/Math/Math.h>
#include <stdlib.h>
#include <time.h>

namespace math
{
    void initializeRandomSeed()
    {
        srand(static_cast<int>(time(nullptr)));
    }

    int getRandomNumber(int from, int to)
    {
        return ((rand() % to+1) + from);
    }
}