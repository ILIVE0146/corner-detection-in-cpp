
#include "TextBox.hpp"

int gui::TextBox::getNumberOfLines()
{
    return this->para.size();
}
void gui::TextBox::setPosition(sf::Vector2f pos)
{
    this->pos = pos;
}
sf::Vector2f gui::TextBox::getPosition()
{
    return this->pos;
}
void gui::TextBox::setSelectable(bool selectable)
{
    this->isSelected = selectable;
}
bool gui::TextBox::getSelectable()
{
    return this->isSelected;
}
void gui::TextBox::setEditable(bool edit)
{
    this->isEditable = edit;
}
bool gui::TextBox::getEditable()
{
    return this->isEditable;
}

void gui::TextBox::setMaxLimit(unsigned int limit)
{
    this->maxLimit = limit;
}
unsigned int gui::TextBox::getMaxLimit()
{
    return this->maxLimit;
}
bool gui::TextBox::isMouseOverlap(sf::RenderWindow &window)
{
    if (this->box.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool gui::TextBox::isButtonClicked(sf::RenderWindow &window, sf::Mouse::Button mousebtn)
{
    if (this->isMouseOverlap(window))
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

void gui::TextBox::setString(std::string string)
{
    if (this->para.empty() == true)
    {
        this->para.push_back(sf::Text(string, this->font, this->size));
    }
    else
    {
        this->para.back().setString(string);
    }
}

void gui::TextBox::eventHandler(sf::Event event)
{
    if (this->isEditable == true && this->isSelected == true)
    {
        sf::Uint32 charTyped = event.text.unicode;
        sf::String stringBuf = this->para.back().getString();
        if (event.key.code == sf::Keyboard::Backspace)
        {
            if (stringBuf.isEmpty())
            {
                this->para.pop_back();
            }
            else
            {
                stringBuf.erase(stringBuf.getSize() - 1);
            }
        }
        else if (event.key.code == sf::Keyboard::Enter)
        {
            if (this->maxLimit == 0 || this->para.size() < this->maxLimit)
            {
                this->para.push_back(sf::Text("", this->font, this->size));
            }
            else
            {
                this->isSelected = false;
            }
        }
        else if (event.key.code == sf::Keyboard::Escape)
        {
            this->isSelected = false;
        }
        else if (charTyped > 31 && charTyped < 127)
        {
            stringBuf = stringBuf + static_cast<char>(charTyped);
            this->para.back().setString(stringBuf);
        }
    }
}
void gui::TextBox::update()
{
    this->box.setPosition(this->pos);

    if (this->para.back().getGlobalBounds().width + 60 > this->boxSize.x)
    {
        boxSize.x = this->para.back().getGlobalBounds().width + this->para.back().getCharacterSize() * 3;
    }
    if (this->para.back().getGlobalBounds().height + 40 > this->boxSize.y)
    {
        this->boxSize.y = this->para.back().getGlobalBounds().height + this->para.back().getCharacterSize() * 2;
    }
    this->boxSize = maths::round(this->boxSize);

    this->box.setSize(this->boxSize);

    this->box.setFillColor(sf::Color(51, 50, 50, 100));

    this->para.back().setPosition(maths::round(sf::Vector2f(this->box.getPosition().x + (this->box.getGlobalBounds().width / 2.f) - (this->para.back().getGlobalBounds().width / 2.f + this->para.back().getLocalBounds().left), this->box.getPosition().y + (this->box.getGlobalBounds().height / 2.f) - (this->para.back().getGlobalBounds().height / 2.f + this->para.back().getLocalBounds().top))));
}
void gui::TextBox::inputHandler(sf::RenderWindow &window, sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (this->isMouseOverlap(window))
        {
            this->isSelected = true;
        }
    }
}
void gui::TextBox::draw(sf::RenderWindow &window)
{
    window.draw(this->box);
    for (auto itr = this->para.begin(); itr != this->para.end(); itr++)
    {
        window.draw(*itr);
    }
}