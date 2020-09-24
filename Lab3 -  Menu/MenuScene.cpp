#include "MenuScene.h"

MenuScene::MenuScene(int id, MenuObject* parent) : 
    MenuObject(id, parent)
{
    _isActive = false;
}

bool MenuScene::getState()
{
    return _isActive;
}

void MenuScene::toggleState()
{
    _isActive = !_isActive;
}

void MenuScene::display()
{
    for (auto& item : _items)
    {
        item->display();
    }
}

void MenuScene::addItem(MenuItem* newItem)
{
    _items.push_back(newItem);
}

MenuItem* MenuScene::getItemByID(int id)
{
    for (auto& item : _items)
    {
        if (item->getID() == id)
        {
            return item;
        }
    }
    return nullptr;
}

MenuItem* MenuScene::getItemByCoord(prtd_ct::Point &position)
{
    for (auto& item : _items)
    {
        prtd_ct::Rectangle itemRect = item->getRectangle();
        if (position.x >= itemRect.point.x &&
            position.x <= (itemRect.point.x + itemRect.width) &&
            position.y >= itemRect.point.y &&
            position.y <= (itemRect.point.y + itemRect.height))
        {
            return item;
        }
    }
    return nullptr;
}

void MenuScene::processLeftClick(prtd_ct::Point &clickPosition)
{
    MenuItem* targetItem = getItemByCoord(clickPosition);
    if (targetItem != nullptr)
    {
        targetItem->processLeftClick(clickPosition);
    }
}
