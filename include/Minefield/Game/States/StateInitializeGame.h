#pragma once
#include <Minefield/Game/State.h>

namespace game::stateInitializeGame
{
Board createBoard();
unsigned int getMinesPerPlayer();
unsigned int getValidatedIntFromRange(std::string const& inputMsg, unsigned int min, unsigned int max);
std::vector<game::Player> createPlayers(unsigned int minesPerPlayer);
} // namespace game::stateInitializeGame