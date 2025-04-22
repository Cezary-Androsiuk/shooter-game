#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include <SFML/Graphics.hpp>

#include "objects/entities/Enemy.h"

class EnemySpawner
{
    /* INITIALIZE */

public:
    EnemySpawner();
    ~EnemySpawner();

private:
    /* OTHER */
    sf::Vector2f getRandomPositionOutsideScreen(const sf::Vector2f &enemySize) const;

    /* EVENTS */

    /* UPDATE */
    void updateSpawnClock();

    /* RENDER */
    /* ------ */

public:
    void pollEvent(const sf::Event &event);
    void update();
    /// NO RENDER

    std::shared_ptr<Enemy> createdEnemy();

private:
    sf::Clock m_spawnClock;
    int m_spawnDelayMS;
    bool m_readyToSpawn;
    int m_spawnCountLimit = 1;
};

#endif // ENEMYSPAWNER_H
