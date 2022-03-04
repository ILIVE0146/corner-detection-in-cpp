#include "ControlPanel.hpp"

ControlPanel::ControlPanel(const sf::Font &font) : bg(sf::RectangleShape({CONTROL_PANEL_WIDTH, SCREEN_HEIGHT})),
                                                   font(font),
                                                   h_dist_Text(sf::Text("D1:- ", this->font, 15)),
                                                   v_dist_Text(sf::Text("D2:- ", this->font, 15)),
                                                   h_1_text(sf::Text("Top Hor bar:-", font, 15)),
                                                   h_2_text(sf::Text("Bottom hor bar:-", font, 15)),
                                                   v_1_text(sf::Text("left ver bar:-", font, 15)),
                                                   v_2_text(sf::Text("right ver bar:-", font, 15)),

                                                   h_dist(gui::TextBox({215, 45}, {0, 0}, font)),
                                                   v_dist(gui::TextBox({215, 45}, {0, 0}, font)),

                                                   h_1_1(gui::Button({0, 0}, {50, 35}, sf::Text("+1px", font, 15))),
                                                   h_1_2(gui::Button({0, 0}, {50, 35}, sf::Text("-1px", font, 15))),
                                                   h_2_1(gui::Button({0, 0}, {50, 35}, sf::Text("+1px", font, 15))),
                                                   h_2_2(gui::Button({0, 0}, {50, 35}, sf::Text("-1px", font, 15))),
                                                   v_1_1(gui::Button({0, 0}, {50, 35}, sf::Text("+1px", font, 15))),
                                                   v_1_2(gui::Button({0, 0}, {50, 35}, sf::Text("-1px", font, 15))),
                                                   v_2_1(gui::Button({0, 0}, {50, 35}, sf::Text("+1px", font, 15))),
                                                   v_2_2(gui::Button({0, 0}, {50, 35}, sf::Text("-1px", font, 15))),

                                                   h_line1(Line({0, 100}, sf::RectangleShape({SCREEN_WIDTH - CONTROL_PANEL_WIDTH, 5}))),
                                                   h_line2(Line({0, 300}, sf::RectangleShape({SCREEN_WIDTH - CONTROL_PANEL_WIDTH, 5}))),
                                                   v_line1(Line({100, 0}, sf::RectangleShape({5, SCREEN_HEIGHT}))),
                                                   v_line2(Line({300, 0}, sf::RectangleShape({5, SCREEN_HEIGHT}))),

                                                   opencvBtn(gui::Button({0, 0}, {215, 45}, sf::Text("Auto Detect", font, 15)))
{
    this->bg.setPosition(SCREEN_WIDTH - CONTROL_PANEL_WIDTH, 0);
    this->bg.setFillColor(sf::Color(30, 30, 30));

    h_dist.setEditable(false);
    v_dist.setEditable(false);

    h_1_1.setIsRounded(5);
    h_1_2.setIsRounded(5);
    h_2_1.setIsRounded(5);
    h_2_2.setIsRounded(5);
    v_1_1.setIsRounded(5);
    v_1_2.setIsRounded(5);
    v_2_1.setIsRounded(5);
    v_2_2.setIsRounded(5);

    auto bg_pos = bg.getPosition();

    this->h_1_text.setPosition(bg_pos + sf::Vector2f{15, 10});
    this->h_1_1.setPosition(h_1_text.getPosition() + sf::Vector2f{15, 30});
    this->h_1_2.setPosition(h_1_text.getPosition() + sf::Vector2f{130, 30});

    this->h_2_text.setPosition(bg_pos + sf::Vector2f{15, 90});
    this->h_2_1.setPosition(h_2_text.getPosition() + sf::Vector2f{15, 30});
    this->h_2_2.setPosition(h_2_text.getPosition() + sf::Vector2f{130, 30});

    this->v_1_text.setPosition(bg_pos + sf::Vector2f{15, 170});
    this->v_1_1.setPosition(v_1_text.getPosition() + sf::Vector2f{15, 30});
    this->v_1_2.setPosition(v_1_text.getPosition() + sf::Vector2f{130, 30});

    this->v_2_text.setPosition(bg_pos + sf::Vector2f{15, 250});
    this->v_2_1.setPosition(v_2_text.getPosition() + sf::Vector2f{15, 30});
    this->v_2_2.setPosition(v_2_text.getPosition() + sf::Vector2f{130, 30});

    h_dist_Text.setPosition(bg_pos + sf::Vector2f{15, 330});
    h_dist.setPosition(h_dist_Text.getPosition() + sf::Vector2f{0, 30});
    v_dist_Text.setPosition(bg_pos + sf::Vector2f{15, 410});
    v_dist.setPosition(v_dist_Text.getPosition() + sf::Vector2f{0, 30});

    opencvBtn.setPosition(bg_pos + sf::Vector2f{CONTROL_PANEL_WIDTH / 2 - (opencvBtn.getSize().x / 2), 500});
}

