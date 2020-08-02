#pragma once

class MenuObject
{
public:
    MenuObject(MenuObject* parent = nullptr);

    void        setParent(MenuObject* parent);
    MenuObject* getParent();

protected:
    MenuObject* _parent;
};