#pragma once
#include <Minefield/Game/State.h>

namespace game
{
namespace stateGameUpdate
{
    bool areEnoughTilesToPlay(GameContext const& gameContext);
    unsigned int calculateGuessesAverage(GameContext const& gameContext);
    bool validateCoordinates(std::vector<Coordinate> const& coordinates, std::string const& coordinateType, unsigned int coordinatesToValidate, GameContext const& gameContext);
    std::vector<Coordinate> getPlayerCoordinatesInput(std::string const& playerName, std::string const& coordinateType, unsigned int coordinatesToValidate, GameContext const& gameContext);

    void phaseSetMines(GameContext & gameContext);
    void phaseSetGuesses(GameContext & gameContext);
    void phaseSetTakenBoardTiles(GameContext & gameContext, state::PlayersMines & playersMines, state::PlayersGuesses & playersGuesses);
    int phaseCheckCollisions(GameContext & gameContext, state::PlayersMines const& playersMines, state::PlayersGuesses const& playersGuesses, state::PlayersToRemove& playersToRemove);
    bool phaseCheckGameState(GameContext & gameContext, int roundHits, std::vector<Player> const& playersToRemove);

} // namespace game::stateGameUpdate
}