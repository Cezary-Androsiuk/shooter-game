#ifndef GHOST_H
#define GHOST_H

#include <SFML/Graphics.hpp>

#include "objects/entities/Enemy.h"

constexpr float GHOST_SPEED = 200.f;

class Ghost : public Enemy
{
    /* INITIALIZE */
    void initData();
    void initBody();

public:
    Ghost();

private:

    /* UPDATE */
    void limitGhostMovementToMap();
    void updateBody();

public:
    void init() override;

    void pollEvent(const sf::Event &event) override;
    void update() override;
    void render(sf::RenderTarget *target) override;

private:
    struct{
        sf::RectangleShape bounds;
    } m_body;
};

#endif // GHOST_H
