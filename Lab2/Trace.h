#pragma once

#include "Arrow.h"

class Trace
{
public:
    Trace(Arrow& arr = Arrow(), int size = 100);

public:
    void updateTrace(Arrow& arr = Arrow());
    Arrow& getArrow(int index);

private:
    int _size;
    Arrow* _trace;
};