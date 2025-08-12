#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Minefield/Math/Math.h>

namespace math::tests 
{
TEST(Range, is_value_within_uint_range) 
{
    unsigned int num = 10;
    unsigned int min = 0;
    unsigned int max = 15;

    EXPECT_TRUE(math::isUIntInRange(num, min, max));
}

TEST(Range, is_value_outside_uint_range)
{
    unsigned int num = 10;
    unsigned int min = 0;
    unsigned int max = 5;

    EXPECT_FALSE(math::isUIntInRange(num, min, max));
}

TEST(Prueba, probando)
{
    bool mibool = true;
    if (math::getRandomNumber(1, 2) < 3)
    {
        EXPECT_FALSE(false);
    }
    
}
}