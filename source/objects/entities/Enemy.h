#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy
{
    /* INITIALIZE */

public:
    Enemy();
    ~Enemy();

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

#endif // ENEMY_H
