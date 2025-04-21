#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>

#include "objects/Bullet.h"

#include "utils/Constants.h"

class Weapon
{
    void initData();
    void initRenderModel();

public:
    Weapon();
    ~Weapon();

private:
    /* OTHER */

    /* EVENTS */

    /* UPDATE */
    void updateRenderModel();

    /* RENDER */

public:
    void init();
    void pollEvent(const sf::Event &event);
    void update();
    void render(sf::RenderTarget *target);

    void setPlayerSize(sf::Vector2f playerSize);
    void setPosition(sf::Vector2f position);
    void setRotationAngle(float rotationAngle);
    void setWeaponIndex(uint index);

    std::unique_ptr<Bullet> getBulletFromShot();

private:
    struct{
        sf::Sprite weaponBody;
    } m_renderModel;

    sf::Vector2f m_playerSize;
    sf::Vector2f m_position;
    float m_rotationAngle;

    sf::Clock m_shotDelayTimer;
    int m_shotDelay;

    uint m_setWeaponIndex;
    uint m_usedWeaponIndex;

    int m_ammo;
};

#endif // WEAPON_H
