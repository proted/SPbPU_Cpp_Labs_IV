#include "MenuView.h"

#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"

#include "glut.h"
#include "SpecialFunctions.h"

using namespace boost;
using namespace boost::property_tree;

MenuView::MenuView(string description, MenuObject* parent) :
    MenuObject(0, parent)
{

    std::ifstream menuSctructure_json(description);
    ptree pt;
    json_parser::read_json(menuSctructure_json, pt);
    for (auto& sceneArrayItem : pt.get_child("scene"))
    {
        int         sc_id   = sceneArrayItem.second.get<int>("id");
        int         sc_w    = sceneArrayItem.second.get<int>("width");
        int         sc_h    = sceneArrayItem.second.get<int>("height");
        MenuScene*  scene   = new MenuScene(sc_id, this);
        for (auto& itemArrayItem : sceneArrayItem.second.get_child("item"))
        {
            int                  it_id   = itemArrayItem.second.get<int>("id");
            string               it_text = itemArrayItem.second.get<string>("text");
            int                  it_w    = itemArrayItem.second.get<int>("width");
            int                  it_h    = itemArrayItem.second.get<int>("height");
            double               it_posX = (double)itemArrayItem.second.get<int>("posX");
            double               it_posY = (double)itemArrayItem.second.get<int>("posY");
            prtd_ct::Rectangle   it_rect = prtd_ct::Rectangle{ prtd_ct::Point{it_posX, it_posY}, (double)it_w, (double)it_h };
            MenuItem*   item    = new MenuItem(it_id, it_rect, it_text, scene);
            scene->addItem(item);
        }
        addScene(scene);
    }

    getSceneByID(1)->getItemByID(11)->setSpecialDrawingFunc(sdf_button11);

    getSceneByID(1)->getItemByID(11)->setSpecialClickingFunc(scf_button11);
    getSceneByID(2)->getItemByID(21)->setSpecialClickingFunc(scf_button21);

    _activeScene = getSceneByID(1);
}

MenuScene* MenuView::getSceneByID(int id)
{
    for (auto& scene : _scenes)
    {
        if (scene->getID() == id)
        {
            return scene;
        }
    }
    return nullptr;
}

void MenuView::addScene(MenuScene* newScene)
{
    _scenes.push_back(newScene);
}

void MenuView::swapScene(int targetSceneID)
{
    for (auto& scene : _scenes)
    {
        if (scene->getID() == targetSceneID)
        {
            _activeScene->toggleState();
            scene->toggleState();
            _activeScene = scene;
        }
    }
}

void MenuView::display()
{
    if (_activeScene == nullptr)
    {
        return;
    }
    _activeScene->display();
}

void MenuView::processLeftClick(prtd_ct::Point &clickPosition)
{
    if (_activeScene == nullptr)
    {
        return;
    }
    _activeScene->processLeftClick(clickPosition);
}

