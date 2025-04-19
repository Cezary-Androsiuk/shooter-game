#include "Enemy.h"

void Enemy::initData()
{
    m_position.x = 0.f;
    m_position.y = 0.f;

    m_movementSpeedAddons.msDefault = 100.f; /// need to be overrited
    m_health = 100.f; /// need to be overrited
    m_damage = 10.f; /// need to be overrited
    m_movementSpeedAddons.msMultiplier = 1.f;
    m_movementSpeedAddons.msTimeMultiplier = 1.f;
    m_movementSpeedAddons.msRandomness = Random::getFloat(
        Data::Enemy::getSpeedDecreaseRandomness(),
        Data::Enemy::getSpeedIncreaseRandomness()
    );

    m_movementSpeedAddons.collisionRoughness = 0.8; //Data::getCollisionRoughness();

    m_damageDelayConstant = Data::Enemy::getDealDamageDelay();
    m_damageDelay = m_damageDelayConstant;
    m_canDealDamage = true;
    m_damageLagDeterminer = (-1) * Data::Enemy::getDealDamageLagDeterminer();
    m_damageLagIncrease = 0.f;
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
    // printf("%0.4f, %0.4f, L: %0.2f\n", direction.x, direction.y, length);

    if (length > 0) {
        return direction / length;
    }
    return sf::Vector2f(0, 0);
}

void Enemy::computeMovementSpeed()
{
    m_movementSpeed = m_movementSpeedAddons.msDefault *
                      m_movementSpeedAddons.msMultiplier *
                      m_movementSpeedAddons.msTimeMultiplier *
                      m_movementSpeedAddons.msRandomness *
                      DeltaTime::get()->value();

    m_movementSpeedWithRoughness = m_movementSpeed *
                                   m_movementSpeedAddons.collisionRoughness;
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
            /// decrease movement in available direction due to collision roughnes
            m_position.y -= m_moveVector.y * m_movementSpeedWithRoughness;
        }
        else if (minOverlap == overlapRight)
        {
            m_position.x = obstacleBounds.right;
            /// decrease movement in available direction due to collision roughnes
            m_position.y -= m_moveVector.y * m_movementSpeedWithRoughness;
        }
        else if (minOverlap == overlapTop)
        {
            m_position.y = obstacleBounds.top - m_size.y;
            /// decrease movement in available direction due to collision roughnes
            m_position.x -= m_moveVector.x * m_movementSpeedWithRoughness;
        }
        else if (minOverlap == overlapBottom)
        {
            m_position.y = obstacleBounds.bottom;
            /// decrease movement in available direction due to collision roughnes
            m_position.x -= m_moveVector.x * m_movementSpeedWithRoughness;
        }
    }
}

void Enemy::performMoveTowardsPlayer()
{
    m_moveVector = calculateNormalizedMovementVector(m_position, m_playerPosition);

    // float directionSum
    // m_moveDirectionRatio =

    m_position.x += m_moveVector.x * m_movementSpeed;
    m_position.y += m_moveVector.y * m_movementSpeed;
}

void Enemy::updateDamageDelay()
{
    m_damageDelay -= DeltaTime::get()->value();
    if(m_damageDelay < 0)
    {
        /// if delay was much below 0, then
        if(m_damageDelay < m_damageLagDeterminer)
            m_damageLagIncrease = m_damage * m_damageDelay * (-1);
        else
            m_damageLagIncrease = 0.f;

        // printf("can deal damage: %g\n", m_damage + m_damageLagIncrease);
        // fflush(stdout);

        m_canDealDamage = true;
        m_damageDelay = m_damageDelayConstant;
    }
}

void Enemy::init()
{
    this->initData();
}

void Enemy::pollEvent(const sf::Event &event)
{

}

void Enemy::update()
{
    this->computeMovementSpeed();
    this->updateDamageDelay();

    this->performMoveTowardsPlayer();
}

void Enemy::render(sf::RenderTarget *target)
{

}

const sf::Vector2f &Enemy::getPosition() const
{
    return m_position;
}

const sf::Vector2f &Enemy::getSize() const
{
    return m_size;
}

void Enemy::setPosition(sf::Vector2f position)
{
    m_position = position;
}

void Enemy::setPlayerPosition(sf::Vector2f position)
{
    m_playerPosition = position;
}

void Enemy::setAvailableAreaForEnemy(std::shared_ptr<Map> map)
{
    m_map = map;
}
