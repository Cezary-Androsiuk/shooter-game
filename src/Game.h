#ifndef GAME_H
#define GAME_H

#include <vector>

#include <SFML/Graphics.hpp>

#include "enums/GameState.h"

#include "Menu.h"
#include "Princess.h"
#include "RocketSpawner.h"
#include "Rocket.h"

#define DEBUG_VIEW true // makes window smaller
#define BACKGROUND_SF_COLOR sf::Color(30, 30, 30)

class Game
{
    /* INITIALIZE */
    void initValues();
    void initWindow();

    Game();
    ~Game();

    /* OTHER */
    void updateCurrentrTick();
    void updateDeltaTime();

    /* EVENTS */
    void pollEvent();

    /* UPDATE */
    void updateMenu();
    void updatePlay();
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

    sf::Clock m_deltaTimeClock;
    float m_dt;
    size_t m_minFPS;
    size_t m_maxFPS;
    size_t m_currentTick;

    GameState m_gameState;

    Menu m_menu;
    Princess m_princess;
    RocketSpawner m_rocketSpawner;
    std::vector<Rocket> m_rockets;

};

#endif // GAME_H
