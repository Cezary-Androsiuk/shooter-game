#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>

class State
{
public:
    virtual ~State();

public:
    /* EVENTS */
    virtual void pollEvent() = 0;

    /* UPDATE */
    virtual void update() = 0;

    /* RENDER */
    virtual void render(sf::RenderTarget *target) = 0;

};

#endif // STATE_H
