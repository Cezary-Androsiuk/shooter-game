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
#include "states/DefeatState.h"
#include "objects/entities/Player.h"
#include "environment/Sound.h"

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
    void initSound();

    void initMenuState();
    void initPlayState();
    void initPausePlayState();
    void initDefeatState();

    Game();
    ~Game();

    void exitGame();

    /* OTHER */
    void changeStateFromMenuToPlay();   /// Menu -> Play
    void changeStateFromPlayToPause();  /// Play -> Pause
    void changeStateFromPauseToPlay();  /// Pause -> Play
    void changeStateFromPauseToMenu();  /// Pause -> Menu
    void changeStateFromPlayToDefeat(); /// Play -> Defeat
    void changeStateFromDefeatToMenu(); /// Defeat -> Menu
    void freeUnusedState();

    /* EVENTS */
    void pollEventGame();
    void pollEvent();

    /* UPDATE */
    void updateFPSLabel();
    void updateMenuState();
    void updatePlayState();
    void updatePausePlayState();
    void updateDefeatState();
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
    std::unique_ptr<DefeatState> m_defeatState;

    Player *m_player;
    Sound *m_sound;
};

#endif // GAME_H
