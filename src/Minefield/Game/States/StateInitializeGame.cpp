#include <Minefield/Game/States/StateInitializeGame.h>
#include <Minefield/Game/States/StateGameUpdate.h>
#include <Minefield/Math/Math.h>

namespace game::utils::stateInitializeGame
{
unsigned int getMinesPerPlayer()
{
    constexpr unsigned int kMinMinesSize = 1;
    constexpr unsigned int kMaxMinesSize = 8;
    unsigned int minesPerPlayer = getValidatedIntFromRange("> Mines per Player: ", kMinMinesSize, kMaxMinesSize);

    console::output::println("Game Config: Mines set to ", minesPerPlayer, " per player");
    console::output::println();
    return minesPerPlayer;
}

unsigned int getValidatedIntFromRange(std::string const& inputMsg, unsigned int min, unsigned int max)
{
    unsigned int validatedValue = 0;
    bool isValueValidated = false;

    while (!isValueValidated)
    {
        console::output::print(inputMsg);
        validatedValue = console::input::readInt();
        isValueValidated = math::isUIntInRange(validatedValue, min, max);

        if (!isValueValidated)
        {
            console::output::println("X Invalid size. It must be between ", min, '-', max);
        }
    }
    return validatedValue;
}

Board createBoard()
{
    constexpr unsigned int kMinAxisSize = 2;
    constexpr unsigned int kMaxAxisSize = 50;
    unsigned int heightValue = stateInitializeGame::getValidatedIntFromRange("> Board Height: ", kMinAxisSize, kMaxAxisSize);
    unsigned int widthValue = stateInitializeGame::getValidatedIntFromRange("> Board Width: ", kMinAxisSize, kMaxAxisSize);

    game::utils::board::TileMatrix mMatrix{heightValue, std::vector<Tile>(widthValue)};
    for (unsigned int i = 0; i < heightValue; i++)
    {
        for (unsigned int j = 0; j < widthValue; j++)
        {
            mMatrix[i][j] = Tile{TileType::Empty, Coordinate{i, j}};
        }
    }

    console::output::println("Game Config: Board created (", heightValue, 'x', widthValue, ')');
    console::output::println();
    return game::Board{mMatrix, game::BoardDimensions{widthValue, heightValue}};
}

std::vector<Player> createPlayers(unsigned int minesPerPlayer)
{
    console::output::print("> Players Quantity: ");
    unsigned int size = console::input::readInt();
    std::vector<Player> players;
    std::string name;
    char inputPlayerAI = ' ';
    bool isPlayerAI = false;
    unsigned int botCount = 0;

    for (unsigned int i = 0; i < size; i++)
    {
        console::output::print("> Is Player ", (i + 1), " AI (Y/N): ");
        inputPlayerAI = console::input::readChar();
        if (inputPlayerAI == 'Y' || inputPlayerAI == 'y')
        {
            isPlayerAI = true;
            botCount++;
            name = std::string{"Bot "} + std::to_string(botCount);
            console::output::println(name, " created");
        }
        else
        {
            console::output::print("> Player ", (i + 1), " Name: ");
            name = console::input::readString();
        }

        console::output::println();
        players.push_back(Player{PlayerData(name, minesPerPlayer, isPlayerAI)});
    }
    console::output::println("Game Config: ", players.size(), " Players Created");
    console::output::println();
    return players;
}
} // namespace utils::stateInitializeGame

namespace game
{
    using namespace utils::stateInitializeGame;

    std::unique_ptr<State> StateInitializeGame::execute(GameContext& gameContext)
    {
        console::output::println("[GAME CONFIG]");

        Board board = createBoard();
        unsigned int minesPerPlayer = getMinesPerPlayer();
        std::vector<Player> players = createPlayers(minesPerPlayer);
        gameContext = GameContext(board, minesPerPlayer, players);

        console::input::pressEnterToContinue();

        return std::make_unique<StateGameUpdate>();
    }
}