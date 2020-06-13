#include <QtWidgets/QApplication>

#include <QGraphicsView>

#include "MenuView.h"
#include "MenuScene.h"
#include "MenuItem.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MenuView* MENU = new MenuView("menu");

    return a.exec();
}
