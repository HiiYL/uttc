#ifndef REPLAY_HPP_INCLUDED
#define REPLAY_HPP_INCLUDED
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <fstream>
#include "helper.hpp"
class Replay    {
public:
    Replay(sf::RenderWindow &App, ResourceHolder* res_container);
    void record();
    void record(bool player_turn, sf::TcpSocket* socket);
    void save();
    void saveToFile(unsigned int i);
    void loadReplay();
    void play(sf::Sprite& mockCursor);
    bool checkFile(unsigned int i);
    sf::Vector2f getCurrPosition()  {return curr_position;};
    bool click;
private:
    sf::RenderWindow &window;
    bool only_once;
    bool loaded;
    bool saved;
    std::vector<sf::Vector2f>::size_type counter;
    ResourceHolder* resources;
    std::string replay_file[4];
    std::ifstream in;
    std::vector<sf::Vector2f> replay_temp;
    std::vector<sf::Vector2f> moves;
    sf::Vector2f curr_position;
    sf::Time elapsed;
    sf::Clock internalClock;
    sf::Vector2f position;
    const int PollRate;
    unsigned int file_no;
};

#endif // REPLAY_HPP_INCLUDED
