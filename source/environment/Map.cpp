#include "Map.h"

Map::Map()
    : m_obstaclesBuilded{false}
{
}

Map::~Map()
{
    for(Obstacle *obstacle : m_obstacles)
        delete obstacle;
}

void Map::setMapSize(sf::Vector2u mapSize)
{
    m_mapSize = mapSize;
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
    for(Obstacle *obstacle : m_obstacles)
        obstacle->render(target);
}

const sf::Vector2u &Map::getMapSize()
{
    return m_mapSize;
}

const std::vector<Obstacle *> Map::getObstacles()
{
    return m_obstacles;
}
