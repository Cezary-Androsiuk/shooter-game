#include "Ghost.h"

void Ghost::initData()
{
    m_movementSpeedDefault = Data::Enemy::Ghost::getDefaultSpeed();

    /// Size
    m_size.x = 50.f;
    m_size.y = 50.f;
}

void Ghost::initBody()
{
    m_body.bounds.setPosition(m_position);
    m_body.bounds.setFillColor(sf::Color(180, 40, 40));
    m_body.bounds.setSize(m_size);
    // m_body.bounds.setOrigin(sf::Vector2f(m_size.x/2, m_size.y/2));
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

    // FloatRectEdges playerEdges(m_position.x, m_position.y, m_position.x + m_size.x, m_position.y + m_size.y);
    // float windowSizeX = static_cast<float>(m_map->getMapSize().x);
    // float windowSizeY = static_cast<float>(m_map->getMapSize().y);
    // FloatRectEdges windowEgdes(0.f, 0.f, windowSizeX, windowSizeY);

    // this->preventMoveThatExitBounds(playerEdges, windowEgdes);

    // for(Obstacle *obstacle : m_map->getObstacles())
    //     this->preventMoveThatEnterBounds(playerEdges, obstacle->getBounds());
}

void Ghost::updateBody()
{
    m_body.bounds.setPosition(m_position);
    m_body.boundsShadow.setPosition({m_position.x-10, m_position.y-10});
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

    this->performMoveTowardsPlayer();
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
