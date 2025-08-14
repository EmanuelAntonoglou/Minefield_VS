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
        Tile(TileType const& tileType, Coordinate const& coordinate) : tileType(tileType), coordinate(coordinate) {};

        TileType tileType;
        Coordinate coordinate;
    };

    namespace utils::board
    {
        using TileMatrix = std::vector<std::vector<Tile>>;
        bool isValidCoordinate(Coordinate const& tileCoordinate, TileMatrix const& matrix, BoardDimensions const& boardDimensions);
        TileType const* getTile(Coordinate const& tileCoordinate, TileMatrix const& matrix, BoardDimensions const& boardDimensions);
    } // namespace board
    
    class Board
    {
    public:
        Board() = default;
        Board(utils::board::TileMatrix matrix, BoardDimensions boardDimensions);

        inline BoardDimensions const& dimensions() const noexcept { return mBoardDimensions; }
        inline utils::board::TileMatrix matrix() const { return mMatrix; }
        void print() const;
        void changeTileType(Coordinate const& tileCoordinate, TileType const& tileType);
        std::vector<Tile> getTilesOfType(TileType const& tileType) const;

    private:
        BoardDimensions mBoardDimensions;
        utils::board::TileMatrix mMatrix;
    };
    
}