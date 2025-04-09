#ifndef PLAYER_H
#define PLAYER_H

#include <cmath>

#include <SFML/Graphics.hpp>

#include "mechanics/DeltaTime.h"

// player speed
constexpr float PLAYER_SPEED_STRAIGHT = 100.f;
constexpr float PLAYER_SPEED_OBLIQUE = 100.f;

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
    void setAvailableAreaForPlayer(const sf::FloatRect availableAreaForPlayer);

private:
    struct{
        sf::RectangleShape bounds;

    } m_body;

    sf::Vector2f m_position;
    sf::Vector2f m_size;

    sf::FloatRect m_availableAreaForPlayer;

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
