#include <Minefield/Console/Input.h>
#include <Minefield/Console/Output.h>
#include <Minefield/Game/States/StateGameUpdate.h>
#include <Minefield/Game/States/StateMainMenu.h>
#include <Minefield/Math/Math.h>

#include <algorithm>
#include <vector>

namespace game::state::gameUpdate
{
NextState execute(GameContext& gameContext)
{
    bool hasGameEnded = false;
    unsigned int roundCount = 1;
    int roundHits = -1;
    PlayersMines playersMines;
    PlayersGuesses playersGuesses;
    PlayersToRemove playersToRemove;

    if (gameUpdate::phaseCheckGameState(gameContext, roundHits, playersToRemove))
    {
        return mainMenu::execute(gameContext);
    }

    console::output::println("[GAME STARTED]");
    while (!hasGameEnded)
    {
        console::output::println("[Round ", roundCount, ']');

        gameUpdate::phaseSetMines(gameContext);
        gameUpdate::phaseSetGuesses(gameContext);
        gameUpdate::phaseSetTakenBoardTiles(gameContext, playersMines, playersGuesses);
        roundHits = gameUpdate::phaseCheckCollisions(gameContext, playersMines, playersGuesses, playersToRemove);
        hasGameEnded = gameUpdate::phaseCheckGameState(gameContext, roundHits, playersToRemove);

        console::input::pressAnyKeyToContinue();

        playersMines.clear();
        playersGuesses.clear();
        playersToRemove.clear();
        roundCount++;
    }

    return mainMenu::execute(gameContext);
}

bool areEnoughTilesToPlay(GameContext const& gameContext)
{
    unsigned int avaliableTiles = gameContext.board.getCoordinatesOfTileType(TileType::Empty).size();
    unsigned int playersQuantity = gameContext.players.size();
    unsigned int guessesforNextRound = calculateGuessesAverage(gameContext);
    return (avaliableTiles > (playersQuantity * guessesforNextRound));
}

unsigned int calculateGuessesAverage(GameContext const& gameContext)
{
    if (gameContext.players.empty())
    {
        return 0;
    }

    unsigned int average = 0;
    for (auto const& player : gameContext.players)
    {
        average += player.data.minesLeft();
    }

    return (average / gameContext.players.size());
}

bool validateCoordinates(std::vector<Coordinate> const& coordinates, std::string const& coordinateType, unsigned int coordinatesToValidate, GameContext const& gameContext)
{
    if (coordinates.empty())
    {
        console::output::println("X No valid coordinates. Please use this format: X,Y X,Y...");
        return false;
    }
    else if (coordinates.size() < coordinatesToValidate)
    {
        console::output::println("X Too few coordinates. Use your ", coordinatesToValidate, ' ', coordinateType);
        return false;
    }
    else if (coordinates.size() > coordinatesToValidate)
    {
        console::output::println("X Too many coordinates. You have only ", coordinatesToValidate, ' ', coordinateType);
        return false;
    }

    for (auto const& coordinate : coordinates)
    {
        TileType const* tile = utils::board::getTile(Coordinate{coordinate.x, coordinate.y}, gameContext.board.matrix(), gameContext.board.dimensions());
        if (tile == nullptr)
        {
            console::output::println("X Some ", coordinateType, " are placed beyond board dimensions. Please place them between x(1,",
                gameContext.board.dimensions().x, ") and y(1,", gameContext.board.dimensions().y, ")");
            return false;
        }
        else if (*tile == TileType::Taken || *tile == TileType::Bomb)
        {
            console::output::println("X Some ", coordinateType, " are placed in taken or exploded tiles. Please place in free spaces");
            return false;
        }
    }
    return true;
}

std::vector<Coordinate> getPlayerCoordinatesInput(std::string const& playerName, std::string const& coordinateType, unsigned int coordinatesToValidate, GameContext const& gameContext)
{
    bool inputValidated = false;
    std::string inputStr;
    std::vector<Coordinate> coordinates;

    console::output::println("Set your ", coordinateType, " in this format: X,Y X,Y...");
    while (!inputValidated)
    {
        gameContext.board.print();
        inputStr = console::input::readInput<std::string>(playerName, "'s " + coordinateType, " (", coordinatesToValidate, " Left): ");
        coordinates = parseCoordinates(inputStr);
        inputValidated = state::gameUpdate::validateCoordinates(coordinates, coordinateType, coordinatesToValidate, gameContext);
    }
    return coordinates;
}

void phaseSetMines(GameContext& gameContext)
{
    for (auto& player : gameContext.players)
    {
        std::vector<Coordinate> minesCoordinates;
        if (!player.data.isAI())
        {
            minesCoordinates = state::gameUpdate::getPlayerCoordinatesInput(player.data.name(), "mines", player.data.minesLeft(), gameContext);
            console::output::println(minesCoordinates[0].x, ',', minesCoordinates[0].y);
        }
        else
        {
            std::vector<Coordinate> tiles = gameContext.board.getCoordinatesOfTileType(TileType::Empty);
            for (unsigned int i = 0; i < player.data.minesLeft(); i++)
            {
                unsigned int randomNumber = math::getRandomNumber(0, tiles.size() - 1);
                minesCoordinates.emplace_back(tiles[randomNumber]);
                console::output::println(minesCoordinates[0].x, ',', minesCoordinates[0].y);
            }
            console::output::println(player.data.name(), " has sets its mines");
        }
        player.minesCoordinates = minesCoordinates;

        console::input::pressAnyKeyToContinue();
    }
}

void phaseSetGuesses(GameContext& gameContext)
{
    unsigned int guessesAvr = state::gameUpdate::calculateGuessesAverage(gameContext);

    for (auto& player : gameContext.players)
    {
        std::vector<Coordinate> guessesCoordinates;
        if (!player.data.isAI())
        {
            guessesCoordinates = state::gameUpdate::getPlayerCoordinatesInput(player.data.name(), "guesses", guessesAvr, gameContext);
        }
        else
        {
            std::vector<Coordinate> tiles = gameContext.board.getCoordinatesOfTileType(TileType::Empty);
            for (unsigned int i = 0; i < guessesAvr; i++)
            {
                unsigned int randomNumber = math::getRandomNumber(0, tiles.size() - 1);
                guessesCoordinates.emplace_back(tiles[randomNumber]);
            }
            console::output::println(player.data.name(), " has sets its guesses");
        }
        player.guessCoordinates = guessesCoordinates;

        console::input::pressAnyKeyToContinue();
    }
}

void phaseSetTakenBoardTiles(GameContext& gameContext, PlayersMines& playersMines, PlayersGuesses& playersGuesses)
{
    for (auto& player : gameContext.players)
    {
        auto const& mines = player.minesCoordinates;
        for (auto const& mine : mines)
        {
            playersMines.emplace_back(&player, mine);
        }

        auto const& guesses = player.guessCoordinates;
        for (auto const& guess : guesses)
        {
            playersGuesses.emplace_back(&player, guess);
            gameContext.board.changeTileType(Coordinate{guess.x, guess.y}, TileType::Taken);
        }
    }
}

int phaseCheckCollisions(GameContext& gameContext, PlayersMines const& playersMines, PlayersGuesses const& playersGuesses, PlayersToRemove& playersToRemove)
{
    unsigned int roundHits = 0;
    for (auto const& guess : playersGuesses)
    {
        for (auto const& mine : playersMines)
        {
            if (guess.second == mine.second)
            {
                console::output::println(guess.first->data.name(), " hit ", mine.first->data.name(), "'s mine at ", (mine.second.x + 1), ',', (mine.second.y + 1));
                gameContext.board.changeTileType(Coordinate{mine.second.x, mine.second.y}, TileType::Bomb);
                roundHits++;

                if (mine.first->data.reduceOneMine() == 0)
                {
                    playersToRemove.emplace_back(*mine.first);
                };
            }
            // TODO: check mine collisions are in the same tile
        }
    }
    return roundHits;
}

bool phaseCheckGameState(GameContext& gameContext, int roundHits, std::vector<Player> const& playersToRemove)
{
    if (roundHits == 0)

    {
        gameContext.board.print();
        console::output::println("No mines were hit this round");
    }
    else
    {
        for (auto const& playerToRemove : playersToRemove)
        {
            console::output::println(playerToRemove.data.name(), " Loses");
            std::erase(gameContext.players, playerToRemove);
        }

        if (gameContext.players.size() == 1)
        {
            console::output::println("Game Ended: ", gameContext.players.front().data.name(), " Wins");
            return true;
        }
        else if (gameContext.players.empty())
        {
            console::output::println("Game Ended: Draw");
            return true;
        }
        else if (!state::gameUpdate::areEnoughTilesToPlay(gameContext))
        {
            console::output::println("Not enough tiles to play");
            console::output::println("Game Ended: Draw");
            console::output::println();
            return true;
        }
    }
    return false;
}
} // namespace game::state::gameUpdate