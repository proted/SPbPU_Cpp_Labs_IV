#pragma once

#include <string>
#include <functional>

#include "boost/signals2.hpp"
#include "Rectangle.h"
#include "MenuObject.h"

using namespace std;
using namespace boost::signals2;

class MenuItem : public MenuObject
{
    typedef void(*CallbackClick)(MenuItem*, Point);

public:
    MenuItem(int id, int rectW, int rectH, Point position, string text, MenuObject* parent = nullptr);
    ~MenuItem();

    void                drawItem();
    void                setPosition(Point newPosition);
    void                setSpecialDrawingFunc(std::function<void(MenuItem*)> sdf);
    void                setSpecialClickingFunc(CallbackClick scf);
    class Rectangle     getPosition();
    string              getText() { return _text; }
    int                 getID() { return _id; }
    void                processLeftClick(Point clickPosition);

public:
    signal<void(int)>               signal_SwapScene;

private:
    int                             _id;
    string                          _text;
    class Rectangle                 _rectangle;
    
    function<void(MenuItem*)>       _specialDrawingFunc = nullptr;
    CallbackClick                   _specialClickingFunc = nullptr;
};