#include <Minefield/Game/States/StateMainMenu.h>
#include <Minefield/Game/States/StateInitializeGame.h>

namespace game
{
    std::unique_ptr<State> StateMainMenu::execute()
    {
        console::output::println("[MAIN MENU]");
        console::output::println("Welcome to Game! Select an option to continue:");
        console::output::println("1. Start");
        console::output::println("2. Quit");
        console::output::print("> ");

        std::unique_ptr<State> nextState;
        UserSelection userSelection = static_cast<UserSelection>(console::input::readInt());
        console::output::println("");

        switch (userSelection)
        {
        case UserSelection::INITIALIZE_GAME:
            nextState = std::make_unique<StateInitializeGame>(mGameContext);
            break;
        case UserSelection::QUIT:
            nextState = nullptr;
            break;
        default:
            nextState = std::make_unique<StateMainMenu>(mGameContext);
            break;
        }
        return nextState;
    }
}