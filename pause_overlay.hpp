#ifndef PAUSE_OVERLAY_HPP_INCLUDED
#define PAUSE_OVERLAY_HPP_INCLUDED
#include <SFML/Graphics.hpp>
#include "helper.hpp"
#include "button.hpp"
class PauseOverlay:public sf::Drawable {
public:
    PauseOverlay(sf::RenderWindow &App, ResourceHolder* res_container, bool is_online);

    bool updateEvent(sf::Event event);
    int update();
    int getActionKeyCode(){return action_keycode;};
    bool isPaused() {return game_paused;};
    void setPaused(const bool &a) {game_paused = a;};
    void setString(const std::string &s) {text.setString(s);};
    void disableRestart() {restartDisabled = true;};
    void isDisconnected(bool c) {disconnect_mode = c;};
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(screenDarken);
        target.draw(banner);
        target.draw(text);
        if(!restartDisabled)
            target.draw(restart);
        target.draw(menu);
        target.draw(exit);
        if(!disconnect_mode)
            target.draw(resume);
    }
private:
    ResourceHolder* resources;
    Button restart;
    Button menu;
    Button exit;
    Button resume;
    TextureHolder textures;
    FontHolder fonts;
    sf::RectangleShape banner;
    sf::RectangleShape screenDarken;
    sf::Text text;
    int action_keycode;
    bool game_paused;
    bool restartDisabled;
    bool online_mode;
    bool disconnect_mode;
};

#endif // PAUSE_SCREEN_HPP_INCLUDED
