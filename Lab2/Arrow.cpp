#include "Arrow.h"

Arrow::Arrow(double x_init, double y_init, double angle_init, double len)
{
    x_pos = x_init;
    y_pos = y_init;
    angle = angle_init;
    length = len;
}
Arrow::~Arrow()
{

}
Arrow::Arrow(const Arrow& arr)
{
    x_pos = arr.x_pos;
    y_pos = arr.y_pos;
    angle = arr.angle;
    length = arr.length;
}

void Arrow::move(double dR)
{
    x_pos += dR * cos(angle);
    y_pos += dR * sin(angle);
}
void Arrow::turn(double dPhi)
{
    angle += dPhi;
}
void Arrow::resetState()
{
    x_pos = 0;
    y_pos = 0;
    angle = 0;
}
double Arrow::getX()
{
    return x_pos;
}
double Arrow::getY()
{
    return y_pos;
}
double Arrow::getAngle()
{
    return angle;
}
double Arrow::getLength()
{
    return length;
}