/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1141125087
Contacts #1 : 0164111005 HII YONG LIAN
Lecture Section : TC101
Tutorial Section: TC201
********************************************/
//EXPLANATION
//HANDLES ALL THINGS SINGLE PLAYER
#include "screen_1.hpp"
int screen_1::Run(sf::RenderWindow &App) {

    bool Running = true;
    bool player1_turn = true;
    Replay replay(App, resources);

    Sidebar sidebar(App, resources);
    Cursor mouse_cursor(App,resources->textures.get("MouseCursor"));

    sf::Sprite background;
    background.setTexture(resources->textures.get("GameBackground"));
    srand (time(0));
    int starting_index = rand()%9;
    resources->start_index = starting_index;
    Board board(starting_index, App, resources);
    board.move(0,50);
    board.animateMovement(sf::Vector2f(200,50),3);
    Player* player1 (new Player(board.getBoardGrid(), 'X'));
    Player* player2 (new Player(board.getBoardGrid(),'O'));
    Player* curr_player;
    player1->setTexture(&resources->textures.get("Player1Mark"));
    player2->setTexture(&resources->textures.get("Player2Mark"));

    sf::Text header_text;
    header_text.setPosition(App.getSize().x/3, App.getSize().y*0.01);
    header_text.setColor(sf::Color::Red);
    header_text.setFont(resources->fonts.get("KenVecFuture"));

    VictoryBanner vic(App,player1,player2,replay, resources);
    PauseOverlay pause_screen(App, resources, false);

    while (Running)
    {
        sf::Event Event;
        while (App.pollEvent(Event))
        {
            board.handleEvents(Event);
            if(sidebar.updateEvents(Event))
                pause_screen.setPaused(true);
            if(pause_screen.updateEvent(Event))
            {
               return pause_screen.getActionKeyCode();
            }
            if(vic.handleEvents((Event)))
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
        mouse_cursor.update();                      //tracks the mouse_cursor

        if(!board.game_done && !board.tie)    {     //checks if game is done
            if(sidebar.checkTimer(resources->isTimerActivated,resources->turn_timer))   {
                board.update(curr_player);      //updates all variables
                if(board.round_done)   {
                    player1_turn = !player1_turn;
                    sidebar.restartClock();       //restarts the timer
                    board.round_done = false;
                }
            }
            else   {
                player1_turn = !player1_turn;
                sidebar.restartClock();
            }
            replay.record();
        }
        else
        {
            header_text.setString("");
            replay.save();
            sidebar.stopMusic();
            vic.displayBanner();
        }
        board.updateAnimation();
        App.clear();
        App.draw(background);
        App.draw(board);
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
