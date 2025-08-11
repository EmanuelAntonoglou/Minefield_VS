#pragma once
#include <vector>
#include <string>
#include <Minefield/Math/Vector2UInt.h>

namespace game
{
    struct Coordinate : math::Vector2UInt
    {
        Coordinate() = default;
        Coordinate(unsigned int xVal, unsigned int yVal) : math::Vector2UInt{xVal, yVal} {}

        bool operator==(const Coordinate& other) const 
        {
            return x == other.x && y == other.y;
        }
    };

    std::vector<Coordinate> parseCoordinates(std::string const& input);
}