#include "GlobalData.h"

#include "utils/InitialData.h"
#include "utils/Constants.h"
#include "utils/Support.h"

void GlobalData::loadFonts()
{
    if(!m_fontOpenSansRegular.loadFromFile(FONT_PATH::OPEN_SANS_REGULAR))
    {
        std::string message = "Cannot load font from path:\n";
        message += FONT_PATH::OPEN_SANS_REGULAR;
        Support::displayApplicationError(message);
        exit(1);
    }
    printf("font: 'OpenSans-Regular' loaded\n");

    if(!m_fontInkFree.loadFromFile(FONT_PATH::INK_FREE))
    {
        std::string message = "Cannot load font from path:\n";
        message += FONT_PATH::INK_FREE;
        Support::displayApplicationError(message);
        exit(1);
    }
    printf("font: 'InkFree' loaded\n");

    fflush(stdout);
}

void GlobalData::loadMenuStateBackgroundTexture()
{
    if(!m_menuStateBackgroundTexture.loadFromFile(MENU_BACKGROUND_IMAGE_PATH, sf::IntRect(0,0,1920,1080)))
    {
        std::string message = "Cannot load menu state background texture from path:\n";
        message += MENU_BACKGROUND_IMAGE_PATH;
        Support::displayApplicationError(message);
        exit(1);
    }
    printf("texture: 'menu state background' loaded\n");

    fflush(stdout);
}

void GlobalData::loadPlayBackgroundTexture()
{
    if(!m_playBackgroundTexture.loadFromFile(PLAY_BACKGROUND_IMAGE_PATH, sf::IntRect(0,0,1920,1080)))
    {
        std::string message = "Cannot load play background texture from path:\n";
        message += PLAY_BACKGROUND_IMAGE_PATH;
        Support::displayApplicationError(message);
        exit(1);
    }
    printf("texture: 'play background' loaded\n");

    fflush(stdout);
}

void GlobalData::loadMainSpriteTexture()
{
    if(!m_mainSpriteTexture.loadFromFile(MAIN_SPRITE::TEXTURE_PATH, sf::IntRect(0,0,500,500)))
    {
        std::string message = "Cannot load main sprite texture from path:\n";
        message += MAIN_SPRITE::TEXTURE_PATH;
        Support::displayApplicationError(message);
        exit(1);
    }
    printf("texture: 'main sprite' loaded\n");

    fflush(stdout);
}

void GlobalData::loadPausePlayStateBackgroundTexture()
{
    if(!m_pausePlayStateBackgroundTexture.loadFromFile(PAUSE_BACKGROUND_IMAGE_PATH, sf::IntRect(0,0,1920,1080)))
    {
        std::string message = "Cannot load pause play state background texture from path:\n";
        message += PAUSE_BACKGROUND_IMAGE_PATH;
        Support::displayApplicationError(message);
        exit(1);
    }
    printf("texture: 'pause play state background' loaded\n");

    fflush(stdout);
}

void GlobalData::loadDefeatStateBackgroundTexture()
{
    if(!m_defeatStateBackgroundTexture.loadFromFile(DEFEAT_BACKGROUND_IMAGE_PATH, sf::IntRect(0,0,1920,1080)))
    {
        std::string message = "Cannot load defeat state background texture from path:\n";
        message += DEFEAT_BACKGROUND_IMAGE_PATH;
        Support::displayApplicationError(message);
        exit(1);
    }
    printf("texture: 'defeat state background' loaded\n");

    fflush(stdout);
}

void GlobalData::loadGotDamageAnimationTexture()
{
    if(!m_gotDamageAnimationTexture.loadFromFile(GOT_DAMAGE_ANIMATION_TEXTURE, sf::IntRect(0,0,1920,1080)))
    {
        std::string message = "Cannot load got damage animation texture from path:\n";
        message += GOT_DAMAGE_ANIMATION_TEXTURE;
        Support::displayApplicationError(message);
        exit(1);
    }
    printf("animation texture: 'got damage' loaded\n");

    fflush(stdout);
}

void GlobalData::loadPlayStatInfoNotchTexture()
{
    if(!m_playStatInfoNotchTexture.loadFromFile(PLAY_STAT_INFO_NOTCH_IMAGE_PATH, sf::IntRect(0,0,800,90)))
    {
        std::string message = "Cannot load play stat info notch texture from path:\n";
        message += PLAY_STAT_INFO_NOTCH_IMAGE_PATH;
        Support::displayApplicationError(message);
        exit(1);
    }
    printf("texture: 'play stat info notch' loaded\n");

    fflush(stdout);
}

GlobalData::GlobalData()
{
    this->loadFonts();
    this->loadMenuStateBackgroundTexture();
    this->loadPlayBackgroundTexture();
    this->loadMainSpriteTexture();
    this->loadPausePlayStateBackgroundTexture();
    this->loadDefeatStateBackgroundTexture();
    this->loadGotDamageAnimationTexture();
    this->loadPlayStatInfoNotchTexture();
}

GlobalData *GlobalData::getInstance()
{
    static GlobalData globalData;
    return &globalData;
}

const sf::Font &GlobalData::getFontOpenSansRegular() const
{
    return m_fontOpenSansRegular;
}

const sf::Font &GlobalData::getFontInkFree() const
{
    return m_fontInkFree;
}

const sf::Texture &GlobalData::getMenuStateBackgroundTexture() const
{
    return m_menuStateBackgroundTexture;
}

const sf::Texture &GlobalData::getPlayBackgroundTexture() const
{
    return m_playBackgroundTexture;
}

const sf::Texture &GlobalData::getMainSpriteTexture() const
{
    return m_mainSpriteTexture;
}

const sf::Texture &GlobalData::getPausePlayStateBackgroundTexture() const
{
    return m_pausePlayStateBackgroundTexture;
}

const sf::Texture &GlobalData::getPlayStatInfoNotchTexture() const
{
    return m_playStatInfoNotchTexture;
}

const sf::Texture &GlobalData::getGotDamageAnimationTexture() const
{
    return m_gotDamageAnimationTexture;
}

const sf::Texture &GlobalData::getDefeatStateBackgroundTexture() const
{
    return m_defeatStateBackgroundTexture;
}

const sf::Vector2f &GlobalData::getWindowSize() const
{
    return m_windowSize;
}

const sf::Vector2f &GlobalData::getWindowRatio() const
{
    return m_windowRatio;
}

const sf::Vector2f &GlobalData::getMousePosition() const
{
    return m_mousePosition;
}

void GlobalData::setWindowSize(const sf::Vector2f &windowSize)
{
    m_windowSize = windowSize;
    m_windowRatio = sf::Vector2f(
        m_windowSize.x / InitialData::Game::getTargetWidth(),
        m_windowSize.y / InitialData::Game::getTargetHeight()
    );
    // printf("%0.2f, %0.2f\n", m_windowRatio.x, m_windowRatio.y);
}

void GlobalData::setMousePosition(const sf::Vector2f &mousePosition)
{
    m_mousePosition = mousePosition;
}
