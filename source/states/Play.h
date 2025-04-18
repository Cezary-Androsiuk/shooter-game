#ifndef PLAY_H
#define PLAY_H

#include <SFML/Graphics.hpp>

#include "State.h"

#include "mechanics/spawners/EnemySpawner.h"
#include "objects/entities/Enemy.h"
#include "objects/entities/Player.h"
#include "environment/Map.h"

class Play : public State
{
    void initMap();
    void initPlayer();
    void initEnemySpawner();
    void initObjects();

public:
    Play();
    ~Play();

    void init();

private:
    /* OTHER */

    /* EVENTS */

    /* UPDATE */
    void updateEnemySpawner();
    void updateEnemies();

    /* RENDER */

public:
    void pollEvent(const sf::Event &event) override;
    void update() override;
    void render(sf::RenderTarget *target) override;

    /// SETTERS
    void setWindowSize(const sf::Vector2u &size);

private:
    sf::Vector2u m_windowSize;

    std::shared_ptr<Map> m_map;
    Player m_player;

    EnemySpawner m_enemySpawner;
    std::vector<std::shared_ptr<Enemy>> m_enemies;
};

#endif // PLAY_H
