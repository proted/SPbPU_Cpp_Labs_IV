#pragma once

#include <string>
#include <vector>

#include <QGraphicsView>
#include <QWidget>
#include <QList>

#include "MenuScene.h"
#include "MenuItem.h"

using namespace std;

class MenuView : public QGraphicsView
{
    Q_OBJECT
public:
    MenuView(QString description, QWidget* parent = nullptr);
    
signals:

private slots:
    void swapSceneRequest();

private:
    vector<MenuScene*>      _scenes;
    vector<MenuItem*>       _items;

public:
    MenuScene* getSceneByID(int id);

private:

};