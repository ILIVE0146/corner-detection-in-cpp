#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "gui/TextBox.hpp"
class errorMessage
{
private:
    std::string message;
    sf::Font font;
    bool isClosed = false;

public:
    errorMessage(std::string message, sf::Font &font);
    bool getIsclosed() { return isClosed; };
};
