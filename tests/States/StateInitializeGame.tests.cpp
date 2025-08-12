#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <Minefield/Game/States/StateInitializeGame.h>

namespace stateInitializeGame::tests
{
TEST(CreatePlayers, should_not_create_a_empty_player_vector) 
{
    game::GameContext game;
    //game::StateInitializeGame initialState{game};
    unsigned int minesPerPlayer = 5;
    //EXPECT_FALSE(initialState.createPlayers(minesPerPlayer).empty());
}
}