#pragma once

#include <string>
#include <vector>

#include "boost/signals2.hpp"
#include "MenuScene.h"

using namespace std;

class MenuView : public MenuObject
{
public:
    MenuView(int argc, char** argv, string description, MenuObject* parent = nullptr);
    ~MenuView();

    MenuScene*  getSceneByID(int id);
    void        addScene(MenuScene* newScene);
    void        swapScene(int targetSceneID);
    void        displayView();
    void        processLeftClick(Point clickPosition);

private:
    vector<MenuScene*>          _scenes;
    MenuScene*                  _activeScene = nullptr;
};