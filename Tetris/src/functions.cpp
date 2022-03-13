#include "functions.h"

int get_randomPieceNumber(const int maxPossibleNumber)
{
    return rand() % maxPossibleNumber;
}

int get_updateTime(const float seconds)
{
    if (seconds > 1000)
        return 25;
    return int(25 + ((seconds - 1000) * (seconds - 1000)) * 0.0007);
}

int increaseScore(const float seconds)
{
    return int(1 + ((seconds * seconds) * 0.001));
}

sf::String toString(const long long input)
{
    std::ostringstream ss;
    ss << input;
    return ss.str();
}

void drawGrid(block(&grid)[10][20], const int blockSize, const int pixelsBetweenBlocks, sf::RenderWindow& window)
{
    for (int x{ 0 }; x < 10; ++x)
        for (int y{ 0 }; y < 20; ++y)
            grid[x][y].draw(static_cast<float>(x * (blockSize + pixelsBetweenBlocks)), static_cast<float>(y * (blockSize + pixelsBetweenBlocks)), window);
}

bool isAnyKeyPressed()
{
    for (int k{ -1 }; k < sf::Keyboard::KeyCount; ++k)
    {
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(k)))
            return true;
    }
    return false;
}

void getNewPiece(piece& player, piece& staticPiece, int& nextPieceNumber, const sf::Vector2i staticPiece_position, const int blockSize, const int pixelsBetweenBlocks)
{
    player = piece(nextPieceNumber, blockSize + pixelsBetweenBlocks);
    nextPieceNumber = get_randomPieceNumber();
    staticPiece = piece(nextPieceNumber, blockSize + pixelsBetweenBlocks);
    staticPiece.position = staticPiece_position;
}