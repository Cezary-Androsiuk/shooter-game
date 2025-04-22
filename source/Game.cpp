#include "Game.h"

#include "utils/Constants.h"
#include "utils/Support.h"
#include "utils/InitialData.h"
#include "utils/DeltaTime.h"
#include "utils/GlobalData.h"
#include "objects/Weapon.h"
#include "objects/Armor.h"

void Game::initData()
{
    m_gameState = GameState::Menu;
    m_fps.maxFPS = 0;
    m_fps.minFPS = (uint)-1;
    m_renderTextureInitialized = false;
    m_enableLaggingTests = InitialData::Game::getEnableLaggingTests();
}

void Game::initRenderWindow()
{
    sf::Vector2u windowSize(
        sf::VideoMode::getDesktopMode().width,
        sf::VideoMode::getDesktopMode().height);

    if(InitialData::Game::getDebugView()) /// makes window smaller
    {
        windowSize.x *= 0.6;
        windowSize.y *= 0.6;
    }

    sf::VideoMode vm = sf::VideoMode(windowSize.x, windowSize.y);

    m_renderWindow = std::make_unique<sf::RenderWindow>(
        vm, "Shooter Game",
        InitialData::Game::getDebugView() ?
            sf::Style::Default : sf::Style::None,
        m_contextSettings
    );
    // m_renderWindow->setFramerateLimit(240);

    GlobalData::getInstance()->setWindowSize({
        static_cast<float>(windowSize.x),
        static_cast<float>(windowSize.y)
    });
}

void Game::initRenderTexture()
{
    m_renderTexture = std::make_unique<sf::RenderTexture>();

    if(!m_renderTexture->create(m_renderWindow->getSize().x, m_renderWindow->getSize().y))
    {
        fprintf(stderr, "creating render texture failed\n");
        fflush(stderr);
        return;
    }

    m_renderSprite = std::make_unique<sf::Sprite>(m_renderTexture->getTexture());

    /// flip sprite - default rendering has different coordinates
    m_renderSprite->setScale(1.f, -1.f); /// vertical flip
    m_renderSprite->setPosition(0, m_renderWindow->getSize().y);

    m_renderTextureInitialized = true;
}

void Game::initBlurShader()
{
    m_blurShader = std::make_unique<sf::Shader>();

    if (!m_blurShader->loadFromFile(RENDER_SHADER1_PATH, sf::Shader::Fragment))
    {
        // Support::displayApplicationError("cannot load blur.frag file");
        fprintf(stderr, "loading render shader failed\n");
        fflush(stderr);
        return;
    }

    m_blurShader->setUniform("size", GlobalData::getInstance()->getWindowSize());
    m_blurShader->setUniform("blurDirections", 16.f);
    m_blurShader->setUniform("blurQuality", 8.f);
    m_blurShader->setUniform("blurSize", 16.f);

    fflush(stderr); /// setUniform could produce some errors
}

void Game::initFPSLabel()
{
    m_fps.fpsLabel.setFont(GlobalData::getInstance()->getFontOpenSansRegular());
    m_fps.fpsLabel.setString("FPS");
    m_fps.fpsLabel.setCharacterSize(16);
    m_fps.fpsLabel.setVisible(false);
    m_fps.displayed = InitialData::Game::getEnabledFPSAtStart();
}

void Game::initPlayer()
{
    m_player = Player::getInstance();
    // m_player->setWeapon(std::make_unique<Weapon>());
    // m_player->setArmor(std::make_unique<Armor>());

    m_player->init();
}

void Game::initMenuState()
{
    printf("init menu\n");fflush(stdout);
    m_menuState = std::make_unique<MenuState>();
    m_menuState->init();
}

void Game::initPlayState()
{
    printf("init play\n");fflush(stdout);
    m_playState = std::make_unique<PlayState>();
    m_playState->init();
}

