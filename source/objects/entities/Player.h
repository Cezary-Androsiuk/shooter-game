#ifndef PLAYER_H
#define PLAYER_H

#include <cmath>
#include <memory>

#include <SFML/Graphics.hpp>

#include "mechanics/DeltaTime.h"
#include "utils/RectEdges.h"
#include <environment/Map.h>

// player speed
constexpr float PLAYER_SPEED_STRAIGHT = 500.f;
constexpr float PLAYER_SPEED_OBLIQUE = 500.f / 1.4142f /* sqrt(2) */;

// player health points on start
constexpr int PLAYER_HP = 100;

// player ammo in clip on start
constexpr int PLAYER_AMMO = 50;



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
    void move(float xmove, float ymove);
    void move(sf::Vector2f move);

    /* EVENTS */
    // void pollEvent(sf::Event &event);

private:
    /* UPDATE */
    void preventMoveThatExitBounds(
        const FloatRectEdges &playerBounds,
        const FloatRectEdges &obstacleBounds);
    void preventMoveThatEnterBounds(
        const FloatRectEdges &playerBounds,
        const FloatRectEdges &obstacleBounds);
    void limitPlayerMovementToScreenArea();
    void updateBody();
    void updateMovement();
public:
    void update();

private:
    /* RENDER */
public:
    void render(sf::RenderTarget *target);

public:
    /* GETTERS */


    /* SETTERS */
    void setDeltaTimePtr(const float *dt);
    void setPosition(const sf::Vector2f &position);
    void setAvailableAreaForPlayer(std::shared_ptr<Map> map);

private:
    struct{
        sf::RectangleShape bounds;

    } m_body;

    sf::Vector2f m_position;
    sf::Vector2f m_size;

    std::shared_ptr<Map> m_map;

    int m_points;
    int m_healthPoints;
    int m_ammo;
    int m_headCount;

    // int m_healTimer;
    // float playerSize;
    // int effect;
    // int randomDirection;

};

#endif // PLAYER_H
