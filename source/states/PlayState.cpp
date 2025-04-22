#include "PlayState.h"

#include "utils/GlobalData.h"

void PlayState::initData()
{
    m_bullets.reserve(64);
}

void PlayState::initMap()
{
    m_map = std::make_shared<Map>();
    m_map->buildObstacles();
}

void PlayState::initPlayer()
{
    m_player = Player::getInstance();
    const sf::Vector2f &windowSize = GlobalData::getInstance()->getWindowSize();

    m_player->setPosition(sf::Vector2f(windowSize.x/2.f, windowSize.y/2.f));
    m_player->setAvailableAreaForPlayer(m_map);
    m_player->setEnemies(&m_enemies);

    m_player->init();
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

    printf("created playstate\n");
    fflush(stdout);
}

PlayState::~PlayState()
{

}

void PlayState::init()
{
    this->initObjects();
}

void PlayState::updatePlayer()
{
    m_player->update();

    std::unique_ptr<Bullet> bullet = m_player->getWeapon()->getBulletFromShot();
    if(bullet)
    {
        m_bullets.push_back(std::unique_ptr<Bullet>(bullet.release()));
    }

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

    enemy->setPlayerBounds(m_player->getBounds());
    enemy->setAvailableAreaForEnemy(m_map);
}

void PlayState::updateEnemies()
{
    for(const auto &enemy : m_enemies)
    {
        enemy->update();
    }
}

void PlayState::updateBullets()
{
    for (auto it = m_bullets.begin(); it != m_bullets.end(); ) {
        (*it)->update();

        /// deletes the object
        if ((*it)->getReadyToDie()) {
            it = m_bullets.erase(it);
        } else {
            ++it;
        }
    }
}

void PlayState::pollEvent(const sf::Event &event)
{
    m_enemySpawner.pollEvent(event);
    m_player->pollEvent(event);

    for(const auto &bullet : m_bullets)
        bullet->pollEvent(event);
}

void PlayState::update()
{
    this->updatePlayer();
    this->updateEnemySpawner();
    this->updateEnemies();
    this->updateBullets();
}

void PlayState::render(sf::RenderTarget *target)
{
    m_map->render(target);

    for(const auto &enemy : m_enemies)
        enemy->render(target);

    m_player->render(target);

    for(const auto &bullet : m_bullets)
        bullet->render(target);
}
