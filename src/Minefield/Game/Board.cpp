#include <Minefield/Game/Board.h>
#include <Minefield/Console/Output.h>
#include <Minefield/Console/Input.h>

namespace game
{
    Board::Board(TileMatrix matrix, BoardDimensions boardDimensions) : mMatrix(matrix), mBoardDimensions(boardDimensions) {};

    const TileType *Board::getTile(Coordinate const &tileCoordinate)
    {
        if (!isValidCoordinate(tileCoordinate))
        {
            return nullptr;
        }
        return &mMatrix[tileCoordinate.x][tileCoordinate.y].tileType;
    }

    void Board::changeTileType(Coordinate const& tileCoordinate, TileType const& tileType)
    {
        if (isValidCoordinate(tileCoordinate))
        {
            mMatrix[tileCoordinate.x][tileCoordinate.y].tileType = tileType;
        }
    }

    bool Board::isValidCoordinate(Coordinate const& tileCoordinate)
    {
        return !mMatrix.empty() &&
                tileCoordinate.x >= 0 && tileCoordinate.x < mBoardDimensions.x &&
                tileCoordinate.y >= 0 && tileCoordinate.y < mBoardDimensions.y;
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
                TileType tile = mMatrix[x][y].tileType;
                std::string tileStr(1, static_cast<char>(tile));
                console::output::print(tileStr, 2);
                console::output::print();
            }
            console::output::println();
        }
    }

    std::vector<Tile> Board::getTilesOfType(TileType const& tileType) const
    {
        std::vector<Tile> tilesOfType;
        for (auto const &row : mMatrix)
        {
            for (auto const &tile : row)
            {
                if (tile.tileType == tileType)
                {
                    tilesOfType.push_back(tile);
                }
            }
        }
        return tilesOfType;
    }
}