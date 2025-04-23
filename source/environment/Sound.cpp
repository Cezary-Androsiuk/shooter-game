#include "Sound.h"

#include "utils/Constants.h"

void Sound::initData()
{

}

void Sound::initMusic()
{
    if(!m_music.openFromFile(SOUND::MUSIC_AUDIO_FILE_PATH))
    {
        fprintf(stderr, "music loading failed\n");
        fflush(stderr);
        m_musicLoaded = false;
        return;
    }
    m_musicLoaded = true;
    m_music.setVolume(3.f);
    m_music.setLoop(true);
}

void Sound::initWeaponShot()
{
    if(!m_weaponShot.buffer.loadFromFile(SOUND::SHOT_AUDIO_FILE_PATH))
    {
        fprintf(stderr, "shot sound loading failed\n");
        fflush(stderr);
        m_weaponShot.loaded = false;
        return;
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

void Sound::playMusic()
{
    if(!m_musicLoaded)
        return;

    if(m_music.getStatus() != sf::Music::Status::Playing)
        m_music.play();
}

void Sound::pauseMusic()
{
    if(!m_musicLoaded)
        return;

    m_music.pause();
}

void Sound::stopMusic()
{
    if(!m_musicLoaded)
        return;

    m_music.stop();
}

void Sound::playShot()
{
    if(!m_weaponShot.loaded)
        return;

    m_weaponShot.sounds.push(std::make_unique<sf::Sound>());
    sf::Sound *sound = m_weaponShot.sounds.back().get();

    sound->setBuffer(m_weaponShot.buffer);
    sound->setVolume(2.f);
    sound->play();
}
