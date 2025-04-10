#ifndef RECTANGLEEDGES_H
#define RECTANGLEEDGES_H

#include <SFML/Graphics/Rect.hpp>

/// INSPIRED BY sf::Rect<T>

template <typename T>
class RectangleEdges
{
public:
    RectangleEdges();
    RectangleEdges(T left, T top, T rigtht, T bottom);
    RectangleEdges(const sf::Rect<T> &bounds);

    T left;   //!< Left coordinate of the rectangle
    T top;    //!< Top coordinate of the rectangle
    T right;  //!< Right coordinate of the rectangle
    T bottom; //!< Bottom coordinate of the rectangle
};

typedef RectangleEdges<float> FloatRectEdges;
typedef RectangleEdges<int> IntRectEdges;
typedef RectangleEdges<unsigned int> UIntRectEdges;

#endif // RECTANGLEEDGES_H
