/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1141125087
Contacts #1 : 0164111005 HII YONG LIAN
Lecture Section : TC101
Tutorial Section: TC201
********************************************/
//A SMALL CLASS TO AVOID REPETITIVE WRITING OF CURSOR CREATION
#include "cursor.hpp"
void Cursor::setTexture(sf::Texture &texture)  {
    cursor.setTexture(texture);
}
void Cursor::update()    {
     position = (sf::Vector2f)sf::Mouse::getPosition(window);
     cursor.setPosition(position);
}
void Cursor::externalUpdate(sf::Vector2f position)    {
     cursor.setPosition(position);
}
