#include "RectangleEdges.h"

template <typename T>
RectangleEdges<T>::RectangleEdges()
    : left(0), top(0), right(0), bottom(0)
{
}

template <typename T>
RectangleEdges<T>::RectangleEdges(T left, T top, T right, T bottom)
    : left(left), top(top), right(right), bottom(bottom)
{
}

template<typename T>
RectangleEdges<T>::RectangleEdges(const sf::Rect<T> &bounds)
    : left(bounds.left)
    , top(bounds.top)
    , right(bounds.left + bounds.width)
    , bottom(bounds.top + bounds.height)
{

}
