#include "SpecialFunctions.h"

void sdf_button11(MenuItem* item)
{
    prtd_ct::Rectangle pos = item->getRectangle();
    double x = pos.point.x;
    double y = pos.point.y;
    double w = pos.width;
    double h = pos.height;

    glBegin(GL_TRIANGLES);
    glColor3d(1.0, 0.0, 0.5);

    glVertex2d(x, y);
    glVertex2d(x + w / 2, y + h);
    glVertex2d(x + w, y);

    glEnd();
}

void scf_button11(MenuItem* item, prtd_ct::Point &point)
{
    ((MenuView*)item->getParent()->getParent())->swapScene(2);
}

void scf_button21(MenuItem* item, prtd_ct::Point &point)
{
    ((MenuView*)item->getParent()->getParent())->swapScene(1);
}
