#pragma once
#include "State.h"

namespace game
{
    class StateMainMenu : public State
    {
        public:
            StateMainMenu(GameContext gameContext) : State(gameContext) {}
            std::unique_ptr<State> execute() override;
            enum class UserSelection
            {
                INITIALIZE_GAME = 1,
                QUIT = 2
            };
    };
}