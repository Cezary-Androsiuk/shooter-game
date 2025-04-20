#include "MenuState.h"

#include "utils/GlobalData.h"
#include "utils/Constants.h"

void MenuState::initBackgroundImage()
{
    const sf::Vector2f &windowSize = GlobalData::getInstance()->getWindowSize();
    m_backgroundImageBox = std::make_unique<ImageBox>(
        MENU_BACKGROUND_IMAGE_PATH,
        sf::FloatRect(0,0, windowSize.x, windowSize.y));
}

void MenuState::initStartPlayButton()
{
    const sf::Vector2f &windowRatio = GlobalData::getInstance()->getWindowRatio();

    m_startPlayButton = std::make_unique<Button>();
    m_startPlayButton->setSize(sf::Vector2f((395.f-10) *windowRatio.x, (106.f-10) *windowRatio.y));
    m_startPlayButton->setPosition(sf::Vector2f((89.f+5) *windowRatio.x, (320.f+5) *windowRatio.y));

    // if(m_fontLoaded)
    //     m_startPlayButton->setText(sf::Text("Start Game", m_font, 20 *wr));

    m_startPlayButton->setColor(ELEMENT_COLOR_IDLE);
    m_startPlayButton->setColorHover(ELEMENT_COLOR_HOVER);
    m_startPlayButton->setColorPress(ELEMENT_COLOR_PRESS);
}

void MenuState::initExitGameButton()
{
    const sf::Vector2f &windowRatio = GlobalData::getInstance()->getWindowRatio();

    m_exitButton = std::make_unique<Button>();
    m_exitButton->setSize(sf::Vector2f((395.f-10) *windowRatio.x, (106.f-10) *windowRatio.y));
    m_exitButton->setPosition(sf::Vector2f((89.f+5) *windowRatio.x, (888.f+5) *windowRatio.y));
    m_exitButton->setColor(ELEMENT_COLOR_IDLE);
    m_exitButton->setColorHover(ELEMENT_COLOR_HOVER);
    m_exitButton->setColorPress(ELEMENT_COLOR_PRESS);
}

void MenuState::initObjects()
{
    this->initBackgroundImage();
    this->initStartPlayButton();
    this->initExitGameButton();
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

bool MenuState::exitGameRequest()
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
}

void MenuState::update()
{
    m_startPlayButton->update();
    m_exitButton->update();
}

void MenuState::render(sf::RenderTarget *target)
{
    m_backgroundImageBox->render(target);
    m_startPlayButton->render(target);

    m_exitButton->render(target);
}
