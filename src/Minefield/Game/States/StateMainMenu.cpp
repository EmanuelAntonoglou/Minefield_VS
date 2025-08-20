#include <Minefield/Console/Input.h>
#include <Minefield/Console/Output.h>
#include <Minefield/Game/States/StateInitializeGame.h>
#include <Minefield/Game/States/StateMainMenu.h>

namespace game::state::mainMenu
{
NextState execute(GameContext& gameContext)
{
    NextState nextState = {nullptr};

    console::output::println("[MAIN MENU]");
    console::output::println("Welcome to Game! Select an option to continue:");
    console::output::println("1. Start");
    console::output::println("2. Quit");
    console::output::println();
    auto userSelection = static_cast<UserSelection>(console::input::readInput<int>());
    console::output::clearBuffer();

    switch (userSelection)
    {
    case UserSelection::INITIALIZE_GAME:
        nextState = state::initializeGame::execute(gameContext);
        break;
    case UserSelection::QUIT:
        nextState = {nullptr};
        break;
    default:
        nextState = state::mainMenu::execute(gameContext);
        break;
    }
    return nextState;
}
} // namespace game::state::mainMenu