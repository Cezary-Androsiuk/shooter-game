#ifndef ENEMY_H
#define ENEMY_H

#include <memory>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "utils/InitialData.h"
#include "utils/Random.h"
#include "utils/RectEdges.h"
#include "utils/DeltaTime.h"
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

    /* EVENTS */

    /* UPDATE */
    void updateMovementSpeed();
    ///
    /// NOTE: move following method logic to PlayState or AdvancedComputation class
    ///
    void preventMoveThatEnterBounds(
        const FloatRectEdges &playerBounds,
        const FloatRectEdges &obstacleBounds);
    void performMoveTowardsPlayer();
    void updateDamageDelay();
    void updateMovementSpeedTimeMultiplier();
    void updatePlayerCenter();
    void updateCenter();
    void updateRotation();

    /* RENDER */

public:
    virtual void init();
    virtual void pollEvent(const sf::Event &event);
    virtual void update();
    virtual void render(sf::RenderTarget *target);

    const sf::Vector2f &getPosition() const;
    const sf::Vector2f &getSize() const;
    sf::FloatRect getBounds() const;
    float getMovementSpeed() const;
    float getPlayerMoveSlowDownRatio() const;
    bool getReadyToAttack();
    float getDamage() const;

    void setPosition(sf::Vector2f position);
    void setAvailableAreaForEnemy(std::shared_ptr<Map> map);
    void setPlayerBounds(const sf::FloatRect *playerBounds);

protected:
    sf::Vector2f m_position;
    sf::Vector2f m_size;
    sf::Vector2f m_moveVector;
    sf::Vector2f m_center;
    float m_rotationAngle;
    sf::Vector2f m_moveDirectionRatio;
    const sf::FloatRect *m_playerBounds;
    sf::Vector2f m_playerCenter;
    float m_health;

    float m_damage;
    sf::Clock m_attackDelayTimer;
    float m_attackDelay;
    bool m_readyToAttack;

    float m_movementSpeed; /// calculated after every update from dt and movement speed addons
    float m_movementSpeedWithRoughness;
    struct{
        float msDefault;
        float msMultiplier; /// will be increased if needed
        float msTimeMultiplier; /// will be increased with time
        sf::Clock msTimeMultiplierClock;
        float msRandomness;
        float collisionRoughness;
    }m_movementSpeedAddons;
    float m_playerMoveSlowDownRatio;

    std::shared_ptr<Map> m_map;
};

#endif // ENEMY_H
