#include "MenuScene.h"

MenuScene::MenuScene(int id, MenuObject* parent)
{
    _id = id;
    _isActive = false;
    _parent = parent;
}

MenuScene::~MenuScene()
{
}

int MenuScene::getID()
{
    return _id;
}

bool MenuScene::getState()
{
    return _isActive;
}

void MenuScene::toggleState()
{
    _isActive = !_isActive;
}

void MenuScene::drawScene()
{
    for (auto& item : _items)
    {
        item->drawItem();
    }
}

void MenuScene::addItem(MenuItem* newItem)
{
    _items.push_back(newItem);
    newItem->setParent(this);
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

MenuItem* MenuScene::getItemByCoord(Point position)
{
    for (auto& item : _items)
    {
        Rectangle itemRect = item->getPosition();
        if (position.x >= itemRect.getPosX() &&
            position.x <= (itemRect.getPosX() + itemRect.getWidth()) &&
            position.y >= itemRect.getPosY() &&
            position.y <= (itemRect.getPosY() + itemRect.getHeight()))
        {
            return item;
        }
    }
    return nullptr;
}

void MenuScene::processLeftClick(Point clickPosition)
{
    MenuItem* targetItem = getItemByCoord(clickPosition);
    if (targetItem != nullptr)
    {
        targetItem->processLeftClick(clickPosition);
    }
}
