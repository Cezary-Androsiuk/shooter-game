#include "PlayPauseState.h"

void PlayPauseState::initContinueButton()
{
    m_continueButton = std::make_unique<Button>();
    // m_continueButton->setSize(sf::Vector2f())
}

void PlayPauseState::initObjects()
{

}

PlayPauseState::PlayPauseState()
{

}

PlayPauseState::~PlayPauseState()
{

}

void PlayPauseState::init()
{

}

bool PlayPauseState::continueRequest()
{

}

void PlayPauseState::fflushGui()
{

}

void PlayPauseState::pollEvent(const sf::Event &event)
{

}

void PlayPauseState::update()
{

}

void PlayPauseState::render(sf::RenderTarget *target)
{

}

void PlayPauseState::setWindowSize(const sf::Vector2u &size)
{
    m_windowSize = size;
}
