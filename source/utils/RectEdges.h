#ifndef RECTEDGES_H
#define RECTEDGES_H

#include <SFML/Graphics/Rect.hpp>

/// INSPIRED BY sf::Rect<T>

template <typename T>
class RectEdges
{
public:
    RectEdges();
    RectEdges(T left, T top, T right, T bottom);
    RectEdges(const sf::Rect<T> &bounds);

    T left;   //!< Left coordinate of the rectangle
    T top;    //!< Top coordinate of the rectangle
    T right;  //!< Right coordinate of the rectangle
    T bottom; //!< Bottom coordinate of the rectangle
};

typedef RectEdges<float> FloatRectEdges;
typedef const FloatRectEdges &creFloat;

#endif // RECTEDGES_H
