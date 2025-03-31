#ifndef ROCKET_H
#define ROCKET_H

#include <SFML/Graphics.hpp>

class Rocket
{
    /* INITIALIZE */

public:
    Rocket();
    ~Rocket();

private:
    /* OTHER */


    /* EVENTS */
    void pollEvent();

    /* UPDATE */
    void update();

    /* RENDER */
    void render(sf::RenderTarget *target);


public:

private:

};

#endif // ROCKET_H
