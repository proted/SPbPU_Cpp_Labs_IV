#include "MenuView.h"

#include <QApplication>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

MenuView::MenuView(QString description, QWidget* parent)
    : QGraphicsView(parent)
{
    QFile file;
    file.setFileName(description);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString str = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
    if (doc.isObject())
    {
        QJsonObject json = doc.object();
        QJsonArray sceneArray = json["scene"].toArray();
        for (auto &sc : sceneArray)
        {
            if (sc.isObject())
            {
                QJsonObject jsonScene = sc.toObject();
                int sceneId = jsonScene["id"].toInt();
                int sceneW = jsonScene["width"].toInt();
                int sceneH = jsonScene["height"].toInt();
                MenuScene* scene = new MenuScene(sceneId);
                scene->setSceneRect(0, 0, sceneW, sceneH);
                _scenes.push_back(scene);

                QJsonArray itemArray = jsonScene["item"].toArray();
                for (auto& it : itemArray)
                {
                    if (it.isObject())
                    {
                        QJsonObject jsonItem = it.toObject();
                        int itemId = jsonItem["id"].toInt();
                        QString itemText = jsonItem["text"].toString();
                        int itemW = jsonItem["width"].toInt();
                        int itemH = jsonItem["height"].toInt();
                        int posX = jsonItem["posX"].toInt();
                        int posY = jsonItem["posY"].toInt();
                        MenuItem* item = new MenuItem(itemId, itemW, itemH, itemText);
                        item->setPos(QPointF(posX, posY));
                        scene->addItem(item);
                        scene->addItemToList(item);
                    }
                }
            }
        }
    }

    MenuItem* btn_nextScene = getSceneByID(1)->getItemByID(1);
    MenuItem* btn_exit      = getSceneByID(1)->getItemByID(2);
    MenuItem* btn_prevScene = getSceneByID(2)->getItemByID(3);

    connect(btn_nextScene, &MenuItem::mousePressSignal, this, &MenuView::swapSceneRequest);
    connect(btn_prevScene, &MenuItem::mousePressSignal, this, &MenuView::swapSceneRequest);
    connect(btn_exit, &MenuItem::mousePressSignal, this, &qApp->quit);

    this->setScene(_scenes[0]);
    _scenes[0]->toggleState();
    this->show();
}

void MenuView::swapSceneRequest()
{
    for (int i = 0; i < _scenes.size(); i++)
    {
        if (!_scenes[i]->getState())
        {
            this->setScene(_scenes[i]);            
        }
        _scenes[i]->toggleState();
    }
}

MenuScene* MenuView::getSceneByID(int id)
{
    for (auto &i : _scenes)
    {
        if (i->getID() == id)
        {
            return i;
        }
    }
    return nullptr;
}
