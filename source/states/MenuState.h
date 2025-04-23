#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <SFML/Graphics.hpp>
#include <SimpleGUI/Button.hpp>
#include <SimpleGUI/ImageBox.hpp>

#include <memory>

#include "State.h"
#include "views/ShopView.h"

using namespace sgui;

class MenuState : public State
{
    /* INITIALIZE */
    void initBackgroundImage();
    void initStartPlayButton();
    void initExitGameButton();
    void initShop();
    void initObjects();

public:
    MenuState();
    ~MenuState();

    void init();
    bool requestPlayState();
    bool requestExitGame();

    void fflushGui();

public:
    void pollEvent(const sf::Event &event) override;
    void update() override;
    void render(sf::RenderTarget *target) override;

private:
    std::unique_ptr<sf::Sprite> m_backgroundSprite;
    std::unique_ptr<Button> m_startPlayButton;

    std::unique_ptr<Button> m_exitButton;

    std::unique_ptr<sf::Sprite> m_shopSprite;

    ShopView m_shopView;
};

#endif // MENUSTATE_H
