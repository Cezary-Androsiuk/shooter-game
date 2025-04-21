#ifndef PLAYER_H
#define PLAYER_H

#include <cmath>
#include <memory>

#include <SFML/Graphics.hpp>

#include "utils/Constants.h"
#include "utils/RectEdges.h"
#include "objects/entities/Enemy.h"
#include "environment/Map.h"
#include "objects/Weapon.h"
#include "objects/Armor.h"

class Player
{
    /* INITIALIZE */
    void initData();
    void deserializeData();
    void initRenderModel();
    void initWeapon();
    void initArmor();
    void initEquipment();

    /* DESTROY */
    void serializeData();

private:
    Player();
    ~Player();

    Player(const Player &) = delete;
    Player(Player &&) = delete;
    void operator=(const Player &) = delete;
    void operator=(Player &&) = delete;

public:
    static Player *getInstance();

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
    void updateBounds();
    void updateCenter();
    void updateRenderModel();
    void updateMovement();
    void updateRotation();
    void updateWeapon();
    void updateArmor();
    void updateEquipment();

    /* RENDER */

public:
    void init();
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
    void setWeapon(std::unique_ptr<Weapon> weapon); /// NOT REQUIRED
    void setArmor(std::unique_ptr<Armor> armor); /// NOT REQUIRED

private:
    sf::RectangleShape m_boundsShape;
    bool m_boundsVisible;

    struct{
        sf::Sprite bounds;
        sf::Sprite skin;
        sf::Sprite shirt;
        sf::Sprite bakpack;
    } m_renderModel;

    sf::Vector2f m_position;
    sf::Vector2f m_size;
    sf::FloatRect m_bounds;
    sf::Vector2f m_center;
    sf::Vector2f m_moveVector;
    float m_rotationAngle;
    float m_rotationAngleCorrection;

    std::shared_ptr<Map> m_map;

    int m_points;
    int m_healthPoints;
    int m_headCount;

    const std::vector<std::shared_ptr<Enemy>> *m_enemies;

    float m_movementSpeedStraight; /// calculated after every update from dt and movement speed addons
    float m_movementSpeedOblique; /// calculated after every update from dt and movement speed addons
    struct{
        float msStraightDefault;
        float msMultiplier; /// will be increased if needed
    }m_movementSpeedAddons;

    std::unique_ptr<Weapon> m_weapon;
    std::unique_ptr<Armor> m_armor;

    // int m_healTimer;
    // float playerSize;
    // int effect;
    // int randomDirection;
};

#endif // PLAYER_H
