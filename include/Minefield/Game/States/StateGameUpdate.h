#pragma once
#include "State.h"

namespace game 
{
    class StateGameUpdate : public State 
    {
        using PlayersMines = std::vector<std::pair<Player *, Coordinate>>;
        using PlayersGuesses = std::vector<std::pair<const Player *, Coordinate>>;

        public:
            StateGameUpdate(GameContext gameContext) : State(gameContext) {}
            std::unique_ptr<State> execute() override;
        
        private:
            std::vector<Coordinate> getPlayerCoordinatesInput(std::string const& playerName, std::string const& coordinateType, unsigned int coordinatesToValidate);
            bool validateCoordinates(std::vector<Coordinate> const& coordinates, std::string const& coordinateType, unsigned int coordinatesToValidate);
            unsigned int calculateGuessesAverage();
            void phaseSetMines();
            void phaseSetGuesses();
            void phaseSetTakenBoardTiles(PlayersMines& playersMines, PlayersGuesses& playersGuesses);
            bool phaseCheckCollisions(PlayersMines const& playersMines, PlayersGuesses const& playersGuesses, std::vector<Player>& playersToRemove);
            bool phaseCheckGameState(int roundHits, std::vector<Player> const& playersToRemove);
            bool areEnoughTilesToPlay();
    };
}