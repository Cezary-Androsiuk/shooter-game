#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <SFML/Graphics.hpp>

class StateManager
{
public:
    StateManager();
    ~StateManager();

private:
    /* OTHER */

    /* EVENTS */

    /* UPDATE */

    /* RENDER */

public:
    void pollEvent();
    void update();
    void render(sf::RenderTarget *target);
};

#endif // STATEMANAGER_H
