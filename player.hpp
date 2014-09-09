#ifndef PLAYER_NEW_HPP_INCLUDED
#define PLAYER_NEW_HPP_INCLUDED
#include "shapeCreate.hpp"
class Player {
 public:
    Player(std::vector<std::vector<char> >* board_grid, char symbol);
    bool getWin() {return win;};
    sf::Texture* texture;
    bool updateState(int i, int j);      //changes boolean array according to input
    void setWin(const bool &a) {win = a;};

    void setTexture(sf::Texture *tex);
    bool checkTie(int index);
    bool checkWin(int index);
    bool checkWinAI(int index, int box_index);

 private:
    bool win;
    std::vector<std::vector<char> >* grid_ptr;
    int curr_grid_x;        //remembers current grid for use with checking for tie
    int curr_grid_y;        //ditto
    int curr_index;
    char player_symbol;
    bool tie;
};


#endif // PLAYER_NEW_HPP_INCLUDED
