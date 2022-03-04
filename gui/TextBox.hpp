// #pragma once
// #include <vector>
// #include <SFML/Graphics.hpp>

// #include "shapes.hpp"
// namespace gui
// {
//     class TextBox
//     {
//     private:
//         std::vector<sf::Text> textArray;
//         sf::RoundedRectangleShape innerBox;
//         sf::RectangleShape outerBox;

//     public:
//         TextBox(sf::Vector2f outerBoxSize, sf::Vector2f innerBoxSize = {0, 0});
//         int getNumberOfText();
//         void addString(sf::Text text);
//         void addString(std::string string, const sf::Font &font);
//     };
// }

// #pragma once

// #include <iostream>
// #include <sstream>
// #include <SFML/Graphics.hpp>

// // Define keys:
// #define BACKSPACE_KEY 8
// #define ENTER_KEY 13
// #define ESCAPE_KEY 27

// namespace gui
// {
//     class Textbox
//     {
//     public:
//         Textbox(int size, sf::Color color, bool sel);

//         // Make sure font is passed by reference:
//         void setFont(sf::Font &fonts);

//         void setPosition(sf::Vector2f point);

//         // Set char limits:
//         void setLimit(bool ToF);

//         void setLimit(bool ToF, int lim);

//         // Change selected state:
//         void setSelected(bool sel);

//         std::string getText();

//         void drawTo(sf::RenderWindow &window);

//         // Function for event loop:
//         void typedOn(sf::Event input);

//     private:
//         sf::Text textbox;

//         std::ostringstream text;
//         bool isSelected = false;
//         bool hasLimit = false;
//         int limit = 0;

//         // Delete the last character of the text:
//         void deleteLastChar()
//         {
//             std::string t = text.str();
//             std::string newT = "";
//             for (int i = 0; i < t.length() - 1; i++)
//             {
//                 newT += t[i];
//             }
//             text.str("");
//             text << newT;
//             textbox.setString(text.str() + "_");
//         }

//         // Get user input:
//         void inputLogic(int charTyped)
//         {
//             // If the key pressed isn't delete, or the two selection keys, then append the text with the char:
//             if (charTyped != BACKSPACE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY)
//             {
//                 text << static_cast<char>(charTyped);
//             }
//             // If the key is delete, then delete the char:
//             else if (charTyped == BACKSPACE_KEY)
//             {
//                 if (text.str().length() > 0)
//                 {
//                     deleteLastChar();
//                 }
//             }
//             // Set the textbox text:
//             textbox.setString(text.str() + "_");
//         }
//     };
// }

#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

#include "shapes.hpp"
#include "maths.hpp"
namespace gui
{
    class TextBox
    {
    private:
        std::vector<sf::Text> para;
        sf::RoundedRectangleShape box;

        unsigned int size;
        sf::Vector2f boxSize;
        sf::Vector2f pos;
        sf::Font font;

        bool isSelected = false;
        bool isEditable = true;
        unsigned int maxLimit = 0U;

    public:
        TextBox(const sf::Vector2f boxSize, const sf::Vector2f position, const sf::Font &font, const unsigned int size = 15) : size(size), boxSize(boxSize), pos(position), font(font)
        {
            this->para.push_back(sf::Text("", this->font, this->size));
            this->box.setCornersRadius(10);
            this->box.setSize(boxSize);
            this->box.setPosition(position);
        };
        TextBox(const sf::RoundedRectangleShape box, const sf::Font font, const unsigned int size = 15U) : box(box), size(size), font(font)
        {
            this->para.push_back(sf::Text("", this->font, this->size));
        };

        int getNumberOfLines();

        void setPosition(sf::Vector2f pos);
        sf::Vector2f getPosition();

        void setSelectable(bool selectable);
        bool getSelectable();

        void setString(std::string string);

        void setEditable(bool edit);
        bool getEditable();

        void setMaxLimit(unsigned int limit);
        unsigned int getMaxLimit();

        void update();
        void eventHandler(sf::Event e);

        bool isMouseOverlap(sf::RenderWindow &window);

        bool isButtonClicked(sf::RenderWindow &window, sf::Mouse::Button mousebtn);

        void inputHandler(sf::RenderWindow &window, sf::Event &event);

        void draw(sf::RenderWindow &window);
    };
}