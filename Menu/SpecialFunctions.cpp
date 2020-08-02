#include "SpecialFunctions.h"

void sdf_button11(MenuItem* item)
{
    Rectangle pos = item->getPosition();
    double x = pos.getPosX();
    double y = pos.getPosY();
    double w = pos.getWidth();
    double h = pos.getHeight();

    glBegin(GL_TRIANGLES);
    glColor3d(1.0, 0.0, 0.5);

    glVertex2d(x, y);
    glVertex2d(x + w / 2, y + h);
    glVertex2d(x + w, y);

    glEnd();
}

void scf_button11(MenuItem* item, Point point)
{
    ((MenuView*)item->getParent()->getParent())->swapScene(2);
}

void scf_button21(MenuItem* item, Point point)
{
    ((MenuView*)item->getParent()->getParent())->swapScene(1);
}
