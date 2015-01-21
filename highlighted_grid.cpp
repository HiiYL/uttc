/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1141125087
Contacts #1 : 0164111005 HII YONG LIAN
Lecture Section : TC101
Tutorial Section: TC201
********************************************/
//GENERATES A HIGHLIGHTED GRID TO INDICATE CURRENT PLAYING FIELD
#include "highlighted_grid.hpp"
#include "shapeCreate.hpp"
HighlightedGrid::HighlightedGrid( Grid &grid,ResourceHolder* res_container, const int &starting_index)  {       //creates a 3x3 grid representing playable areas

    highlighted_grid_sprite.setTexture(res_container->textures.get("Highlight"));
    highlighted_grid = createRectangle(sf::Vector2f(grid.getGridSize(),grid.getGridSize()),grid.getPosition(starting_index));
    highlighted_grid.setOutlineColor(sf::Color::Transparent);
    highlighted_grid_sprite.setPosition(highlighted_grid.getPosition().x-39,
                                        highlighted_grid.getPosition().y-39);
    highlighted_grid_sprite.setColor(sf::Color::White);
    grid_ptr = &grid;
}
void HighlightedGrid::update(const int &index)
{
    highlighted_grid.setPosition(grid_ptr->getPosition(index));
    highlighted_grid_sprite.setPosition(highlighted_grid.getPosition().x-39,
                                        highlighted_grid.getPosition().y-39);
}
std::pair<int,int> HighlightedGrid::getIndex(sf::Vector2f position) {
    for(int i = 0; i < grid_ptr->getGridCells(); i++)
        for(int j = 0 ; j < grid_ptr->getGridCells(); j++)
            if(grid_ptr->contains_box(position,i,j)) {
                return std::make_pair(i,j);
            }
    return std::make_pair(0,0);
}
void HighlightedGrid::move(float x, float y)    {
    highlighted_grid.move(x,y);
    highlighted_grid_sprite.move(x,y);
}
