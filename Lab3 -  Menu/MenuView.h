#pragma once

#include <string>
#include <vector>

#include "MenuScene.h"

using std::string;
using std::vector;

class MenuView : public MenuObject
{
public:
    MenuView(string description, MenuObject* parent = nullptr);

    MenuScene*  getSceneByID(int id);
    void        addScene(MenuScene* newScene);
    void        swapScene(int targetSceneID);
    void        display() override;
    void        processLeftClick(prtd_ct::Point &clickPosition);

private:
    vector<MenuScene*>          _scenes;
    MenuScene*                  _activeScene = nullptr;
};