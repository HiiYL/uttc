#ifndef SCREEN_3_HPP_INCLUDED
#define SCREEN_3_HPP_INCLUDED
#include <SFML/Network.hpp>
#include "game.hpp"
#include "player.hpp"
#include "Messenger.hpp"
#include "victory_banner.hpp"
#include <memory>
#include <ctime>
#include <utility>
#include "cScreen.hpp"
class screen_3 : public cScreen {
public:
    screen_3(ResourceHolder* res_container);
    virtual int Run(sf::RenderWindow &App);
    void setHost(const bool &a) {is_host = a;};
    void setSocket(sf::TcpSocket* in_socket){socket = in_socket;};
    void setReplaySocket(sf::TcpSocket *in_socket) {replaySocket = in_socket;};
    void setMessageSocket(sf::TcpSocket *in_socket) {messageSocket = in_socket;};
    void setPlayerTurn(const bool &a) { player_turn = a;};
private:
    ResourceHolder* resources;
    bool is_host;
    bool player_turn;
    unsigned int port;
    std::string server;
    sf::TcpSocket* socket;
    sf::TcpSocket* replaySocket;
    sf::TcpSocket* messageSocket;
    sf::Texture continue_button_tex;
    sf::Texture banner_background;
    sf::Packet packet;
    TextureHolder textures;
    FontHolder fonts;
    bool is_waiting;

};

#endif // SCREEN_3_HPP_INCLUDED
