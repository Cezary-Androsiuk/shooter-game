#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

#include "State.h"

class Menu : public State
{
    /* INITIALIZE */

public:
    Menu();
    ~Menu();

    void init();

private:
    /* OTHER */

    /* EVENTS */

    /* UPDATE */

    /* RENDER */

public:
    void pollEvent(const sf::Event &event) override;
    void update() override;
    void render(sf::RenderTarget *target) override;

    /// SETTERS
    void setWindowSize(const sf::Vector2u &size);

private:

    sf::Vector2u m_windowSize;
};

#endif // MENU_H
