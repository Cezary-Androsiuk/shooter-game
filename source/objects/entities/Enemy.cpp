#include "Enemy.h"

void Enemy::initData()
{
    m_position.x = 0.f;
    m_position.y = 0.f;

    m_moveSpeedMultiplier = 1.f;
}

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

sf::Vector2f Enemy::calculateNormalizedMovementVector(const sf::Vector2f &currentPosition, const sf::Vector2f &targetPosition)
{
    sf::Vector2f direction = targetPosition - currentPosition;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length > 0) {
        return direction / length;
    }
    return sf::Vector2f(0, 0);
}

void Enemy::preventMoveThatEnterBounds(
    const FloatRectEdges &playerBounds,
    const FloatRectEdges &obstacleBounds)
{
    float overlapLeft   = playerBounds.right - obstacleBounds.left;
    float overlapRight  = obstacleBounds.right - playerBounds.left;
    float overlapTop    = playerBounds.bottom - obstacleBounds.top;
    float overlapBottom = obstacleBounds.bottom - playerBounds.top;

    /// test if collision occur
    if (overlapLeft > 0 && overlapRight > 0 && overlapTop > 0 && overlapBottom > 0)
    {
        /// test what collision is the smallest - that means this edges are colliding
        float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});

        if (minOverlap == overlapLeft)
        {
            m_position.x = obstacleBounds.left - m_size.x;
        }
        else if (minOverlap == overlapRight)
        {
            m_position.x = obstacleBounds.right;
        }
        else if (minOverlap == overlapTop)
        {
            m_position.y = obstacleBounds.top - m_size.y;
        }
        else if (minOverlap == overlapBottom)
        {
            m_position.y = obstacleBounds.bottom;
        }
    }
}

void Enemy::performMoveTowardsPlayer()
{
    m_moveVector = calculateNormalizedMovementVector(m_position, m_playerPosition);

    const float dt = DeltaTime::get()->value();
    m_position.x += m_moveVector.x * m_movementSpeed * dt;
    m_position.y += m_moveVector.y * m_movementSpeed * dt;
}

void Enemy::init()
{
    this->initData();
}

void Enemy::setPosition(sf::Vector2f position)
{
    m_position = position;
}

void Enemy::setPlayerPosition(sf::Vector2f position)
{
    m_lastPlayerPosition = m_playerPosition;
    m_playerPosition = position;
}

void Enemy::setAvailableAreaForEnemy(std::shared_ptr<Map> map)
{
    m_map = map;
}
