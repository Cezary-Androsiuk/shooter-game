#ifndef STARTMENUVIEW_H
#define STARTMENUVIEW_H

#include <SFML/Graphics.hpp>

class StartMenuView
{
    void initPlayerModel();

public:
    StartMenuView();

private:
    /* OTHER */
    void move(float moveX, float moveY);

    /* EVENTS */

    /* UPDATE */

    /* RENDER */

public:
    void init();
    void pollEvent(const sf::Event &event);
    void update();
    void render(sf::RenderTarget *target);

    /* GETTERS */

    /* SETTERS */


private:
    struct{
        sf::Sprite bounds;
        sf::Sprite skin;
        sf::Sprite shirt;
        sf::Sprite bakpack;
    } m_playerModel;

};

#endif // STARTMENUVIEW_H
