#include "MenuObject.h"

MenuObject::MenuObject(MenuObject* parent)
{
    _parent = parent;
}

void MenuObject::setParent(MenuObject* parent)
{
    _parent = parent;
}

MenuObject* MenuObject::getParent()
{
    return _parent;
}
