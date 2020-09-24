#include "MenuItem.h"

#include "glut.h"

MenuItem::MenuItem(int id, prtd_ct::Rectangle rect, string text, MenuObject* parent)
    : MenuObject(id, parent)
{
    _text = text;
    _rectangle = rect;
}

void MenuItem::display()
{
    if (_specialDrawingFunc != nullptr)
    {
        _specialDrawingFunc(this);
        return;
    }
    MenuItem* item = this;
    prtd_ct::Rectangle  rect = item->getRectangle();
    double x = rect.point.x;
    double y = rect.point.y;
    double w = rect.width;
    double h = rect.height;

    glBegin(GL_LINES);
    glColor3d(0.0, 1.0, 0.5);
    glVertex2d(x, y);
    glVertex2d(x + w, y);
    glVertex2d(x + w, y);
    glVertex2d(x + w, y + h);
    glVertex2d(x + w, y + h);
    glVertex2d(x, y + h);
    glVertex2d(x, y + h);
    glVertex2d(x, y);
    glEnd();

    glRasterPos2d(x + w / 2.0 - 8.0 * item->getText().length() / 2.0,
                  y + h / 2.0);
    for (auto& ch : item->getText())
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, ch);
    }
}

void MenuItem::setPosition(prtd_ct::Point &newPosition)
{
    _rectangle.setPosition(newPosition);
}

void MenuItem::setSpecialDrawingFunc(CallbackDraw sdf)
{
    _specialDrawingFunc = sdf;
}

void MenuItem::setSpecialClickingFunc(CallbackClick scf)
{
    _specialClickingFunc = scf;
}

prtd_ct::Rectangle MenuItem::getRectangle()
{
    return _rectangle;
}

void MenuItem::processLeftClick(prtd_ct::Point &clickPosition)
{
    if (_specialClickingFunc != nullptr)
    {
        _specialClickingFunc(this, clickPosition);
        return;
    }
    exit(0);
}
