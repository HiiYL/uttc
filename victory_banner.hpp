#ifndef VICTORY_BANNER_HPP_INCLUDED
#define VICTORY_BANNER_HPP_INCLUDED
#include "player.hpp"
#include "replay.hpp"
#include "button.hpp"
class VictoryBanner:public sf::Drawable {
public:
    VictoryBanner(sf::RenderWindow &App, Player* player_1, Player* player_2,
                  Replay& rep_ref, ResourceHolder* res_container);
    bool handleEvents(sf::Event event);
    void displayBanner();
    void displayBanner(bool is_host);
    int getActionKeyCode(){return action_keycode;};
    bool getShowBanner()    {return showBanner;};
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(screenDarken);
        target.draw(banner);
        target.draw(text);
        target.draw(view_replay);
        target.draw(save_replay);
        target.draw(play_again);
        target.draw(menu);
        target.draw(exit);
        if(show_buttons)    {
            target.draw(replay_1);
            target.draw(replay_2);
            target.draw(replay_3);
        }
    }
private:
    Button play_again;
    Button menu;
    Button exit;
    Button view_replay;
    Button save_replay;
    Button replay_1,replay_2,replay_3;
    Replay& replay;
    TextureHolder textures;
    FontHolder fonts;
    sf::RectangleShape banner;
    sf::RectangleShape screenDarken;
    Player* player_1;
    Player* player_2;
    bool showBanner;
    bool VictoryFanfarePlayed;
    bool DefeatFanfarePlayed;
    bool TieFanfarePlayed;
    bool show_buttons;
    bool replay_saved;
    sf::Text text;
    int action_keycode;
    ResourceHolder* resources;
    sf::Sound victory_fanfare;
    sf::Sound defeat_fanfare;
    sf::Sound tie_fanfare;
};


#endif // VICTORY_BANNER_HPP_INCLUDED
