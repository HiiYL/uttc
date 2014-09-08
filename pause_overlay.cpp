/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1141125087
Contacts #1 : 0164111005 HII YONG LIAN
Lecture Section : TC101
Tutorial Section: TC201
********************************************/
//EXPLANATION
//HANDLES THE PAUSE SCREEN
#include "pause_overlay.hpp"
#include "shapeCreate.hpp"
PauseOverlay::PauseOverlay(sf::RenderWindow &App,ResourceHolder* res_container,
                           bool is_online):
    restart(App),menu(App),exit(App), resume(App)
{
    action_keycode = -999;
    game_paused = false;
    restartDisabled = false;
    disconnect_mode = false;
    online_mode = is_online;

    resources = res_container;
    banner.setSize(sf::Vector2f(600,App.getSize().y));
    banner.setPosition(100, 0);
    banner.setOutlineColor(sf::Color::Transparent);
    banner.setFillColor(sf::Color::White);
    if(online_mode)
        restart.load(resources->textures.get("NetworkLobbyBase"),resources->textures.get("NetworkLobbyHover"));
    else
        restart.load(resources->textures.get("RestartBase"),resources->textures.get("RestartHover"));
    //restart.setScale(0.4);
    exit.load(resources->textures.get("ExitBase"),resources->textures.get("ExitHover"));
    //exit.setScale(0.4);
    exit.setPosition(500,350);
    menu.load(resources->textures.get("ReturnMainMenuBase"),resources->textures.get("ReturnMainMenuHover"));
    //menu.setScale(0.4);
    resume.load(resources->textures.get("ResumeBase"),resources->textures.get("ResumeHover"));
    resume.setPosition((App.getSize().x-resume.getGlobalBounds().x)/2,200);


    restart.setPosition(150,350);
    menu.setPosition(325,350);

    screenDarken = createRectangle(sf::Vector2f(App.getSize().x,App.getSize().y),
                                    sf::Vector2f(0,0),sf::Color(0,0,0,128),
                                    sf::Color::Transparent);
    text.setFont(resources->fonts.get("KenVectorFuture"));
    text.setString("     GAME PAUSED");
    text.setPosition(230,150);
    text.setColor(sf::Color::Black);
}
bool PauseOverlay::updateEvent(sf::Event event)    {
    if(event.type == sf::Event::KeyReleased)
        if(event.key.code == sf::Keyboard::Escape && !disconnect_mode)
            game_paused = !game_paused;
    if(game_paused) {
        if(resume.isClicked() && !disconnect_mode)
            game_paused = false;
        if(restart.isClicked(event) && !restartDisabled)    {
            if(online_mode)
                action_keycode = 3;
            else
                action_keycode = 1;
        }
        if(exit.isClicked(event))
            action_keycode = -1;
        if(menu.isClicked(event))
            action_keycode = 0;
        if(action_keycode!=-999)
            return true;
    }
    return false;
}
