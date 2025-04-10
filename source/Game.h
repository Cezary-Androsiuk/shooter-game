#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

#include "mechanics/DeltaTime.h"

#include "enums/GameState.h"

#include "states/Menu.h"
#include "objects/entities/Player.h"
#include "objects/entities/Enemy.h"
#include "mechanics/spawners/EnemySpawner.h"
#include "environment/Map.h"

#define DEBUG_VIEW true // makes window smaller
#define BACKGROUND_SF_COLOR sf::Color(30, 30, 30)

class Game
{
    /* INITIALIZE */
    void initValues();
    void initWindow();

    void initMap();
    void initPlayer();
    void initObjects();

    Game();
    ~Game();

    /* OTHER */

    /* EVENTS */
    void pollEvent();

    /* UPDATE */
    void updateMenuStage();
    void updatePlayStage();
    void update();

    /* RENDER */
    void renderMenuStage();
    void renderPlayStage();
    void render();

    inline bool running() const noexcept;

public:
    static void play();

private:
    sf::RenderWindow* m_window;
    sf::ContextSettings m_contextSettings;
    sf::Event m_currentEvent;

    sf::Clock m_deltaTimeClock;
    size_t m_minFPS;
    size_t m_maxFPS;

    GameState m_gameState;

    Menu m_menu;
    std::shared_ptr<Map> m_map;
    Player m_player;
    EnemySpawner m_enemySpawner;
    std::vector<Enemy> m_enemies;

};

#endif // GAME_H
