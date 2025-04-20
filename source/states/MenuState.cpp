#include "MenuState.h"

const char *BACKGROUND_IMAGE_PATH = "resources/images/MenuBackground.png";

void MenuState::initFonts()
{
    if(!m_font.loadFromFile(FONT_PATH))
    {
        fprintf(stderr, "loading font file failed from %s", FONT_PATH);
    }
    else
    {
        m_fontLoaded = true;
    }
}

void MenuState::initBackgroundImage()
{
    m_backgroundImageBox = std::make_unique<ImageBox>(
        BACKGROUND_IMAGE_PATH,
        sf::FloatRect(0,0, m_windowSize.x, m_windowSize.y));
}

void MenuState::initStartPlayButton()
{
    m_startPlayButton = std::make_unique<Button>();
    m_startPlayButton->setSize(sf::Vector2f((395.f-10) *wr, (106.f-10) *hr));
    m_startPlayButton->setPosition(sf::Vector2f((89.f+5) *wr, (320.f+5) *hr));

    // if(m_fontLoaded)
    //     m_startPlayButton->setText(sf::Text("Start Game", m_font, 20 *wr));

    m_startPlayButton->setColor(ELEMENT_COLOR_IDLE);
    m_startPlayButton->setColorHover(ELEMENT_COLOR_HOVER);
    m_startPlayButton->setColorPress(ELEMENT_COLOR_PRESS);
}

void MenuState::initExitGameButton()
{
    m_exitButton = std::make_unique<Button>();
    m_exitButton->setSize(sf::Vector2f((395.f-10) *wr, (106.f-10) *hr));
    m_exitButton->setPosition(sf::Vector2f((89.f+5) *wr, (888.f+5) *hr));
    m_exitButton->setColor(ELEMENT_COLOR_IDLE);
    m_exitButton->setColorHover(ELEMENT_COLOR_HOVER);
    m_exitButton->setColorPress(ELEMENT_COLOR_PRESS);
}

void MenuState::initObjects()
{
    this->wr = m_windowSize.x / 1920.f; // width ratio
    this->hr = m_windowSize.y / 1080.f; // height ratio

    this->initBackgroundImage();
    this->initStartPlayButton();
    this->initExitGameButton();
}

MenuState::MenuState()
    : m_fontLoaded{false}
{

}

MenuState::~MenuState()
{

}

void MenuState::init()
{
    this->initFonts();
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

void MenuState::setWindowSize(const sf::Vector2u &size)
{
    m_windowSize = size;
}
