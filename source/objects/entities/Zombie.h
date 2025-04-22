#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "objects/entities/Enemy.h"

class Zombie : public Enemy
{
    /* INITIALIZE */
    void initData();
    void initRenderModel();

public:
    Zombie();
    ~Zombie();

private:
    /* OTHER */

    /* EVENTS */

    /* UPDATE */
    ///
    /// NOTE: move following method logic to PlayState class
    ///
    void limitZombieMovementToMap();
    void updateRenderModel();

    /* RENDER */

public:
    void init() override;

    void pollEvent(const sf::Event &event) override;
    void update() override;
    void render(sf::RenderTarget *target) override;

    void setType(int type);

private:
    sf::RectangleShape m_boundsShape;
    bool m_boundsVisible;

    struct{
        sf::Sprite body;
    } m_renderModel;

    int m_type;
};

#endif // ZOMBIE_H
