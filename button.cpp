/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1141125087
Contacts #1 : 0164111005 HII YONG LIAN
Lecture Section : TC101
Tutorial Section: TC201
********************************************/
//EXPLANATION
//A CLASS TO CREATE CLICKABLE STUFF
//ALSO EASILY ALLOWS SWAPPING OF TEXTURES
#include "button.hpp"
Button::Button(sf::RenderWindow& App):window(App)
{
    hasHoverTexture = false;
    hasSwapTexture = false;
    swapped = false;
    hasTextCursor = false;
    text_orientation = "bottom";
    only_once = true;
}
void Button::load(sf::Texture &texture, sf::Font &font) {
    button.setTexture(texture);
    text.setFont(font);
}
void Button::load(sf::Texture &texture) {
    base = &texture;
    button.setTexture(texture);
}
void Button::load(sf::Texture &texture_base, sf::Texture &texture_highlight)   {
    base = &texture_base;
    base_hover = &texture_highlight;
    button.setTexture(*base);
    hasHoverTexture = true;
}
void Button::load(sf::Texture &texture_base, sf::Texture &texture_highlight,
                   sf::Texture &swap_tex, sf::Texture &swap_highlight)
{
    base = &texture_base;
    base_hover = &texture_highlight;
    swap_base = &swap_tex;
    swap_hover = &swap_highlight;
    button.setTexture(*base);
    hasHoverTexture = true;
    hasSwapTexture = true;
}
 void Button::setString(const std::string &s)   {
    text_string = s;
    text.setString(s);
    text.setColor(sf::Color::Black);
    text.setCharacterSize(button.getGlobalBounds().height*0.2);
    repositionString(s);
}
void Button::repositionString(const std::string &s) {
        std::string::size_type str_size = s.size();
        //text.setCharacterSize(14);
        text.setColor(sf::Color::Black);
        if(text_orientation == "center")
            text.setPosition(button.getPosition().x+button.getGlobalBounds().width/2-text.getGlobalBounds().width/2,
                            button.getPosition().y+button.getGlobalBounds().height/2-text.getGlobalBounds().height/2);
        else
            text.setPosition(button.getPosition().x+button.getGlobalBounds().width/2-text.getGlobalBounds().width/2,
                         button.getPosition().y+button.getGlobalBounds().height);

}
bool Button::isClicked()   {
    position = (sf::Vector2f)sf::Mouse::getPosition(window);
    if(button.getGlobalBounds().contains(position)) {
        if(hasHoverTexture)button.setTexture(*base_hover, true);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if(hasSwapTexture)button.setTexture(*swap_base, true);
                return true;
        }
    }
    else
        if(hasHoverTexture)button.setTexture(*base, true);
    return false;
}
bool Button::isClicked(sf::Event event)   {
    position = (sf::Vector2f)sf::Mouse::getPosition(window);
    if(button.getGlobalBounds().contains(position)) {
        if(hasHoverTexture) {
            if(swapped)button.setTexture(*swap_hover, true);
            else button.setTexture(*base_hover, true);
        }
        if(event.type == sf::Event::MouseButtonPressed) {
            if(hasSwapTexture)  {
                if((!swapped))button.setTexture(*swap_base, true);
                else button.setTexture(*base,true);
                swapped=!swapped;
            }
                return true;
        }
    }
    else
        if(hasHoverTexture) {
            if(swapped)button.setTexture(*swap_base,true);
            else button.setTexture(*base, true);
        }
    return false;
}
void Button::updateAnimation()
{
    if(only_once)   {
        internalClock.restart();
        only_once = false;
    }
    internalElapsed = internalClock.getElapsedTime();
    if(button.getPosition()!=animation_dest)    {
            sf::Vector2f movement = internalElapsed.asSeconds()*animation_speed*(animation_dest-button.getPosition());
            button.move(movement);
            text.move(movement);
            internalClock.restart();
    }
};
