#include "Enemy.h"

void Enemy::initData()
{
    m_position.x = 0.f;
    m_position.y = 0.f;

    /// Size
    m_size.x = 50.f;
    m_size.y = 50.f;
}

void Enemy::initBody()
{
    m_body.bounds.setPosition(m_position);
    m_body.bounds.setFillColor(sf::Color(180, 40, 40));
    m_body.bounds.setSize(m_size);
    // m_body.bounds.setOrigin(sf::Vector2f(m_size.x/2, m_size.y/2));
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

void Enemy::limitEnemyMovementToMap()
{
    FloatRectEdges playerEdges(m_position.x, m_position.y, m_position.x + m_size.x, m_position.y + m_size.y);
    float windowSizeX = static_cast<float>(m_map->getMapSize().x);
    float windowSizeY = static_cast<float>(m_map->getMapSize().y);
    FloatRectEdges windowEgdes(0.f, 0.f, windowSizeX, windowSizeY);

    /// enemies will start outsite the box
    // this->preventMoveThatExitBounds(playerEdges, windowEgdes);

    for(Obstacle *obstacle : m_map->getObstacles())
        this->preventMoveThatEnterBounds(playerEdges, obstacle->getBounds());
}

void Enemy::updateMove()
{
    // if(m_playerPosition != m_lastPlayerPosition)
    // {
    // }
    m_moveVector = calculateNormalizedMovementVector(m_position, m_playerPosition);

    // static int i=0;
    // if((i++)%100 == 1)
    // {
    //     printf("move v: %f %f\n", m_moveVector.x, m_moveVector.y);
    //     fflush(stdout);
    // }

    const float dt = DeltaTime::get()->value();
    m_position.x += m_moveVector.x * ENEMY_SPEED * dt;
    m_position.y += m_moveVector.y * ENEMY_SPEED * dt;

}

void Enemy::updateBody()
{
    m_body.bounds.setPosition(m_position);
}

void Enemy::init()
{
    this->initData();
    this->initBody();
}

void Enemy::pollEvent(const sf::Event &event)
{

}

void Enemy::update()
{
    this->updateMove();
    this->limitEnemyMovementToMap();

    this->updateBody();

    // static int i=0;
    // if((i++)%100 == 1)
    // {
    //     printf("%f %f\n", m_position.x, m_position.y);
    //     fflush(stdout);
    // }
}

void Enemy::render(sf::RenderTarget *target)
{
    target->draw(m_body.bounds);
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
