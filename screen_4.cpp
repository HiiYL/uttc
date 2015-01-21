/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1141125087
Contacts #1 : 0164111005 HII YONG LIAN
Lecture Section : TC101
Tutorial Section: TC201
********************************************/
//EXPLANATION
//THIS IS THE REPLAY GALLERY SCREEN
#include "screen_4.hpp"
#include "replay.hpp"
#include "cursor.hpp"
#include "button.hpp"
screen_4::screen_4(ResourceHolder* res_container)  {            //VIEW REPLAY CLASS
    resources = res_container;
}
int screen_4::Run(sf::RenderWindow &App)
{
    bool file_not_found = false;
    sf::Text text;
    text.setFont(resources->fonts.get("Simplifica"));
    text.setColor(sf::Color::Black);
    text.setString("No Records Found.");
    Replay replay(App, resources);
    Cursor mouse_cursor(App);
    mouse_cursor.setTexture(resources->textures.get("MouseCursor"));
    sf::Sprite background;
    background.setTexture(resources->textures.get("Background"));
    Button back_button(App);
    back_button.load(resources->textures.get("BackBase"),resources->textures.get("BackHover"));

    Button replay_temp(App);
    replay_temp.load(resources->textures.get("CircleRegBlueBase"),resources->textures.get("CircleRegBlueHover"));
    replay_temp.setFont(resources->fonts.get("Simplifica"));
    replay_temp.setTextOrientation("center");
    replay_temp.setScale(0.5);
    replay_temp.setPosition(300,200);
    replay_temp.setString("Previous Match");
    replay_temp.setCharacterSize(35);
    replay_temp.animatedMovement(sf::Vector2f(350,25),3);

    Button replay_1(App);
    replay_1.load(resources->textures.get("CircleRegBlueBase"),resources->textures.get("CircleRegBlueHover"));
    replay_1.setFont(resources->fonts.get("Simplifica"));
    replay_1.setTextOrientation("center");
    replay_1.setScale(0.5);
    replay_1.setPosition(300,200);
    replay_1.setString("Replay 1");
    replay_1.setCharacterSize(35);
    replay_1.animatedMovement(sf::Vector2f(150,275),3);

    Button replay_2(App);
    replay_2.load(resources->textures.get("CircleRegBlueBase"),resources->textures.get("CircleRegBlueHover"));
    replay_2.setFont(resources->fonts.get("Simplifica"));
    replay_2.setTextOrientation("center");
    replay_2.setScale(0.5);
    replay_2.setPosition(300,200);
    replay_2.setString("Replay 2");
    replay_2.setCharacterSize(35);
    replay_2.animatedMovement(sf::Vector2f(350,275),3);
    Button replay_3(App);
    replay_3.load(resources->textures.get("CircleRegBlueBase"),resources->textures.get("CircleRegBlueHover"));
    replay_3.setFont(resources->fonts.get("Simplifica"));
    replay_3.setTextOrientation("center");
    replay_3.setScale(0.5);
    replay_3.setPosition(300,200);
    replay_3.setString("Replay 3");
    replay_3.setCharacterSize(35);
    replay_3.animatedMovement(sf::Vector2f(550,275),3);
    if(!replay.checkFile(0))
        replay_temp.setString("EMPTY");
    if(!replay.checkFile(1))
        replay_1.setString("EMPTY");
    if(!replay.checkFile(2))
        replay_2.setString("EMPTY");
    if(!replay.checkFile(3))
        replay_3.setString("EMPTY");

    while(App.isOpen())
    {
        sf::Event event;
        while(App.pollEvent(event))
        {
            if (back_button.isClicked(event))
                return 0;
            if(replay_temp.isClicked(event))    {
                if(replay.checkFile(0)) {
                    resources->replay_file_no = 0;
                    return 4;
                }
            }
            if (replay_1.isClicked(event))  {
                if(replay.checkFile(1)) {
                    resources->replay_file_no = 0;
                    return 4;
                }
            }
            if (replay_2.isClicked(event))  {
                if(replay.checkFile(2)) {
                    resources->replay_file_no = 0;
                    return 4;
                }
            }
            if (replay_3.isClicked(event))  {
                if(replay.checkFile(3)) {
                    resources->replay_file_no = 0;
                    return 4;
                }
            }
            if(event.type == sf::Event::Closed) {
                resources->replay_file_no = 4;
                return -1;
            }
        }
        replay_temp.updateAnimation();
        replay_1.updateAnimation();
        replay_2.updateAnimation();
        replay_3.updateAnimation();
        mouse_cursor.update();
        App.clear(sf::Color::Black);
        App.draw(background);
        App.draw(back_button);
        if(file_not_found)
            App.draw(text);
        App.draw(replay_temp);
        App.draw(replay_1);
        App.draw(replay_2);
        App.draw(replay_3);

        App.draw(mouse_cursor);
        App.display();
    }
    return -1;
}
