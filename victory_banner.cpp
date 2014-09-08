/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1141125087
Contacts #1 : 0164111005 HII YONG LIAN
Lecture Section : TC101
Tutorial Section: TC201
********************************************/
//IN CHARGE OF THE CREATION OF VICTORY_BANNER
#include "victory_banner.hpp"
VictoryBanner::VictoryBanner(sf::RenderWindow &App, Player* p1,
                             Player* p2,Replay& rep_ref, ResourceHolder* res_container):
    play_again(App),menu(App),exit(App), view_replay(App),save_replay(App),replay_1(App),
    replay_2(App),replay_3(App),replay(rep_ref)
{
    showBanner = false;
    VictoryFanfarePlayed = false;
    DefeatFanfarePlayed = false;
    TieFanfarePlayed = false;
    show_buttons = false;
    replay_saved = false;
    action_keycode = -999;
    resources = res_container;
    player_1 = p1;
    player_2 = p2;
    banner.setSize(sf::Vector2f(App.getSize().x,400));
    banner.setPosition(0, 100);
    banner.setOutlineColor(sf::Color::Transparent);
    banner.setFillColor(sf::Color::White);

    play_again.load(resources->textures.get("PlayAgain"),resources->fonts.get("KenVectorFuture"));
    exit.load(resources->textures.get("Exit"),resources->fonts.get("KenVectorFuture"));
    menu.load(resources->textures.get("Menu"),resources->fonts.get("KenVectorFuture"));
    view_replay.load(resources->textures.get("MatchReplayBase"),resources->textures.get("MatchReplayHover"));
    view_replay.setPosition((App.getSize().x-view_replay.getGlobalBounds().x)/2,200);
    play_again.setPosition(175,350);
    menu.setPosition(375,350);
    exit.setPosition(575,350);

    play_again.setString("New Game");
    exit.setString("EXIT");
    menu.setString("MENU");
    text.setFont(resources->fonts.get("KenVectorFuture"));
    text.setPosition(260,150);
    text.setColor(sf::Color::Black);

    screenDarken = createRectangle(sf::Vector2f(App.getSize().x,App.getSize().y),
                                    sf::Vector2f(0,0),sf::Color(0,0,0,128),
                                    sf::Color::Transparent);
    victory_fanfare.setBuffer(resources->sounds.get("Victory"));
    defeat_fanfare.setBuffer(resources->sounds.get("Defeat"));
    tie_fanfare.setBuffer(resources->sounds.get("Tie"));

    view_replay.load(resources->textures.get("MatchReplayBase"),resources->textures.get("MatchReplayHover"));
    view_replay.setPosition(150,200);

    save_replay.load(resources->textures.get("BarGreyBase"),resources->textures.get("BarGreyHover"));
    save_replay.setPosition(421,200);
    save_replay.setFont(resources->fonts.get("Simplifica"));
    save_replay.setString("Save Replay");
    save_replay.setTextOrientation("center");
    save_replay.setCharacterSize(25);


    replay_1.load(resources->textures.get("CircleRegBlueBase"),resources->textures.get("CircleRegBlueHover"));
    replay_1.setFont(resources->fonts.get("Simplifica"));
    replay_1.setScale(0.3);
    replay_1.setPosition(325,280);
    replay_1.setString("Replay Slot 1");
    replay_1.setTextOrientation("center");
    replay_1.setCharacterSize(25);
    replay_1.animatedMovement(sf::Vector2f(140,280),3);

    replay_2.load(resources->textures.get("CircleRegBlueBase"),resources->textures.get("CircleRegBlueHover"));
    replay_2.setFont(resources->fonts.get("Simplifica"));

    replay_2.setScale(0.3);
    replay_2.setPosition(325,280);
    replay_2.setString("Replay Slot 2");
    replay_2.setTextOrientation("center");
    replay_2.setCharacterSize(25);

    replay_3.load(resources->textures.get("CircleRegBlueBase"),resources->textures.get("CircleRegBlueHover"));
    replay_3.setFont(resources->fonts.get("Simplifica"));
    replay_3.setString("Replay Slot 3");
    replay_3.setTextOrientation("center");

    replay_3.setScale(0.3);
    replay_3.setPosition(325,280);
    replay_3.setCharacterSize(25);
    replay_3.animatedMovement(sf::Vector2f(550,280),3);

    play_again.animatedMovement(sf::Vector2f(175,425),3);
    menu.animatedMovement(sf::Vector2f(375,425),3);
    exit.animatedMovement(sf::Vector2f(575,425),3);
}
bool VictoryBanner::handleEvents(sf::Event event)    {
    if(showBanner)   {
        if(play_again.isClicked(event))
            action_keycode = 1;
        if(exit.isClicked(event))
            action_keycode = -1;
        if(menu.isClicked(event))
            action_keycode = 0;
        if(view_replay.isClicked(event))
            action_keycode = 4;
        if(save_replay.isClicked(event) && !replay_saved)   {
            show_buttons = !show_buttons;
            if(show_buttons)
                save_replay.setString("Cancel");
            else
                save_replay.setString("Save Replays");
        }
        if(show_buttons)    {
            if(replay_1.isClicked(event))
            {
                replay.saveToFile(1);
                show_buttons = false;
                save_replay.setString("Replay Saved");
                replay_saved = true;
            }
            if(replay_2.isClicked(event))
            {
                replay.saveToFile(2);
                show_buttons = false;
                save_replay.setString("Replay Saved");
                replay_saved = true;
            }
            if(replay_3.isClicked(event))
            {
                replay.saveToFile(3);
                show_buttons = false;
                save_replay.setString("Replay Saved");
                replay_saved = true;
            }
        }

        if(action_keycode!=-999)
            return true;
    }
    return false;
}
void VictoryBanner:: displayBanner()  {
        if(show_buttons)    {
            replay_1.updateAnimation();
            replay_3.updateAnimation();
            play_again.updateAnimation();
            menu.updateAnimation();
            exit.updateAnimation();
        }
        if(player_1->getWin())
            text.setString("Player 1 Wins!");
        else if(player_2->getWin())
                text.setString("Player 2 Wins!");
            else
                text.setString("                 Tie!");
        showBanner = true;
        if(!VictoryFanfarePlayed && (player_1->getWin() || player_2->getWin()))     {
            victory_fanfare.play();
            VictoryFanfarePlayed = true;
        }
        if(!TieFanfarePlayed && !player_1->getWin() && !player_2->getWin())   {
            tie_fanfare.play();
            TieFanfarePlayed = true;
        }
    }
void VictoryBanner:: displayBanner(bool is_host)  {
        if(show_buttons)    {
            replay_1.updateAnimation();
            replay_3.updateAnimation();
            play_again.updateAnimation();
            menu.updateAnimation();
            exit.updateAnimation();
        }
        bool win = false;
        bool lose = false;
        if((player_1->getWin() && is_host) || (player_2->getWin() && !is_host))   {
                text.setString("Victory!!");
                win = true;
        }
        else if((player_1->getWin() && !is_host) || (player_2->getWin() && is_host))  {
                text.setString("DEFEAT~");
                lose = true;
            }
            else
                text.setString("ITS A MIRACLE \n            Tie!");
        showBanner = true;
        if(!VictoryFanfarePlayed && win)     {
            victory_fanfare.play();
            VictoryFanfarePlayed = true;
        }
        if(!DefeatFanfarePlayed && lose)    {
            defeat_fanfare.play();
            DefeatFanfarePlayed = true;
        }
}
