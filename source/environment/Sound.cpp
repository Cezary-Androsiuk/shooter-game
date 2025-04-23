#include "Sound.h"

#include "utils/Constants.h"

void Sound::initData()
{

}

void Sound::initMusic()
{

}

void Sound::initWeaponShot()
{
    if(!m_weaponShot.buffer.loadFromFile(SOUND::SHOT_AUDIO_FILE_PATH))
    {
        fprintf(stderr, "shot sound loading failed\n");
        fflush(stderr);
        m_weaponShot.loaded = false;
    }
    m_weaponShot.loaded = true;
}

Sound::Sound()
{
    this->initData();
    this->initMusic();
    this->initWeaponShot();
}

Sound::~Sound()
{

}

Sound *Sound::getInstance()
{
    static Sound sound;
    return &sound;
}

void Sound::update()
{
    if(!m_weaponShot.sound.empty())
    {
        // if(m_weaponShot.sound.front().getStatus() != sf::Sound::Status::Playing)
        // {
        //     m_weaponShot.sound.pop();
        //     printf("Shot POP!\n"); fflush(stdout);
        // }
    }
}

void Sound::playShot()
{
    if(!m_weaponShot.loaded)
        return;

    printf("Shot play!\n"); fflush(stdout);
    sf::Sound *sound = new sf::Sound;
    sound->setBuffer(m_weaponShot.buffer);
    sound->setVolume(SOUND::VOLUME);
    sound->play();
    // m_weaponShot.sound.push(sound);
}
