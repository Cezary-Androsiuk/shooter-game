#include "PlayState.h"

#include "utils/GlobalData.h"
#include "objects/Weapon.h"

void PlayState::initMap()
{
    m_map = std::make_shared<Map>();
    m_map->buildObstacles();
}

void PlayState::initPlayer()
{
    const sf::Vector2f &windowSize = GlobalData::getInstance()->getWindowSize();

    m_player.setPosition(sf::Vector2f(windowSize.x/2.f, windowSize.y/2.f));
    m_player.setAvailableAreaForPlayer(m_map);
    m_player.setEnemies(&m_enemies);
    m_player.setWeapon(std::make_unique<Weapon>());
    m_player.setArmor(std::make_unique<Armor>());

    m_player.init();
}

void PlayState::initEnemySpawner()
{

}

void PlayState::initObjects()
{
    this->initMap();
    this->initPlayer();
    this->initEnemySpawner();
}

PlayState::PlayState()
{
}

PlayState::~PlayState()
{

}

void PlayState::init()
{
    this->initObjects();
}

void PlayState::updateEnemySpawner()
{
    m_enemySpawner.update();
    std::shared_ptr<Enemy> enemy = m_enemySpawner.createdEnemy();
    if(!enemy)
    {
        return;
    }

    m_enemies.push_back(enemy);

    enemy->setPlayerBounds(m_player.getBounds());
    enemy->setAvailableAreaForEnemy(m_map);
}

void PlayState::updateEnemies()
{
    for(auto enemy : m_enemies)
    {
        enemy->update();
    }
}

void PlayState::pollEvent(const sf::Event &event)
{
    m_enemySpawner.pollEvent(event);
}

void PlayState::update()
{
    this->updateEnemySpawner();
    this->updateEnemies();

    m_player.update();
}

void PlayState::render(sf::RenderTarget *target)
{
    m_map->render(target);
    m_player.render(target);
    for(auto enemy : m_enemies)
        enemy->render(target);
}
