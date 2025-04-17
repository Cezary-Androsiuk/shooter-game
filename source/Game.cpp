#include "Game.h"

void Game::initFPSLabel()
{
    if(!m_fpsFont.loadFromFile(FONT_PATH))
    {
        fprintf(stderr, "loading font file failed from %s",  FONT_PATH);
    }
    else
    {
        m_fontLoaded = true;
        m_fpsLabel.setFont(m_fpsFont);
        m_fpsLabel.setString("FPS");
        m_fpsLabel.setCharacterSize(16);
        m_fpsLabel.setVisible(false);
    }
}

void Game::initValues()
{
    // m_gameState = GameState::Menu;
    m_gameState = GameState::Play;
    m_fps.maxFPS = 0;
    m_fps.minFPS = (uint)-1;
}

void Game::initWindow()
{
    sf::VideoMode vm = DEBUG_VIEW ? sf::VideoMode(800, 600) : sf::VideoMode::getDesktopMode();
    // m_contextSettings
    m_window = new sf::RenderWindow(vm, "Shooter Game", DEBUG_VIEW ? sf::Style::Default : sf::Style::Fullscreen, m_contextSettings);
    // m_window->setFramerateLimit(240);
}

void Game::initRenderTexture()
{
    // printf("max size: %u, ", sf::Texture::getMaximumSize());
    fflush(stdout);

    m_renderTextureInitialized = true;

    if(!m_renderTexture.create(m_window->getSize().x, m_window->getSize().y))
    {

        m_renderTextureInitialized = false;
    }

    m_renderSprite = std::make_unique<sf::Sprite>(m_renderTexture.getTexture());
}

void Game::initMenu()
{
    m_menu.setWindowSize(m_window->getSize());

    m_menu.init();
}

void Game::initPlay()
{
    m_play.setWindowSize(m_window->getSize());

    m_play.init();
}

Game::Game()
    : m_fontLoaded{false}
{
    printf("game start\n");fflush(stdout);
    this->initFPSLabel();
    this->initValues();
    this->initWindow();
    this->initRenderTexture();
    this->initMenu();
    this->initPlay();
}

Game::~Game()
{
    delete m_window;
}

void Game::changeStateToPlay()
{
    m_gameState = GameState::Play;
}

void Game::changeStateToMenu()
{
    m_gameState = GameState::Menu;
    m_menu.fflushGui();
}

void Game::pollEventGame()
{
    static bool allowEscapeKey = true;

    switch (m_currentEvent.type){
    case sf::Event::Closed:
        m_window->close(); // prevent clicking X to close window
        break;
    case sf::Event::KeyPressed:
        if(m_currentEvent.key.code == sf::Keyboard::Escape)
        {
            if(allowEscapeKey)
            {
                if(m_gameState == GameState::Menu)
                    this->changeStateToPlay();
                else
                    this->changeStateToMenu();
            }
            allowEscapeKey = false;
        }
    case sf::Event::KeyReleased:
        if(m_currentEvent.key.code == sf::Keyboard::Escape)
        {
            // printf("released\n");
            // fflush(stdout);
            allowEscapeKey = true;
        }
#if DEBUG_EXIT_APP
        if(m_currentEvent.key.code == sf::Keyboard::Grave)
            m_window->close();
#endif
        break;
    default:
        break;
    }
}

void Game::pollEvent()
{
    if(m_gameState == GameState::Play)
    {
        while(m_window->pollEvent(m_currentEvent)){
            this->pollEventGame();
            m_play.pollEvent(m_currentEvent);
        }
    }
    else if(m_gameState == GameState::Menu)
    {
        while(m_window->pollEvent(m_currentEvent)){
            this->pollEventGame();
            m_menu.pollEvent(m_currentEvent);
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
        snprintf(snOut, sizeof(snOut), "avgFPS: %u, min: %u", m_fps.avgFPS, m_fps.minFPS);
        // snprintf(snOut, sizeof(snOut), "frame: %u, fps: %d, min: %u", dt->currentGameTick(), fps, m_minFPS);
        // snprintf(snOut, sizeof(snOut), "frame: %u, fps: %d, (min: %u, max: %u)", dt->currentGameTick(), fps, m_minFPS, m_maxFPS);
        m_fpsLabel.setString(sf::String(snOut));

        sf::Vector2f boundsSize = m_fpsLabel.getSize();
        float newYPosition = m_window->getSize().x - boundsSize.x - 15;
        static bool firstSet = true;
        if(firstSet)
        {
            m_fpsLabel.setVisible(true);
            firstSet = false;
        }
        m_fpsLabel.setPosition({
            newYPosition,
            boundsSize.y
        });

    }
}


void Game::update()
{

    switch (m_gameState) {
    case GameState::Menu: m_menu.update(); break;
    case GameState::Play: m_play.update(); break;
    default: printf("unknown game state, can't update\n"); break;
    }

    if(m_menu.hasRequestStateEnd())
        this->changeStateToPlay();

    this->updateFPSLabel();
}

void Game::renderToTexture()
{

}

void Game::renderToScreen()
{

}

void Game::render()
{
    if(m_renderTextureInitialized)
        this->renderToTexture();
    else
        this->renderToScreen();

    m_window->clear(BACKGROUND_SF_COLOR);

    if(m_gameState == GameState::Menu)
    {
        // m_play.render(m_window); // make it background

        // sf::RectangleShape shape(sf::Vector2f(m_window->getSize().x, m_window->getSize().y));
        // shape.setFillColor(sf::Color(30,30,30, 200));
        // m_window->draw(shape);

        m_menu.render(m_window);
    }
    else if(m_gameState == GameState::Play)
    {
        m_play.render(m_window);
    }
    else
    {
        printf("unknown game state, can't render\n");
    }

    m_fpsLabel.render(m_window);

    m_window->display();
}

bool Game::running() const noexcept
{
    return m_window->isOpen();
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
    printf("\n");
}
