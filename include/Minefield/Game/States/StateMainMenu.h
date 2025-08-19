#pragma once
#include <Minefield/Game/GameContext.h>

namespace game::state::mainMenu
{
NextState execute(GameContext& gameContext);

enum class UserSelection
{
    INITIALIZE_GAME = 1,
    QUIT = 2
};
} // namespace game::state::mainMenu