#include "MenuScene.h"

MenuScene::MenuScene(int id, MenuObject* parent) : 
    MenuObject(id, parent)
{
    _isActive = false;
    if (id == 2)
    {
        MenuItem* dummyEnemy = new MenuItem(-100, prtd_ct::Rectangle{ prtd_ct::Point{-100, -100}, 1, 1 }, "", this);
        this->addItem(dummyEnemy);
        this->_enemies.push_back(dummyEnemy);

        MenuItem* dummyEnemyProjectile = new MenuItem(-1000000, prtd_ct::Rectangle{ prtd_ct::Point{-100, -100}, 1, 1 }, "", this);
        this->addItem(dummyEnemyProjectile);
        this->_enemiesProjectiles.push_back(dummyEnemyProjectile);

        MenuItem* dummyDefenderProjectile = new MenuItem(100000, prtd_ct::Rectangle{ prtd_ct::Point{-100, -100}, 1, 1 }, "", this);
        this->addItem(dummyDefenderProjectile);
        this->_alliesProjectiles.push_back(dummyDefenderProjectile);
    }
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

void MenuScene::setSpecialKeyboardFunc(CallbackKeyboard skf)
{
    _specialKeyboardFunc = skf;
}

void MenuScene::setSpecialIdleFunc(CallbackIdle sif)
{
    _specialIdleFunc = sif;
}

void MenuScene::setSpecialSpecialFunc(CallbackSpecial ssf)
{
    _specialSpecialFunc = ssf;
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

void MenuScene::removeItemByID(int id)
{
    for (auto iter = _items.begin(); iter != _items.end(); ++iter)
    {
        if ((*iter)->getID() == id)
        {
            _items.erase(iter);
            return;
        }
    }
}

void MenuScene::processLeftClick(prtd_ct::Point &clickPosition)
{
    MenuItem* targetItem = getItemByCoord(clickPosition);
    if (targetItem != nullptr)
    {
        targetItem->processLeftClick(clickPosition);
    }
}

void MenuScene::processKeyboard(unsigned char key)
{
    if (_specialKeyboardFunc != nullptr)
    {
        _specialKeyboardFunc(this, key);
    }
}

void MenuScene::processIdle()
{
    if (_specialIdleFunc != nullptr)
    {
        _specialIdleFunc(this);
    }
}

void MenuScene::processSpecial(int key)
{
    if (_specialSpecialFunc != nullptr)
    {
        _specialSpecialFunc(this, key);
    }
}
