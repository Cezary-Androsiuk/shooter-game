#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include <SFML/Graphics.hpp>

#include "objects/entities/Enemy.h"
#include "objects/entities/Ghost.h"

#define SPAWN_DELATY_MS 20 /// 2000 ms

class EnemySpawner
{
    /* INITIALIZE */

public:
    EnemySpawner();
    ~EnemySpawner();

private:
    /* OTHER */

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

    void setMapSize(sf::Vector2u mapSize);

private:
    sf::Clock m_spawnClock;
    int m_speedDelayMS;
    bool m_readyToSpawn;

    sf::Vector2u m_mapSize;
};

#endif // ENEMYSPAWNER_H
