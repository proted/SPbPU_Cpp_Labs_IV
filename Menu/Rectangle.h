#pragma once

typedef struct Point
{
    double x, y;
} Point;

class Rectangle
{
public:
    Rectangle();
    Rectangle(double width, double height, Point position);
    ~Rectangle();

    void    setPosition(Point newPosition);
    double  getPosX() { return _position.x; }
    double  getPosY() { return _position.y; }
    double  getWidth() { return _width; }
    double  getHeight() { return _height; }

private:
    Point       _position;
    double      _width;
    double      _height;
};