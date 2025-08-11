#include <Minefield/Game/States/StateGameUpdate.h>
#include <Minefield/Game/States/StateMainMenu.h>
#include <vector>
#include <algorithm>
#include <Minefield/Math/Math.h>

namespace game
{
    std::unique_ptr<State> StateGameUpdate::execute()
    {
        bool hasGameEnded = false;
        unsigned int roundCount = 1;
        int roundHits = -1;
        std::vector<std::pair<Player *, Coordinate>> playersMines;
        std::vector<std::pair<const Player *, Coordinate>> playersGuesses;
        std::vector<Player> playersToRemove;

        if (phaseCheckGameState(roundHits, playersToRemove))
        {
            return std::make_unique<StateMainMenu>(mGameContext);
        }

        console::output::println("[GAME STARTED]");
        while (!hasGameEnded)
        {
            console::output::println("[Round ", roundCount, ']');
            
            phaseSetMines();
            phaseSetGuesses();
            phaseSetTakenBoardTiles(playersMines, playersGuesses);
            roundHits = phaseCheckCollisions(playersMines, playersGuesses, playersToRemove);
            hasGameEnded = phaseCheckGameState(roundHits, playersToRemove);

            console::input::pressEnterToContinue();
            //FIXME: Guesses duplicate sometimes

            playersMines.clear();
            playersGuesses.clear();
            playersToRemove.clear();
            roundHits = 0;
            roundCount++;
        }
        return std::make_unique<StateMainMenu>(mGameContext);
    }

    void StateGameUpdate::phaseSetMines()
    {
        for (auto &player : mGameContext.players)
        {
            std::vector<Coordinate> minesCoordinates;
            if (!player.data.isAI())
            {
                minesCoordinates = getPlayerCoordinatesInput(player.data.name(), "mines", player.data.minesLeft());
            }
            else 
            {
                std::vector<Tile> tiles = mGameContext.board.getTilesOfType(TileType::Empty);
                for (unsigned int i = 0; i < player.data.minesLeft(); i++)
                {
                    unsigned int randomNumber = math::getRandomNumber(0, tiles.size()-1);
                    minesCoordinates.emplace_back(tiles[randomNumber].coordinate);
                }
                console::output::println(player.data.name(), " has sets its mines");
            }
            player.minesCoordinates = minesCoordinates;

            console::input::pressEnterToContinue();
        }
    }

    void StateGameUpdate::phaseSetGuesses()
    {
        unsigned int guessesAvr = calculateGuessesAverage();
        
        for (auto &player : mGameContext.players)
        {
            std::vector<Coordinate> guessesCoordinates;
            if (!player.data.isAI())
            {
                guessesCoordinates = getPlayerCoordinatesInput(player.data.name(), "guesses", guessesAvr);
            }
            else 
            {
                std::vector<Tile> tiles = mGameContext.board.getTilesOfType(TileType::Empty);
                for (unsigned int i = 0; i < guessesAvr; i++)
                {
                    unsigned int randomNumber = math::getRandomNumber(0, tiles.size()-1);
                    guessesCoordinates.emplace_back(tiles[randomNumber].coordinate);
                }
                console::output::println(player.data.name(), " has sets its guesses");
            }
            player.guessCoordinates = guessesCoordinates;

            console::input::pressEnterToContinue();
        }
    }

    void StateGameUpdate::phaseSetTakenBoardTiles(PlayersMines& playersMines, PlayersGuesses& playersGuesses)
    {
        for (auto &player : mGameContext.players)
        {
            const auto &mines = player.minesCoordinates;
            for (auto &mine : mines)
            {
                playersMines.emplace_back(&player, mine);
            }

            const auto &guesses = player.guessCoordinates;
            for (auto &guess : guesses)
            {
                playersGuesses.emplace_back(&player, guess);
                mGameContext.board.changeTileType(Coordinate{guess.x, guess.y}, TileType::Taken);
            }
        }
    }

    bool StateGameUpdate::phaseCheckCollisions(PlayersMines const& playersMines, PlayersGuesses const& playersGuesses, std::vector<Player>& playersToRemove)
    {
        unsigned int roundHits = 0;
        for (auto const& guess : playersGuesses)
        {
            for (auto const& mine : playersMines)
            {
                if (guess.second == mine.second)
                {
                    console::output::println(guess.first->data.name(), " hit ", mine.first->data.name(), "'s mine at ", (mine.second.x + 1), ',', (mine.second.y + 1));
                    mGameContext.board.changeTileType(Coordinate{mine.second.x, mine.second.y}, TileType::Bomb);
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

    bool StateGameUpdate::phaseCheckGameState(int roundHits, std::vector<Player> const& playersToRemove)
    {
        if (roundHits == 0)
        {
            mGameContext.board.print();
            console::output::println("No mines were hit this round");
        }
        else
        {
            for (auto const& playerToRemove : playersToRemove)
            {
                console::output::println(playerToRemove.data.name(), " Loses");
                std::erase(mGameContext.players, playerToRemove);
            }

            if (mGameContext.players.size() == 1)
            {
                console::output::println("Game Ended: ", mGameContext.players.front().data.name(), " Wins");
                return true;
            }
            else if (mGameContext.players.empty())
            {
                console::output::println("Game Ended: Draw");
                return true;
            }
            else if (!areEnoughTilesToPlay())
            {
                console::output::println("Not enough tiles to play");
                console::output::println("Game Ended: Draw");
                console::output::println();
                return true;
            }
        }
        return false;
    }

    bool StateGameUpdate::areEnoughTilesToPlay()
    {
        unsigned int avaliableTiles = mGameContext.board.getTilesOfType(TileType::Empty).size();
        unsigned int playersQuantity = mGameContext.players.size();
        unsigned int guessesforNextRound = calculateGuessesAverage();
        return (avaliableTiles > (playersQuantity * guessesforNextRound));
    }

    std::vector<Coordinate> StateGameUpdate::getPlayerCoordinatesInput(std::string const& playerName, std::string const& coordinateType, unsigned int coordinatesToValidate)
    {
        bool inputValidated = false;
        std::string inputStr;
        std::vector<Coordinate> coordinates;
        
        console::output::println("Set your ", coordinateType, " in this format: X,Y X,Y...");
        while (!inputValidated)
        {
            mGameContext.board.print();
            console::output::print("> ", playerName, "'s " + coordinateType, " (", coordinatesToValidate, " Left): ");
            inputStr = console::input::readString();
            coordinates = parseCoordinates(inputStr);
            console::output::clearBuffer();
            inputValidated = validateCoordinates(coordinates, coordinateType, coordinatesToValidate);
        }
        return coordinates;
    }

    bool StateGameUpdate::validateCoordinates(std::vector<Coordinate> const& coordinates, std::string const& coordinateType, unsigned int coordinatesToValidate)
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

        for (auto const &coordinate : coordinates)
        {
            const TileType *tile = mGameContext.board.getTile(Coordinate{coordinate.x, coordinate.y});
            if (tile == nullptr)
            {
                console::output::println("X Some ", coordinateType, " are placed beyond board dimensions. Please place them between x(1,", mGameContext.board.dimensions().x, ") and y(1,", mGameContext.board.dimensions().y, ")");
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

    unsigned int StateGameUpdate::calculateGuessesAverage()
    {
        if (mGameContext.players.empty())
        {
            return 0;
        }

        unsigned int average = 0;
        for (auto const& player : mGameContext.players)
        {
            average += player.data.minesLeft();
        }

        return (average/mGameContext.players.size());
    }
}