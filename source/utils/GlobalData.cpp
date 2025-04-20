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
}

void GlobalData::loadMainSpriteTexture()
{
    if(!m_mainSpriteTexture.loadFromFile(MAIN_SPRITE_TEXTURE_PATH, sf::IntRect(0,0,500,500)))
    {
        std::string message = "Cannot load main sprite texture from path:\n";
        message += FONT_PATH::OPEN_SANS_REGULAR;
        Support::displayApplicationError(message);
        exit(1);
    }
}

GlobalData::GlobalData()
{
    this->loadFonts();
    this->loadMainSpriteTexture();
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

const sf::Texture &GlobalData::getMainSpriteTexture() const
{
    return m_mainSpriteTexture;
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
