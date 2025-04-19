#ifndef ENEMY_H
#define ENEMY_H

#include <memory>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "utils/Data.h"
#include "utils/Random.h"
#include "utils/RectEdges.h"
#include "mechanics/DeltaTime.h"
#include "environment/Map.h"

/// speed range will be in range:
/// [movementSpeed * ENEMY_SPEED_DECREASE_RANDOMNESS, movementSpeed * ENEMY_SPEED_INCREASE_RANDOMNESS]
constexpr float ENEMY_SPEED_DECREASE_RANDOMNESS = 0.9f;
constexpr float ENEMY_SPEED_INCREASE_RANDOMNESS = 1.1f;
constexpr float ENEMY_DEFAULT_SPEED = 300.f;

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

    void computeMovementSpeed();

    /* EVENTS */

    /* UPDATE */
    void preventMoveThatEnterBounds(
        const FloatRectEdges &playerBounds,
        const FloatRectEdges &obstacleBounds);
    void performMoveTowardsPlayer();

    /* RENDER */

public:
    virtual void init();
    virtual void pollEvent(const sf::Event &event);
    virtual void update();
    virtual void render(sf::RenderTarget *target);

    const sf::Vector2f &getPosition() const;
    const sf::Vector2f &getSize() const;

    void setPosition(sf::Vector2f position);
    void setPlayerPosition(sf::Vector2f position);
    void setAvailableAreaForEnemy(std::shared_ptr<Map> map);

protected:
    sf::Vector2f m_position;
    sf::Vector2f m_size;
    sf::Vector2f m_playerPosition;
    float m_health;
    float m_damage;

    float m_movementSpeed; /// calculated after every update from dt and movement speed addons
    struct{
        float msDefault;
        float msMultiplier; /// will be increased if needed
        float msTimeMultiplier; /// will be increased with time
        float msRandomness;
    }m_movementSpeedAddons;

    std::shared_ptr<Map> m_map;
};

#endif // ENEMY_H
