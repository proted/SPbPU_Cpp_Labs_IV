#pragma once

namespace prtd_ct
{
    typedef struct Point
    {
        double x, y;
    } Point;

    typedef struct Rectangle
    {
        Point point;
        double width, height;

        void setPosition(Point& newPosition)
        {
            point.x = newPosition.x;
            point.y = newPosition.y;
        }
    } Rectangle;
}