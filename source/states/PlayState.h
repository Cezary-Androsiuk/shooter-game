#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <SFML/Graphics.hpp>

#include "State.h"

#include "mechanics/spawners/EnemySpawner.h"
#include "objects/entities/Enemy.h"
#include "objects/entities/Player.h"
#include "environment/Map.h"

class PlayState : public State
{
    void initMap();
    void initPlayer();
    void initEnemySpawner();
    void initObjects();

public:
    PlayState();
    ~PlayState();

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

private:
    std::shared_ptr<Map> m_map;
    Player *m_player;

    EnemySpawner m_enemySpawner;
    std::vector<std::shared_ptr<Enemy>> m_enemies;
};

#endif // PLAYSTATE_H
