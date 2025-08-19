#pragma once
#include <Minefield/Game/GameContext.h>
#include <Minefield/Console/Output.h>
#include <Minefield/Console/Input.h>
#include <memory>

namespace game
{
namespace state
{
enum class UserSelection
{
    INITIALIZE_GAME = 1,
    QUIT = 2
};

using PlayersMines = std::vector<std::pair<Player*, Coordinate>>;
using PlayersGuesses = std::vector<std::pair<Player const*, Coordinate>>;
using PlayersToRemove = std::vector<Player>;

NextState stateMainMenuUpdate(GameContext& gameContext);
NextState stateInitializeUpdate(GameContext& gameContext);
NextState stateGameUpdate(GameContext& gameContext);
} // namespace state
}