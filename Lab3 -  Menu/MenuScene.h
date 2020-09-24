#pragma once

#include <vector>

#include "MenuItem.h"

using std::vector;

class MenuScene : public MenuObject
{
public:
    MenuScene(int id, MenuObject* parent = nullptr);

    bool        getState();
    void        toggleState();
    void        display() override;
    void        addItem(MenuItem* newItem);
    MenuItem*   getItemByID(int id);
    MenuItem*   getItemByCoord(prtd_ct::Point &position);
    void        processLeftClick(prtd_ct::Point &clickPosition);

private:
    bool                _isActive;
    vector<MenuItem*>   _items;
};