#include <gtest/gtest.h>
#include <Minefield/Game/Board.h>
#include <Minefield/Console/Output.h>

namespace game::tests
{
    TEST(Board, constructor_should_keep_dimensions_and_tiles)
    {
        BoardDimensions dimensions(3, 3);
        utils::board::TileMatrix matrix(3, std::vector<TileType>(3));

        for (unsigned int x = 0; x < dimensions.x; ++x)
        {
            for (unsigned int y = 0; y < dimensions.y; ++y)
            {
                matrix[x][y] = TileType::Empty;
            }
        }

        matrix[1][1] = TileType::Bomb;

        Board board(matrix, dimensions);

        EXPECT_EQ(board.dimensions().x, 3);
        EXPECT_EQ(board.dimensions().y, 3);

        const TileType* tile1 = game::utils::board::getTile(Coordinate(0, 0), matrix, dimensions);
        const TileType* tile2 = game::utils::board::getTile(Coordinate(1, 1), matrix, dimensions);
        const TileType* tile3 = game::utils::board::getTile(Coordinate(2, 2), matrix, dimensions);

        EXPECT_EQ(*tile1, TileType::Empty);
        EXPECT_EQ(*tile2, TileType::Bomb);
        EXPECT_EQ(*tile3, TileType::Empty);
    }

    TEST(Board, change_tile_type_should_only_update_target_tile)
    {
        BoardDimensions dimensions(5, 5);
        utils::board::TileMatrix matrix;
        Board board(utils::board::TileMatrix(), BoardDimensions(5, 5));

        for (unsigned int x = 0; x < dimensions.x; ++x)
        {
            for (unsigned int y = 0; y < dimensions.y; ++y)
            {
                matrix[x][y] = TileType::Empty;
            }
        }

        board.changeTileType(Coordinate(1, 1), TileType::Empty);
        console::output::println(static_cast<int>(board.matrix()[1][1]));

        const TileType* tile1 = game::utils::board::getTile(Coordinate(1, 1), board.matrix(), board.dimensions());
        //const TileType* tile2 = game::utils::board::getTile(Coordinate(2, 3), board.matrix(), board.dimensions());

        //EXPECT_EQ(*tile1, TileType::Guess);
        EXPECT_EQ(*tile1, TileType::Empty);
    }

    TEST(Board, get_tiles_of_type_should_return_all_bombs)
    {
        BoardDimensions dimensions(4, 4);
        utils::board::TileMatrix matrix(4, std::vector<TileType>(4, TileType::Empty));

        matrix[0][1] = TileType::Bomb;
        matrix[1][3] = TileType::Bomb;
        matrix[3][2] = TileType::Bomb;

        Board board(matrix, dimensions);

        std::vector<Coordinate> bombTiles = board.getCoordinatesOfTileType(TileType::Bomb);

        EXPECT_EQ(bombTiles.size(), 3);

        bool foundCoord = false;
        for (auto const& tile : bombTiles)
        {
            if (tile.x == 1 && tile.y == 3)
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
        utils::board::TileMatrix matrix(1, std::vector<TileType>(1, TileType::Bomb));

        Board board(matrix, dimensions);

        EXPECT_EQ(board.dimensions().x, 1);
        EXPECT_EQ(board.dimensions().y, 1);
        EXPECT_EQ(board.getCoordinatesOfTileType(TileType::Bomb).size(), 1);
    }

    TEST(Board, constructor_should_create_an_empty_board)
    {
        BoardDimensions dimensions(0, 0);
        utils::board::TileMatrix matrix;

        Board board(matrix, dimensions);

        EXPECT_EQ(board.dimensions().x, 0);
        EXPECT_EQ(board.getCoordinatesOfTileType(TileType::Bomb).size(), 0);
    }
} 
