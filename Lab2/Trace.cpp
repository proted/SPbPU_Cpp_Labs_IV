#include "Trace.h"

Trace::Trace(Arrow& arr, int size)
{
    _size = size;
    _trace = new Arrow[_size];
    for (int i = 0; i < _size; i++)
    {
        _trace[i] = Arrow(arr);
    }
}

void Trace::updateTrace(Arrow& arr)
{
    for (int i = _size - 1; i > 0; i--)
    {
        _trace[i] = Arrow(_trace[i - 1]);
    }
    _trace[0] = Arrow(arr);
}
Arrow& Trace::getArrow(int index)
{
    return _trace[index];
}