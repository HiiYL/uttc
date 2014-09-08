#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "screen_3.hpp"
#include "TextCursor.hpp"
class screen_2 : public cScreen    {
public:
    screen_2(ResourceHolder* res_container);
    virtual int Run(sf::RenderWindow &App);
private:
    std::string server;

    TextureHolder* textures;
    ResourceHolder* resources;
    unsigned short port;
    unsigned short port_replay;
    unsigned short port_messaging;

};
