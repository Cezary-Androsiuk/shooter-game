#include "Enemy.h"

#include "utils/AdvancedComputation.h"

void Enemy::initData()
{
    m_position.x = 0.f;
    m_position.y = 0.f;

    m_movementSpeedAddons.msDefault = 100.f; /// need to be overrited
    m_healthPoints = 100.f; /// need to be overrited
    m_damage = 10.f; /// need to be overrited
    m_movementSpeedAddons.msMultiplier = 1.f;
    m_movementSpeedAddons.msTimeMultiplier = 1.f;
    m_movementSpeedAddons.msRandomness = Random::getFloat(
        InitialData::Enemy::getSpeedDecreaseRandomness(),
        InitialData::Enemy::getSpeedIncreaseRandomness()
    );

    m_movementSpeedAddons.collisionRoughness = InitialData::getCollisionRoughness();

    m_attackDelay = InitialData::Enemy::getAttackDelayMS();
    m_attackDelayTimer.restart();
    m_readyToAttack = true;
}

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

void Enemy::updateMovementSpeed()
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
    const FloatRectEdges &entityBounds,
    const FloatRectEdges &obstacleBounds)
{
    ///
    /// NOTE: move this logic to PlayState class
    ///
    float overlapLeft   = entityBounds.right - obstacleBounds.left;
    float overlapRight  = obstacleBounds.right - entityBounds.left;
    float overlapTop    = entityBounds.bottom - obstacleBounds.top;
    float overlapBottom = obstacleBounds.bottom - entityBounds.top;

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
    m_moveVector = AdvancedComputation::calculateNormalizedVector(m_center, m_playerCenter);

    m_position.x += m_moveVector.x * m_movementSpeed;
    m_position.y += m_moveVector.y * m_movementSpeed;
}

void Enemy::updateDamageDelay()
{
    if(!m_readyToAttack)
    {
        if(m_attackDelayTimer.getElapsedTime().asMilliseconds() > m_attackDelay)
        {
            m_attackDelayTimer.restart();
            m_readyToAttack = true;
        }
    }
}

void Enemy::updateMovementSpeedTimeMultiplier()
{
    int elapsedTimeMS = m_movementSpeedAddons.msTimeMultiplierClock.getElapsedTime().asMilliseconds();
    if(elapsedTimeMS > InitialData::Enemy::getSpeedIncreaseTimeDelayMS())
    {
        m_movementSpeedAddons.msTimeMultiplierClock.restart();
        m_movementSpeedAddons.msTimeMultiplier *=
            InitialData::Enemy::getSpeedIncreaseTimeAmountMultiplier();
    }
}

void Enemy::updatePlayerCenter()
{
    m_playerCenter.x = m_playerBounds->left + m_playerBounds->width/2;
    m_playerCenter.y = m_playerBounds->top + m_playerBounds->height/2;
}

void Enemy::updateCenter()
{
    m_center.x = m_position.x + m_size.x/2;
    m_center.y = m_position.y + m_size.y/2;
}

void Enemy::updateRotation()
{
    m_rotationAngle = AdvancedComputation::vectorToRotation(m_center, m_playerCenter);
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
    this->updateMovementSpeed();
    this->updateDamageDelay();
    this->updateMovementSpeedTimeMultiplier();
    this->updateCenter();
    this->updatePlayerCenter();
    this->updateRotation();

    this->performMoveTowardsPlayer();
}

void Enemy::render(sf::RenderTarget *target)
{

}

const sf::Vector2f &Enemy::getSize() const
{
    return m_size;
}

sf::FloatRect Enemy::getBounds() const
{
    return sf::FloatRect(m_position, m_size);
}

float Enemy::getMovementSpeed() const
{
    return m_movementSpeed;
}

float Enemy::getPlayerMoveSlowDownRatio() const
{
    return m_playerMoveSlowDownRatio;
}

bool Enemy::getReadyToAttack()
{
    if(m_readyToAttack)
    {
        m_readyToAttack = false;
        m_attackDelayTimer.restart();
        return true;
    }
    return false;
}

float Enemy::getDamage() const
{
    return m_damage;
}

bool Enemy::getEnemyAlive() const
{
    return m_healthPoints > 0;
}

void Enemy::setPosition(sf::Vector2f position)
{
    m_position = position;
}

void Enemy::setAvailableAreaForEnemy(std::shared_ptr<Map> map)
{
    m_map = map;
}

void Enemy::setPlayerBounds(const sf::FloatRect *playerBounds)
{
    m_playerBounds = playerBounds;
}

void Enemy::dealDamage(float damage)
{
    m_healthPoints -= damage;
}
