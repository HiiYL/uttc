/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1141125087
Contacts #1 : 0164111005 HII YONG LIAN
Lecture Section : TC101
Tutorial Section: TC201
********************************************/
//EXPLANATION
//MANAGES RESOURCES SUCH AS TEXTURES ,FONTS AND SOUNDS
//ALSO LINKS ALL PARTS OF THE PROGRAM TOGETHER
#include "helper.hpp"
void TextureHolder::load(const std::string& name, const std::string& filename)
{
    sf::Texture* texture(new sf::Texture());
    texture->loadFromFile(filename);
    mTextureMap.insert(std::make_pair(name, texture));
}
sf::Texture& TextureHolder::get(const std::string& name)
{
    auto found = mTextureMap.find(name);
    return *found->second;
}


void FontHolder::load(const std::string & name, const std::string& filename)
{
    sf::Font* font(new sf::Font());
    font->loadFromFile(filename);
    mFontMap.insert(std::make_pair(name, font));
}
sf::Font& FontHolder::get(const std::string & name)
{
    std::map<const std::string, sf::Font*>::iterator found = mFontMap.find(name);
    return *found->second;
}



void SoundBufferHolder::load(const std::string & name, const std::string& filename)
{
    sf::SoundBuffer* buffer(new sf::SoundBuffer());
    buffer->loadFromFile(filename);
    mSoundBufferMap.insert(std::make_pair(name, buffer));
}
sf::SoundBuffer& SoundBufferHolder::get(const std::string & name)
{
    std::map<const std::string, sf::SoundBuffer*>::iterator found = mSoundBufferMap.find(name);
    return *found->second;
}
