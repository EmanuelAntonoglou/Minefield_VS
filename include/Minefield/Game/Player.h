#pragma once
#include <string>
#include <vector>
#include <Minefield/Game/Coordinate.h>

namespace game
{
    class PlayerData
    {
    public:
        PlayerData() = default;
        PlayerData(std::string const &name, unsigned int minesLeft, bool isAI);
        bool operator==(const PlayerData &other) const
        {
            return this->name() == other.name();
        }

        inline const std::string &name() const noexcept { return mName; }
        inline unsigned int minesLeft() const noexcept { return mMinesLeft; }
        inline bool isAI() const noexcept { return mIsAI; }
        unsigned int reduceOneMine() noexcept;

    private:
        std::string mName;
        unsigned int mMinesLeft = 0;
        bool mIsAI = false;
    };

    struct Player
    {
        Player() = default;
        Player(PlayerData data) : data(data) {};
        bool operator==(const Player &other) const
        {
            return this->data == other.data;
        }
        
        PlayerData data;
        std::vector<Coordinate> minesCoordinates;
        std::vector<Coordinate> guessCoordinates;
    };
}