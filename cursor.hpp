#ifndef CURSOR_HPP_INCLUDED
#define CURSOR_HPP_INCLUDED
#include <SFML/Graphics.hpp>
class Cursor : public sf::Drawable {
public:
    Cursor(sf::RenderWindow& App):window(App) {};
    Cursor(sf::RenderWindow& App, sf::Texture &texture):window(App){cursor.setTexture(texture);};
    void setTexture(sf::Texture &texture);
    void update();
    void externalUpdate(sf::Vector2f position);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.texture = &texture;
        target.draw(cursor,states);
    }
private:
    sf::Sprite cursor;
    sf::Texture texture;
    sf::Vector2f position;
    sf::RenderWindow &window;
};




#endif // CURSOR_HPP_INCLUDED
