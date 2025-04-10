#ifndef MAP_H
#define MAP_H

#include <vector>

#include <SFML/Graphics.hpp>

#include "environment/Obstacle.h"

class Map
{
public:
    Map();
    ~Map();

    void setMapSize(sf::Vector2u mapSize);
    void buildObstacles();

public:
    /* RENDER */
    void render(sf::RenderTarget *target);

    /* GETTERS */
    const sf::Vector2u &getMapSize();
    const std::vector<Obstacle *> getObstacles();

private:
    std::vector<Obstacle *> m_obstacles;
    bool m_obstaclesBuilded;

    sf::Vector2u m_mapSize;
};

#endif // MAP_H