void ControlPanel::eventHandler(sf::Event event, sf::RenderWindow &window)
{
    h_dist.eventHandler(event);
    v_dist.eventHandler(event);

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        if (h_1_1.isMouseOnButton(window))
        {
            linedata[0] = true;
        }
        else if (h_1_2.isMouseOnButton(window))
        {
            linedata[1] = true;
        }
        else if (h_2_1.isMouseOnButton(window))
        {
            linedata[2] = true;
        }
        else if (h_2_2.isMouseOnButton(window))
        {
            linedata[3] = true;
        }
        else if (v_1_1.isMouseOnButton(window))
        {
            linedata[4] = true;
        }
        else if (v_1_2.isMouseOnButton(window))
        {
            linedata[5] = true;
        }
        else if (v_2_1.isMouseOnButton(window))
        {
            linedata[6] = true;
        }
        else if (v_2_2.isMouseOnButton(window))
        {
            linedata[7] = true;
        }
        else if (opencvBtn.isMouseOnButton(window))
        {
            startOpencv = true;
        }
    }
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        linedata = {false, false, false, false, false, false, false, false};
    }
}

bool ControlPanel::checkLine(sf::Event event, const sf::Vector2i &mousePos)
{
    if (h_line1.getRectangle().getGlobalBounds().contains(mousePos.x, mousePos.y))
    {
        h_line1.getIsSelected() = true;
        return true;
    }
    else if (h_line2.getRectangle().getGlobalBounds().contains(mousePos.x, mousePos.y))
    {
        h_line2.getIsSelected() = true;
        return true;
    }
    else if (v_line1.getRectangle().getGlobalBounds().contains(mousePos.x, mousePos.y))
    {
        v_line1.getIsSelected() = true;
        return true;
    }
    else if (v_line2.getRectangle().getGlobalBounds().contains(mousePos.x, mousePos.y))
    {
        v_line2.getIsSelected() = true;
        return true;
    }
    return false;
}
void ControlPanel::resetSelected()
{
    h_line1.getIsSelected() = false;
    h_line2.getIsSelected() = false;
    v_line1.getIsSelected() = false;
    v_line2.getIsSelected() = false;
}
void ControlPanel::update(sf::Time &dt, sf::RenderWindow &window, const sf::Vector2i &mousePrev)
{
    if (linedata[0] == true)
    {
        h_line1.getRectangle().move({0, LineSpeed * dt.asSeconds()});
    }
    if (linedata[1] == true)
    {
        h_line1.getRectangle().move({0, -LineSpeed * dt.asSeconds()});
    }
    if (linedata[2] == true)
    {
        h_line2.getRectangle().move({0, LineSpeed * dt.asSeconds()});
    }
    if (linedata[3] == true)
    {
        h_line2.getRectangle().move({0, -LineSpeed * dt.asSeconds()});
    }
    if (linedata[4] == true)
    {
        v_line1.getRectangle().move({LineSpeed * dt.asSeconds(), 0});
    }
    if (linedata[5] == true)
    {
        v_line1.getRectangle().move({-LineSpeed * dt.asSeconds(), 0});
    }
    if (linedata[6] == true)
    {
        v_line2.getRectangle().move({LineSpeed * dt.asSeconds(), 0});
    }
    if (linedata[7] == true)
    {
        v_line2.getRectangle().move({-LineSpeed * dt.asSeconds(), 0});
    }

    h_dist.update();
    v_dist.update();

    h_1_1.update(window);
    h_1_2.update(window);
    h_2_1.update(window);
    h_2_2.update(window);

    v_1_1.update(window);
    v_1_2.update(window);
    v_2_1.update(window);
    v_2_2.update(window);

    h_line1.update(window, mousePrev);
    v_line1.update(window, mousePrev);
    h_line2.update(window, mousePrev);
    v_line2.update(window, mousePrev);

    opencvBtn.update(window);

    auto h_m1 = h_line1.getMidpoint();
    auto h_m2 = h_line2.getMidpoint();
    auto v_m1 = v_line1.getMidpoint();
    auto v_m2 = v_line2.getMidpoint();

    if (h_m1.y < h_m2.y)
    {
        v_dist.setString(std::to_string((h_m2.y - h_m1.y) / IMAGE_SCALE));
    }
    else
    {
        v_dist.setString(std::to_string((h_m1.y - h_m2.y) / IMAGE_SCALE));
    }
    if (v_m1.x < v_m2.x)
    {
        h_dist.setString(std::to_string((v_m2.x - v_m1.x) / IMAGE_SCALE));
    }
    else
    {
        h_dist.setString(std::to_string((v_m1.x - v_m2.x) / IMAGE_SCALE));
    }
}

void ControlPanel::drawTo(sf::RenderWindow &window)
{
    h_line1.drawTo(window);
    h_line2.drawTo(window);
    v_line1.drawTo(window);
    v_line2.drawTo(window);

    window.draw(this->bg);

    window.draw(h_1_text);
    window.draw(h_2_text);
    window.draw(v_1_text);
    window.draw(v_2_text);

    h_1_1.draw(window);
    h_1_2.draw(window);
    h_2_1.draw(window);
    h_2_2.draw(window);

    v_1_1.draw(window);
    v_1_2.draw(window);
    v_2_1.draw(window);
    v_2_2.draw(window);

    window.draw(this->h_dist_Text);
    h_dist.draw(window);

    window.draw(this->v_dist_Text);
    v_dist.draw(window);

    opencvBtn.draw(window);
}

std::vector<Line *> ControlPanel::getLines()
{
    std::vector<Line *> buf;
    buf.push_back(&this->h_line1);
    buf.push_back(&this->h_line2);
    buf.push_back(&this->v_line1);
    buf.push_back(&this->v_line2);

    return buf;
}