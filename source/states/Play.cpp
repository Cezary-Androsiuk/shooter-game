#include "Play.h"


void Play::initMap()
{
    m_map = std::make_shared<Map>();
    m_map->setMapSize(m_windowSize);
    m_map->buildObstacles();
}

void Play::initPlayer()
{
    float width = static_cast<float>(m_windowSize.x);
    float height = static_cast<float>(m_windowSize.y);
    m_player.setPosition(sf::Vector2f(width/2.f, height/2.f));
    m_player.setAvailableAreaForPlayer(m_map);
    m_player.setEnemies(&m_enemies);
}

void Play::initEnemySpawner()
{
    m_enemySpawner.setMapSize(m_windowSize);

}

void Play::initObjects()
{
    this->initMap();
    this->initPlayer();
    this->initEnemySpawner();
}

Play::Play()
{
}

Play::~Play()
{

}

void Play::init()
{
    this->initObjects();
}

void Play::updateEnemySpawner()
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

void Play::updateEnemies()
{
    for(auto enemy : m_enemies)
    {
        enemy->update();
    }
}

void Play::pollEvent(const sf::Event &event)
{
    m_enemySpawner.pollEvent(event);
}

void Play::update()
{
    this->updateEnemySpawner();
    this->updateEnemies();

    m_player.update();
}

void Play::render(sf::RenderTarget *target)
{
    m_map->render(target);
    m_player.render(target);
    for(auto enemy : m_enemies)
        enemy->render(target);
}

void Play::setWindowSize(const sf::Vector2u &size)
{
    m_windowSize = size;
}
