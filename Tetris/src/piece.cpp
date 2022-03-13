#include "piece.h"

void piece::updateOffsets()
{
    switch (type)
    {
    case 0: // Square
        block_offset[0] = sf::Vector2i(0, 0);
        block_offset[1] = sf::Vector2i(1, 0);
        block_offset[2] = sf::Vector2i(0, 1);
        block_offset[3] = sf::Vector2i(1, 1);
        orientation = 0;
        break;
    case 1: // Z
        if (orientation == 1)
        {
            block_offset[0] = sf::Vector2i(2, 0);
            block_offset[1] = sf::Vector2i(2, 1);
            block_offset[2] = sf::Vector2i(1, 1);
            block_offset[3] = sf::Vector2i(1, 2);
        }
        else
        {
            block_offset[0] = sf::Vector2i(0, 1);
            block_offset[1] = sf::Vector2i(1, 1);
            block_offset[2] = sf::Vector2i(1, 2);
            block_offset[3] = sf::Vector2i(2, 2);
            orientation = 0;
        }
        break;
    case 2: // S
        if (orientation == 1)
        {
            block_offset[0] = sf::Vector2i(1, 0);
            block_offset[1] = sf::Vector2i(1, 1);
            block_offset[2] = sf::Vector2i(2, 1);
            block_offset[3] = sf::Vector2i(2, 2);
        }
        else
        {
            block_offset[0] = sf::Vector2i(0, 2);
            block_offset[1] = sf::Vector2i(1, 2);
            block_offset[2] = sf::Vector2i(1, 1);
            block_offset[3] = sf::Vector2i(2, 1);
            orientation = 0;
        }
        break;
    case 3: // L
        switch (orientation)
        {
        case 1:
            block_offset[0] = sf::Vector2i(0, 0);
            block_offset[1] = sf::Vector2i(1, 0);
            block_offset[2] = sf::Vector2i(1, 1);
            block_offset[3] = sf::Vector2i(1, 2);
            break;
        case 2:
            block_offset[0] = sf::Vector2i(2, 0);
            block_offset[1] = sf::Vector2i(0, 1);
            block_offset[2] = sf::Vector2i(1, 1);
            block_offset[3] = sf::Vector2i(2, 1);
            break;
        case 3:
            block_offset[0] = sf::Vector2i(2, 2);
            block_offset[1] = sf::Vector2i(1, 0);
            block_offset[2] = sf::Vector2i(1, 1);
            block_offset[3] = sf::Vector2i(1, 2);
            break;
        default:
            block_offset[0] = sf::Vector2i(0, 2);
            block_offset[1] = sf::Vector2i(0, 1);
            block_offset[2] = sf::Vector2i(1, 1);
            block_offset[3] = sf::Vector2i(2, 1);
            orientation = 0;
        }
        break;
    case 4: // inverted-L
        switch (orientation)
        {
        case 1:
            block_offset[0] = sf::Vector2i(0, 2);
            block_offset[1] = sf::Vector2i(1, 0);
            block_offset[2] = sf::Vector2i(1, 1);
            block_offset[3] = sf::Vector2i(1, 2);
            break;
        case 2:
            block_offset[0] = sf::Vector2i(0, 0);
            block_offset[1] = sf::Vector2i(0, 1);
            block_offset[2] = sf::Vector2i(1, 1);
            block_offset[3] = sf::Vector2i(2, 1);
            break;
        case 3:
            block_offset[0] = sf::Vector2i(2, 0);
            block_offset[1] = sf::Vector2i(1, 0);
            block_offset[2] = sf::Vector2i(1, 1);
            block_offset[3] = sf::Vector2i(1, 2);
            break;
        default:
            block_offset[0] = sf::Vector2i(2, 2);
            block_offset[1] = sf::Vector2i(0, 1);
            block_offset[2] = sf::Vector2i(1, 1);
            block_offset[3] = sf::Vector2i(2, 1);
            orientation = 0;
        }
        break;
    case 5: // Triangle
        switch (orientation)
        {
        case 1:
            block_offset[0] = sf::Vector2i(0, 1);
            block_offset[1] = sf::Vector2i(1, 0);
            block_offset[2] = sf::Vector2i(1, 1);
            block_offset[3] = sf::Vector2i(1, 2);
            break;
        case 2:
            block_offset[0] = sf::Vector2i(1, 0);
            block_offset[1] = sf::Vector2i(0, 1);
            block_offset[2] = sf::Vector2i(1, 1);
            block_offset[3] = sf::Vector2i(2, 1);
            break;
        case 3:
            block_offset[0] = sf::Vector2i(2, 1);
            block_offset[1] = sf::Vector2i(1, 0);
            block_offset[2] = sf::Vector2i(1, 1);
            block_offset[3] = sf::Vector2i(1, 2);
            break;
        default:
            block_offset[0] = sf::Vector2i(1, 2);
            block_offset[1] = sf::Vector2i(0, 1);
            block_offset[2] = sf::Vector2i(1, 1);
            block_offset[3] = sf::Vector2i(2, 1);
            orientation = 0;
        }
        break;
    default: // Stick
        if (orientation == 1)
        {
            block_offset[0] = sf::Vector2i(1, 0);
            block_offset[1] = sf::Vector2i(1, 1);
            block_offset[2] = sf::Vector2i(1, 2);
            block_offset[3] = sf::Vector2i(1, 3);
        }
        else
        {
            block_offset[0] = sf::Vector2i(0, 1);
            block_offset[1] = sf::Vector2i(1, 1);
            block_offset[2] = sf::Vector2i(2, 1);
            block_offset[3] = sf::Vector2i(3, 1);
            orientation = 0;
        }
    }
}

