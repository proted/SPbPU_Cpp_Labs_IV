#pragma once

#include <string>

#include "Rectangle.h"
#include "MenuObject.h"

using std::string;

class MenuItem : public MenuObject
{
    typedef void(*CallbackClick)(MenuItem*, prtd_ct::Point&);
    typedef void(*CallbackDraw)(MenuItem*);

public:
    MenuItem(int id, prtd_ct::Rectangle rect, string text, MenuObject* parent = nullptr);

    void                display() override;

    void                setSpecialDrawingFunc(CallbackDraw sdf);
    void                setSpecialClickingFunc(CallbackClick scf);

    prtd_ct::Rectangle  getRectangle();
    void                setRectangle(prtd_ct::Rectangle& newRectangle);

    string              getText() { return _text; }
    void                processLeftClick(prtd_ct::Point &clickPosition);


public:
    int                             _enemyMovingDirection = 0;
    unsigned int                    _enemyTimeSinceLastShot = 0;


private:
    string                          _text;
    prtd_ct::Rectangle              _rectangle;
    
    CallbackDraw                    _specialDrawingFunc = nullptr;
    CallbackClick                   _specialClickingFunc = nullptr;
};