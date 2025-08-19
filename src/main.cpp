#include <memory>
#include <Minefield/Math/Math.h>
#include <Minefield/Game/State.h>
#include <iostream>

int main()
{
    math::initializeRandomSeed();
    game::GameContext gameContext;
    
    do
    {
        gameContext.currentState = game::state::stateMainMenuUpdate(gameContext);
    } while (gameContext.currentState.updateFunction != nullptr);

    return 0;
}
