#include "EnemySpawner.h"
#include <iostream>

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
    if(m_readyToSpawn)
    {
        m_readyToSpawn = false;
        printf("enemy spawned\n");
        fflush(stdout);

        std::shared_ptr<Enemy> enemy = std::make_shared<Ghost>();
        enemy->setPosition({-100.f, -100.f});
        return enemy;
    }

    return nullptr;
}

void EnemySpawner::setMapSize(sf::Vector2u mapSize)
{
    m_mapSize = mapSize;
}
