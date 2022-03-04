#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#include "globalVariables.hpp"

class Line
{
private:
    sf::RectangleShape rect;
    bool isSelected = false;

public:
    Line(sf::Vector2f position ,sf::RectangleShape rect);
    sf::RectangleShape &getRectangle();
    bool &getIsSelected()
    {
        return isSelected;
    };
    sf::Vector2i getMidpoint();
    void update(sf::RenderWindow &window, sf::Vector2i m_prev);
    void drawTo(sf::RenderWindow &window);
};
