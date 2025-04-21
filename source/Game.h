#ifndef GAME_H
#define GAME_H

#include <memory>
#include <queue>

#include <SFML/Graphics.hpp>
#include <SimpleGUI/Label.hpp>

#include "utils/Constants.h"
#include "enums/GameState.h"
#include "states/MenuState.h"
#include "states/PlayState.h"
#include "states/PausePlayState.h"
#include "objects/entities/Player.h"

using namespace sgui;

class Game
{
    /* INITIALIZE */
    void initData();
    void initRenderWindow();
    void initRenderTexture();
    void initBlurShader();
    void initFPSLabel();
    void initPlayer();

    void initMenuState();
    void initPlayState();
    void initPausePlayState();

    Game();
    ~Game();

    void exitGame();

    /* OTHER */
    void changeStateFromMenuToPlay();
    void changeStateFromPlayToPause();
    void changeStateFromPauseToPlay();
    void changeStateFromPauseToMenu();
    void freeUnusedState();

    /* EVENTS */
    void pollEventGame();
    void pollEvent();

    /* UPDATE */
    void updateFPSLabel();
    void updateMenuState();
    void updatePlayState();
    void updatePausePlayState();
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
    std::unique_ptr<sf::RenderWindow> m_renderWindow;
    std::unique_ptr<sf::RenderTexture> m_renderTexture;
    std::unique_ptr<sf::Sprite> m_renderSprite;
    std::unique_ptr<sf::Shader> m_blurShader;
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

        Label fpsLabel;
    } m_fps;

    GameState m_gameState;
    std::unique_ptr<MenuState> m_menuState;
    std::unique_ptr<PlayState> m_playState;
    std::unique_ptr<PausePlayState> m_pausePlayState;

    Player *m_player;
};

#endif // GAME_H
