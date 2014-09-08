#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED
#include <SFML/Graphics.hpp>
class Button  : public sf::Drawable  {
public:
    Button(sf::RenderWindow& App);
    void load(sf::Texture &texture, sf::Font &font);
    void load(sf::Texture &texture);
    void load(sf::Texture &texture_base, sf::Texture &texture_highlight);
    void load(sf::Texture &texture_base, sf::Texture &texture_highlight,
                   sf::Texture &swap_base, sf::Texture &swap_highlight);
    void setFont(sf::Font &in_font){text.setFont(in_font);};
    void setCharacterSize(int i) {text.setCharacterSize(i); repositionString(text_string);};
    void setTextColor(sf::Color color)   {text.setColor(color);};
    void setTextOrientation(const std::string &s) {text_orientation = s;repositionString(text_string);};
    void setPosition(float x, float y) {button.setPosition(sf::Vector2f(x,y));};
    void setPosition(sf::Vector2f position) {button.setPosition(position);};
    void setString(const std::string &s);
    void setScale(float x, float y) {button.setScale(x,y);};
    void setScale(float x) {button.setScale(x,x);};
    void setColor(const sf::Color &color) {button.setColor(color);};

    void animatedMovement(sf::Vector2f dest, float speed){ animation_origin = button.getPosition();
                                                                  animation_dest = dest; animation_speed = speed;};
    void updateAnimation();
    sf::Vector2f getPosition()  {return button.getPosition();};
    sf::Vector2f getGlobalBounds() {return sf::Vector2f(button.getGlobalBounds().width,
                                                   button.getGlobalBounds().height);};
    sf::Text* getTextPtr()  {return &text;};
    bool isClicked();
    bool isClicked(sf::Event event);


virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(button);
        if(text.getString()!="")target.draw(text);
    }
private:
    bool hasHoverTexture;
    bool hasSwapTexture;
    bool swapped;
    bool hasTextCursor;
    sf::Vector2f animation_origin;
    sf::Vector2f animation_dest;
    float animation_speed;
    std::string text_orientation;
    std::string text_string;
    sf::Sprite button;
    sf::Vector2f position;
    sf::Texture* base;
    sf::Texture* base_hover;
    sf::Texture* swap_base;
    sf::Texture* swap_hover;
    sf::Texture blank_box;
    sf::RenderWindow &window;
    sf::Text text;
    sf::Font* font;
    sf::Clock internalClock;
    sf::Time internalElapsed;
    bool only_once;

    void repositionString(const std::string &s);
};

#endif // BUTTON_HPP_INCLUDED
