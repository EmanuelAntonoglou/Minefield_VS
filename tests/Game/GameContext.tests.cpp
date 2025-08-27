#include <gtest/gtest.h>
#include <Minefield/Game/GameContext.h>

namespace game::tests
{
    TEST(GameContext, default_constructor_should_initialize_empty)
    {
        GameContext const context;

        EXPECT_EQ(context.minesPerPlayer, 0);
        EXPECT_TRUE(context.players.empty());
        EXPECT_EQ(context.currentState.updateFunction, nullptr);

        EXPECT_EQ(context.board.dimensions().x, 0);
        EXPECT_EQ(context.board.dimensions().y, 0);
    }

    TEST(GameContext, constructor_should_correctly_assign_members)
    {
        BoardDimensions dimensions(5, 5);
        utils::board::TileMatrix matrix(5, std::vector<Tile>(5));

        Board board(matrix, dimensions);
        unsigned int minesPerPlayer = 10;
        std::vector<Player> players = {Player(PlayerData("Player1", 10, false)), Player(PlayerData("Player2", 10, true))};

        GameContext const context(board, minesPerPlayer, players);

        EXPECT_EQ(context.board.dimensions().x, 5);
        EXPECT_EQ(context.board.dimensions().y, 5);
        EXPECT_EQ(context.players.size(), 2);
        EXPECT_EQ(context.players, players);
        EXPECT_EQ(context.minesPerPlayer, minesPerPlayer);
        EXPECT_EQ(context.currentState.updateFunction, nullptr);
    }

    TEST(GameContext, copy_constructor_should_create_deep_copy)
    {
        BoardDimensions dimensions(3, 3);
        std::vector<Player> players = {Player(PlayerData("SoloPlayer", 5, false))};
        Board board(utils::board::TileMatrix(3, std::vector<Tile>(3)), dimensions);        
        GameContext originalContext(board, 5, players);

        GameContext copiedContext(originalContext);

        // checking copiedContext
        EXPECT_EQ(originalContext.minesPerPlayer, copiedContext.minesPerPlayer);
        EXPECT_EQ(originalContext.players, copiedContext.players);
        EXPECT_EQ(originalContext.board.dimensions().x, copiedContext.board.dimensions().x);

        // modify the original
        originalContext.players.push_back(Player(PlayerData("AnotherPlayer", 5, false)));
        originalContext.minesPerPlayer = 99;

        // copiedContext should not have changed
        EXPECT_NE(originalContext.players.size(), copiedContext.players.size());
        EXPECT_EQ(copiedContext.players.size(), 1);
        EXPECT_NE(originalContext.minesPerPlayer, copiedContext.minesPerPlayer);
        EXPECT_EQ(copiedContext.minesPerPlayer, 5);
    }
    
    TEST(GameContext, assignment_operator_should_copy_state)
    {
        BoardDimensions dimensions(8, 8);
        Board board(utils::board::TileMatrix(8, std::vector<Tile>(8)), dimensions);
        std::vector<Player> players = {Player(PlayerData("SourcePlayer", 7, false))};
        GameContext sourceContext(board, 7, players);

        GameContext destinationContext;

        destinationContext = sourceContext;

        EXPECT_EQ(destinationContext.minesPerPlayer, 7);
        EXPECT_EQ(destinationContext.players, sourceContext.players);
        EXPECT_EQ(destinationContext.board.dimensions().x, 8);
    }
}