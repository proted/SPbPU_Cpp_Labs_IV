#include "Rectangle.h"

Rectangle::Rectangle()
{
    _position.x = _position.y = _width = _height = 0;
}

Rectangle::Rectangle(double width, double height, Point position)
{
    _width = width;
    _height = height;
    _position.x = position.x;
    _position.y = position.y;
}

Rectangle::~Rectangle()
{
}

void Rectangle::setPosition(Point newPosition)
{
    _position = newPosition;
}