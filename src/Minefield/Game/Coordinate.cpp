#include <Minefield/Game/Coordinate.h>

#include <regex>
#include <sstream>

namespace game
{
std::vector<Coordinate> parseCoordinates(std::string const& input)
{
    std::vector<Coordinate> coordinates;
    std::istringstream iss(input);
    std::string pair;

    while (iss >> pair)
    {
        size_t comma_pos = pair.find(',');
        if (comma_pos != std::string::npos)
        {
            int x = std::stoi(pair.substr(0, comma_pos));
            int y = std::stoi(pair.substr(comma_pos + 1));
            coordinates.emplace_back(x - 1, y - 1);
        }
    }
    return coordinates;
}
} // namespace game