#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <SFML/Graphics.hpp>
#include <SimpleGUI/Label.hpp>

#include "State.h"

#include "mechanics/spawners/EnemySpawner.h"
#include "objects/entities/Enemy.h"
#include "objects/entities/Player.h"
#include "objects/Bullet.h"
#include "environment/Map.h"

#include "animations/Animation.h"

class PlayState : public State
{
    void initData();
    void initMap();
    void initPlayer();
    void initEnemySpawner();
    void initObjects();
    void initStatInfo();

public:
    PlayState();
    ~PlayState();

    void init();

    bool requestDefeatState();

private:
    /* OTHER */

    /* EVENTS */

    /* UPDATE */
    void updatePlayer();
    void updateEnemySpawner();
    void updateEnemies();
    void updatePlayerAndEnemiesRelation();
    void updateBullets();
    void updateBulletsAndEnemiesRelation();

    void updateStatInfo();

    void updateAnimations();

    /* RENDER */
    void renderStatInfo(sf::RenderTarget *target);

public:
    void pollEvent(const sf::Event &event) override;
    void update() override;
    void render(sf::RenderTarget *target) override;

    float getEarnedMoney() const;
    int getSurvivedSeconds() const;

private:
    std::shared_ptr<sf::Sprite> m_statInfoNotch;

    std::shared_ptr<Map> m_map;
    Player *m_player;
    std::vector<std::unique_ptr<Bullet>> m_bullets;

    EnemySpawner m_enemySpawner;
    std::vector<std::shared_ptr<Enemy>> m_enemies;

    std::vector<std::unique_ptr<Animation>> m_animations;

    float m_sesionMoney;
    sf::Clock m_sessionTime;
    int m_survivedSeconds;
    std::unique_ptr<sgui::Label> m_moneyLabel;
    std::unique_ptr<sgui::Label> m_timeLabel;
    sf::Clock m_statInfoDisplayClock;
    int m_statInfoDisplayDelay;
};

#endif // PLAYSTATE_H