void Game::initPausePlayState()
{
    printf("init pause\n");fflush(stdout);
    m_pausePlayState = std::make_unique<PausePlayState>();

    /// PausePlay state can be started only from the Play state
    /// that means RenderTexture has inside last frame that was displayed (frame from Play state)
    if(m_renderTextureInitialized)
    {
        sf::RenderTexture renderTexture;
        if(renderTexture.create(m_renderWindow->getSize().x, m_renderWindow->getSize().y))
        {
            if(InitialData::Game::getApplyShaders())
                renderTexture.draw(*m_renderSprite, m_blurShader.get());
            else
                renderTexture.draw(*m_renderSprite);

            m_pausePlayState->setBlurredPlayBackgroundImage(
                renderTexture.getTexture().copyToImage());
        }
        else
        {
            fprintf(stderr, "failed to create blurred play background image\n");
            fflush(stderr);
            m_pausePlayState->disableBlurredPlayBackground();
        }
    }

    m_pausePlayState->init();
}

void Game::initDefeatState()
{
    printf("init defeat\n");fflush(stdout);
    m_defeatState = std::make_unique<DefeatState>();

    /// PausePlay state can be started only from the Play state
    /// that means RenderTexture has inside last frame that was displayed (frame from Play state)
    if(m_renderTextureInitialized)
    {
        sf::RenderTexture renderTexture;
        if(renderTexture.create(m_renderWindow->getSize().x, m_renderWindow->getSize().y))
        {
            // if(InitialData::Game::getApplyShaders())
            //     renderTexture.draw(*m_renderSprite, m_blurShader.get());
            // else
                renderTexture.draw(*m_renderSprite);

            m_defeatState->setBlurredPlayBackgroundImage(
                renderTexture.getTexture().copyToImage());
        }
        else
        {
            fprintf(stderr, "failed to create blurred play background image\n");
            fflush(stderr);
            m_defeatState->disableBlurredPlayBackground();
        }
    }

    m_defeatState->init();
}

Game::Game()
{
    printf("game start\n");fflush(stdout);

    this->initData();

    this->initRenderWindow();
    this->initRenderTexture();
    this->initBlurShader();
    this->initFPSLabel();

    this->initPlayer();

    this->initMenuState();
}

Game::~Game()
{
    printf("game end\n");fflush(stdout);
}

void Game::exitGame()
{
    m_renderWindow->close();
}

void Game::changeStateFromMenuToPlay()
{
    initPlayState();
    m_gameState = GameState::Play;
}

void Game::changeStateFromPlayToPause()
{
    initPausePlayState();
    m_gameState = GameState::PausePlay;
}

void Game::changeStateFromPauseToPlay()
{
    m_gameState = GameState::Play;
}

void Game::changeStateFromPauseToMenu()
{
    initMenuState();
    m_gameState = GameState::Menu;
}

void Game::changeStateFromPlayToDefeat()
{
    initDefeatState();
    m_gameState = GameState::Defeat;
}

void Game::changeStateFromDefeatToMenu()
{
    initMenuState();
    m_gameState = GameState::Menu;
}

void Game::freeUnusedState()
{
    if(m_menuState && m_gameState != GameState::Menu)
        m_menuState.reset();

    /// do not delete play nor pause states while one of them is active
    bool isNotPlayState = m_gameState != GameState::Play &&
                          m_gameState != GameState::PausePlay;

    if(m_playState && isNotPlayState)
        m_playState.reset();

    if(m_pausePlayState && m_gameState != GameState::PausePlay)
        m_pausePlayState.reset();

    if(m_defeatState && m_gameState != GameState::Defeat)
        m_defeatState.reset();
}

