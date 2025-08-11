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
        State() = default;
        explicit State(GameContext gameContext);
        virtual ~State() = default;
        virtual std::unique_ptr<State> execute() = 0;

    protected:
        GameContext mGameContext;
    };
}