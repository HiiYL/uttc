#ifndef SIDEBAR_HPP_INCLUDED
#define SIDEBAR_HPP_INCLUDED
#include "patch.hpp"
#include "button.hpp"
#include "helper.hpp"
class Sidebar :public sf::Drawable   {
public:
    Sidebar(sf::RenderWindow &App,ResourceHolder* resources);
    bool update(sf::Clock clock);
    bool updateEvents(sf::Event event);
    bool checkTimer(bool timer_enabled,int timer );
    void move(float x, float y);
    void restartClock() {internalClock.restart();};
    void stopMusic()    {music.stop();};
    bool getPaused ()   {return paused;};
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(timer_button);
        target.draw(menu_button);
        target.draw(speaker_button);
    }
private:
    sf::CircleShape timer;
    sf::Text timer_string;
    sf::Clock internalClock;
    sf::Time elapsed;

    int TURN_TIMER;
    sf::Music music;
    sf::Sprite home_button;
    sf::Sprite music_button;
    TextureHolder textures;
    sf::Texture timer_texture;
    sf::Texture speaker;
    sf::Texture speaker_mute;
    sf::Texture home;
    FontHolder fonts;
    sf::Font font;
    sf::RenderWindow& window;
    sf::Vector2f position;
    Button speaker_button;
    Button timer_button;
    Button menu_button;
    bool paused;
    ResourceHolder* resources;
    bool timer_enabled;
};


#endif // SIDEBAR_HPP_INCLUDED
