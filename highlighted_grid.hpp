#ifndef HIGHLIGHTEDGRID_HPP_INCLUDED
#define HIGHLIGHTEDGRID_HPP_INCLUDED
#include "helper.hpp"
#include "grid.hpp"
class HighlightedGrid : public sf::Drawable, public sf::Transformable   {
public:
    HighlightedGrid(Grid &grid,ResourceHolder* res_container, const int &starting_index);
    void update(const int &index);
    bool withinBounds(sf::Vector2f position) {return (highlighted_grid.getGlobalBounds().contains(position));};
    std::pair<int,int> getIndex(sf::Vector2f position);
    void move(float x, float y);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        states.texture = NULL;
        //target.draw(highlighted_grid, states);
        target.draw(highlighted_grid_sprite, states);
    }
    void find_grid(sf::Vector2f position);
private:
    sf::RectangleShape highlighted_grid;
    sf::Sprite highlighted_grid_sprite;
    Grid* grid_ptr;
    int hover_x;
    int hover_y;
};


#endif // HIGHLIGHTEDGRID_H_INCLUDED
