#pragma once

#include <SFML/Graphics.hpp>
#include "gui/TextBox.hpp"
#include "gui/Button.hpp"
#include "globalVariables.hpp"
#include "Line.hpp"

class ControlPanel
{
public:
    ControlPanel(const sf::Font &font);
    void eventHandler(sf::Event event, sf::RenderWindow &window);
    bool checkLine(sf::Event event, const sf::Vector2i &mousePos);
    void resetSelected();
    sf::RectangleShape &getBackground() { return bg; };
    bool &checkOpencvstatus() { return startOpencv; };
    gui::Button &getOpencvBtn() { return opencvBtn; };
    void update(sf::Time &dt, sf::RenderWindow &window, const sf::Vector2i &mousePrev);
    void drawTo(sf::RenderWindow &window);
    std::vector<Line *> getLines();

private:
    sf::RectangleShape bg;
    sf::Font font;

    sf::Text h_dist_Text, v_dist_Text, h_1_text, h_2_text, v_1_text, v_2_text;

    gui::TextBox h_dist, v_dist;

    gui::Button h_1_1, h_1_2, h_2_1, h_2_2, v_1_1, v_1_2, v_2_1, v_2_2;

    Line h_line1, h_line2, v_line1, v_line2;

    gui::Button opencvBtn;

    bool startOpencv = false;

    std::array<bool, 8> linedata = {false, false, false, false, false, false, false, false};

};