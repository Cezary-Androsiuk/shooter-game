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
#include "utils/DeltaTime.h"

#include "enums/GameState.h"

#include "states/Menu.h"
#include "states/Play.h"

#include "SimpleGUI/Label.hpp"
using namespace sgui;

#define BACKGROUND_SF_COLOR sf::Color(30, 30, 30)

class Game
{
    /* INITIALIZE */
    void initFPSLabel();
    void initValues();
    void initRenderWindow();
    void initRenderTexture();
    void initRenderShader();

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
    void renderObjects(sf::RenderTarget *target);
    void renderUsingTexture();
    void renderRightToScreen();
    void render();

    inline bool running() const noexcept;

public:
    static void play();

private:
    sf::RenderWindow* m_renderWindow;
    sf::RenderTexture m_renderTexture;
    std::unique_ptr<sf::Sprite> m_renderSprite;
    sf::Shader m_renderShader;
    bool m_applyShaders;
    bool m_renderTextureInitialized;
    sf::ContextSettings m_contextSettings;
    sf::Event m_currentEvent;

    bool m_enableLaggingTests;

    struct{
        bool displayed;
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

        sf::Font fpsFont;
        bool fontLoaded;
        Label fpsLabel;
    } m_fps;

    GameState m_gameState;
    Menu m_menu;
    Play m_play;
    // EnemySpawner m_enemySpawner;
    // std::vector<Enemy> m_enemies;

};

#endif // GAME_H
