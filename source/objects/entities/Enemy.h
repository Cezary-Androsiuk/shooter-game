#ifndef ENEMY_H
#define ENEMY_H

#include <memory>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "mechanics/DeltaTime.h"
#include "environment/Map.h"
#include "utils/RectEdges.h"

constexpr float ENEMY_SPEED = 400.f;

class Enemy
{
    /* INITIALIZE */
    void initData();

public:
    Enemy();
    virtual ~Enemy();

protected:
    /* OTHER */
    static sf::Vector2f calculateNormalizedMovementVector(
        const sf::Vector2f& currentPosition,
        const sf::Vector2f& targetPosition);

    /* EVENTS */

    /* UPDATE */
    void preventMoveThatEnterBounds(
        const FloatRectEdges &playerBounds,
        const FloatRectEdges &obstacleBounds);
    void performMoveTowardsPlayer();

    /* RENDER */

public:
    virtual void init();
    virtual void pollEvent(const sf::Event &event) = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderTarget *target) = 0;

    void setPosition(sf::Vector2f position);
    void setPlayerPosition(sf::Vector2f position);
    void setAvailableAreaForEnemy(std::shared_ptr<Map> map);

protected:
    sf::Vector2f m_position;
    sf::Vector2f m_size;
    float m_movementSpeed;
    float m_moveSpeedMultiplier;
    sf::Vector2f m_moveVector;

    std::shared_ptr<Map> m_map;

    sf::Vector2f m_lastPlayerPosition;
    sf::Vector2f m_playerPosition;
};

#endif // ENEMY_H
