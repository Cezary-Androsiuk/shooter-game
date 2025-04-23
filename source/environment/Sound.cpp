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
    if(!m_weaponShot.sounds.empty())
    {
        if(m_weaponShot.sounds.front()->getStatus() != sf::Sound::Status::Playing)
        {
            m_weaponShot.sounds.pop();
        }
    }
}

void Sound::playShot()
{
    if(!m_weaponShot.loaded)
        return;

    m_weaponShot.sounds.push(std::make_unique<sf::Sound>());
    sf::Sound *sound = m_weaponShot.sounds.back().get();

    sound->setBuffer(m_weaponShot.buffer);
    sound->setVolume(SOUND::SHOT_VOLUME);
    sound->play();
}
