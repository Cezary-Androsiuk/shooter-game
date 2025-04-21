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

private:
    struct{
        sf::Sprite weaponBody;
    } m_renderModel;

    int m_ammo;
};

#endif // WEAPON_H
