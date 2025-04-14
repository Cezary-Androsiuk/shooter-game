#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

#include "mechanics/DeltaTime.h"

#include "enums/GameState.h"

#include "states/Menu.h"
#include "states/Play.h"
// #include "objects/entities/Enemy.h"
// #include "mechanics/spawners/EnemySpawner.h"

#define DEBUG_VIEW false // makes window smaller
#define DEBUG_EXIT_APP true // if 'P' is pressed then exit app
#define BACKGROUND_SF_COLOR sf::Color(30, 30, 30)

class Game
{
    /* INITIALIZE */
    void initValues();
    void initWindow();

    void initMenu();
    void initPlay();

    Game();
    ~Game();

    /* OTHER */

    /* EVENTS */
    void pollEventGame();
    void pollEvent();

    /* UPDATE */
    void update();

    /* RENDER */
    void render();

    inline bool running() const noexcept;

public:
    static void play();

private:
    sf::RenderWindow* m_window;
    sf::ContextSettings m_contextSettings;
    sf::Event m_currentEvent;

    size_t m_minFPS;
    size_t m_maxFPS;

    GameState m_gameState;
    Menu m_menu;
    Play m_play;


    // EnemySpawner m_enemySpawner;
    // std::vector<Enemy> m_enemies;

};

#endif // GAME_H
