#ifndef PLAY_H
#define PLAY_H

#include <SFML/Graphics.hpp>

#include "State.h"

class Play : public State
{
public:
    Play();
    ~Play();

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

#endif // PLAY_H
