/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1141125087
Contacts #1 : 0164111005 HII YONG LIAN
Lecture Section : TC101
Tutorial Section: TC201
********************************************/
//EXPLANATION
//GENERATES A 9x9 GRID AND PROVIDE HELPFUL FUNCTIONS

#include "grid.hpp"
#include "shapeCreate.hpp"
Grid::Grid(ResourceHolder* res_container):gridCells(9),gridCellSize(50),gridSpacing(30)  {
    gridSize = 3*gridCellSize;
    gridX = 0;
    gridY = 0;
    resources = res_container;//overlay texture
    std::vector<sf::RectangleShape> temp;
    for(int i = 1; i <= gridCells; i++)   {
        for(int j = 1; j <= gridCells; j++)   {
            box = createRectangle(sf::Vector2f(gridCellSize,gridCellSize),sf::Vector2f(gridX,gridY));
            box.setFillColor(sf::Color::Transparent);
            box.setOutlineThickness(0);
            temp.push_back(box);
            if(!(j%3))    {                  //every 3 columns jump forward by gridSpacing
                gridX-=3*gridCellSize;
                gridY+=gridCellSize;
            }
            gridX+=gridCellSize;
        }
        gridX+= gridSpacing + 3*gridCellSize;
        gridY -= 3*gridCellSize;
        if(!(i%3))    {
            gridX-=(9*gridCellSize+3*gridSpacing);
            gridY+=3*gridCellSize + gridSpacing;
        }
        grid.push_back(temp);
        temp.clear();
    }
    for(int i = 0; i < gridCells; i ++) {
        sf::RectangleShape temp = createRectangle(sf::Vector2f(gridSize,gridSize),
                                                  grid[i][0].getPosition(),sf::Color::White,
                                                  sf::Color::Transparent);
        temp.setTexture(&resources->textures.get("Overlay"));
        overlay.push_back(temp);
    }
}
bool Grid::setTexture(int grid_index, int box_index,const sf::Texture *texture) {
    if(grid[grid_index][box_index].getTexture() == NULL)    {
        grid[grid_index][box_index].setFillColor(sf::Color(255,255,255,255));
        grid[grid_index][box_index].setTexture(texture);
        return true;
    }
    return false;
}

bool Grid::contains_box(sf::Vector2f location, int grid_no, int box)  {
    return(grid[grid_no][box].getGlobalBounds().contains(location));
}
bool Grid::contains(sf::Vector2f location)  {
    for(std::vector<std::vector<sf::RectangleShape> >::iterator i = grid.begin(); i != grid.end(); ++i )
           for(std::vector<sf::RectangleShape>::iterator r = i->begin(); r != i->end(); ++r)
            if(r->getGlobalBounds().contains(location))
                return true;
    return false;
}
void Grid::move(float x, float y)       {
    for(std::vector<std::vector<sf::RectangleShape> >::iterator i = grid.begin(); i != grid.end(); ++i )
           for(std::vector<sf::RectangleShape>::iterator r = i->begin(); r != i->end(); ++r)
                r->move(x,y);
    for(std::vector<sf::RectangleShape>::iterator i = overlay.begin(); i != overlay.end(); ++i)
        i->move(x,y);
}
