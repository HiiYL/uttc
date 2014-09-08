/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1141125087
Contacts #1 : 0164111005 HII YONG LIAN
Lecture Section : TC101
Tutorial Section: TC201
********************************************/
//EXPLANATION
//HANDLES INTIAL HANDSHAKING OF LAN PLAY
//THEN PASSES IT ONTO SCREEN_3 TO HANDLE GAME LOGIC
#include "screen_2.hpp"
#include "cursor.hpp"
screen_2::screen_2(ResourceHolder* res_container)  {            //MULTIPLAYER LOBBY CLASS
    //server = "localhost";
    port = 53006;
    port_replay = 53008;
    port_messaging = 53115;
    resources = res_container;
}
int screen_2::Run(sf::RenderWindow &App)
{
    Button go_back(App);
    go_back.load(resources->textures.get("BackBase"),resources->textures.get("BackHover"));
    go_back.setPosition(-25,-25);

    Button host(App);
    host.load(resources->textures.get("HostBase"),resources->textures.get("HostHover"));
    host.setPosition(300,200);
    host.animatedMovement(sf::Vector2f(50,50),3);

    Button join(App);
    join.load(resources->textures.get("JoinBase"),resources->textures.get("JoinHover"));
    join.setPosition(300,200);
    join.animatedMovement(sf::Vector2f(400,50),3);

    Button address_bar(App);
    address_bar.load(resources->textures.get("AddressBarBase"),resources->textures.get("AddressBarHover"));
    address_bar.setPosition(-25,350);
    address_bar.setFont(resources->fonts.get("Simplifica"));
    address_bar.setString("Type or Click to Enter IP Address");
    address_bar.setTextOrientation("center");
    TextCursor text_cursor(address_bar.getTextPtr());

    bool is_host = false;
    bool is_client = false;
    bool show_address_bar = false;
    bool done = false;
    bool Running = true;
    bool showTextCursor = false;
    sf::Clock clock;
    sf::Time elapsed;
    sf::TcpSocket socket;
    sf::TcpSocket socket_replay;
    sf::TcpSocket socket_messaging;

    sf::TcpListener listener;
    sf::TcpListener listener_replay;
    sf::TcpListener listener_messaging;
    sf::IpAddress ip;
    sf::Sprite background;

    background.setTexture(resources->textures.get("Background"));
    Cursor mouse_cursor(App,resources->textures.get("MouseCursor"));

    listener.setBlocking(0);
    listener_replay.setBlocking(0);
    listener_messaging.setBlocking(0);
    socket.setBlocking(0);
    socket_messaging.setBlocking(0);
    socket_replay.setBlocking(0);
    sf::Packet packet;
    bool only_once = true;
    srand (time(0));
    int starting_index = rand()%9;

    sf::Text server_prompt = createText(sf::Vector2f(200,450),sf::Color::Red,48);
    server_prompt.setFont(resources->fonts.get("Simplifica"));
    server_prompt.setString("     Please choose an Option");
    std::string str;
    while (Running)
    {
        sf::Event event;
        while (App.pollEvent(event))
        {
            if(go_back.isClicked()) //if go_back is clicked return to main menu
                return 0;
            if(host.isClicked(event) && !is_client)   {
                host.animatedMovement(sf::Vector2f(225,50),3);          //animations
                is_host = true;
                is_client = false;
                show_address_bar = false;
            }
            if(join.isClicked(event)&& !is_host)   {
                join.animatedMovement(sf::Vector2f(225,50),3);          //animations
                is_host = false;
                is_client = true;
                show_address_bar = true;
            }
            if(address_bar.isClicked(event) && show_address_bar)    {
                address_bar.setString(str);
                showTextCursor = true;
            }
            if(join.isClicked(event) && str.size()>0)   {
                done = true;
                clock.restart();
            }
            if (event.type == sf::Event::TextEntered && show_address_bar)   {
                {
                    if (event.text.unicode == '\b') {
                        if(str.size()>0)    {
                            str.erase(str.size() - 1, 1);
                            address_bar.setString(str);
                        }
                        else    {
                            showTextCursor = false;
                            address_bar.setString("Enter IP Address");
                        }
                    }
                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))   {
                        if(str.size()>1)    {
                            done = true;
                            clock.restart();
                        }
                    }
                    else if (event.text.unicode < 128)  {
                        str += static_cast<char>(event.text.unicode);
                        address_bar.setString(str);
                        showTextCursor = true;
                    }
                }
            }
            if (event.type == sf::Event::Closed)
            {
                return (-1);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                return 0;
        }
        host.updateAnimation();
        join.updateAnimation();
        mouse_cursor.update();
        text_cursor.update();


        if(is_client && done)
        {
            address_bar.setString("Waiting for Host. . . ");
            std::string received;
            std::string sent = "testpacket";
            //std::cout << str << std::endl;
            socket.connect(str,port);
            socket.receive(packet);
            if(packet >> resources->isTimerActivated >> resources->turn_timer >> resources->start_index)  {
                    socket_replay.connect(str, port_replay);
                    socket_messaging.connect(str,port_messaging);
                    screen_3 s3(resources);
                    s3.setHost(false);      //sets the host to false
                    s3.setPlayerTurn(false);
                    packet.clear();
                    packet << sent;
                    socket.send(packet);
                    s3.setSocket(&socket);
                    s3.setReplaySocket(&socket_replay);
                    s3.setMessageSocket(&socket_messaging);
                    return(s3.Run(App));
            }
            else    {
                elapsed = clock.getElapsedTime();
                if(elapsed.asSeconds()>1)   {
                    std::cout << elapsed.asSeconds();
                    address_bar.setString("No Host Found... Please Try Again");
                    done = false;
                    clock.restart();
                }
            }
        }
        if(is_host) {
            if(only_once)    {
                listener.listen(port);
                listener_replay.listen(port_replay);
                listener_messaging.listen(port_messaging);
                only_once =false;
            }
            sf::IpAddress ip;
            std::string ip_add = ip.getLocalAddress().toString();
            server_prompt.setString("             SERVER HOSTED  \n      Waiting for Connections  \n              " + ip_add );
            listener.accept(socket);
            listener_replay.accept(socket_replay);
            listener_messaging.accept(socket_messaging);
            std::string intial_packet = "abcAbc";        //TESTING THE CONNECTION
            packet.clear();
            resources->start_index = starting_index;
            packet << resources->isTimerActivated << resources->turn_timer << starting_index;
            socket.send(packet);
            socket.receive(packet);
            std::string received_intial_packet;
            packet >> received_intial_packet;
            if(received_intial_packet == "testpacket")    {
                packet.clear();
                screen_3 s3(resources);
                s3.setHost(true);
                s3.setPlayerTurn(true);
                s3.setSocket(&socket);
                s3.setReplaySocket(&socket_replay);
                s3.setMessageSocket(&socket_messaging);
                return(s3.Run(App));
            }
        }

        App.clear(sf::Color::Black);
        App.draw(background);
        if(!is_client)
            App.draw(host);
        if(!is_host)
            App.draw(join);
        App.draw(go_back);
        App.draw(server_prompt);
        if(show_address_bar)    {
            App.draw(address_bar);
            if(showTextCursor)App.draw(text_cursor);
        }
        App.draw(mouse_cursor);
        App.display();
    }
    return (-1);
}
