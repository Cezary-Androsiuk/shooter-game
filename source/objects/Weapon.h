#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>

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

private:
    struct{
        sf::Sprite weaponBody;
    } m_renderModel;

    sf::Vector2f m_playerSize;
    sf::Vector2f m_position;
    float m_rotationAngle;

    int m_ammo;
};

#endif // WEAPON_H
