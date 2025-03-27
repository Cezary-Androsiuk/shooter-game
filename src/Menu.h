#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

class Menu
{
    /* INITIALIZE */

public:
    Menu();
    ~Menu();

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

#endif // MENU_H
