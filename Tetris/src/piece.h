#pragma once
#include "block.h"

class piece
{
private:
    int blockSize;
    int type;
    int orientation{ 0 };

    void updateOffsets();

public:
    block blocks[4];
    sf::Vector2i block_offset[4];
    sf::Vector2i position;

    piece(const int piece_type, const int block_size);

    void draw(sf::RenderWindow& window);
    bool update(const bool (&grid)[10][20]);
    void turn(const bool (&grid)[10][20]);
    void move(const bool direction, const bool(&grid)[10][20]);
};