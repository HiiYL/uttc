#ifndef COMPANION_HPP_INCLUDED
#define COMPANION_HPP_INCLUDED
#include <SFML/Graphics.hpp>
#include <map>
namespace Textures {
 enum ID {MouseCursor, PlayButton, ExitButton, Background, Home};
}
namespace Fonts {
 enum ID{KenVecFuture};
}
namespace SoundBuffers {
 enum ID{};
}
class TextureHolder
{
public:
    void load(Textures::ID id,const std::string& filename);
    sf::Texture& get(Textures::ID id);
    const sf::Texture& get(Textures::ID id) const;
private:
    std::map<Textures::ID, std::unique_ptr<sf::Texture>> mTextureMap;
};
void TextureHolder::load(Textures::ID id, const std::string& filename)
{
    std::unique_ptr<sf::Texture> texture(new sf::Texture());
    texture->loadFromFile(filename);
    mTextureMap.insert(std::make_pair(id, std::move(texture)));
}
sf::Texture& TextureHolder::get(Textures::ID id)
{
    auto found = mTextureMap.find(id);
    return *found->second;
}

class FontHolder
{
public:
    void load(Fonts::ID id,
    const std::string& filename);
    sf::Font& get(Fonts::ID id);
    const sf::Font& get(Fonts::ID id) const;
private:
    std::map<Fonts::ID, std::unique_ptr<sf::Font>> mFontMap;
};
void FontHolder::load(Fonts::ID id, const std::string& filename)
{
    std::unique_ptr<sf::Font> font(new sf::Font());
    font->loadFromFile(filename);
    mFontMap.insert(std::make_pair(id, std::move(font)));
}
sf::Font& FontHolder::get(Fonts::ID id)
{
    auto found = mFontMap.find(id);
    return *found->second;
}


class SoundBufferHolder
{
public:
    void load(SoundBuffers::ID id,const std::string& filename);
    sf::SoundBuffer& get(SoundBuffers::ID id);
    const sf::SoundBuffer& get(SoundBuffers::ID id) const;
private:
    std::map<SoundBuffers::ID, std::unique_ptr<sf::SoundBuffer>> mSoundBufferMap;
};
void SoundBufferHolder::load(SoundBuffers::ID id, const std::string& filename)
{
    std::unique_ptr<sf::SoundBuffer> buffer(new sf::SoundBuffer());
    buffer->loadFromFile(filename);
    mSoundBufferMap.insert(std::make_pair(id, std::move(buffer)));
}
sf::SoundBuffer& SoundBufferHolder::get(SoundBuffers::ID id)
{
    auto found = mSoundBufferMap.find(id);
    return *found->second;
}
#endif // COMPANION_HPP_INCLUDED
