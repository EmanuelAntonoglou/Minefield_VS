#pragma once
#include <vector>
#include <Minefield/Math/Vector2UInt.h>
#include "Coordinate.h"
#include <optional>

namespace game
{
    struct BoardDimensions : math::Vector2UInt
    {
        BoardDimensions() = default;
        BoardDimensions(unsigned int wVal, unsigned int hVal) : math::Vector2UInt{wVal, hVal} {};
    };

    enum class TileType : char
    {
        Empty = 'o',
        Guess = '?',
        Bomb = '*',
        Taken = 'x'
    };

    struct Tile
    {
        Tile() = default;
        Tile(TileType tileType, Coordinate coordinate) : tileType(tileType), coordinate(coordinate) {};

        TileType tileType;
        Coordinate coordinate;
    };

    class Board
    {
        
    public:
        using TileMatrix = std::vector<std::vector<Tile>>;

        Board() = default;
        Board(TileMatrix matrix, BoardDimensions boardDimensions);

        void print() const;
        const BoardDimensions& dimensions() const noexcept { return mBoardDimensions; }
        const TileType *getTile(Coordinate const &tileCoordinate);
        void changeTileType(Coordinate const& tileCoordinate, TileType const& tileType);
        bool isValidCoordinate(Coordinate const& tileCoordinate);
        std::vector<Tile> getTilesOfType(TileType const& tileType) const;

    private:
        BoardDimensions mBoardDimensions;
        TileMatrix mMatrix;
    };
}