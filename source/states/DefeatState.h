#ifndef DEFEATSTATE_H
#define DEFEATSTATE_H

#include <SFML/Graphics.hpp>
#include <SimpleGUI/Button.hpp>
#include <SimpleGUI/Label.hpp>

#include <memory>

#include "State.h"

using namespace sgui;

class DefeatState : public State
{
    /* INITIALIZE */
    void initBlurredPlayBackgroundSprite();
    void initBackgroundSprite();
    void initExitPlayButton();
    void initStats();
    void intMargin();

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
    void setEarnedMoney(float earnedMoney);
    void setSurvivedSeconds(int survivedSeconds);

    void refreshStats();
    void disableBlurredPlayBackground();

private:
    sf::Texture m_blurredPlayBackgroundTexture;
    std::unique_ptr<sf::Sprite> m_blurredPlayBackgroundSprite;
    bool m_blurredPlayBackgroundLoaded;

    std::unique_ptr<sf::Sprite> m_backgroundSprite;

    std::unique_ptr<Button> m_exitPlayButton;

    float m_earnedMoney;
    int m_survivedSeconds;
    std::unique_ptr<sgui::Label> m_moneyLabel;
    std::unique_ptr<sgui::Label> m_timeLabel;


    std::shared_ptr<sf::Sprite> m_statInfoNotch;
    struct {
        sf::RectangleShape top;
        sf::RectangleShape bottom;
        sf::RectangleShape left;
        sf::RectangleShape right;
    } m_margin;
};

#endif // DEFEATSTATE_H
