#pragma once
#include <math.h>

#define PI 3.1415926535897932384626433832795

class Arrow
{
public:
    Arrow(double x_init = 0, double y_init = 0, double angle_init = PI / 4, double len = 150.0);
    ~Arrow();
    Arrow(const Arrow& arr);

public:
    void move(double dR);
    void turn(double dPhi);
    void resetState();
    double getX();
    double getY();
    double getAngle();
    double getLength();

private:
    double x_pos;
    double y_pos;
    double angle;
    double length;
};