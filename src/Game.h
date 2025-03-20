#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#define DEBUG_VIEW true // makes window smaller
#define BACKGROUND_SF_COLOR sf::Color(30, 30, 30)

class Game
{
    /* INITIALIZE */
    void initWindow();

    Game();
    ~Game();

    /* OTHER */
    void updateCurrentrTick();
    void updateDeltaTime();

    /* EVENTS */
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

    sf::Clock m_deltaTimeClock;
    float m_dt;

    size_t m_currentTick;
};

#endif // GAME_H
