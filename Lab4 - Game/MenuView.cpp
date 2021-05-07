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
            MenuItem*            item    = new MenuItem(it_id, it_rect, it_text, scene);
            scene->addItem(item);
        }
        addScene(scene);
    }
    for (auto& params : pt.get_child("params"))
    {
        getSceneByID(2)->_projectileVelocity            = params.second.get<double>("projectileVelocity"); 
        getSceneByID(2)->_defenderVelocity              = params.second.get<double>("defenderVelocity");
        getSceneByID(2)->_defenderFireCooldown          = params.second.get<unsigned int>("defenderFireCooldown");
        getSceneByID(2)->_enemyRespawnCooldown          = params.second.get<unsigned int>("enemyRespawnCooldown");
        getSceneByID(2)->_enemiesVelocity               = params.second.get<double>("enemiesVelocity");
        getSceneByID(2)->_enemyFireChance               = params.second.get<int>("enemyFireChance_oneBy");
        getSceneByID(2)->_enemyFireCooldown             = params.second.get<unsigned int>("enemyFireCooldown");
        getSceneByID(2)->_enemyProjectileVelocity       = params.second.get<double>("enemyProjectileVelocity");
        getSceneByID(2)->_enemyChangeDirectionChance    = params.second.get<int>("enemyChangeDirectionChance_oneBy");
    }

    getSceneByID(1)->getItemByID(11)->setSpecialClickingFunc(scf_button11);
    getSceneByID(2)->getItemByID(21)->setSpecialClickingFunc(scf_button21);

    getSceneByID(2)->getItemByID(-2)->setSpecialDrawingFunc(sdf_stats);

    getSceneByID(2)->setSpecialKeyboardFunc(skf_scene2);

    getSceneByID(2)->setSpecialIdleFunc(sif_scene2);

    getSceneByID(2)->setSpecialSpecialFunc(ssf_scene2);

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

void MenuView::processKeyboard(unsigned char key)
{
    _activeScene->processKeyboard(key);
}

void MenuView::processIdle()
{
    _activeScene->processIdle();
}

void MenuView::processSpecial(int key)
{
    _activeScene->processSpecial(key);
}

