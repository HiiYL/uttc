#ifndef SHAPE_CREATE_HPP_INCLUDED
#define SHAPE_CREATE_HPP_INCLUDED
#include <SFML/Graphics.hpp>
#include <vector>
#include "player.hpp"
sf::RectangleShape createRectangle(sf::Vector2f myRectangleSize, sf::Vector2f position = sf::Vector2f(0,0),
                             const sf::Color& myFillColor = sf::Color::White,
                             const sf::Color& myOutlineColor = sf::Color::Black,
                             float myOutlineThickness = -2
							 );
sf::Text createText (sf::Vector2f position = sf::Vector2f(0,0),
                     const sf::Color& textColor = sf::Color::Red,
                        int text_size = 24
                    );
#endif // SHAPE_CREATE_INCLUDED

