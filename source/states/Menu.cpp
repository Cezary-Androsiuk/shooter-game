#include "Menu.h"

void Menu::initFonts()
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

void Menu::initExitButton()
{
    m_exitButton = new Button();
    m_exitButton->setSize(sf::Vector2f(84.f *wr, 38.f *hr));
    m_exitButton->setPosition(sf::Vector2f(30.f *wr, 30.f *hr));

    if(m_fontLoaded)
        m_exitButton->setText(sf::Text("Exit", m_font, 20 *wr));

    m_exitButton->setColor(ELEMENT_COLOR_IDLE);
    m_exitButton->setColorHover(ELEMENT_COLOR_HOVER);
    m_exitButton->setColorPress(ELEMENT_COLOR_PRESS);
    m_exitButton->setColorText(TEXT_COLOR);
}

void Menu::initObjects()
{
    this->wr = m_windowSize.x / 1920.f; // width ratio
    this->hr = m_windowSize.y / 1080.f; // height ratio

    this->initExitButton();
}

Menu::Menu()
    : m_fontLoaded{false}
{

}

Menu::~Menu()
{

}

void Menu::init()
{
    this->initFonts();
    this->initObjects();
}

bool Menu::hasRequestStateEnd()
{
    if(m_requestStateEnd)
    {
        m_requestStateEnd = false;
        return true;
    }
    return false;
}

void Menu::fflushGui()
{
    m_exitButton->fflush();
    // m_exitButton->event(sf::Event());
}

void Menu::pollEvent(const sf::Event &event)
{
    m_exitButton->event(event);
}

void Menu::update()
{
    m_exitButton->update();
    if(m_exitButton->getClick())
        m_requestStateEnd = true;
}

void Menu::render(sf::RenderTarget *target)
{
    m_exitButton->render(target);
}

void Menu::setWindowSize(const sf::Vector2u &size)
{
    m_windowSize = size;
}
