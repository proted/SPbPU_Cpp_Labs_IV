#pragma once

#include <vector>

#include <QGraphicsScene>
#include <QGraphicsItem>

#include "MenuItem.h"

using namespace std;

class MenuScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit MenuScene(int id, QObject* parent = nullptr);

private:
    int                 _id;
    bool                _isActive = false;
    vector<MenuItem*>    _menu_items;

public:
    bool        getState() { return _isActive; }
    void        toggleState() { _isActive = !_isActive; }
    void        addItemToList(MenuItem* item);
    MenuItem*   getItemByID(int id);
    int         getID() { return _id; }

protected:
    //void mousePressEvent(QGraphicsSceneMouseEvent* e) override;
    //void keyPressEvent(QKeyEvent* e) override;

};