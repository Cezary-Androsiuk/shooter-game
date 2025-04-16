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
    void initBody();

public:
    Enemy();
    ~Enemy();

private:
    /* OTHER */
    sf::Vector2f calculateNormalizedMovementVector(const sf::Vector2f& currentPosition,
                                                   const sf::Vector2f& targetPosition);

    /* EVENTS */

    /* UPDATE */
    void preventMoveThatEnterBounds(
        const FloatRectEdges &playerBounds,
        const FloatRectEdges &obstacleBounds);
    void limitEnemyMovementToMap();
    void updateMove();

    void updateBody();

    /* RENDER */

public:
    void init();

    void pollEvent(const sf::Event &event);
    void update();
    void render(sf::RenderTarget *target);

    void setPosition(sf::Vector2f position);
    void setPlayerPosition(sf::Vector2f position);
    void setAvailableAreaForEnemy(std::shared_ptr<Map> map);

private:
    struct{
        sf::RectangleShape bounds;

    } m_body;

    sf::Vector2f m_position;
    sf::Vector2f m_size;

    std::shared_ptr<Map> m_map;

    sf::Vector2f m_lastPlayerPosition;
    sf::Vector2f m_playerPosition;
    sf::Vector2f m_moveVector;

};

#endif // ENEMY_H
