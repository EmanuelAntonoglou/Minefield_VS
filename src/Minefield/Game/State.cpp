#include <Minefield/Game/State.h>
#include <Minefield/Game/GameContext.h>
#include <Minefield/Game/States/StateInitializeGame.h>
#include <Minefield/Game/States/StateGameUpdate.h>

namespace game::state
{
NextState stateMainMenuUpdate(GameContext& gameContext)
{
    console::output::println("[MAIN MENU]");
    console::output::println("Welcome to Game! Select an option to continue:");
    console::output::println("1. Start");
    console::output::println("2. Quit");
    console::output::print("> ");

    NextState nextState = {nullptr};
    auto userSelection = static_cast<UserSelection>(console::input::readInt());
    console::output::println("");

    switch (userSelection)
    {
    case UserSelection::INITIALIZE_GAME:
        nextState = stateInitializeUpdate(gameContext);
        break;
    case UserSelection::QUIT:
        nextState = {nullptr};
        break;
    default:
        nextState = stateMainMenuUpdate(gameContext);
        break;
    }
    return nextState;
}

NextState stateInitializeUpdate(GameContext& gameContext)
{
    console::output::println("[GAME CONFIG]");

    Board board = stateInitializeGame::createBoard();
    unsigned int minesPerPlayer = stateInitializeGame::getMinesPerPlayer();
    std::vector<Player> players = stateInitializeGame::createPlayers(minesPerPlayer);
    gameContext = GameContext(board, minesPerPlayer, players);

    console::input::pressEnterToContinue();

    return stateGameUpdate(gameContext);
}

NextState stateGameUpdate(GameContext& gameContext)
{
    bool hasGameEnded = false;
    unsigned int roundCount = 1;
    int roundHits = -1;
    PlayersMines playersMines;
    PlayersGuesses playersGuesses;
    PlayersToRemove playersToRemove;

    if (stateGameUpdate::phaseCheckGameState(gameContext, roundHits, playersToRemove))
    {
        return stateMainMenuUpdate(gameContext);
    }

    console::output::println("[GAME STARTED]");
    while (!hasGameEnded)
    {
        console::output::println("[Round ", roundCount, ']');

        stateGameUpdate::phaseSetMines(gameContext);
        stateGameUpdate::phaseSetGuesses(gameContext);
        stateGameUpdate::phaseSetTakenBoardTiles(gameContext, playersMines, playersGuesses);
        roundHits = stateGameUpdate::phaseCheckCollisions(gameContext, playersMines, playersGuesses, playersToRemove);
        hasGameEnded = stateGameUpdate::phaseCheckGameState(gameContext, roundHits, playersToRemove);

        console::input::pressEnterToContinue();

        playersMines.clear();
        playersGuesses.clear();
        playersToRemove.clear();
        roundHits = 0;
        roundCount++;
    }

    return stateMainMenuUpdate(gameContext);
}
}