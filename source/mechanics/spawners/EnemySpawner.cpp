#include "EnemySpawner.h"

#include "utils/GlobalData.h"
#include "utils/Random.h"
#include "utils/InitialData.h"
#include "objects/entities/Zombie.h"

EnemySpawner::EnemySpawner()
    : m_readyToSpawn{false}
{
    m_spawnDelayMS = InitialData::EnemySpawner::getSpawnDelayMS();
    printf("created spawner\n");
    fflush(stdout);
}

EnemySpawner::~EnemySpawner()
{

}

sf::Vector2f EnemySpawner::getRandomPositionOutsideScreen(const sf::Vector2f &enemySize) const
{
    const sf::Vector2f &windowSize = GlobalData::getInstance()->getWindowSize();

    const float spawnDistanceToScreen = InitialData::EnemySpawner::getSpawnDistanceToScreen();
    const int site = Random::getInt(0, 3);

    const float xMin = /*0.f*/      - enemySize.x   - spawnDistanceToScreen;
    const float xMax = windowSize.x  /*+ 0.f*/       + spawnDistanceToScreen;
    const float yMin = /*0.f*/      - enemySize.y   - spawnDistanceToScreen;
    const float yMax = windowSize.y  /*+ 0.f*/       + spawnDistanceToScreen;

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
    // return nullptr;

    if(m_readyToSpawn)
    {
        m_readyToSpawn = false;

        /// read probabilites
        float probabilities[ZOMBIE_TYPES_COUNT];
        float sum = 0;
        #pragma unroll
        for(int i=0; i<ZOMBIE_TYPES_COUNT; i++)
        {
            probabilities[i] = InitialData::Enemy::Zombie::getSpawnChance(i);
            sum += probabilities[i];
            fflush(stdout);
        }

        /// draw what zombie should spawn
        float randNumber = Random::getFloat(0.f, sum);
        int zombieType = ZOMBIE_TYPES_COUNT-1;
        fflush(stdout);
        sum = 0;
        #pragma unroll
        for(int i=0; i<ZOMBIE_TYPES_COUNT; i++)
        {
            sum += probabilities[i];
            if(randNumber < sum)
            {
                zombieType = i;
                break;
            }
        }

        std::shared_ptr<Enemy> enemy = std::make_shared<Zombie>(zombieType);

        // printf("%u %u\n", m_mapSize.x, m_mapSize.y);
        enemy->init();

        enemy->setPosition(this->getRandomPositionOutsideScreen( enemy->getSize() ));

        return enemy;
    }

    return nullptr;
}
