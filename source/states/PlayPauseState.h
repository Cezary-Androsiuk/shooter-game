#ifndef PLAYPAUSESTATE_H
#define PLAYPAUSESTATE_H

#include <SFML/Graphics.hpp>
#include <SimpleGUI/Button.hpp>

#include <memory>

#include "State.h"

using namespace sgui;

class PlayPauseState : public State
{
    /* INITIALIZE */
    void initContinueButton();
    void initObjects();

public:
    PlayPauseState();
    ~PlayPauseState();

    void init();
    bool continueRequest();

    void fflushGui();

public:
    void pollEvent(const sf::Event &event) override;
    void update() override;
    void render(sf::RenderTarget *target) override;

    /// SETTERS
    void setWindowSize(const sf::Vector2u &size);

private:
    sf::Vector2u m_windowSize;
    /// allows to scale view
    float wr, hr; /// width ratio, height ratio

    std::unique_ptr<Button> m_continueButton;
};

#endif // PLAYPAUSESTATE_H
