#include <Minefield/Console/Input.h>
#include <Minefield/Console/Output.h>
#include <Minefield/Math/Math.h>
#include <Minefield/Game/States/StateGameUpdate.h>
#include <Minefield/Game/States/StateInitializeGame.h>

namespace game::state::initializeGame
{
NextState execute(GameContext& gameContext)
{
    console::output::println("[GAME CONFIG]");

    Board board = initializeGame::createBoard();
    unsigned int minesPerPlayer = initializeGame::getMinesPerPlayer();
    std::vector<Player> players = initializeGame::createPlayers(minesPerPlayer);
    gameContext = GameContext(board, minesPerPlayer, players);

    console::input::pressAnyKeyToContinue();

    return gameUpdate::execute(gameContext);
}

unsigned int getMinesPerPlayer()
{
    constexpr unsigned int kMinMinesSize = 1;
    constexpr unsigned int kMaxMinesSize = 8;
    unsigned int minesPerPlayer = getValidatedIntFromRange("Mines per Player: ", kMinMinesSize, kMaxMinesSize);

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
        validatedValue = console::input::readInput<int>(inputMsg);
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
    unsigned int heightValue = initializeGame::getValidatedIntFromRange("Board Height: ", kMinAxisSize, kMaxAxisSize);
    unsigned int widthValue = initializeGame::getValidatedIntFromRange("Board Width: ", kMinAxisSize, kMaxAxisSize);

    game::utils::board::TileMatrix mMatrix{heightValue, std::vector<TileType>(widthValue)};
    for (unsigned int i = 0; i < heightValue; i++)
    {
        for (unsigned int j = 0; j < widthValue; j++)
        {
            mMatrix[i][j] = TileType::Empty;
        }
    }

    console::output::println("Game Config: Board created (", heightValue, 'x', widthValue, ')');
    console::output::println();
    return game::Board{mMatrix, game::BoardDimensions{widthValue, heightValue}};
}

std::vector<Player> createPlayers(unsigned int minesPerPlayer)
{
    std::vector<Player> players;
    unsigned int size = 0;
    std::string name;
    char inputPlayerAI = ' ';
    bool isPlayerAI = false;
    unsigned int botCount = 0;

    size = console::input::readInput<int>("Players Quantity: ");
    console::output::println();

    for (unsigned int i = 0; i < size; i++)
    {
        bool validatedInput = false;

        while (!validatedInput)
        {
            inputPlayerAI = console::input::readInput<char>("Is Player ", (i + 1), " AI (Y/N): ");

            if (inputPlayerAI == 'Y' || inputPlayerAI == 'y')
            {
                validatedInput = true;
                isPlayerAI = true;
                botCount++;
                name = std::string{"Bot "} + std::to_string(botCount);
                console::output::println(name, " created");
            }
            else if (inputPlayerAI == 'N' || inputPlayerAI == 'n')
            {
                validatedInput = true;
                name = console::input::readInput<std::string>("> Player ", (i + 1), " Name: ");
            }
            else
            {
                console::output::println("Invalid input, please try again.");
            }
        }
        players.emplace_back(PlayerData(name, minesPerPlayer, isPlayerAI));

        console::output::println();
    }
    console::output::println("Game Config: ", players.size(), " Players Created");
    console::output::println();
    return players;
}
} // namespace game::state::initializeGame