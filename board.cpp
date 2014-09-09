/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1141125087
Contacts #1 : 0164111005 HII YONG LIAN
Lecture Section : TC101
Tutorial Section: TC201
********************************************/
//EXPLANATION
//A CLASS TO LINK PREVIEW, HIGHLIGHT_GRID AND GRID TOGETHER AS WELL AS HANDLE ALL LOGIC
#include <iostream>
#include <algorithm>
#include "board.hpp"
Board::Board(int starting_index, sf::RenderWindow& in_window, ResourceHolder *res_container):
    resources(res_container),grid(res_container),playable_grid(grid,res_container, starting_index),
    preview(grid),window(in_window)
{
    game_done = false;
    round_done = false;
    tie = false;
    is_clicked = false;
    mouseClicked = false;
    only_once = true;
    number_of_moves = 0;
    std::vector<char> temp;
    for(int i = 0 ; i < 9 ; i ++)   {       //creates a 9x9 char representation of the current board
        for(int j = 0; j < 9 ; j++)
            temp.push_back(' ');
        board_grid.push_back(temp);
        temp.clear();
    }
    placement[0].setBuffer(resources->sounds.get("Placement1"));            //self explanatory
    placement[1].setBuffer(resources->sounds.get("Placement2"));
    placement_invalid[0].setBuffer(resources->sounds.get("PlacementInvalid1"));
    placement_invalid[1].setBuffer(resources->sounds.get("PlacementInvalid2"));
    srand(time(0));
};
void Board::handleEvents(const sf::Event &event)   {        //to handle mouse Clicks
    if(event.type == sf::Event::MouseButtonPressed)
        mouseClicked = true;
}
void  Board::update(Player* curr_player)  {
    position = (sf::Vector2f)sf::Mouse::getPosition(window);      // retrieves cursor position from renderWindow
    preview.update(position,playable_grid, curr_player->texture); // updates the preview
    if(mouseClicked)
    {
        mouseClicked = false;
        if(grid.contains(position)) {                            //checks if the cursor is within grid
            if(playable_grid.withinBounds(position))             //checks if the cursor is within highlighted grid
            {
                sound_to_play = rand()%2;
                placement[sound_to_play].play();
                indices = playable_grid.getIndex(position);
                if(grid.setTexture(indices.first,indices.second,curr_player->texture)) {
                    game_done = curr_player->updateState(indices.first,indices.second);
                    playable_grid.update(indices.second);
                    round_done = true;
                    number_of_moves++;
                    tie = checkTie(curr_player, indices.second);
                }
                else
                {
                    sound_to_play = rand()%2;
                    placement_invalid[sound_to_play].play();
                }
            }
            else
            {
                sound_to_play = rand()%2;
                placement_invalid[sound_to_play].play();
            }
        }
    }
}
void Board::updateAI(Player* curr_player, Player* oppo_player)   {
    //int index = rand()%9;
    int index = 0;
    int counter = 0 ;
    std::vector<int> free_index;
    bool decided = false;
    for(int i = 0 ; i < board_grid[indices.second].size(); i++)   {
        if(board_grid[indices.second][i] == ' ')
            free_index.push_back(i);
    }
    for(auto &i : free_index) {
        if(board_grid[indices.second][i] == ' ')    {
                if(curr_player->checkWinAI(indices.second,i))    {
                    std::cout << "YOU LOSE!" << std::endl;
                    index = i;
                    decided = true;
                    break;
                }
                if(oppo_player->checkWinAI(indices.second,i))    {
                    std::cout << "YOU CAN'T WIN" << std::endl;
                    index = i;
                    decided = true;
                    break;
                }
        }
    }
    std::cout << std::endl;
    if(!decided)    {
        std::cout << "I DON'T KNOW WHAT I'M DOING" << std::endl;
        for(auto &i : free_index)   {
            for(int j = 0 ; j < 9; j++)    {
                if(board_grid[i][j]==' ')
                    if(oppo_player->checkWinAI(i,j))    {
                        free_index.erase(find(free_index.begin(),free_index.end(),i));
                        std::cout << "YOU THOUGHT I MIGHT LET YOU WIN BY CLICKING BOX " << i << std::endl;
                        std::cout << "OHO, HOW NAIVE"<< std::endl << std::endl;
                    }
            }
        }
        if(find(free_index.begin(),free_index.end(), 4) != free_index.end())    {
            for(auto &i : free_index)
                std::cout << i << " ";
            std::cout << std::endl;
            index = 4;
        }
        else    {
            int j = rand()%free_index.size();
            index = free_index[j];
        }
    }
    grid.setTexture(indices.second,index,curr_player->texture);
    sound_to_play = rand()%2;
    placement[sound_to_play].play();
    game_done = curr_player->updateState(indices.second,index);
    playable_grid.update(index);
    round_done = true;
    number_of_moves++;
    tie = checkTie(curr_player, indices.second);
}
void Board::update(Player* curr_player, sf::TcpSocket *socket)  {       //update overload for online play(CLIENT)
    position = (sf::Vector2f)sf::Mouse::getPosition(window);
    socket->receive(packet);
    std::pair<int,int> indices;
    if(packet >> indices.first >> indices.second)   {
        if(indices.first < 10 && indices.second < 10 )   {           //BASIC DATA VALIDATION - NEEDED FOR RUBBISH DATA THAT SLIPS PAST THE FIRST TEST FOR WHATEVER REASON
            if(grid.setTexture(indices.first,indices.second,curr_player->texture)) {
                sound_to_play = rand()%2;
                placement[sound_to_play].play();
                game_done = curr_player->updateState(indices.first,indices.second);
                playable_grid.update(indices.second);
                round_done = true;
                number_of_moves++;
                tie = checkTie(curr_player, indices.second);
            }
        }
    }
}

