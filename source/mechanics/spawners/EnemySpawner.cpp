#include "EnemySpawner.h"

EnemySpawner::EnemySpawner()
    : m_readyToSpawn{false}
{
    m_spawnDelayMS = Data::EnemySpawner::getSpawnDelayMS();
}

EnemySpawner::~EnemySpawner()
{

}

sf::Vector2f EnemySpawner::getRandomPositionOutsideScreen(const sf::Vector2f &enemySize) const
{
    const float spawnDistanceToScreen = Data::EnemySpawner::getSpawnDistanceToScreen();
    const int site = Random::getInt(0, 3);

    const float xMin = /*0.f*/      - enemySize.x   - spawnDistanceToScreen;
    const float xMax = m_mapSize.x  /*+ 0.f*/       + spawnDistanceToScreen;
    const float yMin = /*0.f*/      - enemySize.y   - spawnDistanceToScreen;
    const float yMax = m_mapSize.y  /*+ 0.f*/       + spawnDistanceToScreen;

    switch (site) {
    case 0: /// left
        return sf::Vector2f(xMin, Random::getFloat(yMin, yMax));
        break;
    case 1: /// right
        return sf::Vector2f(xMax, Random::getFloat(yMin, yMax));
        break;
    case 2: /// top
        return sf::Vector2f(Random::getFloat(xMin, xMax), yMin);
        break;
    case 3: /// bottom
        return sf::Vector2f(Random::getFloat(xMin, xMax), yMax);
        break;
    }

    /// impossible to reach
    return sf::Vector2f(0.f, 0.f);
}

void EnemySpawner::updateSpawnClock()
{
    if (m_spawnClock.getElapsedTime().asMilliseconds() >= m_spawnDelayMS) {
        m_spawnClock.restart();

        m_readyToSpawn = true;
    }
}

void EnemySpawner::pollEvent(const sf::Event &event)
{

}

void EnemySpawner::update()
{
    this->updateSpawnClock();
}

std::shared_ptr<Enemy> EnemySpawner::createdEnemy()
{
    static int enemiesSpawned = 0;
    if(m_readyToSpawn && enemiesSpawned < m_spawnCountLimit)
    {
        m_readyToSpawn = false;
        if(m_spawnDelayMS < 400)
        {
            if(enemiesSpawned % 10 == 0)
            {
                printf("enemy spawned %d\n", enemiesSpawned);
                fflush(stdout);
            }
        }
        else
        {
            printf("enemy spawned %d\n", enemiesSpawned);
            fflush(stdout);
        }
        ++enemiesSpawned;

        std::shared_ptr<Enemy> enemy = std::make_shared<Zombie>();
        enemy->init();

        enemy->setPosition(this->getRandomPositionOutsideScreen( enemy->getSize() ));

        // printf("%u %u\n", m_mapSize.x, m_mapSize.y);

        return enemy;
    }

    return nullptr;
}

void EnemySpawner::setMapSize(sf::Vector2u mapSize)
{
    m_mapSize = mapSize;
}
