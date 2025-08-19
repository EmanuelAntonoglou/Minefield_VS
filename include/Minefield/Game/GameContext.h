#pragma once
#include <vector>
#include <iostream>
#include "Board.h"
#include "Player.h"
#include <Minefield/Game/State.h>
#include <functional>

namespace game
{
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
}