void Board::update(Player* curr_player, bool host, sf::TcpSocket* socket)    {  //update overload for online play(HOST)
    position = (sf::Vector2f)sf::Mouse::getPosition(window);
    preview.update(position,playable_grid, curr_player->texture);
    if(mouseClicked)
    {
        mouseClicked = false;
        if(playable_grid.withinBounds(position))
        {
            sound_to_play = rand()%2;
            placement[sound_to_play].play();
            std::pair<int,int> indices = playable_grid.getIndex(position);  //retrieves index of the cursor
            if(grid.setTexture(indices.first,indices.second,curr_player->texture)) {
                packet.clear();                                             //clears the packet to avoid errant data
                packet << indices.first << indices.second;
                socket->send(packet);
                game_done = curr_player->updateState(indices.first,indices.second);
                playable_grid.update(indices.second);
                round_done = true;                                      //boolean to check if round is done
                number_of_moves++;
                tie = checkTie(curr_player, indices.second);
            }
            else
            {
                sound_to_play = rand()%2;
                placement_invalid[sound_to_play].play();            //error sounds
            }
        }
        else
        {
            sound_to_play = rand()%2;
            placement_invalid[sound_to_play].play();              //ditto
        }
    }
}
void Board::update(Player* curr_player,sf::Vector2f position, bool click)    {  //update overload for replays
    preview.update(position,playable_grid, curr_player->texture);
    if(click)
    {
        if(playable_grid.withinBounds(position))
        {
            sound_to_play = rand()%2;
            placement[sound_to_play].play();
            std::pair<int,int> indices = playable_grid.getIndex(position);
            if(grid.setTexture(indices.first,indices.second,curr_player->texture)) {
                game_done = curr_player->updateState(indices.first,indices.second);
                playable_grid.update(indices.second);
                round_done = true;
                number_of_moves++;
                tie = checkTie(curr_player, indices.first);
            }
        }
    }
}

void Board::move(float x, float y) {     //function needed to preserve click-able areas after movement
    grid.move( x, y);
    playable_grid.move(x,y);
}
void Board::updateAnimation()           //updates the board's location to simulate movement animation
{
    if(only_once)   {
        internalClock.restart();
        only_once = false;
    }
    internalElapsed = internalClock.getElapsedTime();
    if(getPosition()!=animation_dest)    {
            sf::Vector2f movement = internalElapsed.asSeconds()*animation_speed*(animation_dest-getPosition());
            move(movement.x,movement.y);
    }
};
bool Board::checkTie(Player* curr_player, int index)   {        //check if tie
    return (curr_player->checkTie(index) ||number_of_moves>80);
}
