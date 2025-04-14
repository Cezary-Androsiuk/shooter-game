#include "Game.h"

void Game::initValues()
{
    // m_gameState = GameState::Menu;
    m_gameState = GameState::Play;
    m_maxFPS = 0;
    m_minFPS = (size_t)-1;
}

void Game::initWindow()
{
    sf::VideoMode vm = DEBUG_VIEW ? sf::VideoMode(800, 600) : sf::VideoMode::getDesktopMode();
    // m_contextSettings
    m_window = new sf::RenderWindow(vm, "Shooter Game", DEBUG_VIEW ? sf::Style::Default : sf::Style::Fullscreen, m_contextSettings);
    // m_window->setFramerateLimit(240);
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
{
    this->initValues();
    this->initWindow();
    this->initMenu();
    this->initPlay();
}

Game::~Game()
{
    delete m_window;
}

void Game::pollEventGame()
{
    switch (m_currentEvent.type){
    case sf::Event::Closed:
        m_window->close();
        break;
    case sf::Event::KeyPressed:
        if(m_currentEvent.key.code == sf::Keyboard::Escape)
        {
            if(m_gameState == GameState::Menu)
                m_gameState = GameState::Play;
            else
                m_gameState = GameState::Menu;
        }
#if DEBUG_EXIT_APP
        if(m_currentEvent.key.code == sf::Keyboard::P)
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


void Game::update()
{
    DeltaTime *dt = DeltaTime::get();
    if(dt->currentGameTick() % 100 == 1)
    {
        int fps = 1.f/dt->value();
        if(fps > m_maxFPS) m_maxFPS = fps;
        if(fps < m_minFPS) m_minFPS = fps;

        printf("\r                              \r");
        printf("frame: % 9llu, fps: % 6d, (min: %llu, max: %llu)", dt->currentGameTick(), fps, m_minFPS, m_maxFPS);
        fflush(stdout);
    }

    switch (m_gameState) {
    case GameState::Menu: m_menu.update(); break;
    case GameState::Play: m_play.update(); break;
    default: printf("unknown game state, can't update\n"); break;
    }
}

void Game::render()
{
    m_window->clear(BACKGROUND_SF_COLOR);

    if(m_gameState == GameState::Menu)
    {
        m_play.render(m_window); // make it background

        sf::RectangleShape shape(sf::Vector2f(m_window->getSize().x, m_window->getSize().y));
        shape.setFillColor(sf::Color(30,30,30, 200));
        m_window->draw(shape);

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
