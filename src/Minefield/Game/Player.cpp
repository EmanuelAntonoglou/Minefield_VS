#include <Game/Player.h>
#include <Console/Output.h>
#include <Console/Input.h>

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