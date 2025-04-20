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

    void buildObstacles();

public:
    /* RENDER */
    void render(sf::RenderTarget *target);

    /* GETTERS */
    const std::vector<Obstacle *> getObstacles();

private:
    std::vector<Obstacle *> m_obstacles;
    bool m_obstaclesBuilded;
};

#endif // MAP_H
