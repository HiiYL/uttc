#ifndef SCREEN_1_HPP_INCLUDED
#define SCREEN_1_HPP_INCLUDED
#include "cScreen.hpp"
#include "player.hpp"
#include "shapeCreate.hpp"
#include "helper.hpp"
#include "cursor.hpp"
#include "board.hpp"
#include "replay.hpp"
#include "sidebar.hpp"
#include "victory_banner.hpp"
#include "pause_overlay.hpp"
#include <memory>
#include <ctime>
#include <utility>
class screen_1 : public cScreen {
public:
    screen_1(ResourceHolder *res_container) {resources = res_container;};
    virtual int Run(sf::RenderWindow &App);
private:
    ResourceHolder *resources;
    sf::Texture banner_background;
    TextureHolder textures;
    FontHolder fonts;
};


#endif // SCREEN_5_HPP_INCLUDED
