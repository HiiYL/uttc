/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1141125087
Contacts #1 : 0164111005 HII YONG LIAN
Lecture Section : TC101
Tutorial Section: TC201
********************************************/
//EXPLANATION
//PLAYER INSTANCE FOR EACH PLAYER
//EACH GAME HOLDS 2 PLAYERS
#include "player.hpp"
Player::Player(std::vector<std::vector<char> >* board_grid, char symbol):
        grid_ptr(board_grid),player_symbol(symbol)
{
    win = false;
};
bool Player::updateState(int i, int j)  {
    (*grid_ptr)[i][j] = player_symbol;
    win = checkWin(i);
    return (win);
}
bool Player::checkWin(int index) {
    curr_index = index;
    for(int i = 0 ; i < 7 ; i+=3)   {
        if((*grid_ptr)[index][i] == player_symbol &&
            (*grid_ptr)[index][i+1] == player_symbol &&
             (*grid_ptr)[index][i+2] == player_symbol)       //for vertical
            return true;
    }
    for(int i = 0 ; i < 3; i++) {
        if((*grid_ptr)[index][i] == player_symbol &&
            (*grid_ptr)[index][i+3] == player_symbol &&
             (*grid_ptr)[index][i+6] == player_symbol)
            return true;
    }
    if((*grid_ptr)[index][0] == player_symbol &&
        (*grid_ptr)[index][4] == player_symbol &&
         (*grid_ptr)[index][8] == player_symbol)
        return true;
    if((*grid_ptr)[index][2] == player_symbol &&
        (*grid_ptr)[index][4] == player_symbol &&
         (*grid_ptr)[index][6] == player_symbol)
        return true;
    return false;       //otherwise return false
}
bool Player::checkWinAI(int index, int box_index)  {
    (*grid_ptr)[index][box_index] = player_symbol;
    bool win = false;
   for(int i = 0 ; i < 7 ; i+=3)   {
        if((*grid_ptr)[index][i] == player_symbol &&
            (*grid_ptr)[index][i+1] == player_symbol &&
             (*grid_ptr)[index][i+2] == player_symbol)       //for vertical
            win = true;
    }
    for(int i = 0 ; i < 3; i++) {
        if((*grid_ptr)[index][i] == player_symbol &&
            (*grid_ptr)[index][i+3] == player_symbol &&
             (*grid_ptr)[index][i+6] == player_symbol)
            win = true;
    }
    if((*grid_ptr)[index][0] == player_symbol &&
        (*grid_ptr)[index][4] == player_symbol &&
         (*grid_ptr)[index][8] == player_symbol)
        win = true;
    if((*grid_ptr)[index][2] == player_symbol &&
        (*grid_ptr)[index][4] == player_symbol &&
         (*grid_ptr)[index][6] == player_symbol)
        win = true;
    (*grid_ptr)[index][box_index] = ' ';
    return win;
}
bool Player::checkTie(int index) {
    for(std::vector<char>::iterator i = (*grid_ptr)[index].begin(); i != (*grid_ptr)[index].end(); ++i) {
        if((*i)==' ') {
            return false;
        }
    }
    return true;
}
void Player::setTexture(sf::Texture *tex)    {
    texture = tex;
}
