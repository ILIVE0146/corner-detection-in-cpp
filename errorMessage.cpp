#include "errorMessage.hpp"

errorMessage::errorMessage(std::string message, sf::Font &font) : message(message), font(font)
{
    sf::RenderWindow window(sf::VideoMode(300, 200), "ERROR", sf::Style::Close);
    gui::TextBox errorBox({200, 100}, {10, 10}, font);
    errorBox.setEditable(false);
    errorBox.setString(message);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                isClosed = true;
                window.close();
            }
            errorBox.eventHandler(event);
        }
        errorBox.update();
        window.clear();
        errorBox.draw(window);
        window.display();
    }
}