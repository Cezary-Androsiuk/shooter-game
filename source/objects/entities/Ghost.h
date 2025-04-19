#ifndef GHOST_H
#define GHOST_H

#include "utils/Data.h"
#include "objects/entities/Enemy.h"

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
        sf::RectangleShape boundsShadow;
    } m_body;
};

#endif // GHOST_H
