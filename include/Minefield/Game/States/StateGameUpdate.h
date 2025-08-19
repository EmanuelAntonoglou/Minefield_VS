#pragma once
#include <Minefield/Game/GameContext.h>

namespace game::state::gameUpdate
{
NextState execute(GameContext& gameContext);
bool areEnoughTilesToPlay(GameContext const& gameContext);
unsigned int calculateGuessesAverage(GameContext const& gameContext);
bool validateCoordinates(std::vector<Coordinate> const& coordinates, std::string const& coordinateType, unsigned int coordinatesToValidate, GameContext const& gameContext);
std::vector<Coordinate> getPlayerCoordinatesInput(std::string const& playerName, std::string const& coordinateType, unsigned int coordinatesToValidate, GameContext const& gameContext);

void phaseSetMines(GameContext& gameContext);
void phaseSetGuesses(GameContext& gameContext);
void phaseSetTakenBoardTiles(GameContext& gameContext, PlayersMines& playersMines, PlayersGuesses& playersGuesses);
int phaseCheckCollisions(GameContext& gameContext, PlayersMines const& playersMines, PlayersGuesses const& playersGuesses, PlayersToRemove& playersToRemove);
bool phaseCheckGameState(GameContext& gameContext, int roundHits, std::vector<Player> const& playersToRemove);

} // namespace game::state::gameUpdate
