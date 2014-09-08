/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1141125087
Contacts #1 : 0164111005 HII YONG LIAN
Lecture Section : TC101
Tutorial Section: TC201
********************************************/
//EXPLANATION
//MAIN FUNCTION
//DOESN"T DO MUCH, JUST CREATES ALL THE SCREENS AND THE RENDER WINDOW
#include <iostream>
#include <SFML/Graphics.hpp>
#include "screens.hpp"
#include "screen_5.hpp"
#include "helper.hpp"
#include "loadResources.hpp"
int main(int argc, char** argv)
{
    std::vector<cScreen*> Screens;
    int screen = 0;
    ResourceHolder resources;
    loadResources(&resources);
    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Ultimate Tic Tac Toe WIP");
    App.setVerticalSyncEnabled(1);
    App.setMouseCursorVisible(false);
    screen_0 s0(&resources);
    Screens.push_back(&s0);
    screen_1 s1(&resources);
    Screens.push_back(&s1);
    screen_2 s2(&resources);
    Screens.push_back(&s2);
    screen_4 s4(&resources);
    Screens.push_back(&s4);
    screen_5 s5(&resources);
    Screens.push_back(&s5);
    while (screen >= 0)
    {
        screen = Screens[screen]->Run(App);
    }

    return EXIT_SUCCESS;
}

