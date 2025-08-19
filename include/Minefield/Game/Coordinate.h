#pragma once
#include <Minefield/Math/Vector2UInt.h>

#include <string>
#include <vector>

namespace game
{
struct Coordinate : math::Vector2UInt
{
    Coordinate() = default;
    Coordinate(unsigned int xVal, unsigned int yVal)
    : math::Vector2UInt{xVal, yVal}
    {
    }

    bool operator==(Coordinate const& other) const
    {
        return x == other.x && y == other.y;
    }
};

std::vector<Coordinate> parseCoordinates(std::string const& input);
} // namespace game