#include "Obstacle.h"

#include "utils/Constants.h"
#include "utils/GlobalData.h"

Obstacle::Obstacle(sf::FloatRect bounds)
{
    m_bounds = bounds;

    // m_boundsBody.setSize(sf::Vector2f(bounds.width, bounds.height));
    // m_boundsBody.setPosition(sf::Vector2f(bounds.left, bounds.top));
    // m_boundsBody.setFillColor(sf::Color::Red);

    const sf::Texture &mainSpriteTexture =
        GlobalData::getInstance()->getMainSpriteTexture();

    const int frameSizeX = MAIN_SPRITE::OBSTACLE_FRAME_SIZE_X;
    const int frameSizeY = MAIN_SPRITE::OBSTACLE_FRAME_SIZE_Y;
    const int frameOffsetX = MAIN_SPRITE::OBSTACLE_FRAME_OFFSET_X;
    const int frameOffsetY = MAIN_SPRITE::OBSTACLE_FRAME_OFFSET_Y;

    int objectYPos = frameOffsetY;
    m_body.setTexture(mainSpriteTexture, false);
    m_body.setTextureRect(
        sf::IntRect(frameOffsetX, objectYPos, frameSizeX, frameSizeY));
    m_body.setPosition(sf::Vector2f(bounds.left, bounds.top));
}

void Obstacle::render(sf::RenderTarget *target)
{
    // target->draw(m_boundsBody);
    target->draw(m_body);
}

const sf::FloatRect &Obstacle::getBounds() const
{
    return m_bounds;
}
