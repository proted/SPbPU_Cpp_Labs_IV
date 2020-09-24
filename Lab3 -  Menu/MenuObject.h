#pragma once

class MenuObject
{
public:
    MenuObject(int id, MenuObject* parent = nullptr) 
    {
        _id = id; 
        _parent = parent;
    }

    MenuObject*     getParent();
    int             getID();
    virtual void    display() {}

private:
    MenuObject*     _parent;
    int             _id;
};