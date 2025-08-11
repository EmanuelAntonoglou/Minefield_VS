#pragma once

namespace math 
{
    inline bool isUIntInRange(unsigned int num, unsigned int min, unsigned int max) { return (num >= min && num <= max);}
    void initializeRandomSeed();
    int getRandomNumber(int from, int to);
}