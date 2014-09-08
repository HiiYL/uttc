#ifndef MESSENGER_HPP_INCLUDED
#define MESSENGER_HPP_INCLUDED
#include "helper.hpp"
#include "shapeCreate.hpp"
#include "TextCursor.hpp"
#include "button.hpp"
#include <SFML/Network.hpp>
#include <iostream>
class Messenger : public sf::Drawable{
public:
    Messenger(sf::RenderWindow &App, ResourceHolder* res_containers);
    void updateEvents(sf::Event& event);
    void update(sf::TcpSocket *socket);
    void checkShift();
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(chat);
        if(show_chat)   {
          target.draw(message_box);
          target.draw(current_text_box);
          target.draw(textlog);
          target.draw(text);
          target.draw(text_cursor);
        }

    }
private:
    sf::RectangleShape message_box;
    sf::RectangleShape current_text_box;
    sf::Text text;
    sf::Text textlog;
    sf::RenderWindow &window;
    sf::Sound message_receive;
    FontHolder font;
    std::string str;
    std::string chatlog;
    TextCursor text_cursor;
    ResourceHolder* resources;
    Button chat;
    bool send;
    bool show_chat;
};



#endif // MESSENGER_HPP_INCLUDED
