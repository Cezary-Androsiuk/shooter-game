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

    const sf::Vector2f &windowSize = GlobalData::getInstance()->getWindowSize();
    const sf::Vector2f &windowRatio = GlobalData::getInstance()->getWindowRatio();

    sf::Vector2f obstacleSize(40, 40);

    /// temporary position:
    auto tPos = [&](float x, float y){
        return sf::Vector2f(x, y);
    };
    /// temporary position:
    auto tRect = [&](float x, float y){
        return sf::FloatRect(tPos(x, y), obstacleSize);
    };


    /// left
    m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 -180 ,windowSize.y/2+60)));
    // m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 -180 ,windowSize.y/2+20)));
    // m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 -180 ,windowSize.y/2-20))); /// center
    // m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 -180 ,windowSize.y/2-60)));
    m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 -180 ,windowSize.y/2-100)));

    /// right
    m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 +140 ,windowSize.y/2+60)));
    // m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 +140 ,windowSize.y/2+20)));
    // m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 +140 ,windowSize.y/2-20))); /// center
    // m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 +140 ,windowSize.y/2-60)));
    m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 +140 ,windowSize.y/2-100)));


    /// top
    m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 -220 ,windowSize.y/2 -240)));
    m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 -180 ,windowSize.y/2 -240)));
    // m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 -140 ,windowSize.y/2 -240)));
    // m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 -100 ,windowSize.y/2 -240)));
    m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 -60 ,windowSize.y/2 -240)));
    m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 -20 ,windowSize.y/2 -240))); /// center
    m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 +20 ,windowSize.y/2 -240))); /// center
    // m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 +60 ,windowSize.y/2 -240)));
    // m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 +100 ,windowSize.y/2 -240)));
    m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 +140 ,windowSize.y/2 -240)));
    m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 +180 ,windowSize.y/2 -240)));


    /// top
    m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 -220 ,windowSize.y/2 -240)));
    m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 -180 ,windowSize.y/2 -240)));
    // m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 -140 ,windowSize.y/2 -240)));
    // m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 -100 ,windowSize.y/2 -240)));
    m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 -60 ,windowSize.y/2 -240)));
    m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 -20 ,windowSize.y/2 -240))); /// center
    m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 +20 ,windowSize.y/2 -240))); /// center
    // m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 +60 ,windowSize.y/2 -240)));
    // m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 +100 ,windowSize.y/2 -240)));
    m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 +140 ,windowSize.y/2 -240)));
    m_obstacles.push_back(new Obstacle(tRect(windowSize.x/2 +180 ,windowSize.y/2 -240)));

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
