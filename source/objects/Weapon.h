#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>

#include "objects/Bullet.h"

#include "utils/Constants.h"

class Weapon
{
    /* INITIALIZE */
    void initData();
    void initRenderModel();

public:
    Weapon();
    ~Weapon();

private:
    /* OTHER */

    /* EVENTS */

    /* UPDATE */
    void updateWeaponType();
    void updateRenderModel();

    /* RENDER */

public:
    void init();
    void pollEvent(const sf::Event &event);
    void update();
    void render(sf::RenderTarget *target);

    std::unique_ptr<Bullet> getBulletFromShot();

    void setPlayerSize(sf::Vector2f playerSize);
    void setPosition(sf::Vector2f position);
    void setRotationAngle(float rotationAngle);
    void setWeaponIndex(uint index);

    void rememberIfMouseButtonClicked();

private:
    struct{
        sf::Sprite body;
    } m_renderModel;

    sf::Vector2f m_playerSize;
    sf::Vector2f m_position;
    float m_rotationAngle;

    struct{
        bool needCheck;
        bool mouseLButtonClickedWhileInitialization;
    } m_clickCorrection;
    sf::Clock m_shotDelayTimer;
    int m_shotDelay;

    uint m_setWeaponIndex;
    uint m_usedWeaponIndex;

    int m_ammo;
};

#endif // WEAPON_H
