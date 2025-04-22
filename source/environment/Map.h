#ifndef MAP_H
#define MAP_H

#include <vector>

#include <SFML/Graphics.hpp>

#include "environment/Obstacle.h"

class Map
{
    void initBackground();

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
    sf::Sprite m_background;

    std::vector<Obstacle *> m_obstacles;
    bool m_obstaclesBuilded;
};

#endif // MAP_H
