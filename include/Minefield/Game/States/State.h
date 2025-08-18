#pragma once
#include <Minefield/Game/GameContext.h>
#include <Minefield/Console/Output.h>
#include <Minefield/Console/Input.h>
#include <memory>

namespace game
{
    class State
    {
    public:
        virtual ~State() = default;
        virtual std::unique_ptr<State> execute(GameContext& gameContext) = 0;
    };
}