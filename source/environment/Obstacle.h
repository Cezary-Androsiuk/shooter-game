#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>

class Obstacle
{
public:
    Obstacle(sf::FloatRect bounds);

public:
    /* RENDER */
    void render(sf::RenderTarget *target);

    /* GETTERS */
    const sf::FloatRect &getBounds() const;

private:
    sf::FloatRect m_bounds;
    // sf::RectangleShape m_boundsBody;

    sf::Sprite m_body;
};

#endif // OBSTACLE_H
