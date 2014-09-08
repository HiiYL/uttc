#ifndef PREVIEW_HPP_INCLUDED
#define PREVIEW_HPP_INCLUDED
class Preview : public sf::Drawable , public sf::Transformable {
public:
    Preview(Grid &grid):grid_ptr(&grid){} ;
    void update (sf::Vector2f in_position, HighlightedGrid grid,sf::Texture *texture);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        states.texture = NULL;
        target.draw(preview,states);
    }
private:
    bool find_box(sf::Vector2f in_position);
    Grid* grid_ptr;
    sf::Vector2f position;
    sf::Sprite preview;
    sf::Texture *preview_texture;
};
bool inline Preview::find_box(sf::Vector2f in_position)   {
    for(std::vector<std::vector<sf::RectangleShape> >::iterator i = grid_ptr->grid.begin(); i !=grid_ptr->grid.end(); ++i)
        for(std::vector<sf::RectangleShape>::iterator r = i->begin(); r!= i->end(); ++r)
            if(r->getGlobalBounds().contains(in_position))   {
                position = r->getPosition();
                return true;
            }
    return false;
}
void inline Preview::update(sf::Vector2f in_position, HighlightedGrid grid, sf::Texture *texture)  {
    preview.setTexture(*texture);
    if(find_box(in_position))   {
        if(grid.withinBounds(in_position))
           preview.setColor(sf::Color(255,255,255,128));
        else
            preview.setColor(sf::Color(0,0,0,128));
        preview.setPosition(position);
    }
    else    {
        preview.setColor(sf::Color::Transparent);
    }
    return;
}


#endif // PREVIEW_HPP_INCLUDED
