#pragma once
#include <SFML/Graphics.hpp>

class block {
private:
    sf::Color color;
    sf::Vector2f size;
    bool active;
public:

    block();

    int getSize();
    void draw(const float x, const float y, sf::RenderWindow& window);
    void setColor(const int n_color);
    void setActive(const bool input);
    bool getActive();
};