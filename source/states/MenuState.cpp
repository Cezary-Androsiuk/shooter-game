#include "MenuState.h"

#include "utils/GlobalData.h"
#include "utils/Constants.h"

void MenuState::initBackgroundImage()
{
    const sf::Vector2f &windowRatio = GlobalData::getInstance()->getWindowRatio();

    m_backgroundSprite = std::make_unique<sf::Sprite>(
        GlobalData::getInstance()->getMenuStateBackgroundTexture(),
        sf::IntRect(0,0, 1920, 1080));
    m_backgroundSprite->setScale(windowRatio);
}

void MenuState::initStartPlayButton()
{
    const sf::Vector2f &windowRatio = GlobalData::getInstance()->getWindowRatio();

    m_startPlayButton = std::make_unique<Button>();
    m_startPlayButton->setPosition(sf::Vector2f((89.f+5) *windowRatio.x, (320.f+5) *windowRatio.y));
    m_startPlayButton->setSize(sf::Vector2f((395.f-10) *windowRatio.x, (106.f-10) *windowRatio.y));

    m_startPlayButton->setColor(ELEMENT_COLOR_IDLE);
    m_startPlayButton->setColorHover(ELEMENT_COLOR_HOVER);
    m_startPlayButton->setColorPress(ELEMENT_COLOR_PRESS);
}

void MenuState::initExitGameButton()
{
    const sf::Vector2f &windowRatio = GlobalData::getInstance()->getWindowRatio();

    m_exitButton = std::make_unique<Button>();
    m_exitButton->setPosition(sf::Vector2f((89.f+5) *windowRatio.x, (888.f+5) *windowRatio.y));
    m_exitButton->setSize(sf::Vector2f((395.f-10) *windowRatio.x, (106.f-10) *windowRatio.y));

    m_exitButton->setColor(ELEMENT_COLOR_IDLE);
    m_exitButton->setColorHover(ELEMENT_COLOR_HOVER);
    m_exitButton->setColorPress(ELEMENT_COLOR_PRESS);
}

void MenuState::initShop()
{
    const sf::Vector2f &windowRatio = GlobalData::getInstance()->getWindowRatio();

    m_shopSprite = std::make_unique<sf::Sprite>(
        GlobalData::getInstance()->getShopTexture(),
        sf::IntRect(0,0,1284,674));
    m_shopSprite->setScale(windowRatio);
    m_shopSprite->setPosition(sf::Vector2f(575, 320));

    m_shopView.init();
}

void MenuState::initObjects()
{
    this->initBackgroundImage();
    this->initStartPlayButton();
    this->initExitGameButton();
    this->initShop();
}

MenuState::MenuState()
{

}

MenuState::~MenuState()
{

}

void MenuState::init()
{
    this->initObjects();
}

bool MenuState::requestPlayState()
{
    return m_startPlayButton->getClick();
}

bool MenuState::requestExitGame()
{
    return m_exitButton->getClick();
}


void MenuState::fflushGui()
{
    m_startPlayButton->fflush();
}

void MenuState::pollEvent(const sf::Event &event)
{
    m_startPlayButton->event(event);
    m_exitButton->event(event);
    m_shopView.pollEvent(event);
}

void MenuState::update()
{
    m_startPlayButton->update();
    m_exitButton->update();
    m_shopView.update();
}

void MenuState::render(sf::RenderTarget *target)
{
    target->draw(*m_backgroundSprite);
    target->draw(*m_shopSprite);

    m_startPlayButton->render(target);

    m_exitButton->render(target);

    m_shopView.render(target);
}
