#include "Ghost.h"

void Ghost::initData()
{
    m_movementSpeedAddons.msDefault = Data::Enemy::Ghost::getMovementSpeed();
    m_health = Data::Enemy::Ghost::getHealth();
    m_damage = Data::Enemy::Ghost::getDamage();

    /// Size
    m_size.x = 50.f;
    m_size.y = 50.f;
}

void Ghost::initBody()
{
    m_body.bounds.setPosition(m_position);
    m_body.bounds.setFillColor(sf::Color(180, 40, 40));
    m_body.bounds.setSize(m_size);

    m_body.boundsShadow.setPosition({m_position.x-5, m_position.y-5});
    m_body.boundsShadow.setFillColor(sf::Color(130, 20, 20, 180));
    m_body.boundsShadow.setSize({m_size.x+10, m_size.y+10});
}

Ghost::Ghost()
    : Enemy()
{

}

void Ghost::limitGhostMovementToMap()
{
    /// ghosts are not affected by obstacles
}

void Ghost::updateBody()
{
    m_body.bounds.setPosition(m_position);
    m_body.boundsShadow.setPosition({m_position.x-5, m_position.y-5});
}

void Ghost::init()
{
    Enemy::init();

    this->initData();
    this->initBody();
}

void Ghost::pollEvent(const sf::Event &event)
{
    Enemy::pollEvent(event);
}

void Ghost::update()
{
    Enemy::update();

    this->limitGhostMovementToMap();

    this->updateBody();

    // static int i=0;
    // if((i++)%100 == 1)
    // {
    //     printf("%f %f\n", m_moveVector.x, m_moveVector.y);
    //     fflush(stdout);
    // }
}

void Ghost::render(sf::RenderTarget *target)
{
    Enemy::render(target);

    target->draw(m_body.bounds);
    target->draw(m_body.boundsShadow);
}
