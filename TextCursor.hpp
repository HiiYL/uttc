#ifndef TEXTCURSOR_HPP_INCLUDED
#define TEXTCURSOR_HPP_INCLUDED
#include <SFML/Graphics.hpp>
class TextCursor : public sf::Drawable {
public:
    TextCursor(sf::Text *text);
    TextCursor() {};
    void update();
    void bindToText(sf::Text *text);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if(draw_cursor)
            target.draw(text_cursor);
    }
private:
    bool draw_cursor;
    sf::Text* text_ptr;
    sf::RectangleShape text_cursor;
    sf::Clock internalClock;
    sf::Time internalElapsed;
};


#endif // TEXTCURSOR_HPP_INCLUDED
