#pragma once
#include <Minefield/Game/GameContext.h>
#include <Minefield/Game/Board.h>
#include <Minefield/Game/Player.h>

namespace game::state::initializeGame
{
NextState execute(GameContext& gameContext);
Board createBoard();
unsigned int getMinesPerPlayer();
unsigned int getValidatedIntFromRange(std::string const& inputMsg, unsigned int min, unsigned int max);
std::vector<Player> createPlayers(unsigned int minesPerPlayer);
} // namespace game::state::initializeGame