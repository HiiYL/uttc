/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1141125087
Contacts #1 : 0164111005 HII YONG LIAN
Lecture Section : TC101
Tutorial Section: TC201
********************************************/
//CREATES THAT BLINKY THING WHEN YOU ARE ENTERING INTO A TEXT FIELD
#include "TextCursor.hpp"
TextCursor::TextCursor( sf::Text *text)
{
    draw_cursor = true;
    text_ptr = text;
    text_cursor.setSize(sf::Vector2f(8, text_ptr->getGlobalBounds().height));
    text_cursor.setFillColor(sf::Color::Black);
};
void TextCursor::update()   {
    internalElapsed = internalClock.getElapsedTime();
    //std::cout << text_ptr->getGlobalBounds().width << std::endl;
    text_cursor.setPosition(text_ptr->getPosition().x+text_ptr->getGlobalBounds().width,
                             text_ptr->getPosition().y);
    if(internalElapsed.asMilliseconds() > 500)  {
            draw_cursor = !draw_cursor;
            internalClock.restart();
    }
}
void TextCursor::bindToText(sf::Text *text)   {
    draw_cursor = true;
    text_ptr = text;
    text_cursor.setSize(sf::Vector2f(8, 16));
    text_cursor.setFillColor(sf::Color::Black);
}
