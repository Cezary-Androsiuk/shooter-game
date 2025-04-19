#include "Zombie.h"

void Zombie::initData()
{
    m_movementSpeedAddons.msDefault = Data::Enemy::Zombie::getMovementSpeed();
    m_playerMoveSlowDownRatio = Data::Enemy::Zombie::getPlayerMoveSlowDownRatio();
    m_health = Data::Enemy::Zombie::getHealth();
    m_damage = Data::Enemy::Zombie::getDamage();

    /// Size
    m_size.x = 50.f;
    m_size.y = 50.f;


}

void Zombie::initBody()
{
    m_body.bounds.setPosition(m_position);
    m_body.bounds.setFillColor(sf::Color(40, 180, 40));
    m_body.bounds.setSize(m_size);

    m_body.boundsShadow.setPosition({m_position.x-5, m_position.y-5});
    m_body.boundsShadow.setFillColor(sf::Color(20, 130, 20, 180));
    m_body.boundsShadow.setSize({m_size.x+10, m_size.y+10});
}

Zombie::Zombie()
    : Enemy()
{

}

void Zombie::limitZombieMovementToMap()
{
    FloatRectEdges entityEdges(m_position.x, m_position.y, m_position.x + m_size.x, m_position.y + m_size.y);
    FloatRectEdges playerBounds(
        m_playerBounds->left, m_playerBounds->top,
        m_playerBounds->left + m_playerBounds->width, m_playerBounds->top + m_playerBounds->height);

    this->preventMoveThatEnterBounds(entityEdges, playerBounds);

    for(Obstacle *obstacle : m_map->getObstacles())
        this->preventMoveThatEnterBounds(entityEdges, obstacle->getBounds());
}

void Zombie::updateBody()
{
    m_body.bounds.setPosition(m_position);
    m_body.boundsShadow.setPosition({m_position.x-5, m_position.y-5});
}

void Zombie::init()
{
    Enemy::init();

    this->initData();
    this->initBody();
}

void Zombie::pollEvent(const sf::Event &event)
{
    Enemy::pollEvent(event);
}

void Zombie::update()
{
    Enemy::update();

    this->limitZombieMovementToMap();

    this->updateBody();
}

void Zombie::render(sf::RenderTarget *target)
{
    Enemy::render(target);

    target->draw(m_body.bounds);
    target->draw(m_body.boundsShadow);
}
