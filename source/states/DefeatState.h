#ifndef DEFEATSTATE_H
#define DEFEATSTATE_H

#include <SFML/Graphics.hpp>
#include <SimpleGUI/Button.hpp>

#include <memory>

#include "State.h"

using namespace sgui;

class DefeatState : public State
{
    /* INITIALIZE */
    void initBlurredPlayBackgroundSprite();
    void initBackgroundSprite();
    void initExitPlayButton();

public:
    DefeatState();
    ~DefeatState();

    void init();

    bool requestExitPlay();

public:
    void pollEvent(const sf::Event &event) override;
    void update() override;
    void render(sf::RenderTarget *target) override;

    void setBlurredPlayBackgroundImage(const sf::Image &image);
    void disableBlurredPlayBackground();

private:
    sf::Texture m_blurredPlayBackgroundTexture;
    std::unique_ptr<sf::Sprite> m_blurredPlayBackgroundSprite;
    bool m_blurredPlayBackgroundLoaded;

    std::unique_ptr<sf::Sprite> m_backgroundSprite;

    std::unique_ptr<Button> m_exitPlayButton;
};

#endif // DEFEATSTATE_H
