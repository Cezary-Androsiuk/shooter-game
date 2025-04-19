#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "utils/Data.h"
#include "objects/entities/Enemy.h"

class Zombie : public Enemy
{
    /* INITIALIZE */
    void initData();
    void initBody();

public:
    Zombie();

private:
    /* UPDATE */
    void limitZombieMovementToMap();
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

#endif // ZOMBIE_H
