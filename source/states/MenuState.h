#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <SFML/Graphics.hpp>
#include <SimpleGUI/Button.hpp>
#include <SimpleGUI/ImageBox.hpp>

#include <memory>

#include "State.h"

using namespace sgui;

class MenuState : public State
{
    /* INITIALIZE */
    void initBackgroundImage();
    void initStartPlayButton();
    void initExitGameButton();
    void initObjects();

public:
    MenuState();
    ~MenuState();

    void init();
    bool requestPlayState();

    bool exitGameRequest();

    void fflushGui();

public:
    void pollEvent(const sf::Event &event) override;
    void update() override;
    void render(sf::RenderTarget *target) override;

private:
    std::unique_ptr<ImageBox> m_backgroundImageBox;
    std::unique_ptr<Button> m_startPlayButton;

    std::unique_ptr<Button> m_exitButton;
};

#endif // MENUSTATE_H
