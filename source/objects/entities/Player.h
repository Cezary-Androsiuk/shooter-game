#ifndef PLAYER_H
#define PLAYER_H

#include <cmath>
#include <memory>

#include <SFML/Graphics.hpp>

#include "utils/Constants.h"
#include "utils/RectEdges.h"
#include "objects/entities/Enemy.h"
#include <environment/Map.h>

class Player
{
    /* INITIALIZE */
    void initData();
    void initBody();

public:
    Player();
    ~Player();

private:
    /* OTHER */
    void move(float moveX, float moveY);
    void computeMovementSpeed();
    static float rotationFromVector(cvFloat originPoint, cvFloat targetPoint);

private:
    /* EVENTS */

    /* UPDATE */
    void preventMoveThatExitBounds(
        const FloatRectEdges &playerBounds,
        const FloatRectEdges &obstacleBounds);
    void preventMoveThatEnterBounds(
        const FloatRectEdges &playerBounds,
        const FloatRectEdges &obstacleBounds);
    void limitMoveThatEnterEnemy(
        const FloatRectEdges &playerBounds,
        std::shared_ptr<Enemy> enemy);
    void limitPlayerMovementToMap();
    void updateBody();
    void updateMovement();
    void updateRotation();
    void updateBounds();

    /* RENDER */

public:
    // void pollEvent(sf::Event &event);
    void update();
    void render(sf::RenderTarget *target);

public:
    /* GETTERS */
    sf::Vector2f getPosition() const;
    const sf::FloatRect *getBounds() const;

    /* SETTERS */
    void setEnemies(const std::vector<std::shared_ptr<Enemy>> *enemies);
    void setPosition(const sf::Vector2f &position);
    void setAvailableAreaForPlayer(std::shared_ptr<Map> map);

private:
    struct{
        sf::RectangleShape bounds;
        sf::RectangleShape rotation;
    } m_body;

    sf::Vector2f m_position;
    sf::Vector2f m_size;
    sf::FloatRect m_bounds;
    sf::Vector2f m_moveVector;
    float m_rotationAngle;

    std::shared_ptr<Map> m_map;

    int m_points;
    int m_healthPoints;
    int m_ammo;
    int m_headCount;

    const std::vector<std::shared_ptr<Enemy>> *m_enemies;

    float m_movementSpeedStraight; /// calculated after every update from dt and movement speed addons
    float m_movementSpeedOblique; /// calculated after every update from dt and movement speed addons
    struct{
        float msStraightDefault;
        float msMultiplier; /// will be increased if needed
    }m_movementSpeedAddons;


    // int m_healTimer;
    // float playerSize;
    // int effect;
    // int randomDirection;
};

#endif // PLAYER_H
