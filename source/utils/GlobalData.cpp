#include "GlobalData.h"

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

const sf::Font *GlobalData::getFontOpenSansRegular() const
{
    return &m_fontOpenSansRegular;
}

const sf::Texture *GlobalData::getMainSpriteTexture() const
{
    return &m_mainSpriteTexture;
}
