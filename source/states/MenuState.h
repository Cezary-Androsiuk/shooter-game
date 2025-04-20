#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <SFML/Graphics.hpp>
#include <SimpleGUI/Button.hpp>
#include <SimpleGUI/ImageBox.hpp>

#include <memory>

#include "State.h"
#include "utils/Constants.h"

extern const char *BACKGROUND_IMAGE_PATH;

#define ELEMENT_COLOR_IDLE sf::Color(0, 0, 0, 0)
#define ELEMENT_COLOR_HOVER sf::Color(220, 220, 220, 20)
#define ELEMENT_COLOR_PRESS sf::Color(220, 220, 220, 40)
#define TEXT_COLOR sf::Color(30, 30, 30)

using namespace sgui;

class MenuState : public State
{
    /* INITIALIZE */
    void initFonts();
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

    /// SETTERS
    void setWindowSize(const sf::Vector2u &size);

private:
    sf::Vector2u m_windowSize;
    /// allows to scale view
    float wr, hr; // width ratio, height ratio

    sf::Font m_font;
    bool m_fontLoaded;

    std::unique_ptr<ImageBox> m_backgroundImageBox;
    std::unique_ptr<Button> m_startPlayButton;

    std::unique_ptr<Button> m_exitButton;
};

#endif // MENUSTATE_H
