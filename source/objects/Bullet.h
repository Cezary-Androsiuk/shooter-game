#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

#include "utils/Constants.h"

class Bullet
{
    void initData();
    void initRenderModel();

public:
    Bullet();
    ~Bullet();

private:
    /* OTHER */

    /* EVENTS */

    /* UPDATE */
    void updatePosition();
    void updateRenderModel();
    void updateReadyToDie();

    /* RENDER */

public:
    void init();
    void pollEvent(const sf::Event &event);
    void update();
    void render(sf::RenderTarget *target);

    void setPosition(sf::Vector2f position);
    void setVelocity(sf::Vector2f velocity);
    void setWeaponIndex(uint index);

    bool getReadyToDie();

private:
    sf::RectangleShape m_boundsShape;
    bool m_boundsVisible;

    struct{
        sf::Sprite body;
    } m_renderModel;

    sf::Vector2f m_velocity;
    sf::Vector2f m_size;
    sf::Vector2f m_position;
    float m_movementSpeed;
    int m_weaponIndex;
    bool m_readyToDie;

    float m_damage;
};

#endif // BULLET_H
