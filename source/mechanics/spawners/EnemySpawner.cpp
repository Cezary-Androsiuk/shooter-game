#include "EnemySpawner.h"

EnemySpawner::EnemySpawner()
    : m_readyToSpawn{false}
{
    m_speedDelayMS = SPAWN_DELATY_MS;
}

EnemySpawner::~EnemySpawner()
{

}

void EnemySpawner::updateSpawnClock()
{
    if (m_spawnClock.getElapsedTime().asMilliseconds() >= m_speedDelayMS) {
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
    if(m_readyToSpawn)
    {
        m_readyToSpawn = false;
        if(++enemiesSpawned % 10 == 0)
        {
            printf("enemy spawned %d\n", enemiesSpawned);
            fflush(stdout);
        }

        std::shared_ptr<Enemy> enemy = std::make_shared<Ghost>();

        // dynamic_cast<Ghost *>(enemy.get())->init();
        enemy->init();

        const sf::Vector2f &enemySize = enemy->getSize();
        const float spawnDistanceToScreen = Data::EnemySpawner::getSpawnDistanceToScreen();
        const int site = Random::getInt(0, 3);

        const float xMin = /*0.f*/      - enemySize.x   - spawnDistanceToScreen;
        const float xMax = m_mapSize.x  /*+ 0.f*/       + spawnDistanceToScreen;
        const float yMin = /*0.f*/      - enemySize.y   - spawnDistanceToScreen;
        const float yMax = m_mapSize.y  /*+ 0.f*/       + spawnDistanceToScreen;

        switch (site) {
        case 0: /// left
            enemy->setPosition({xMin, Random::getFloat(yMin, yMax)});
            break;
        case 1: /// right
            enemy->setPosition({xMax, Random::getFloat(yMin, yMax)});
            break;
        case 2: /// top
            enemy->setPosition({Random::getFloat(xMin, xMax), yMin});
            break;
        case 3: /// bottom
            enemy->setPosition({Random::getFloat(xMin, xMax), yMax});
            break;
        }

        // printf("%u %u\n", m_mapSize.x, m_mapSize.y);

        return enemy;
    }

    return nullptr;
}

void EnemySpawner::setMapSize(sf::Vector2u mapSize)
{
    m_mapSize = mapSize;
}
