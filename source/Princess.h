#ifndef PRINCESS_H
#define PRINCESS_H

#include <SFML/Graphics.hpp>

class Princess
{
    /* INITIALIZE */
    void initData();
    void initBody();

public:
    Princess();
    ~Princess();

private:
    /* OTHER */


    /* EVENTS */
    void pollEvent();

private:
    /* UPDATE */
    void updateBody();
public:
    void update();

private:
    /* RENDER */
public:
    void render(sf::RenderTarget *target);

public:
    /* GETTERS */


    /* SETTERS */
    void setPosition(const sf::Vector2f &position);

private:

    struct{
        sf::RectangleShape bounds;

    } m_body;

    sf::Vector2f m_position;
    sf::Vector2f m_size;

};

#endif // PRINCESS_H
