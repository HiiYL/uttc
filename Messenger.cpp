/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1141125087
Contacts #1 : 0164111005 HII YONG LIAN
Lecture Section : TC101
Tutorial Section: TC201
********************************************/
//HANDLES INSTANT MESSAGING IN THE PROGRAM

#include "Messenger.hpp"
Messenger::Messenger(sf::RenderWindow &App,  ResourceHolder* res_containers):window(App),chat(App)
{
    send = false;
    show_chat = false;
    resources = res_containers;
    chat.load(resources->textures.get("ChatBase"),resources->textures.get("ChatHover"));
    //chat.setScale(0.2);
    chat.setPosition(App.getSize().x-chat.getGlobalBounds().x,App.getSize().y-chat.getGlobalBounds().y);
    message_box.setSize(sf::Vector2f(400,100));
    message_box.setPosition(App.getSize().x-message_box.getGlobalBounds().width-chat.getGlobalBounds().x,
                            App.getSize().y-message_box.getGlobalBounds().height-5);
    message_box.setTexture(&resources->textures.get("ChatBox"));
    message_box.setFillColor(sf::Color(255,255,255,128));

    text.setPosition(message_box.getPosition().x+5,
                     message_box.getPosition().y+message_box.getGlobalBounds().height-16);
    text.setFont(resources->fonts.get("Simplifica"));
    text.setCharacterSize(20);
    text.setColor(sf::Color::Blue);
    text.setString("Type to send a message to your opponent");
    text_cursor.bindToText(&text);
    textlog = text;
    textlog.setString("");
    textlog.move(0,-message_box.getGlobalBounds().height+16);

    current_text_box.setSize(sf::Vector2f(message_box.getGlobalBounds().width*0.92,18));
    current_text_box.setPosition(message_box.getPosition().x+2, message_box.getPosition().y +
                                 message_box.getGlobalBounds().height-20);
    current_text_box.setOutlineColor(sf::Color::Black);
    current_text_box.setFillColor(sf::Color::Transparent);
    current_text_box.setOutlineThickness(1);

    message_receive.setBuffer(resources->sounds.get("MessageReceive"));

}
void Messenger::updateEvents(sf::Event& event)
{
    if(chat.isClicked())
        show_chat = !show_chat;
    if(show_chat)   {
        if (event.type == sf::Event::TextEntered)   {
                {
                    if (event.text.unicode == '\b') {
                        if(str.size()>0)
                            str.erase(str.size() - 1, 1);
                        }
                    else if (event.text.unicode < 128)
                        str += static_cast<char>(event.text.unicode);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))    {
                    send = true;
                    str.erase(str.size() - 1, 1);    //remove send character
                }
        }
        text.setString(str);
    }


}
void Messenger::update(sf::TcpSocket *socket)   {
    text_cursor.update();
    sf::Packet packet;
    socket->receive(packet);
    std::string received;
    if(packet >> received)  {
        message_receive.play();
        std::cout << received;
        chatlog += "Opponent :" + received + " \n";
        checkShift();
        textlog.setString(chatlog);
    }
    if(send)    {
        chatlog+= "You :" + str + " \n";
        textlog.setString(chatlog);
        checkShift();
        packet << str;
        socket->send(packet);
        str.clear();
        send = false;
    }
}
void Messenger::checkShift()   {
    std::vector<std::string>::size_type counter = 0;
    for(std::vector<std::string>::size_type i = 0 ; i != chatlog.size(); i++)
        if(chatlog[i] == '\n')
            counter++;
    if(counter > 3) {
        int pos = chatlog.find('\n',0);
        chatlog.erase(0,pos+1);
    }
}
