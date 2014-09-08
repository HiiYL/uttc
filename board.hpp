#ifndef BOARD_HPP_INCLUDED
#define BOARD_HPP_INCLUDED
#include "grid.hpp"
#include "highlighted_grid.hpp"
#include "preview.hpp"
#include "SFML/Network.hpp"
#include "player.hpp"
class Board : public sf::Drawable, public sf::Transformable{            //creates a board object that connects highlight grid,
public:                                                                 //preview and grid
    Board(int starting_index, sf::RenderWindow& in_window, ResourceHolder *res_container);
    void handleEvents(const sf::Event& event);
    void update(Player* curr_player);
    void animateMovement(sf::Vector2f dest, float speed) {animation_dest = dest; animation_speed = speed;};//overloads update function with different
    void update(Player* curr_player,sf::Vector2f position, bool click);                                    //variables for different results
    void update(Player* curr_player, sf::TcpSocket *socket);
    void update(Player* curr_player, bool wtf, sf::TcpSocket *socket);
    sf::Vector2f getPosition()  {return grid.getPosition(0,0);};
    std::vector<std::vector<char> >* getBoardGrid() {return &board_grid;};
    void move(float x, float y);
    void updateAnimation();

    bool game_done;
    bool round_done;
    bool tie;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const      //draw function to draw the board
    {                                                                               //as one cohesive object
        states.transform *= getTransform();
        states.texture = NULL;
        target.draw(grid,states);
        target.draw(playable_grid,states);
        target.draw(preview,states);
    }
private:
    bool checkTie(Player* curr_player, int index);                      //accepts a Player pointer and an unsigned int to determine
    ResourceHolder* resources;                                          //if match ends in tie
    Grid grid;
    HighlightedGrid playable_grid;
    Preview preview;
    int starting_index;
    bool is_clicked;
    bool mouseClicked;
    bool only_once;
    sf::RenderWindow &window;
    sf::Vector2f position;
    sf::Packet packet;
    sf::Sound placement[2];
    sf::Sound placement_invalid[2];
    sf::Event* event_ptr;
    sf::Time internalElapsed;
    sf::Clock internalClock;
    int sound_to_play;
    int number_of_moves;
    float animation_speed;
    sf::Vector2f animation_dest;
    std::vector<std::vector<char> > board_grid;
};
#endif // BOARD_HPP_INCLUDED
