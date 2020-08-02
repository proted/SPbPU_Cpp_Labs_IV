#include "MenuItem.h"

#include "glut.h"

MenuItem::MenuItem(int id, int rectW, int rectH, Point position, string text, MenuObject* parent)
    : _rectangle(rectW, rectH, position)
{
    _id = id;
    _text = text;
    _specialDrawingFunc = nullptr;
    _parent = parent;
}

MenuItem::~MenuItem()
{
}

void MenuItem::drawItem()
{
    if (_specialDrawingFunc != nullptr)
    {
        _specialDrawingFunc(this);
        return;
    }
    MenuItem* item = this;
    Rectangle pos = item->getPosition();
    double x = pos.getPosX();
    double y = pos.getPosY();
    double w = pos.getWidth();
    double h = pos.getHeight();

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

    glRasterPos2d(pos.getPosX() + pos.getWidth() / 2.0 - 8.0 * item->getText().length() / 2.0,
        pos.getPosY() + pos.getHeight() / 2.0);
    for (auto& ch : item->getText())
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, ch);
    }
}

void MenuItem::setPosition(Point newPosition)
{
    _rectangle.setPosition(newPosition);
}

void MenuItem::setSpecialDrawingFunc(function<void(MenuItem*)> sdf)
{
    _specialDrawingFunc = sdf;
}

void MenuItem::setSpecialClickingFunc(CallbackClick scf)
{
    _specialClickingFunc = scf;
}

Rectangle MenuItem::getPosition()
{
    return _rectangle;
}

void MenuItem::processLeftClick(Point clickPosition)
{
    if (_specialClickingFunc != nullptr)
    {
        _specialClickingFunc(this, clickPosition);
        return;
    }
    exit(0);
}
