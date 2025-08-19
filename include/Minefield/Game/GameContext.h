#pragma once
#include "Board.h"
#include "Player.h"

#include <functional>
#include <iostream>
#include <vector>

namespace game
{
using PlayersMines = std::vector<std::pair<Player*, Coordinate>>;
using PlayersGuesses = std::vector<std::pair<Player const*, Coordinate>>;
using PlayersToRemove = std::vector<Player>;

struct GameContext;

struct NextState
{
    std::function<NextState(GameContext&)> updateFunction = nullptr;
};

struct GameContext
{
    GameContext() = default;
    GameContext(Board board, unsigned int minesPerPlayer, std::vector<Player> players)
    : board(board)
    , minesPerPlayer(minesPerPlayer)
    , players(players) {};
    GameContext& operator=(GameContext const& otherGameContext) = default;
    GameContext(GameContext const& otherGameContext) = default;
    ~GameContext() noexcept = default;

    Board board;
    std::vector<Player> players;
    unsigned int minesPerPlayer = 0;
    NextState currentState;
};
} // namespace game