#include <Minefield/Game/Player.h>
#include <Minefield/Console/Output.h>
#include <Minefield/Console/Input.h>

namespace game
{
    PlayerData::PlayerData(std::string const& name, unsigned int minesLeft, bool isAI) : mName(name), mMinesLeft(minesLeft), mIsAI(isAI) {}

    unsigned int PlayerData::reduceOneMine() noexcept
    {
        if (mMinesLeft > 0)
        {
            mMinesLeft--;
        }
        return mMinesLeft;
    }
}