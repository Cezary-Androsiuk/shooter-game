#include "PausePlayState.h"

#include "utils/Constants.h"
#include "utils/GlobalData.h"

void PausePlayState::initBlurredPlayBackgroundSprite()
{
    sf::Vector2u textureSize = m_blurredPlayBackgroundTexture.getSize();
    m_blurredPlayBackgroundSprite = std::make_unique<sf::Sprite>(
        m_blurredPlayBackgroundTexture,
        sf::IntRect(0,0, textureSize.x, textureSize.y));
    /// scale not required, because image size if for sure size of the window
}

void PausePlayState::initBackgroundSprite()
{
    const sf::Vector2f &windowRatio = GlobalData::getInstance()->getWindowRatio();

    m_backgroundSprite = std::make_unique<sf::Sprite>(
        GlobalData::getInstance()->getPausePlayStateBackgroundTexture(),
        sf::IntRect(0,0, 1920, 1080));
    m_backgroundSprite->setScale(windowRatio);
}

void PausePlayState::initContinuePlayButton()
{
    const sf::Vector2f &windowRatio = GlobalData::getInstance()->getWindowRatio();

    m_continuePlayButton = std::make_unique<Button>();
    m_continuePlayButton->setPosition(sf::Vector2f((841.f+5) *windowRatio.x, (455.f+5) *windowRatio.y));
    m_continuePlayButton->setSize(sf::Vector2f((237.f-10) *windowRatio.x, (63.f-10) *windowRatio.y));

    m_continuePlayButton->setColor(ELEMENT_COLOR_IDLE);
    m_continuePlayButton->setColorHover(ELEMENT_COLOR_HOVER);
    m_continuePlayButton->setColorPress(ELEMENT_COLOR_PRESS);
}

void PausePlayState::initExitPlayButton()
{
    const sf::Vector2f &windowRatio = GlobalData::getInstance()->getWindowRatio();

    m_exitPlayButton = std::make_unique<Button>();
    m_exitPlayButton->setPosition(sf::Vector2f((841.f+5) *windowRatio.x, (566.f+5) *windowRatio.y));
    m_exitPlayButton->setSize(sf::Vector2f((237.f-10) *windowRatio.x, (63.f-10) *windowRatio.y));

    m_exitPlayButton->setColor(ELEMENT_COLOR_IDLE);
    m_exitPlayButton->setColorHover(ELEMENT_COLOR_HOVER);
    m_exitPlayButton->setColorPress(ELEMENT_COLOR_PRESS);
}

PausePlayState::PausePlayState()
{

}

PausePlayState::~PausePlayState()
{

}

void PausePlayState::init()
{
    this->initBlurredPlayBackgroundSprite();
    this->initBackgroundSprite();
    this->initContinuePlayButton();
    this->initExitPlayButton();
}

bool PausePlayState::requestContinuePlay()
{
    return m_continuePlayButton->getClick();
}

bool PausePlayState::requestExitPlay()
{
    return m_exitPlayButton->getClick();
}

void PausePlayState::pollEvent(const sf::Event &event)
{
    m_continuePlayButton->event(event);
    m_exitPlayButton->event(event);
}

void PausePlayState::update()
{
    m_continuePlayButton->update();
    m_exitPlayButton->update();
}

void PausePlayState::render(sf::RenderTarget *target)
{
    target->draw(*m_blurredPlayBackgroundSprite);
    target->draw(*m_backgroundSprite);

    m_continuePlayButton->render(target);
    m_exitPlayButton->render(target);
}

void PausePlayState::setBlurredPlayBackgroundImage(const sf::Image &image)
{
    if(!m_blurredPlayBackgroundTexture.loadFromImage(image))
    {
        fprintf(stderr, "failed to load blurred play background from image\n");
        fflush(stderr);
    }
}
