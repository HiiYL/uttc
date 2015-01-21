#include <iostream>
#include <SFML/Graphics.hpp>
#include "cScreen.hpp"
#include "patch.hpp"
#include "game.hpp"
#include "button.hpp"
#include "helper.hpp"
#include "shapeCreate.hpp"

class screen_0 : public cScreen
{
public:
    screen_0(ResourceHolder* res_container);
    virtual int Run(sf::RenderWindow &App);
private:
    ResourceHolder* resources;
    TextureHolder textures;

};

