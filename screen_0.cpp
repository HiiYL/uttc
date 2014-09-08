/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1141125087
Contacts #1 : 0164111005 HII YONG LIAN
Lecture Section : TC101
Tutorial Section: TC201
********************************************/
//EXPLANATION
//MAIN MENU CLASS
#include "screen_0.hpp"
screen_0::screen_0(ResourceHolder* res_container)
{
    resources = res_container;
}
int screen_0::Run(sf::RenderWindow &App)        //MAIN MENU SCREEN
{
    bool Running = true;
    int timer = 25;
    bool timer_activated = true;
    bool timer_edit_mode = false;
    resources->turn_timer = timer;
    resources->isTimerActivated = timer_activated;
    Button timer_settings (App);
    timer_settings.load(resources->textures.get("ActivateTimerBase"),resources->textures.get("ActivateTimerHover"),
                        resources->textures.get("DeactivateTimerBase"),resources->textures.get("DeactivateTimerHover"));
    //timer_settings.setScale(0.4);
    timer_settings.setPosition(600,400);
    Button timer_edit(App);
    timer_edit.load(resources->textures.get("EditBase"),resources->textures.get("EditHover"));
    //timer_edit.setScale(0.3);
    timer_edit.setPosition(730,550);

    Button timer_edit_back(App);
    timer_edit_back.load(resources->textures.get("TimerEditBase"),resources->textures.get("TimerEditHover"));
    timer_edit_back.setFont(resources->fonts.get("Simplifica"));
     timer_edit_back.setPosition(timer_settings.getPosition());
    timer_edit_back.setTextOrientation("center");
    timer_edit_back.setString(patch::to_string(timer));


    Button increaseTimer(App);
    increaseTimer.load(resources->textures.get("TimerIncrease"));
    increaseTimer.setPosition(timer_edit_back.getPosition().x+timer_edit_back.getGlobalBounds().x/2-increaseTimer.getGlobalBounds().x/2,
                              timer_edit_back.getPosition().y+30);

    Button decreaseTimer(App);
    decreaseTimer.load(resources->textures.get("TimerDecrease"));
    decreaseTimer.setPosition(timer_edit_back.getPosition().x+timer_edit_back.getGlobalBounds().x/2-increaseTimer.getGlobalBounds().x/2,
                              timer_edit_back.getPosition().y+timer_edit_back.getGlobalBounds().y-60);
    Button local(App);
    local.load(resources->textures.get("LocalBase"), resources->textures.get("LocalHover"));
    local.setPosition(300,200);
    local.animatedMovement(sf::Vector2f(50,50),3);
    Button network(App);
    network.load(resources->textures.get("NetworkBase"), resources->textures.get("NetworkHover"));
    network.setPosition(300,200);
    network.animatedMovement(sf::Vector2f(450,50),3);

    Button view_replays(App);
    view_replays.load(resources->textures.get("ViewReplaysBase"), resources->textures.get("ViewReplaysHover"));
    view_replays.setPosition(300,200);
    view_replays.animatedMovement(sf::Vector2f(250,300),3);
    sf::Sprite menu_background;
    menu_background.setTexture(resources->textures.get("BackgroundClouds"));
    sf::Sprite mouse_cursor;
    mouse_cursor.setTexture(resources->textures.get("MouseCursor"));

    while (Running)
    {
        sf::Event event;
        while (App.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                return (-1);
            }
            if(local.isClicked(event))
                return 1;
            if(network.isClicked(event))
                return 2;
            if(view_replays.isClicked(event))
                return(3);
            if(timer_edit_mode) {
                if(increaseTimer.isClicked(event))
                   timer++;
                if(decreaseTimer.isClicked(event))
                    if(timer>1)
                        timer--;
                timer_edit_back.setString(patch::to_string(timer));
                resources->turn_timer = timer;
            }
            if(timer_edit.isClicked(event))
                timer_edit_mode = !timer_edit_mode;
            else
                if(!timer_edit_mode)
                    if(timer_settings.isClicked(event)) {
                        timer_activated = !timer_activated;
                        resources->isTimerActivated = timer_activated;
                    }
            //Key pressed
        }
        view_replays.updateAnimation();
        local.updateAnimation();
        network.updateAnimation();
        //Clearing screen
        App.clear();
        sf::Vector2i Pointer = sf::Mouse::getPosition(App);
        mouse_cursor.setPosition((sf::Vector2f)Pointer);
        //Drawing
        App.draw(menu_background);
        App.draw(local);
        App.draw(network);
        App.draw(timer_settings);
        App.draw(timer_edit);
        if(timer_edit_mode) {
            App.draw(timer_edit_back);
            App.draw(increaseTimer);
            App.draw(decreaseTimer);
        }
        App.draw(view_replays);
        App.draw(mouse_cursor);
        App.display();

    }

    //Never reaching this point normally, but just in case, exit the application
    return (-1);
}
