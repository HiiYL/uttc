/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1141125087
Contacts #1 : 0164111005 HII YONG LIAN
Lecture Section : TC101
Tutorial Section: TC201
********************************************/
//HANDLES ALL REPLAYS
#include "replay.hpp"
Replay::Replay(sf::RenderWindow &App, ResourceHolder* res_container):window(App),resources(res_container),PollRate(14)  {
     saved = false;
     replay_file[0] = "replay_prev.txt";
     replay_file[1] = "replay_1.txt";
     replay_file[2] = "replay_2.txt";
     replay_file[3] = "replay_3.txt";
     only_once = true;
     loaded = false;
     counter = 2;
     click = false;
}
void Replay::record()   {
    elapsed = internalClock.getElapsedTime();
    position = (sf::Vector2f)sf::Mouse::getPosition(window);

    if(elapsed.asMilliseconds()>PollRate)   {
        replay_temp.push_back(position);
        internalClock.restart();
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        replay_temp.push_back(sf::Vector2f(-5000,-5000));
}
void Replay::record(bool player_turn, sf::TcpSocket* socket)   {
    sf::Packet packet;
    if(player_turn) {
        elapsed = internalClock.getElapsedTime();
        position = (sf::Vector2f)sf::Mouse::getPosition(window);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            packet << -5000 << -5000;
            //out << -5000 << " " << -5000 << std::endl;
            replay_temp.push_back(sf::Vector2f(-5000,-5000));
        }
        if(elapsed.asMilliseconds()>PollRate)   {
            packet << static_cast<int>(position.x) << static_cast<int>(position.y);
            //out << static_cast<int>(position.x) << " " << static_cast<int>(position.y) << std::endl;
            replay_temp.push_back(position);
            internalClock.restart();
        }
        socket->send(packet);
    }
    else    {
        int x,y;
        socket->receive(packet);
        while(packet >> x >> y)    {
            curr_position = sf::Vector2f(x,y);
            replay_temp.push_back(sf::Vector2f(x,y));
        }
    }
}
void Replay::save() {
    if(!saved)  {
        std::ofstream out(replay_file[0].c_str());
        out << resources->isTimerActivated << " " << resources->turn_timer << std::endl;    //save game timer state
        out << resources->start_index << " " << 0 << std::endl;
        for(std::vector<sf::Vector2f>::iterator i = replay_temp.begin(); i != replay_temp.end(); ++i)
            out << i->x << " " << i->y << std::endl;
        saved = true;
    }
}
void Replay::saveToFile(unsigned int i)   {
   if(!saved)
        save();
   std::ifstream  src(replay_file[0].c_str());
   std::ofstream  dst(replay_file[i].c_str());
   dst << src.rdbuf();
}
void Replay::loadReplay() {
    int x,y;
    in.open(replay_file[resources->replay_file_no].c_str());
    while (in >> x >> y)
        moves.push_back(sf::Vector2f(x,y));
    resources->isTimerActivated = moves[0].x;   //load game timer state
    resources->turn_timer = moves[0].y;
    resources->start_index = moves[1].x;
    loaded = true;
}
void Replay::play(sf::Sprite& mockCursor)  {
    //if(!loaded) {
    //    loadReplay();
    //}

    elapsed = internalClock.getElapsedTime();
    click = false;
    if(counter!= moves.size())
    {
        if(moves[counter].x == -5000 && moves[counter].y == -5000)  {
            click = true;
            counter++;
        }
        else
        if(elapsed.asMilliseconds()>PollRate)  {
            mockCursor.setPosition(moves[counter]);
            counter++;
            elapsed = internalClock.restart();
        }
    }
}
bool Replay::checkFile(unsigned int i)  {
    std::ifstream in(replay_file[i].c_str());
    return (in.is_open());
}
