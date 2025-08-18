#include <memory>
#include <Minefield/Math/Math.h>
#include <Minefield/Game/States/StateMainMenu.h>

int main()
{
    math::initializeRandomSeed();
    game::GameContext gameContext;
    std::unique_ptr<game::State> currentState = std::make_unique<game::StateMainMenu>();

    while (currentState)
    {
        currentState = currentState->execute(gameContext);
    }

    return 0;
}