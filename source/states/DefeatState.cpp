#include "DefeatState.h"

#include "utils/Constants.h"
#include "utils/GlobalData.h"

void DefeatState::initBlurredPlayBackgroundSprite()
{
    if(!m_blurredPlayBackgroundLoaded)
    {
        printf("skipping initialization of blurred play background in Defeat stage\n");
        fflush(stdout);
        return;
    }

    sf::Vector2u textureSize = m_blurredPlayBackgroundTexture.getSize();
    m_blurredPlayBackgroundSprite = std::make_unique<sf::Sprite>(
        m_blurredPlayBackgroundTexture,
        sf::IntRect(0,0, textureSize.x, textureSize.y));
    /// scale not required, because image size if for sure size of the window

    /// but sprite require vertical flip, due to Image mechanic
    m_blurredPlayBackgroundSprite->setScale(1.f, -1.f);
    m_blurredPlayBackgroundSprite->setPosition(0, textureSize.y);
}

void DefeatState::initBackgroundSprite()
{
    const sf::Vector2f &windowRatio = GlobalData::getInstance()->getWindowRatio();

    m_backgroundSprite = std::make_unique<sf::Sprite>(
        GlobalData::getInstance()->getDefeatStateBackgroundTexture(),
        sf::IntRect(0,0, 1920, 1080));
    m_backgroundSprite->setScale(windowRatio);
}

void DefeatState::initExitPlayButton()
{
    const sf::Vector2f &windowRatio = GlobalData::getInstance()->getWindowRatio();

    m_exitPlayButton = std::make_unique<Button>();
    m_exitPlayButton->setPosition(sf::Vector2f((840.f+5) *windowRatio.x, (630.f+5) *windowRatio.y));
    m_exitPlayButton->setSize(sf::Vector2f((236.f-10) *windowRatio.x, (62.f-10) *windowRatio.y));

    m_exitPlayButton->setColor(ELEMENT_COLOR_IDLE);
    m_exitPlayButton->setColorHover(ELEMENT_COLOR_HOVER);
    m_exitPlayButton->setColorPress(ELEMENT_COLOR_PRESS);
}

DefeatState::DefeatState()
    : m_blurredPlayBackgroundLoaded{false}
{

}

DefeatState::~DefeatState()
{

}

void DefeatState::init()
{
    this->initBlurredPlayBackgroundSprite();
    this->initBackgroundSprite();
    this->initExitPlayButton();
}

bool DefeatState::requestExitPlay()
{
    return m_exitPlayButton->getClick();
}

void DefeatState::pollEvent(const sf::Event &event)
{
    m_exitPlayButton->event(event);
}

void DefeatState::update()
{
    m_exitPlayButton->update();
}

void DefeatState::render(sf::RenderTarget *target)
{
    if(m_blurredPlayBackgroundLoaded)
        target->draw(*m_blurredPlayBackgroundSprite);
    target->draw(*m_backgroundSprite);

    m_exitPlayButton->render(target);
}

void DefeatState::setBlurredPlayBackgroundImage(const sf::Image &image)
{
    if(!m_blurredPlayBackgroundTexture.loadFromImage(image))
    {
        fprintf(stderr, "failed to load blurred play background from image\n");
        fflush(stderr);
        m_blurredPlayBackgroundLoaded = false;
    }
    m_blurredPlayBackgroundLoaded = true;
}

void DefeatState::disableBlurredPlayBackground()
{
    m_blurredPlayBackgroundLoaded = false;
}
