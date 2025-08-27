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
        size_t commaPos = pair.find(',');
        if (commaPos != std::string::npos)
        {
            int x = std::stoi(pair.substr(0, commaPos));
            int y = std::stoi(pair.substr(commaPos + 1));
            coordinates.emplace_back(x - 1, y - 1);
        }
    }
    return coordinates;
}
} // namespace game