void Game::pollEventGame()
{
    switch (m_currentEvent.type){
    case sf::Event::Closed:
        this->exitGame();
        break;
    case sf::Event::KeyPressed:

        if(m_currentEvent.key.code == sf::Keyboard::Escape)
        {
            switch (m_gameState) {
            case GameState::Menu: this->exitGame(); break;
            case GameState::Play: this->changeStateFromPlayToPause(); break;
            case GameState::PausePlay: this->changeStateFromPauseToPlay(); break;
            case GameState::Defeat: this->changeStateFromDefeatToMenu(); break;
            default:
                Support::displayApplicationError("unknown game state, can't render");
                exit(1);
            }
        }
        else if(m_currentEvent.key.code == sf::Keyboard::Grave)
        {
            if(InitialData::Game::getDebugExitView())
                this->exitGame();
        }
        else if(m_currentEvent.key.code == sf::Keyboard::F)
        {
            m_fps.displayed = !m_fps.displayed;
        }
        else if(m_currentEvent.key.code == sf::Keyboard::K) /// kill the player
        {
            m_player->dealDamage(1000);
        }

        if(m_enableLaggingTests)
        {
            static int lagDelay = 100;
            if(m_currentEvent.key.code == sf::Keyboard::L)
            {
                Support::emulateLag(lagDelay);
            }
            else if(m_currentEvent.key.code == sf::Keyboard::Semicolon)
            {
                if(lagDelay > 0)
                    lagDelay -= 20;
                printf("lag delay decreased to: %d\n", lagDelay);
                fflush(stdout);
            }
            else if(m_currentEvent.key.code == sf::Keyboard::Apostrophe)
            {
                lagDelay += 20;
                printf("lag delay increased to: %d\n", lagDelay);
                fflush(stdout);
            }
        }

        // printf("event key code: %d\n", m_currentEvent.key.code);
        // fflush(stdout);
    case sf::Event::KeyReleased:
        break;
    default:
        break;
    }
}

void Game::pollEvent()
{
    GlobalData::getInstance()->setMousePosition(
        m_renderWindow->mapPixelToCoords(
            sf::Mouse::getPosition(*m_renderWindow)
            )
        );

    /// redundant but checking 'if' conditions in loop is not necessary and might be slow
    if(m_gameState == GameState::Menu)
    {
        while(m_renderWindow->pollEvent(m_currentEvent)){
            this->pollEventGame();
            m_menuState->pollEvent(m_currentEvent);
        }
    }
    else if(m_gameState == GameState::Play)
    {
        while(m_renderWindow->pollEvent(m_currentEvent)){
            this->pollEventGame();
            m_playState->pollEvent(m_currentEvent);
        }
    }
    else if(m_gameState == GameState::PausePlay)
    {
        while(m_renderWindow->pollEvent(m_currentEvent)){
            this->pollEventGame();
            m_pausePlayState->pollEvent(m_currentEvent);
        }
    }
    else if(m_gameState == GameState::Defeat)
    {
        while(m_renderWindow->pollEvent(m_currentEvent)){
            this->pollEventGame();
            m_defeatState->pollEvent(m_currentEvent);
        }
    }
}

void Game::updateFPSLabel()
{
    // if(dt->currentGameTick() % 100 == 0)
    int elapsedTime = m_fps.fpsDisplayClock.getElapsedTime().asMilliseconds();
    static bool avgQueueInitialized = false;
    if(elapsedTime > m_fps.fpsDisplayDelayMS || !avgQueueInitialized)
    {
        m_fps.fpsDisplayClock.restart();

        DeltaTime *dt = DeltaTime::get();
        int fps = 1.f/dt->value();


        // if(fps > m_maxFPS) m_maxFPS = fps;
        if(fps < m_fps.minFPS) m_fps.minFPS = fps;


        m_fps.avgFPSData.queue.push(fps);
        m_fps.avgFPSData.sumOfLastNValues += fps;
        bool avgFPSQueueMaxSizeCrossed = m_fps.avgFPSData.queue.size() > m_fps.avgFPSData.maxLastValues;
        if(avgFPSQueueMaxSizeCrossed)
        {
            m_fps.avgFPSData.sumOfLastNValues -= m_fps.avgFPSData.queue.front();
            m_fps.avgFPSData.queue.pop();
        }
        // printf("%u/%u = %u\n", m_fps.avgFPSData.sumOfLastNValues, m_fps.avgFPSData.queue.size(), m_fps.avgFPSData.sumOfLastNValues / m_fps.avgFPSData.queue.size());
        m_fps.avgFPS = m_fps.avgFPSData.sumOfLastNValues / m_fps.avgFPSData.queue.size(); // never division by 0

        if(!m_fps.displayed)
            return;

        if(!avgFPSQueueMaxSizeCrossed)
        {
            // printf("skip not full\n");
            return;
        }

        /// delay print by N new  elements
        // static int callNumberSinceQueueFilled = 0;
        // if(callNumberSinceQueueFilled < 5)
        // {
        //     // printf("skip %d\n", callNumberSinceQueueFilled);
        //     ++callNumberSinceQueueFilled;
        //     return; // skip first N calls due to invalid data
        // }

        avgQueueInitialized = true;

        char snOut[128];
        // snprintf(snOut, sizeof(snOut), "FPS: %u, min: %u", fps, m_fps.minFPS);
        int requiredSize = snprintf(snOut, sizeof(snOut), "avgFPS: %u, min: %u", m_fps.avgFPS, m_fps.minFPS);
        // snprintf(snOut, sizeof(snOut), "frame: %u, fps: %d, min: %u", dt->currentGameTick(), fps, m_minFPS);
        // snprintf(snOut, sizeof(snOut), "frame: %u, fps: %d, (min: %u, max: %u)", dt->currentGameTick(), fps, m_minFPS, m_maxFPS);
        Support::informAboutToSmallBuffer(requiredSize, sizeof(snOut));
        m_fps.fpsLabel.setString(sf::String(snOut));

        sf::Vector2f boundsSize = m_fps.fpsLabel.getSize();
        float newYPosition = m_renderWindow->getSize().x - boundsSize.x - 15;
        static bool firstSet = true;
        if(firstSet)
        {
            m_fps.fpsLabel.setVisible(true);
            firstSet = false;
        }
        m_fps.fpsLabel.setPosition({
            newYPosition,
            boundsSize.y
        });

    }
}

