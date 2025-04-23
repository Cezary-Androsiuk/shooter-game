#ifndef SOUND_H
#define SOUND_H

#include <SFML/Audio.hpp>

#include <queue>
#include <memory>

class Sound
{
    void initData();
    void initMusic();
    void initWeaponShot();

private:
    Sound();
    ~Sound();

    Sound(const Sound &) = delete;
    Sound(Sound &&) = delete;
    void operator=(const Sound &) = delete;
    void operator=(Sound &&) = delete;

public:
    static Sound *getInstance();

    void update();

    void playShot();

private:
    sf::Music m_music;

    struct SoundPair{
        std::queue<std::unique_ptr<sf::Sound>> sounds;
        sf::SoundBuffer buffer;
        bool loaded;
    };

    SoundPair m_weaponShot;
};

#endif // SOUND_H
