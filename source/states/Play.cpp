#include "Play.h"


void Play::initMap()
{
    m_map = std::make_shared<Map>();
    m_map->setMapSize(m_windowSize);
    m_map->buildObstacles();
}

void Play::initPlayer()
{
    float width = static_cast<float>(m_windowSize.x);
    float height = static_cast<float>(m_windowSize.y);
    m_player.setPosition(sf::Vector2f(width/2.f, height/2.f));
    m_player.setAvailableAreaForPlayer(m_map);
}

void Play::initObjects()
{
    this->initMap();
    this->initPlayer();
}

Play::Play()
{
}

Play::~Play()
{

}

void Play::init()
{
    this->initObjects();
}

void Play::pollEvent(const sf::Event &event)
{

}

void Play::update()
{
    m_player.update();
}

void Play::render(sf::RenderTarget *target)
{
    m_map->render(target);
    m_player.render(target);
}

void Play::setWindowSize(const sf::Vector2u &size)
{
    m_windowSize = size;
}
