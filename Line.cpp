#include "Line.hpp"

Line::Line(sf::Vector2f position, sf::RectangleShape rect) : rect(rect)
{
    this->rect.setPosition(position);
}

sf::RectangleShape &Line::getRectangle()
{
    return this->rect;
}

void Line::update(sf::RenderWindow &window, sf::Vector2i m_prev)
{
    auto mousePos = sf::Mouse::getPosition(window);

    if (this->isSelected == true)
    {
        this->rect.setFillColor(sf::Color(35, 208, 217));
        if (mousePos != m_prev)
        {
            if (rect.getGlobalBounds().width > rect.getGlobalBounds().height)
            {
                //line is horizontal
                this->rect.move(0, sf::Vector2f(mousePos - m_prev).y * IMAGE_SCALE);
            }
            else
            {
                this->rect.move(sf::Vector2f(mousePos - m_prev).x * IMAGE_SCALE, 0);
            }
        }
    }
    else
    {
        this->rect.setFillColor(sf::Color::White);
    }
}

void Line::drawTo(sf::RenderWindow &window)
{
    window.draw(rect);
}

sf::Vector2i Line::getMidpoint()
{
    auto size = sf::Vector2f(this->rect.getGlobalBounds().width, this->rect.getGlobalBounds().height);
    auto pos = this->rect.getPosition();
    auto midpoint = sf::Vector2i(pos.x + (size.x / 2), pos.y + (size.y / 2));
    return midpoint;
}