piece::piece(const int piece_type, const int block_size)
{
    blockSize = block_size;
    type = piece_type;
    position.x = 4;
    position.y = -1;
    for (int i{ 0 }; i < 4; ++i)
    {
        blocks[i].setActive(true);
        blocks[i].setColor(type);
    }
    updateOffsets();
}

void piece::draw(sf::RenderWindow& window)
{
    for (int i{ 0 }; i < 4; ++i)
    {
        blocks[i].draw(static_cast<float>((position.x + block_offset[i].x) * blockSize), static_cast<float>((position.y + block_offset[i].y) * blockSize), window);
    }
}

bool piece::update(const bool(&grid)[10][20])
{
    for (int i{ 0 }; i < 4; ++i)
    {
        if (position.y + block_offset[i].y + 1 > 19) // Index Error
        {
            return false;
        }
        else if (grid[position.x + block_offset[i].x][position.y + block_offset[i].y + 1] == true)
        {
            return false; // NOT SUCESS
        }
    }
    position.y++;
    return true; // SUCESS
}

void piece::turn(const bool(&grid)[10][20])
{
    ++orientation;
    updateOffsets();
    bool state{ true };
    int x{};
    int y{};
    for (int i{ 0 }; i < 4; ++i)
    {
        x = position.x + block_offset[i].x;
        y = position.y + block_offset[i].y;
        if (x < 0 || x > 9 || y < 0 || y > 19) // Index Error
        {
            state = false;
            break;
        }
        else if (grid[x][y] == true)
        {
            state = false;
            break;
        }
    }
    if (state == false)
    {
        if (orientation == 0)
        {
            if (type == 0 || type == 1 || type == 2 || type == 6)
            {
                orientation = 2;
            }
            else
            {
                orientation = 4;
            }
        }
        --orientation;
        updateOffsets();
    }
}

void piece::move(const bool direction, const bool(&grid)[10][20])
{
    bool state{ true };
    if (direction)
    {
        for (int i{ 0 }; i < 4; ++i)
        {
            if (position.x + block_offset[i].x + 1 > 9) // Index Error
            {
                state = false;
                break;
            }
            else if (grid[position.x + block_offset[i].x + 1][position.y + block_offset[i].y] == true)
            {
                state = false;
                break;
            }
        }
        if (state)
            position.x++;
    }
    else
    {
        for (int i{ 0 }; i < 4; ++i)
        {
            if (position.x + block_offset[i].x - 1 < 0) // Index Error
            {
                state = false;
                break;
            }
            else if (grid[position.x + block_offset[i].x - 1][position.y + block_offset[i].y] == true)
            {
                state = false; // NOT SUCESS
                break;
            }
        }
        if (state)
            position.x--;
    }
}