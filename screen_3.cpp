/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1141125087
Contacts #1 : 0164111005 HII YONG LIAN
Lecture Section : TC101
Tutorial Section: TC201
********************************************/
//EXPLANATION
//DOES GAME LOGIC OF LAN GAMES
#include "screen_3.hpp"
#include "cursor.hpp"
#include "sidebar.hpp"
#include "board.hpp"
#include "pause_overlay.hpp"
screen_3::screen_3(ResourceHolder* res_container)   {           //MULTIPLAYER GAME
    is_waiting = false;
    port = 53006;
    server = "localhost";
    resources = res_container;
}
int screen_3::Run(sf::RenderWindow &App) {
    Cursor mouse_cursor(App,resources->textures.get("MouseCursor"));

    sf::Sprite mock_cursor;
    mock_cursor.setTexture(resources->textures.get("MockCursor"));

    sf::Sprite background;
    background.setTexture(resources->textures.get("GameBackground"));

    bool Running = true;
    int starting_index = resources->start_index;
    Sidebar sidebar(App, resources);

    sf::Clock clock;

    Board board(starting_index,App, resources);
    board.move(0,50);
    board.animateMovement(sf::Vector2f(200,50),3);
    Replay replay(App, resources);

    Player* player1 (new Player(board.getBoardGrid(),'X'));
    Player* player2 (new Player(board.getBoardGrid(),'O'));
    Player* curr_player;
    player1->setTexture(&resources->textures.get("Player1Mark"));
    player2->setTexture(&resources->textures.get("Player2Mark"));

    Button waiting(App);
    waiting.load(resources->textures.get("WaitingBase"),resources->textures.get("WaitingHover"));
    //waiting.setScale(0.7);
    waiting.setPosition((App.getSize().x-waiting.getGlobalBounds().x)/2+40,App.getSize().y-waiting.getGlobalBounds().y+5);
    VictoryBanner victory_banner(App,player1,player2,replay, resources);
    Messenger messenger(App, resources);
    PauseOverlay pause_screen(App, resources, true);
    while (Running)
    {
        sf::Event event;

        while (App.pollEvent(event))
        {

            if(messageSocket->receive(packet) == sf::Socket::Disconnected)
            {
                sidebar.stopMusic();
                pause_screen.setString("    DISCONNECTED");
                pause_screen.isDisconnected(true);
                pause_screen.setPaused(true);
            }
            else    {
                board.handleEvents(event);             //if not disconnected
                if(sidebar.updateEvents(event))
                    pause_screen.setPaused(true);
            }
            if(pause_screen.updateEvent(event))
            {
               return pause_screen.getActionKeyCode();
            }
            messenger.updateEvents(event);
            if (event.type == sf::Event::Closed)
            {
                return (-1);
            }
            if(victory_banner.handleEvents(event))
            {
                return victory_banner.getActionKeyCode();
            }
        }
        board.updateAnimation();
        messenger.update(messageSocket);
        if((is_host&&player_turn) || (!is_host && !player_turn)) {
            curr_player = player1;
        }
        else {
            curr_player = player2;
        }
        mouse_cursor.update();
        replay.record(player_turn , replaySocket);
        mock_cursor.setPosition(replay.getCurrPosition());
        if(!board.game_done)
            {
                 if(sidebar.checkTimer(resources->isTimerActivated,resources->turn_timer))   {
                    if(player_turn) {
                        is_waiting = false;
                        board.update(curr_player,is_host,socket);
                    }
                    else{
                        is_waiting = true;
                        board.update(curr_player,socket);  //receiver
                    }
                    if(board.round_done)    {
                        sidebar.restartClock();
                        player_turn = !player_turn;
                        board.round_done = false;
                    }
                }
                else    {
                    player_turn = !player_turn;
                    sidebar.restartClock();
                }
            }

            else    {
                replay.save();
                sidebar.stopMusic();
                victory_banner. displayBanner(is_host);
            }
        App.clear();
        App.draw(background);
        App.draw(board);
        if(!player_turn)
            App.draw(mock_cursor);
        if(is_waiting)
            App.draw(waiting);
        App.draw(sidebar);
        if(board.game_done)    {
            App.draw(victory_banner);
        }
        if(pause_screen.isPaused())    {
            App.draw(pause_screen);
        }
        App.draw(messenger);

        App.draw(mouse_cursor);
        App.display();
    }
    return (-1);
}
