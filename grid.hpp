#ifndef GRID_HPP_INCLUDED
#define GRID_HPP_INCLUDED
#include <SFML/Graphics.hpp>
#include "grid.hpp"
#include "helper.hpp"
class Grid  : public sf::Drawable , public sf::Transformable    {
public:
    friend class Preview;
    Grid(ResourceHolder* res_container);
    bool contains(sf::Vector2f location);
    bool contains_box(sf::Vector2f location, int grid_no, int box);
    sf::Vector2f getPosition(const int &box){return grid[box][0].getPosition();};
    sf::Vector2f getPosition(int i, int j){return grid[i][j].getPosition();};
    int getGridCellSize() {return gridCellSize;};
    int getGridSize()   {return gridSize;};
    int getGridCells() {return gridCells;};
    bool setTexture(int grid_index, int box_index,const sf::Texture *texture);
    void move(float x, float y);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        states.texture = NULL;
        for(std::vector<std::vector<sf::RectangleShape> >::const_iterator i = grid.begin(); i != grid.end(); ++i )
           for(std::vector<sf::RectangleShape>::const_iterator r = i->begin(); r != i->end(); ++r)
                if(r->getTexture() != NULL)     {
                    target.draw(*r,states);
                }

        for(std::vector<sf::RectangleShape>::const_iterator i = overlay.begin(); i != overlay.end(); ++i)
            target.draw(*i,states);
    }
private:
    std::vector<std::vector<sf::RectangleShape> > grid;
    std::vector<sf::RectangleShape> overlay;
    ResourceHolder* resources;
    const int gridCells;                 //number of grids NOTE:DON'T TOUCH THIS, SERIOUSLY JUST DON'T
    const int gridCellSize;            //SIZE OF grid cells
    const int gridSpacing;
    int gridSize;
    int gridX;
    int gridY;
    sf::RectangleShape box;
};



#endif // GRID_HPP_INCLUDED
