#pragma once
#include "State.h"

namespace game
{
class StateGameUpdate : public State
{
    using PlayersMines = std::vector<std::pair<Player*, Coordinate>>;
    using PlayersGuesses = std::vector<std::pair<Player const*, Coordinate>>;

public:
    StateGameUpdate(GameContext gameContext) : State(gameContext) {}
    std::unique_ptr<State> execute() override;

private:
    void phaseSetMines();
    void phaseSetGuesses();
    void phaseSetTakenBoardTiles(PlayersMines& playersMines, PlayersGuesses& playersGuesses);
    int phaseCheckCollisions(PlayersMines const& playersMines, PlayersGuesses const& playersGuesses, std::vector<Player>& playersToRemove);
    bool phaseCheckGameState(int roundHits, std::vector<Player> const& playersToRemove);
};
} // namespace game

namespace game::utils::stateGameUpdate
{
bool areEnoughTilesToPlay(GameContext const& gameContext);
unsigned int calculateGuessesAverage(GameContext const& gameContext);
bool validateCoordinates(std::vector<Coordinate> const& coordinates, std::string const& coordinateType, unsigned int coordinatesToValidate, GameContext const& gameContext);
std::vector<Coordinate> getPlayerCoordinatesInput(std::string const& playerName, std::string const& coordinateType, unsigned int coordinatesToValidate, GameContext const& gameContext);
} // namespace game::utils::stateGameUpdate