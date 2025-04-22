#ifndef ADVANCEDCOMPUTATION_H
#define ADVANCEDCOMPUTATION_H

#include <cmath>

#include <SFML/Graphics.hpp>

#include "utils/RectEdges.h"
#include "utils/Constants.h"

class AdvancedComputation
{
public:
    static void preventMoveThatExitBounds(
        creFloat playerBounds,
        creFloat obstacleBounds,
        cvFloat size,
        sf::Vector2f &position);

    static void preventMoveThatEnterBounds(
        creFloat playerBounds,
        creFloat obstacleBounds,
        cvFloat size,
        sf::Vector2f &position);

    static float vectorToRotation(cvFloat originPoint, cvFloat targetPoint);
    static sf::Vector2f rotationToVector(float angleDegrees);

    static sf::Vector2f calculateNormalizedVector(
        cvFloat currentPosition, cvFloat targetPosition);
};

#endif // ADVANCEDCOMPUTATION_H
