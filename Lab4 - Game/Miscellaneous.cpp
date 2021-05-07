#include "Miscellaneous.h"

int misc_isObjectsCollided(MenuItem* obj1, MenuItem* obj2)
{
    int xCollision = 0;
    int yCollision = 0;

    prtd_ct::Rectangle rect1 = obj1->getRectangle();
    prtd_ct::Rectangle rect2 = obj2->getRectangle();

    if ((rect1.point.x + rect1.width >= rect2.point.x) &&
        (rect1.point.x <= rect2.point.x + rect2.width))
    {
        xCollision = 1;
    }
    if ((rect1.point.y + rect1.height >= rect2.point.y) &&
        rect1.point.y <= rect2.point.y + rect2.height)
    {
        yCollision = 1;
    }

    return xCollision && yCollision;
}