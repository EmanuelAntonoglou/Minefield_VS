#include <memory>
#include <Minefield/Math/Math.h>
#include <Minefield/Game/GameContext.h>
#include <Minefield/Game/States/StateMainMenu.h>
#include <iostream>

int main()
{
    math::initializeRandomSeed();
    game::GameContext gameContext;
    
    do
    {
        gameContext.currentState = game::state::mainMenu::execute(gameContext);
    } while (gameContext.currentState.updateFunction != nullptr);

    return 0;
}
