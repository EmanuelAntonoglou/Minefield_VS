#pragma once
#include "State.h"

namespace game
{
    class StateMainMenu : public State
    {
        public:
            std::unique_ptr<State> execute(GameContext& gameContext) override;
            enum class UserSelection
            {
                INITIALIZE_GAME = 1,
                QUIT = 2
            };
    };
}