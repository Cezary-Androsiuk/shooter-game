#include "RectEdges.h"

template<typename T>
RectEdges<T>::RectEdges()
    : left(0), top(0), right(0), bottom(0)
{

}

template<typename T>
RectEdges<T>::RectEdges(T left, T top, T right, T bottom)
    : left(left), top(top), right(right), bottom(bottom)
{

}

template<typename T>
RectEdges<T>::RectEdges(const sf::Rect<T> &bounds)
    : left(bounds.left)
    , top(bounds.top)
    , right(bounds.left + bounds.width)
    , bottom(bounds.top + bounds.height)
{

}

template class RectEdges<float>; /// GPT helps, something like public class instantion or something
