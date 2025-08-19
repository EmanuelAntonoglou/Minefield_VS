#include <Minefield/Console/Input.h>
#include <Minefield/Console/Output.h>
#include <Minefield/Game/Player.h>

namespace game
{
PlayerData::PlayerData(std::string const& name, unsigned int minesLeft, bool isAI)
: mName(name)
, mMinesLeft(minesLeft)
, mIsAI(isAI)
{
}

unsigned int PlayerData::reduceOneMine() noexcept
{
    if (mMinesLeft > 0)
    {
        mMinesLeft--;
    }
    return mMinesLeft;
}
} // namespace game