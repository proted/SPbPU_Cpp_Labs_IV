#pragma once

#include <vector>

#include "MenuItem.h"

class MenuScene : public MenuObject
{
public:
    MenuScene(int id, MenuObject* parent = nullptr);
    ~MenuScene();

    int         getID();
    bool        getState();
    void        toggleState();
    void        drawScene();
    void        addItem(MenuItem* newItem);
    MenuItem*   getItemByID(int id);
    MenuItem*   getItemByCoord(Point position);
    void        processLeftClick(Point clickPosition);

private:
    int                 _id;
    bool                _isActive;
    vector<MenuItem*>   _items;
};