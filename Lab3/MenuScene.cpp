#include "MenuScene.h"

MenuScene::MenuScene(int id, QObject* parent) 
    : QGraphicsScene(parent)
{
    _id = id;
}

void MenuScene::addItemToList(MenuItem* item)
{
    _menu_items.push_back(item);
}

MenuItem* MenuScene::getItemByID(int id)
{
    for (auto i : _menu_items)
    {
        if (i->getID() == id)
        {
            return i;
        }
    }
    return nullptr;
}
