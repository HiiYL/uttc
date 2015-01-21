/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1141125087
Contacts #1 : 0164111005 HII YONG LIAN
Lecture Section : TC101
Tutorial Section: TC201
********************************************/
//EXPLANATION
//THIS IS THE CLASS THAT HANDLES REPLAYS
#include "screen_5.hpp"
#include "cursor.hpp"
#include "board.hpp"
#include "victory_banner.hpp"
#include "pause_overlay.hpp"
#include "sidebar.hpp"
screen_5::screen_5(ResourceHolder* res_container)   {       //PLAY REPLAY CLASS
    resources = res_container;
    file_no = 0;
}
screen_5::screen_5(ResourceHolder* res_container, unsigned int input_file_no) {
    file_no = input_file_no;
}
int screen_5::Run(sf::RenderWindow &App) {
    bool Running = true;
    bool player1_turn = true;

    Cursor mouse_cursor(App,resources->textures.get("MouseCursor"));
    sf::Sprite mock_cursor;
    mock_cursor.setTexture(resources->textures.get("MouseCursor"));

    sf::Sprite background;
    background.setTexture(resources->textures.get("GameBackground"));
    ;

    Replay replay(App, resources);
    replay.loadReplay();

    int starting_index = resources->start_index;
    sf::Clock clock;
    sf::Clock wait_timer;
    Board board(starting_index, App, resources);
    board.move(0,50);
    board.animateMovement(sf::Vector2f(200,50),3);

    Player* player1 (new Player(board.getBoardGrid(),'X'));
    Player* player2 (new Player(board.getBoardGrid(),'O'));
    Player* curr_player;
    player1->setTexture(&resources->textures.get("Player1Mark"));
    player2->setTexture(&resources->textures.get("Player2Mark"));

    VictoryBanner vic(App,player1,player2,replay, resources);
    PauseOverlay pause_screen(App, resources, false);

    Sidebar sidebar(App, resources);

    sf::Text header_text;
    header_text.setPosition(App.getSize().x/3, App.getSize().y*0.01);
    header_text.setColor(sf::Color::Red);
    header_text.setFont(resources->fonts.get("KenVecFuture"));

    while (Running)
    {
        sf::Event Event;
        while (App.pollEvent(Event))
        {
            if(sidebar.updateEvents(Event))
                pause_screen.setPaused(true);
            if(pause_screen.updateEvent(Event))
            {
               return pause_screen.getActionKeyCode();
            }
            if(vic.handleEvents(Event))
            {
                return vic.getActionKeyCode();
            }
            if (Event.type == sf::Event::Closed)
            {
                return (-1);
            }
        }
        if(player1_turn)    {
            curr_player = player1;
            header_text.setString("Player 1's Turn");
        }
        else    {
            curr_player = player2;
            header_text.setString("Player 2's Turn");
        }
        board.updateAnimation();
        mouse_cursor.update();
        replay.play(mock_cursor);
        if(!board.game_done)    {
            if(sidebar.checkTimer(resources->isTimerActivated, resources->turn_timer))   {
                board.update(curr_player,mock_cursor.getPosition(), replay.click);
                if(board.round_done)   {
                    player1_turn = !player1_turn;
                    clock.restart();
                    board.round_done = false;
                    sidebar.restartClock();
                }
            }
            else    {
                player1_turn = !player1_turn;
                clock.restart();
                sidebar.restartClock();
            }
        }
        else    {
            header_text.setString("");
            sidebar.stopMusic();
            vic.displayBanner();
        }
        App.clear();
        App.draw(background);
        App.draw(board);
        App.draw(mock_cursor);
        App.draw(sidebar);
        App.draw(header_text);
        if(vic.getShowBanner())    {
            App.draw(vic);
        }
        if(pause_screen.isPaused())    {
            App.draw(pause_screen);
        }
        App.draw(mouse_cursor);
        App.display();
    }
    return (-1);
}
