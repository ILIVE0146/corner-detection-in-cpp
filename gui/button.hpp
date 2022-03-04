
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "maths.hpp"
#include "shapes.hpp"

namespace gui
{

    class Button
    {
    private:
        sf::Text text;
        sf::RoundedRectangleShape rrect;
        //sf::ConvexShape roundedRectangle;

        bool isHighlighted;
        sf::Vector2f sizeOfRect;
        sf::Vector2f position;
        sf::Color textColor;
        sf::Color textHighlightedColor;
        sf::Color rectColor;
        sf::Color rectHighlightedColor;

    public:
        /// creates a button with default SFML colors
        /// @param position const sf::vector2f const
        /// \param size const sf::vector2f const
        /// \param font const sf::Font& const
        /// \param string const sf::String const
        Button();
        Button(sf::Vector2f const position, sf::Vector2f const size, const sf::Font &font, sf::String const string);

        /// creates a button with default SFML colors
        /// \param rect sf::RoundedRectangleShape const
        /// \param text sf::Text& const
        Button(sf::RoundedRectangleShape const rect, const sf::Text);

        /// creates a button with default SFML colors
        /// \param position sf::vector2f const
        /// \param size sf::vector2f const
        /// \param text sf::Text& const
        Button(sf::Vector2f const position, sf::Vector2f const size, const sf::Text);

        /// creates a button with default SFML colors
        /// \param position sf::vector2f const
        /// \param rect sf::RoundedRectangleShape const
        /// \param Font sf::Font const
        /// \param text sf::String const
        Button(sf::RoundedRectangleShape const rect, const sf::Font &font, sf::String const text);

        // ! use with caution might as well make sf::Text public :P
        /// @return \p sf::Text \p text 's address to modify
        sf::Text &getSFText();

        // ! use with caution might as well make sf::RectangleShape rect :P
        /// \return \p sf::RectangleShape \p rect 's address to modify
        sf::RoundedRectangleShape &getRectangle();

        /// getter method for isHighlighted
        /// \returns bool isHighlighted
        bool getIsHighlighted();

        /// setter method for isHighlighted
        /// \param isButtonHighlighted bool
        void setIsHighlighted(bool isButtonHighlighted);

        /// setter method for position
        /// \param position sf::Vector2f
        void setPosition(sf::Vector2f position);

        ///getter method for position
        ///\returns position of rect which has the button centered in it
        sf::Vector2f getPosition();

        ///getter method for sizeOfRect
        /// \returns size of rectangle around the button sf::Vector2f
        sf::Vector2f getSize();

        ///setter method for sizeOfRect
        ///\param size sf::Vector2f
        void setSize(sf::Vector2f size);

        ///getter method for textColor
        ///\returns sf::Color of idle text
        sf::Color getTextColor();

        ///setter method for textColor
        ///\param color sf::Color
        void setTextColor(sf::Color color);

        ///getter method for textHighlightedColor
        ///\returns sf::Color of text when highlighted
        sf::Color getTextHighlightedColor();

        ///setter method of textHighlightedColor
        ///\param color sf::Color
        void setTextHighlightedColor(sf::Color color);

        ///getter method for rectColor
        ///\returns sf::Color of button box when idle
        sf::Color getButtonColor();

        //setter method for rectColor
        ///\param color sf::Color
        void setButtonColor(sf::Color color);

        ///getter method for rectHighlightedColor
        ///\returns sf::Color when rect is highlighted
        sf::Color getButtonHighlightedColor();

        ///setter method for rectHighlightedColor
        ///\param color sf::Color
        void setButtonHighlightedColor(sf::Color color);

        // updates any changes logic like any changes for highlighing on mouse hover and stuff
        /// \param window sf::RenderWindow&
        void update(sf::RenderWindow &window);

        /// Draws the sf::Text and sf::RectangleShape to the given window
        /// \param window sf::RenderWindow&
        void draw(sf::RenderWindow &window);

        /// Checks if the button is clicked or not
        /// \param window sf::RenderWindow&
        /// \param mouseBtn sf::Mouse::Button
        /// \returns bool, true if clicked, else false
        bool isButtonClicked(sf::RenderWindow &window, sf::Mouse::Button mousebtn = sf::Mouse::Button::Left);

        /// Checks if the button is on mouse or not
        /// \param window sf::RenderWindow&
        /// \returns bool, true mouse is on button, else returns false
        bool isMouseOnButton(sf::RenderWindow &window);

        ///\returns true if radius is greater than 0 else false
        bool getIsRounded();

        float getRadius();
        ///setter method for float radius
        ///\param radius float radius
        void setIsRounded(float radius);

        void setFont(sf::Font);
    };
}

// #pragma once
// #include <vector>
// #include <string>
// #include <SFML/Graphics.hpp>
// namespace gui{
//     class Button{
//         public:
//         Button(sf::RectangleShape rect,sf::Font font,std::string title);

//         void setTitle(std::string);
//         sf::String getTitle();

//         void setTextColor(sf::Color);
//         sf::Color getTextColor();

//         void setFont(sf::Font);
//         sf::Text& getSFText();
//         void settextHighlightedColor(sf::Color);
//         sf::Color getTextHighlightedColor();

//         void setBackgroundColor(sf::Color);
//         sf::Color getbackgroundColor();

//         void setHighlightedColor(sf::Color);
//         sf::Color getHighlightedColor();

//         void setRectangle(sf::RectangleShape);
//         sf::RectangleShape& getRectangle();

//         void setIsHighlighted(bool);
//         bool getIsHighlighted();

//         bool isMouseOnButton(sf::RenderWindow &window);
//         bool isButtonClicked(sf::RenderWindow &window);

//         void update(sf::RenderWindow &window);
//         void draw(sf::RenderWindow &window);

//         private:
//         sf::Text title;
//         sf::Color textHighlightedColor;
//         sf::Color textColor;
//         sf::Color backgroundColor;
//         sf::Color backgroundHighlightedColor;
//         sf::RectangleShape rectangle;
//         bool isHighlighted;
//     };
//     class DropDownList{
//         public:

//         void draw();

//         private:
//         sf::Vector2f position;
//         std::vector<Button> listOfButtons;
//     };
// }
