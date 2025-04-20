#include "Game.h"

void Game::initFPSLabel()
{
    m_fps.fontLoaded = false;

    if(!m_fps.fpsFont.loadFromFile(FONT_PATH))
    {
        fprintf(stderr, "loading font file failed from %s",  FONT_PATH);
    }
    else
    {
        m_fps.fontLoaded = true;
        m_fps.fpsLabel.setFont(m_fps.fpsFont);
        m_fps.fpsLabel.setString("FPS");
        m_fps.fpsLabel.setCharacterSize(16);
        m_fps.fpsLabel.setVisible(false);
        m_fps.displayed = Data::Game::getEnabledFPSAtStart();
    }
}

void Game::initValues()
{
    m_gameState = GameState::Menu;
    m_fps.maxFPS = 0;
    m_fps.minFPS = (uint)-1;
    m_renderTextureInitialized = false;
    m_applyShaders = Data::Game::getApplyShaders();
    m_enableLaggingTests = Data::Game::getEnableLaggingTests();
}

void Game::initRenderWindow()
{
    sf::VideoMode vm =
        Data::Game::getDebugView() ?  /// makes window smaller
                           sf::VideoMode(
                               sf::VideoMode::getDesktopMode().width /2,
                               sf::VideoMode::getDesktopMode().height /2) :
                           sf::VideoMode(
                                sf::VideoMode::getDesktopMode().width,
                                sf::VideoMode::getDesktopMode().height);
    // m_contextSettings
    m_renderWindow = new sf::RenderWindow(
        vm, "Shooter Game",
        Data::Game::getDebugView() ?
            sf::Style::Default :
            sf::Style::None,
        m_contextSettings
    );
    // m_renderWindow->setFramerateLimit(240);
}

void Game::initRenderTexture()
{
    // printf("max size: %u, ", sf::Texture::getMaximumSize());
    // fflush(stdout);

    if(!m_renderTexture.create(m_renderWindow->getSize().x, m_renderWindow->getSize().y))
    {
        fprintf(stderr, "creating render texture failed\n");
        fflush(stderr);
        return;
    }

    m_renderSprite = std::make_unique<sf::Sprite>(m_renderTexture.getTexture());

    /// flip sprite - default rendering has different coordinates
    m_renderSprite->setScale(1.f, -1.f); /// vertical flip
    m_renderSprite->setPosition(0, m_renderWindow->getSize().y);

    m_renderTextureInitialized = true;
}

void Game::initRenderShader()
{
    if (!m_renderShader.loadFromFile(RENDER_SHADER1_PATH, sf::Shader::Fragment))
    {
        // Support::displayApplicationError("cannot load blur.frag file");

        fprintf(stderr, "loading render shader failed\n");
        fflush(stderr);
        return;
    }

    m_renderShader.setUniform("texture", m_renderTexture.getTexture());
    m_renderShader.setUniform("texSize", sf::Vector2f(m_renderWindow->getSize()));  // sf::Vector2f(width, height)
    m_renderShader.setUniform("radius", 50.f);                         // promień blur'a
    m_renderShader.setUniform("direction", sf::Vector2f(1.f, 0.f));   // poziome rozmycie

    // m_renderShader.setUniform("texture", m_renderTexture.getTexture());
    // m_renderShader.setUniform("blurRadius", 2.5f);  // Im wyższa wartość, silniejsze rozmycie
    // m_renderShader.setUniform("textureSize", sf::Vector2f(m_renderWindow->getSize()));

    fflush(stderr);
}

void Game::initMenu()
{
    m_menu.setWindowSize(m_renderWindow->getSize());

    m_menu.init();
}

void Game::initPlay()
{
    m_play.setWindowSize(m_renderWindow->getSize());

    m_play.init();
}

Game::Game()
{
    printf("game start\n");fflush(stdout);

    this->initFPSLabel();
    this->initValues();
    this->initRenderWindow();
    this->initRenderTexture();
    this->initRenderShader();
    this->initMenu();
    this->initPlay();
}

Game::~Game()
{
    delete m_renderWindow;
}

void Game::exitGame()
{

    m_renderWindow->close();
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
        this->exitGame();
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
        else if(m_currentEvent.key.code == sf::Keyboard::F)
        {
            m_fps.displayed = !m_fps.displayed;
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
        if(m_currentEvent.key.code == sf::Keyboard::Escape)
        {
            // printf("released\n");
            // fflush(stdout);
            allowEscapeKey = true;
        }
        if(Data::Game::getDebugExitView())
        {
            if(m_currentEvent.key.code == sf::Keyboard::Grave)
                this->exitGame();
        }
        break;
    default:
        break;
    }
}

void Game::pollEvent()
{
    if(m_gameState == GameState::Play)
    {
        while(m_renderWindow->pollEvent(m_currentEvent)){
            this->pollEventGame();
            m_play.pollEvent(m_currentEvent);
        }
    }
    else if(m_gameState == GameState::Menu)
    {
        while(m_renderWindow->pollEvent(m_currentEvent)){
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


void Game::update()
{

    switch (m_gameState) {
    case GameState::Menu: m_menu.update(); break;
    case GameState::Play: m_play.update(); break;
    default: printf("unknown game state, can't update\n"); break;
    }

    if(m_menu.requestPlayState())
        this->changeStateToPlay();
    if(m_menu.exitGameRequest())
        this->exitGame();

    this->updateFPSLabel();
}

void Game::renderObjects(sf::RenderTarget *target)
{
    if(m_gameState == GameState::Menu)
    {
        // m_play.render(target); // make it background

        // sf::RectangleShape shape(sf::Vector2f(target->getSize().x, target->getSize().y));
        // shape.setFillColor(sf::Color(30,30,30, 200));
        // target->draw(shape);

        m_menu.render(target);
    }
    else if(m_gameState == GameState::Play)
    {
        m_play.render(target);
    }
    else
    {
        printf("unknown game state, can't render\n");
    }

    if(m_fps.displayed)
        m_fps.fpsLabel.render(target);
}

void Game::renderUsingTexture()
{
    m_renderTexture.clear(BACKGROUND_SF_COLOR);

    this->renderObjects(&m_renderTexture);

    if(m_renderShader.isAvailable() && m_applyShaders)
        m_renderWindow->draw(*m_renderSprite, &m_renderShader);
    else
    {
        m_renderWindow->draw(*m_renderSprite);
    }

}

void Game::renderRightToScreen()
{
    this->renderObjects(m_renderWindow);
}

void Game::render()
{
    m_renderWindow->clear(BACKGROUND_SF_COLOR);

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
    printf("\n");
}
