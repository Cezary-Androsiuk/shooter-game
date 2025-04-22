#include "Ghost.h"

void Ghost::initData()
{
    m_movementSpeedAddons.msDefault = InitialData::Enemy::Ghost::getMovementSpeed();
    m_playerMoveSlowDownRatio = InitialData::Enemy::Ghost::getPlayerMoveSlowDownRatio();
    m_healthPoints = InitialData::Enemy::Ghost::getHealth();
    m_damage = InitialData::Enemy::Ghost::getDamage();

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
    FloatRectEdges entityEdges(m_position.x, m_position.y, m_position.x + m_size.x, m_position.y + m_size.y);
    FloatRectEdges playerBounds(
        m_playerBounds->left, m_playerBounds->top,
        m_playerBounds->left + m_playerBounds->width, m_playerBounds->top + m_playerBounds->height);

    this->preventMoveThatEnterBounds(entityEdges, playerBounds);

    /// ghosts are not affected by other obstacles
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
