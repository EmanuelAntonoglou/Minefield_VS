#include <gtest/gtest.h>
#include <Minefield/Game/Player.h>

namespace game::tests
{
    class PlayerDataTestSuite : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            playerData = PlayerData("TestPlayer", 5, false);
        }

        PlayerData playerData;
    };

    TEST_F(PlayerDataTestSuite, constructor_should_set_all_values)
    {
        EXPECT_EQ(playerData.name(), "TestPlayer");
        EXPECT_EQ(playerData.minesLeft(), 5);
        EXPECT_FALSE(playerData.isAI());
    }

    TEST_F(PlayerDataTestSuite, reduceOneMine_should_decrease_mines_only_above_zero)
    {
        unsigned int minesAfterReduction = playerData.reduceOneMine();

        EXPECT_EQ(minesAfterReduction, 4);
        EXPECT_EQ(playerData.minesLeft(), 4);
    }

    TEST_F(PlayerDataTestSuite, reduceOneMine_should_not_go_below_zero)
    {
        playerData = PlayerData("TestPlayer", 1, false);

        playerData.reduceOneMine(); // 0
        unsigned int minesAfterSecondReduction = playerData.reduceOneMine(); // 0 ? or uint max?

        EXPECT_EQ(minesAfterSecondReduction, 0);
        EXPECT_EQ(playerData.minesLeft(), 0);
    }
}
