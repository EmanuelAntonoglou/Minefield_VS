#pragma once
#include "State.h"

namespace game
{
    class StateInitializeGame : public State
    {
        public:
            StateInitializeGame(GameContext gameContext) : State(gameContext) {}
            std::unique_ptr<State> execute() override;
            std::vector<game::Player> createPlayers(unsigned int minesPerPlayer);
        private:
            Board createBoard();
            unsigned int getMinesPerPlayer();
            unsigned int getValidatedIntFromRange(std::string const& inputMsg, unsigned int min, unsigned int max);
    };
}