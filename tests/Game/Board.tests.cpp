#include <gtest/gtest.h>
#include <Minefield/Game/Board.h>

namespace game::tests
{
    TEST(Board, constructor_should_keep_dimensions_and_tiles)
    {
        BoardDimensions dimensions(3, 3);
        utils::board::TileMatrix matrix(3, std::vector<Tile>(3));

        for (unsigned int x = 0; x < dimensions.x; ++x)
        {
            for (unsigned int y = 0; y < dimensions.y; ++y)
            {
                matrix[x][y] = Tile(TileType::Empty, {x, y});
            }
        }

        matrix[1][1] = Tile(TileType::Bomb, {1, 1});

        Board board(matrix, dimensions);

        EXPECT_EQ(board.dimensions().x, 3);
        EXPECT_EQ(board.dimensions().y, 3);

        utils::board::TileMatrix boardMatrix = board.matrix();
        EXPECT_EQ(boardMatrix[0][0].tileType, TileType::Empty);
        EXPECT_EQ(boardMatrix[1][1].tileType, TileType::Bomb);
        EXPECT_EQ(boardMatrix[2][2].tileType, TileType::Empty);
    }

    TEST(Board, change_tile_type_should_only_update_target_tile)
    {
        BoardDimensions dimensions(5, 5);
        utils::board::TileMatrix matrix(5, std::vector<Tile>(5, Tile(TileType::Empty, {})));
        Board board(matrix, dimensions);

        Coordinate coordToChange = {2, 3};
        board.changeTileType(coordToChange, TileType::Guess);

        utils::board::TileMatrix updatedMatrix = board.matrix();

        EXPECT_EQ(updatedMatrix[2][3].tileType, TileType::Guess);

        EXPECT_EQ(updatedMatrix[3][3].tileType, TileType::Empty);
    }

    TEST(Board, get_tiles_of_type_should_return_all_bombs)
    {
        BoardDimensions dimensions(4, 4);
        utils::board::TileMatrix matrix(4, std::vector<Tile>(4, Tile(TileType::Empty, {})));

        matrix[0][1] = Tile(TileType::Bomb, {1, 0});
        matrix[1][3] = Tile(TileType::Bomb, {3, 1});
        matrix[3][2] = Tile(TileType::Bomb, {2, 3});

        Board board(matrix, dimensions);

        std::vector<Tile> bombTiles = board.getTilesOfType(TileType::Bomb);

        EXPECT_EQ(bombTiles.size(), 3);

        bool foundCoord = false;
        for (auto const& tile : bombTiles)
        {
            if (tile.coordinate.x == 3 && tile.coordinate.y == 1)
            {
                foundCoord = true;
                break;
            }
        }
        EXPECT_TRUE(foundCoord);
    }

    TEST(Board, constructor_should_create_one_by_one_board)
    {
        BoardDimensions dimensions(1, 1);
        utils::board::TileMatrix matrix(1, std::vector<Tile>(1, Tile(TileType::Bomb, {0, 0})));

        Board board(matrix, dimensions);

        EXPECT_EQ(board.dimensions().x, 1);
        EXPECT_EQ(board.dimensions().y, 1);
        EXPECT_EQ(board.getTilesOfType(TileType::Bomb).size(), 1);
    }

    TEST(Board, constructor_should_create_an_empty_board)
    {
        BoardDimensions dimensions(0, 0);
        utils::board::TileMatrix matrix;

        Board board(matrix, dimensions);

        EXPECT_EQ(board.dimensions().x, 0);
        EXPECT_EQ(board.getTilesOfType(TileType::Bomb).size(), 0);
    }
} 
