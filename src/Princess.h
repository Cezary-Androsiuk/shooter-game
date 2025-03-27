#ifndef PRINCESS_H
#define PRINCESS_H

#include <SFML/Graphics.hpp>

class Princess
{
    /* INITIALIZE */

public:
    Princess();
    ~Princess();

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

#endif // PRINCESS_H
