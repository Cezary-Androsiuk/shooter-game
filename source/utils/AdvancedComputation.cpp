#include "AdvancedComputation.h"


void AdvancedComputation::preventMoveThatExitBounds(
    creFloat playerBounds, creFloat obstacleBounds,
    cvFloat size, sf::Vector2f &position)
{
    /// Left
    if(playerBounds.left <= obstacleBounds.left)
        position = sf::Vector2f(
            obstacleBounds.left,
            position.y);
    /// Right
    if(playerBounds.right >= obstacleBounds.right)
        position = sf::Vector2f(
            obstacleBounds.right - size.x,
            position.y);
    /// Top
    if(playerBounds.top <= obstacleBounds.top)
        position = sf::Vector2f(
            position.x,
            obstacleBounds.top);
    /// Bottom
    if(playerBounds.bottom >= obstacleBounds.bottom)
        position = sf::Vector2f(
            position.x,
            obstacleBounds.bottom - size.y);
}

void AdvancedComputation::preventMoveThatEnterBounds(
    creFloat playerBounds, creFloat obstacleBounds,
    cvFloat size, sf::Vector2f &position)
{
    float overlapLeft   = playerBounds.right - obstacleBounds.left;
    float overlapRight  = obstacleBounds.right - playerBounds.left;
    float overlapTop    = playerBounds.bottom - obstacleBounds.top;
    float overlapBottom = obstacleBounds.bottom - playerBounds.top;

    /// test if collision occur
    if (overlapLeft > 0 && overlapRight > 0 && overlapTop > 0 && overlapBottom > 0)
    {
        /// test what collision is the smallest - that means this edges are colliding
        float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});

        if (minOverlap == overlapLeft)
        {
            position.x = obstacleBounds.left - size.x;
        }
        else if (minOverlap == overlapRight)
        {
            position.x = obstacleBounds.right;
        }
        else if (minOverlap == overlapTop)
        {
            position.y = obstacleBounds.top - size.y;
        }
        else if (minOverlap == overlapBottom)
        {
            position.y = obstacleBounds.bottom;
        }
    }
}

float AdvancedComputation::vectorToRotation(cvFloat originPoint, cvFloat targetPoint)
{
    /// compute difference
    float dx = targetPoint.x - originPoint.x;
    float dy = targetPoint.y - originPoint.y;

    /// compute angle in radians (knowing that axis Y is inverted in SFML)
    float angleRadians = std::atan2(-dy, dx);
    // printf("Angle: %.2f  |   Pos: %.2f, %.2f   |   ", angleRadians, dx, dy);

    /// convert radians to degrees
    float angleDegrees = angleRadians * (180.0f / static_cast<float>(M_PI));
    angleDegrees = -angleDegrees;

    /// normalize angle [0, 360)
    if (angleDegrees < 0) {
        angleDegrees += 360.0f;
    }

    return angleDegrees;
}

sf::Vector2f AdvancedComputation::rotationToVector(float angleDegrees)
{
    float angleRadians = angleDegrees * M_PI / 180.0f;
    return sf::Vector2f(std::cos(angleRadians), std::sin(angleRadians));
}

sf::Vector2f AdvancedComputation::calculateNormalizedVector(cvFloat currentPosition, cvFloat targetPosition)
{
    sf::Vector2f direction = targetPosition - currentPosition;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    // printf("%0.4f, %0.4f, L: %0.2f\n", direction.x, direction.y, length);

    if (length > 0) {
        return direction / length;
    }
    return sf::Vector2f(0, 0);
}
