#include "Obstacle.h"


Obstacle::Obstacle(sf::FloatRect bounds)
{
    m_bounds = bounds;

    m_body.setSize(sf::Vector2f(bounds.width, bounds.height));
    m_body.setPosition(sf::Vector2f(bounds.left, bounds.top));
    m_body.setFillColor(sf::Color::Red);
}

void Obstacle::render(sf::RenderTarget *target)
{
    target->draw(m_body);
}

const sf::FloatRect &Obstacle::getBounds() const
{
    return m_bounds;
}
