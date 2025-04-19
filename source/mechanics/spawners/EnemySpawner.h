#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include <SFML/Graphics.hpp>

#include "utils/Random.h"
#include "utils/Data.h"
#include "objects/entities/Enemy.h"
#include "objects/entities/Ghost.h"
#include "objects/entities/Zombie.h"

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

    void setMapSize(sf::Vector2u mapSize);

private:
    sf::Clock m_spawnClock;
    int m_spawnDelayMS;
    bool m_readyToSpawn;
    int m_spawnCountLimit = 1;

    sf::Vector2u m_mapSize;
};

#endif // ENEMYSPAWNER_H
