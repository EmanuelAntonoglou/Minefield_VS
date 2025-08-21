#include <gtest/gtest.h>
#include <Minefield/Game/Coordinate.h> 
#include <string>
#include <vector>

namespace game::tests
{
    TEST(Coordinate, constructor_should_set_xy_values)
    {
        Coordinate const c(5, 10);

        EXPECT_EQ(c.x, 5);
        EXPECT_EQ(c.y, 10);
    }

    TEST(Coordinate, equality_operator_should_return_true_for_same_coordinates)
    {
        Coordinate const c1(12, 34);
        Coordinate const c2(12, 34);

        EXPECT_TRUE(c1 == c2);
    }

    TEST(Coordinate, equality_operator_should_return_false_for_different_coordinates)
    {
        Coordinate const c1(5, 8);
        Coordinate const c2(8, 5); 
        Coordinate const c3(5, 9); 

        EXPECT_FALSE(c1 == c2);
        EXPECT_FALSE(c1 == c3);
    }

    TEST(Coordinate, parse_coordinates_should_return_empty_vector_for_empty_input)
    {
        std::string const input = "";
        std::vector<Coordinate> const result = parseCoordinates(input);

        EXPECT_TRUE(result.empty());
    }

    TEST(Coordinate, parse_coordinates_should_handle_multiple_valid_pairs)
    {
        std::string const input = "1,2 10,5 3,3";
        std::vector<Coordinate> const expected = {Coordinate(0, 1), Coordinate(9, 4), Coordinate(2, 2)};

        std::vector<Coordinate> const result = parseCoordinates(input);

        EXPECT_EQ(result, expected);
    }

    TEST(Coordinate, parse_coordinates_should_handle_extra_whitespace)
    {
        std::string const input = "  2,2   9,1  ";
        std::vector<Coordinate> const expected = {Coordinate(1, 1), Coordinate(8, 0)};

        std::vector<Coordinate> const result = parseCoordinates(input);

        EXPECT_EQ(result, expected);
    }
    TEST(Coordinate, parse_coordinates_should_ignore_malformed_pairs)
    {
        std::string const input = " 1,1 river 3,4 plate 5,5 ";
        std::vector<Coordinate> const expected = {Coordinate(0, 0), Coordinate(2, 3), Coordinate(4, 4)};

        std::vector<Coordinate> const result = parseCoordinates(input);

        EXPECT_EQ(result, expected);
    }
}
