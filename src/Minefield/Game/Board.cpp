#include <Minefield/Console/Input.h>
#include <Minefield/Console/Output.h>
#include <Minefield/Game/Board.h>

namespace game::utils::board
{
bool isValidCoordinate(Coordinate const& tileCoordinate, TileMatrix const& matrix, BoardDimensions const& boardDimensions)
{
    return !matrix.empty() && tileCoordinate.x >= 0 && tileCoordinate.x < boardDimensions.x && tileCoordinate.y >= 0 && tileCoordinate.y < boardDimensions.y;
}

TileType const* getTile(Coordinate const& tileCoordinate, TileMatrix const& matrix, BoardDimensions const& boardDimensions)
{
    if (!isValidCoordinate(tileCoordinate, matrix, boardDimensions))
    {
        return nullptr;
    }
    return &matrix[tileCoordinate.x][tileCoordinate.y];
}
} // namespace game::utils::board

namespace game
{
using namespace utils::board;

Board::Board(TileMatrix matrix, BoardDimensions boardDimensions)
: mMatrix(matrix)
, mBoardDimensions(boardDimensions) {};

void Board::changeTileType(Coordinate const& tileCoordinate, TileType const& tileType)
{
    if (isValidCoordinate(tileCoordinate, mMatrix, mBoardDimensions))
    {
        mMatrix[tileCoordinate.y][tileCoordinate.x] = tileType;
    }
}

void Board::print() const
{
    if (mMatrix.empty() || mMatrix[0].empty())
    {
        console::output::println("Error: Can't print board. Matrix is empty");
        return;
    }

    console::output::print();
    console::output::print();
    for (unsigned int y = 0; y < mMatrix[0].size(); y++)
    {
        console::output::print(std::to_string(y + 1), 2);
        console::output::print();
    }
    console::output::println();

    for (unsigned int x = 0; x < mMatrix.size(); x++)
    {
        console::output::print(std::to_string(x + 1), 2);

        for (unsigned int y = 0; y < mMatrix[x].size(); y++)
        {
            TileType tile = mMatrix[x][y];
            std::string tileStr(1, static_cast<char>(tile));
            console::output::print(tileStr, 2);
            console::output::print();
        }
        console::output::println();
    }
}

std::vector<Coordinate> Board::getCoordinatesOfTileType(TileType const& tileType) const
{
    std::vector<Coordinate> coordinatesOfTileType;

    for (unsigned int y = 0; y < mMatrix.size(); y++)
    {
        for (unsigned int x = 0; x < mMatrix[0].size(); x++)
        {
            if (mMatrix[y][x] == tileType)
            {
                coordinatesOfTileType.emplace_back(y, x);
            }
        }
    }
    return coordinatesOfTileType;
}
} // namespace game