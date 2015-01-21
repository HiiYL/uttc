#ifndef SCREEN_4_HPP_INCLUDED
#define SCREEN_4_HPP_INCLUDED
#include <fstream>
#include "cScreen.hpp"
#include "helper.hpp"
class screen_4 : public cScreen {
public:
    screen_4(ResourceHolder* res_container);
    virtual int Run(sf::RenderWindow &App);
private:
    ResourceHolder *resources;
};

#endif // SCREEN_2_HPP_INCLUDED
