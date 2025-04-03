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

private:
    /* OTHER */

    /* EVENTS */

    /* UPDATE */

    /* RENDER */

public:
    void pollEvent() override;
    void update() override;
    void render(sf::RenderTarget *target) override;


private:

};

#endif // MENU_H
