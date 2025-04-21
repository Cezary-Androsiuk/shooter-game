#ifndef PAUSEPLAYSTATE_H
#define PAUSEPLAYSTATE_H

#include <SFML/Graphics.hpp>
#include <SimpleGUI/Button.hpp>
#include <SimpleGUI/ImageBox.hpp>

#include <memory>

#include "State.h"

using namespace sgui;

class PausePlayState : public State
{
    /* INITIALIZE */
    void initBlurredPlayBackgroundSprite();
    void initBackgroundSprite();
    void initContinuePlayButton();
    void initExitPlayButton();

public:
    PausePlayState();
    ~PausePlayState();

    void init();

    bool requestContinuePlay();
    bool requestExitPlay();

public:
    void pollEvent(const sf::Event &event) override;
    void update() override;
    void render(sf::RenderTarget *target) override;

    void setBlurredPlayBackgroundImage(const sf::Image &image);

private:
    sf::Texture m_blurredPlayBackgroundTexture;
    std::unique_ptr<sf::Sprite> m_blurredPlayBackgroundSprite;

    std::unique_ptr<sf::Sprite> m_backgroundSprite;

    std::unique_ptr<Button> m_continuePlayButton;
    std::unique_ptr<Button> m_exitPlayButton;
};

#endif // PAUSEPLAYSTATE_H
