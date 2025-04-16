#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SimpleGUI/Button.hpp>

#include "State.h"
#include "utils/Constants.h"

#define ELEMENT_COLOR_IDLE sf::Color(240, 240, 240)
#define ELEMENT_COLOR_HOVER sf::Color(255, 255, 255)
#define ELEMENT_COLOR_PRESS sf::Color(210, 210, 210)
#define TEXT_COLOR sf::Color(30, 30, 30)

using namespace sgui;

class Menu : public State
{
    /* INITIALIZE */
    void initFonts();
    void initExitButton();
    void initContinueButton();
    void initObjects();

public:
    Menu();
    ~Menu();

    void init();
    bool hasRequestStateEnd();

    void fflushGui();

public:
    void pollEvent(const sf::Event &event) override;
    void update() override;
    void render(sf::RenderTarget *target) override;

    /// SETTERS
    void setWindowSize(const sf::Vector2u &size);

private:
    /// allows to scale view
    float wr, hr; // width ratio, height ratio
    bool m_requestStateEnd;

    sf::Font m_font;
    bool m_fontLoaded;

    sf::Vector2u m_windowSize;

    Button *m_exitButton;
};

#endif // MENU_H
