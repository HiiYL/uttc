#ifndef HELPER_HPP_INCLUDED
#define HELPER_HPP_INCLUDED
#include <map>
#include <memory>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
class TextureHolder
{
public:
    void load(const std::string& name,const std::string& filename);
    sf::Texture& get(const std::string& name);
private:
    std::map<std::string, sf::Texture*> mTextureMap;
};
class FontHolder
{
public:
    void load(const std::string &name, const std::string& filename);
    sf::Font& get(const std::string &name);
private:
    std::map<const std::string , sf::Font*> mFontMap;
};
class SoundBufferHolder
{
public:
    void load(const std::string & name,const std::string& filename);
    sf::SoundBuffer& get(const std::string & name);
    const sf::SoundBuffer& get(const std::string & name) const;
private:
    std::map<const std::string , sf::SoundBuffer*> mSoundBufferMap;
};
struct ResourceHolder {
    ResourceHolder():replay_file_no(0){};             //this is like the jello that the makes parts of the
    TextureHolder textures;         //program cohesive and able to communicate
    FontHolder fonts;               //with each other
    SoundBufferHolder sounds;
    bool isTimerActivated;
    int turn_timer;
    int start_index;
    int replay_file_no;
};


#endif // HELPER_HPP_INCLUDED
