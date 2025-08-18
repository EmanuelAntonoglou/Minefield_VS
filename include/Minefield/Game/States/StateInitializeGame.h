#pragma once
#include "State.h"

namespace game
{
    class StateInitializeGame : public State
    {
        public:
            std::unique_ptr<State> execute(GameContext& gameContext) override;
    };

    namespace utils::stateInitializeGame
    {
        Board createBoard();
        unsigned int getMinesPerPlayer();
        unsigned int getValidatedIntFromRange(std::string const& inputMsg, unsigned int min, unsigned int max);
        std::vector<game::Player> createPlayers(unsigned int minesPerPlayer);
    }
}