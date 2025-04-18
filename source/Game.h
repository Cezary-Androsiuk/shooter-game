#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include <queue>

#include <SFML/Graphics.hpp>

#include "utils/Constants.h"
#include "utils/Support.h"
#include "utils/Random.h"
#include "utils/Data.h"
#include "mechanics/DeltaTime.h"

#include "enums/GameState.h"

#include "states/Menu.h"
#include "states/Play.h"

#include "SimpleGUI/Label.hpp"
using namespace sgui;
// #include "objects/entities/Enemy.h"
// #include "mechanics/spawners/EnemySpawner.h"

#define DEBUG_VIEW true // makes window smaller
#define DEBUG_EXIT_APP true // if '`' is pressed then exit app
#define BACKGROUND_SF_COLOR sf::Color(30, 30, 30)

class Game
{
    /* INITIALIZE */
    void initFPSLabel();
    void initValues();
    void initWindow();
    void initRenderTexture();

    void initMenu();
    void initPlay();

    Game();
    ~Game();

    /* OTHER */
    void changeStateToPlay();
    void changeStateToMenu();

    /* EVENTS */
    void pollEventGame();
    void pollEvent();

    /* UPDATE */
    void updateFPSLabel();
    void update();

    /* RENDER */
    void renderToTexture();
    void renderToScreen();
    void render();

    inline bool running() const noexcept;

public:
    static void play();

private:
    sf::RenderWindow* m_window;
    sf::RenderTexture m_renderTexture;
    std::unique_ptr<sf::Sprite> m_renderSprite;
    bool m_renderTextureInitialized;
    sf::ContextSettings m_contextSettings;
    sf::Event m_currentEvent;

    struct{
        uint minFPS;
        uint maxFPS;

        uint avgFPS;
        struct{
            std::queue<uint> queue;
            uint sumOfLastNValues = 0;
            const uint maxLastValues = 10;
        } avgFPSData;

        sf::Clock fpsDisplayClock;
        const int fpsDisplayDelayMS = 100;
    } m_fps;

    GameState m_gameState;
    Menu m_menu;
    Play m_play;

    sf::Font m_fpsFont;
    bool m_fontLoaded;
    Label m_fpsLabel;
    // EnemySpawner m_enemySpawner;
    // std::vector<Enemy> m_enemies;

};

#endif // GAME_H
