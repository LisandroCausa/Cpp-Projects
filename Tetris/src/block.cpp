#include "block.h"

block::block()
{
    color = sf::Color::Green;
    size = sf::Vector2f(30, 30);
    active = false;
}

int block::getSize()
{
    return static_cast<int>(size.x);
}

void block::draw(const float x, const float y, sf::RenderWindow& window)
{
    if (!active)
        return;
    sf::RectangleShape shape(size);
    shape.setFillColor(color);
    shape.setPosition(x, y);
    window.draw(shape);
}

void block::setColor(const int n_color)
{
    switch (n_color)
    {
    case 0:
        color = sf::Color(236, 237, 5);
        break;
    case 1:
        color = sf::Color(207, 4, 18);
        break;
    case 2:
        color = sf::Color(4, 4, 223);
        break;
    case 3:
        color = sf::Color(235, 158, 5);
        break;
    case 4:
        color = sf::Color(4, 212, 18);
        break;
    case 5:
        color = sf::Color(159, 4, 237);
        break;
    default:
        color = sf::Color(4, 237, 237);
    }
}

void block::setActive(const bool input)
{
    active = input;
}

bool block::getActive()
{
    return active;
}