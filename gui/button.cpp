#include "button.hpp"

void gui::Button::setFont(sf::Font font)
{
    this->text.setFont(font);
}

gui::Button::Button()
{
    this->position = sf::Vector2f(0, 0);
    this->sizeOfRect = sf::Vector2f(5, 5);
    this->isHighlighted = false;
    this->position = position;
    this->text.setString("");
    this->textColor = sf::Color::White;
    this->textHighlightedColor = sf::Color::White;
    this->rectHighlightedColor = sf::Color(42, 188, 199);
    this->rectColor = sf::Color(51, 50, 50, 169);
}

gui::Button::Button(sf::Vector2f const position, sf::Vector2f const size, const sf::Font &font, sf::String const string)
{
    this->isHighlighted = false;
    this->sizeOfRect = size;
    this->position = position;
    this->text.setFont(font);
    this->text.setString(string);
    this->textColor = sf::Color::White;
    this->textHighlightedColor = sf::Color::White;
    this->rectHighlightedColor = sf::Color(42, 188, 199);
    this->rectColor = sf::Color(51, 50, 50, 169);
}
gui::Button::Button(sf::RoundedRectangleShape const rect, const sf::Text txt)
{
    this->isHighlighted = false;
    this->rrect = rect;
    this->text = txt;
    this->position = this->rrect.getPosition();
    this->sizeOfRect = this->rrect.getSize();
    this->rectColor = this->rrect.getFillColor();
    this->rectHighlightedColor = sf::Color(42, 188, 199);
    this->textColor = this->text.getFillColor();
    this->textHighlightedColor = sf::Color::White;
}
gui::Button::Button(sf::Vector2f const position, sf::Vector2f const size, const sf::Text txt)
{
    this->isHighlighted = false;
    this->position = position;
    this->sizeOfRect = size;
    this->text = txt;
    this->textColor = this->text.getFillColor();
    this->textHighlightedColor = sf::Color::White;
    this->rectHighlightedColor = sf::Color(42, 188, 199);
    this->rectColor = sf::Color(51, 50, 50, 169);
}
gui::Button::Button(sf::RoundedRectangleShape const rect, const sf::Font &font, sf::String const text)
{
    this->isHighlighted = false;
    this->rrect = rect;
    this->sizeOfRect = this->rrect.getSize();
    this->position = this->rrect.getPosition();
    this->text.setFont(font);
    this->text.setString(text);
    this->textColor = sf::Color::White;
    this->textHighlightedColor = sf::Color::White;
    this->rectHighlightedColor = sf::Color(42, 188, 199);
    this->rectColor = this->rrect.getFillColor();
}

void gui::Button::update(sf::RenderWindow &window)
{

    /// TEXT CHARACTER RECT SIZE DEPENDENT
    if (this->text.getGlobalBounds().width + 60 > this->sizeOfRect.x)
    {
        sizeOfRect.x = this->text.getGlobalBounds().width + this->text.getCharacterSize() * 3;
    }
    if (this->text.getGlobalBounds().height + 40 > this->sizeOfRect.y)
    {
        sizeOfRect.y = this->text.getGlobalBounds().height + this->text.getCharacterSize() * 2;
    }
    sizeOfRect = maths::round(sizeOfRect);

    this->rrect.setSize(sizeOfRect);
    this->rrect.setPosition(this->position);

    // center aligning text on rect ( dont touch, took 4 fucking hours to figure it out)
    //  dont remember how?
    //* link-> https://learnsfml.com/how-to-center-text/  must watch!!
    this->text.setPosition(maths::round(sf::Vector2f(this->rrect.getPosition().x + (this->rrect.getGlobalBounds().width / 2.f) - (this->text.getGlobalBounds().width / 2.f + this->text.getLocalBounds().left), this->rrect.getPosition().y + (this->rrect.getGlobalBounds().height / 2.f) - (this->text.getGlobalBounds().height / 2.f + this->text.getLocalBounds().top))));

    this->isMouseOnButton(window);

    if (this->isHighlighted)
    {

        this->rrect.setFillColor(this->rectHighlightedColor);
        this->text.setFillColor(this->textHighlightedColor);
    }
    else
    {

        this->rrect.setFillColor(this->rectColor);
        this->text.setFillColor(this->textColor);
    }
}

sf::Text &gui::Button::getSFText()
{
    // TODO: MAKE A BETTER FUNCTION (MULTIPLE) TO ACCESS SF::TEXT
    return this->text;
}
void gui::Button::draw(sf::RenderWindow &window)
{

    window.draw(this->rrect);
    window.draw(this->text);
}

