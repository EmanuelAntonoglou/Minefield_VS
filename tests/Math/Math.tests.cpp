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

TEST(Random, is_random_value_inside_range)
{
    unsigned int from = 0;
    unsigned int to = 5;

    for (int i = 0; i < 1000; ++i)
    {
        unsigned int randNum = math::getRandomNumber(from, to);

        EXPECT_GE(randNum, from);
        EXPECT_LE(randNum, to);
    }
}
}