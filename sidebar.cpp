/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1141125087
Contacts #1 : 0164111005 HII YONG LIAN
Lecture Section : TC101
Tutorial Section: TC201
********************************************/
//HANDLES THE SIDEBAR
//AS In THE TIMER AND THE MUSIC BUTTON
#include "sidebar.hpp"
#include <iostream>
Sidebar::Sidebar(sf::RenderWindow &App , ResourceHolder* res_container):window(App),speaker_button(App),timer_button(App),menu_button(App)   {

    timer_enabled = false;
    resources = res_container;
    timer_button.load(resources->textures.get("TimerBase"),resources->textures.get("TimerHover"));
    //timer_button.setScale(0.5);
    timer_button.setPosition(-20,0);
    timer_button.setFont(resources->fonts.get("Simplifica"));
    timer_button.setString("25");
    timer_button.setTextColor(sf::Color::Red);
    timer_button.setTextOrientation("center");

    speaker_button.load(resources->textures.get("MusicMuteBase"), resources->textures.get("MusicMuteHover"),
                        resources->textures.get("MusicPlayBase"),resources->textures.get("MusicPlayHover"));
    //speaker_button.setScale(0.5);
    speaker_button.setPosition(-20,400);

    menu_button.load(resources->textures.get("MenuBase"), resources->textures.get("MenuHover"));
    menu_button.setPosition(-20,200);
    //menu_button.setScale(0.5);
    music.openFromFile("resources/sounds/theme.ogg");
    music.play();
    music.setLoop(1);
}
bool Sidebar::updateEvents(sf::Event event) {
        if(speaker_button.isClicked(event))  {
            if(music.getStatus()== sf::Music::Playing)
                music.pause();
            else
                music.play();
        }
        if(timer_button.isClicked(event))   {
            std::cout<<"Elapsed Time :"<< elapsed.asSeconds() << std::endl;
        }
        if(menu_button.isClicked(event))    {
            return true;   // TODO : FIND BETTER IMPLEMENTATAION
        }
        return false;
}
bool Sidebar::checkTimer(bool timer_enabled, int timer)  {
    if(timer_enabled)   {
        elapsed = internalClock.getElapsedTime();
        int time_left = timer - elapsed.asSeconds() + 1;
        timer_button.setString(patch::to_string(time_left));
        if(elapsed.asSeconds()<timer)
            return true;
        else    {
            internalClock.restart();
            return false;
        }
    }
    else    {
        timer_button.setString("Disabled");
        return true;
    }
}
