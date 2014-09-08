/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1141125087
Contacts #1 : 0164111005 HII YONG LIAN
Lecture Section : TC101
Tutorial Section: TC201
********************************************/
//SIMPLE UTILITY CLASS TO CUT DOWN ON REPETITIVE TYPING
//BLATANTLY RIPPED FORM THE PROVIDED EXAMPLES (MOUSE GRIDS?)
#include "shapeCreate.hpp"
sf::RectangleShape createRectangle(sf::Vector2f myRectangleSize, sf::Vector2f position,
                             const sf::Color& myFillColor,
                             const sf::Color& myOutlineColor,
                             float myOutlineThickness
							 )
 {
	sf::RectangleShape myRectangle;
	myRectangle.setSize(myRectangleSize);
	myRectangle.setPosition(position);
	myRectangle.setFillColor(myFillColor);
	myRectangle.setOutlineColor(myOutlineColor);
	myRectangle.setOutlineThickness(myOutlineThickness);
	return myRectangle;
 }
sf::Text createText (sf::Vector2f position,
                     const sf::Color& textColor,
                        int text_size
                    )
{
    sf::Text newText;
    newText.setPosition(position);
    newText.setCharacterSize(text_size);
    newText.setColor(textColor);
    return newText;
}