bool gui::Button::isMouseOnButton(sf::RenderWindow &window)
{
    if (this->rrect.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
    {
        this->isHighlighted = true;
        return true;
    }
    else
    {
        this->isHighlighted = false;
        return false;
    }
}

bool gui::Button::isButtonClicked(sf::RenderWindow &window, sf::Mouse::Button mousebtn)
{
    if (this->isMouseOnButton(window))
    {
        if (sf::Mouse::isButtonPressed(mousebtn))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool gui::Button::getIsHighlighted()
{
    return this->isHighlighted;
}

void gui::Button::setIsHighlighted(bool isButtonHighlighted)
{
    this->isHighlighted = isButtonHighlighted;
}

void gui::Button::setPosition(sf::Vector2f position)
{
    this->position = position;
}

sf::Vector2f gui::Button::getPosition()
{
    return this->position;
}

sf::Vector2f gui::Button::getSize()
{
    return this->sizeOfRect;
}

void gui::Button::setSize(sf::Vector2f size)
{
    this->sizeOfRect = size;
}

sf::Color gui::Button::getTextColor()
{
    return this->textColor;
}

void gui::Button::setTextColor(sf::Color color)
{
    this->textColor = color;
}

sf::Color gui::Button::getTextHighlightedColor()
{
    return this->textHighlightedColor;
}

void gui::Button::setTextHighlightedColor(sf::Color color)
{
    this->textHighlightedColor = color;
}

sf::Color gui::Button::getButtonColor()
{
    return this->rectColor;
}

void gui::Button::setButtonColor(sf::Color color)
{
    this->rectColor = color;
}

sf::Color gui::Button::getButtonHighlightedColor()
{
    return this->rectHighlightedColor;
}

void gui::Button::setButtonHighlightedColor(sf::Color color)
{
    this->rectHighlightedColor = color;
}

bool gui::Button::getIsRounded()
{
    if (this->getRectangle().getCornersRadius() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void gui::Button::setIsRounded(float rad)
{
    this->getRectangle().setCornersRadius(rad);
}

sf::RoundedRectangleShape &gui::Button::getRectangle()
{
    // TODO: MAKE A BETTER FUNCTIONS (MULTIPLE) TO ACCESS SF::RoundedRectangleShape
    return this->rrect;
}

// #include "gui.hpp"

// gui::Button::Button(sf::RectangleShape rect,sf::Font font,std::string title){
//     this->title.setFont(font);
//     this->title.setString("title");
//     this->rectangle = rect;
//     this->backgroundColor = sf::Color::Black;
//     this->backgroundHighlightedColor = sf::Color::Blue;
//     this->textHighlightedColor = sf::Color::White;
//     this->textColor = sf::Color::White;
//     this->isHighlighted = false;
// }

// void gui::Button::settextHighlightedColor(sf::Color col){
//     this->textHighlightedColor = col;
// }
// sf::Color gui::Button::getTextHighlightedColor(){
//     return this->textHighlightedColor;
// }

// void gui::Button::setTitle(std::string name){
//     this->title.setString(name);
// }
// sf::String gui::Button::getTitle(){
//     return this->title.getString();
// }
// sf::Text& gui::Button::getSFText(){
//     return this->title;
// }
// void gui::Button::setTextColor(sf::Color col){
//     this->textColor = col;
//     this->title.setFillColor(col);
// }

// sf::Color gui::Button::getTextColor(){
//     return this->title.getFillColor();
// }

// void gui::Button::setFont(sf::Font font){
//     this->title.setFont(font);
// }

// void gui::Button::setIsHighlighted(bool boolean){
//     this->isHighlighted = boolean;
// }
// bool gui::Button::getIsHighlighted(){
//     return this->isHighlighted;
// }

// void gui::Button::setBackgroundColor(sf::Color col){
//     this->backgroundColor = col;
// }
// sf::Color gui::Button::getbackgroundColor(){
//     return this->backgroundColor;
// }

// void gui::Button::setHighlightedColor(sf::Color col){
//     this->backgroundHighlightedColor = col;
// }
// sf::Color gui::Button::getHighlightedColor(){
//     return this->backgroundHighlightedColor;
// }

// void gui::Button::setRectangle(sf::RectangleShape rect){
//     this->rectangle = rect;
// }
// sf::RectangleShape& gui::Button::getRectangle(){
//     return this->rectangle;
// }
// bool gui::Button::isMouseOnButton(sf::RenderWindow &window){
//     if(this->rectangle.getGlobalBounds().contains(sf::Mouse::getPosition(window).x ,sf::Mouse::getPosition(window).y ) ){
//         this->isHighlighted = true;
//         this->rectangle.setFillColor(this->backgroundHighlightedColor);
//         this->title.setFillColor(this->textHighlightedColor);
//         return true;
//     }else{
//         this->isHighlighted = false;
//         this->rectangle.setFillColor(this->backgroundColor);
//         this->title.setFillColor(this->textColor);
//         return false;
//     }
// }
// bool gui::Button::isButtonClicked(sf::RenderWindow &window){
//     if(this->isMouseOnButton(window)){
//         if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
//             return true;
//         }else{
//             return false;
//         }
//     }else{
//         return false;
//     }
// }

// void gui::Button::update(sf::RenderWindow &window){
//     this->isMouseOnButton(window);
// }

// void gui::Button::draw(sf::RenderWindow &window){
//     window.draw(this->rectangle);
//     window.draw(this->title);
// }