void Game::updateMenuState()
{
    m_menuState->update();

    if(m_menuState->requestPlayState())
        this->changeStateFromMenuToPlay();

    if(m_menuState->requestExitGame())
        this->exitGame();
}

void Game::updatePlayState()
{
    m_playState->update();

    if(m_playState->requestDefeatState())
        this->changeStateFromPlayToDefeat();
}

void Game::updatePausePlayState()
{
    m_pausePlayState->update();

    if(m_pausePlayState->requestContinuePlay())
        this->changeStateFromPauseToPlay();

    if(m_pausePlayState->requestExitPlay())
        this->changeStateFromPauseToMenu();
}

void Game::updateDefeatState()
{
    m_defeatState->update();

    if(m_defeatState->requestExitPlay())
        this->changeStateFromDefeatToMenu();
}

void Game::update()
{
    switch (m_gameState) {
    case GameState::Menu: this->updateMenuState(); break;
    case GameState::Play: this->updatePlayState(); break;
    case GameState::PausePlay: this->updatePausePlayState(); break;
    case GameState::Defeat: this->updateDefeatState(); break;
    default:
        Support::displayApplicationError("unknown game state, can't render");
        exit(1);
    }

    this->freeUnusedState();
    this->updateFPSLabel();
}

void Game::renderObjects(sf::RenderTarget *target)
{
    switch (m_gameState) {
    case GameState::Menu: m_menuState->render(target); break;
    case GameState::Play: m_playState->render(target); break;
    case GameState::PausePlay: m_pausePlayState->render(target); break;
    case GameState::Defeat: m_defeatState->render(target); break;
    default:
        Support::displayApplicationError("unknown game state, can't render");
        exit(1);
    }

    if(m_fps.displayed)
        m_fps.fpsLabel.render(target);
}

void Game::renderUsingTexture()
{
    m_renderTexture->clear(WINDOW_BACKGROUND_SF_COLOR);

    this->renderObjects(m_renderTexture.get());

    /// Apply shaders
    // bool applyShaders = InitialData::Game::getApplyShaders();
    // if(m_blurShader->isAvailable() && applyShaders)
    //     m_renderWindow->draw(*m_renderSprite, m_blurShader.get());
    // else


    m_renderWindow->draw(*m_renderSprite);
}

void Game::renderRightToScreen()
{
    this->renderObjects(m_renderWindow.get());
}

void Game::render()
{
    m_renderWindow->clear(WINDOW_BACKGROUND_SF_COLOR);

    if(m_renderTextureInitialized)
    {
        this->renderUsingTexture();
    }
    else
    {
        this->renderRightToScreen();
    }

    m_renderWindow->display();
}

bool Game::running() const noexcept
{
    return m_renderWindow->isOpen();
}

void Game::play()
{
    Game game;
    while(game.running())
    {
        DeltaTime::get()->update();

        game.pollEvent();
        game.update();
        game.render();
    }
}
