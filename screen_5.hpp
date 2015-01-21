#ifndef SCREEN_5_HPP_INCLUDED
#define SCREEN_5_HPP_INCLUDED
#include "game.hpp"
#include "player.hpp"
#include "shapeCreate.hpp"
#include "replay.hpp"
#include "helper.hpp"
#include "cScreen.hpp"
#include <memory>
#include <ctime>
#include <utility>
class screen_5 : public cScreen {
public:
    virtual int Run(sf::RenderWindow &App);
    screen_5(ResourceHolder* res_container);
    screen_5(ResourceHolder* res_container, unsigned int input_file_no);
private:

    sf::Texture continue_button_tex;
    sf::Texture banner_background;
    TextureHolder textures;
    ResourceHolder* resources;
    FontHolder fonts;
    unsigned int file_no;
};


#endif // SCREEN_5_HPP_INCLUDED
