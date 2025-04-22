#include "Map.h"

#include "utils/Constants.h"
#include "utils/GlobalData.h"

void Map::initBackground()
{
    const sf::Vector2f &windowRatio = GlobalData::getInstance()->getWindowRatio();

    m_background.setTexture(
        GlobalData::getInstance()->getPlayBackgroundTexture(), false);
    m_background.setTextureRect(sf::IntRect(0, 0, 1920, 1080));
    m_background.setScale(windowRatio);
}

Map::Map()
    : m_obstaclesBuilded{false}
{
    this->initBackground();
}

Map::~Map()
{
    for(Obstacle *obstacle : m_obstacles)
        delete obstacle;
}

void Map::buildObstacles()
{
    if(m_obstaclesBuilded) return;

    m_obstacles.push_back(new Obstacle(sf::FloatRect(100,100,40,40)));
    m_obstacles.push_back(new Obstacle(sf::FloatRect(200,200,40,40)));

    m_obstaclesBuilded = true;
}

void Map::render(sf::RenderTarget *target)
{
    target->draw(m_background);

    for(Obstacle *obstacle : m_obstacles)
        obstacle->render(target);
}

const std::vector<Obstacle *> Map::getObstacles()
{
    return m_obstacles;
}
