#include "Lab2.h"
#include <QKeyEvent>
#include <QPaintEvent>
#include <QTimerEvent>
#include <QPainter>
#include <QPen>
#include <math.h>

Lab2::Lab2(QWidget *parent)
    : QMainWindow(parent)
{
    timerID = startTimer(15);
    arrow = Arrow();
    for (int i = 0; i < 10; i++)
    {
        trace[i] = Arrow(arrow.getX(), arrow.getY(), arrow.getAngle());
    }
}

void Lab2::keyPressEvent(QKeyEvent* e)
{
    switch (e->key())
    {
        case Qt::Key_Up:
        for (int i = 99; i > 0; i--)
        {
            trace[i].~Arrow();
            trace[i] = Arrow(trace[i - 1].getX(), trace[i - 1].getY(), trace[i - 1].getAngle());
        }
        trace[0].~Arrow();
        trace[0] = Arrow(arrow.getX(), arrow.getY(), arrow.getAngle());
        arrow.move(10);
        break;
        case Qt::Key_Down:
        for (int i = 99; i > 0; i--)
        {
            trace[i].~Arrow();
            trace[i] = Arrow(trace[i - 1].getX(), trace[i - 1].getY(), trace[i - 1].getAngle());
        }
        trace[0].~Arrow();
        trace[0] = Arrow(arrow.getX(), arrow.getY(), arrow.getAngle());
        arrow.move(-10);
        break;
        case Qt::Key_Left:
        for (int i = 99; i > 0; i--)
        {
            trace[i].~Arrow();
            trace[i] = Arrow(trace[i - 1].getX(), trace[i - 1].getY(), trace[i - 1].getAngle());
        }
        trace[0].~Arrow();
        trace[0] = Arrow(arrow.getX(), arrow.getY(), arrow.getAngle());
        arrow.turn(- PI / 180);
        break;
        case Qt::Key_Right:
        for (int i = 99; i > 0; i--)
        {
            trace[i].~Arrow();
            trace[i] = Arrow(trace[i - 1].getX(), trace[i - 1].getY(), trace[i - 1].getAngle());
        }
        trace[0].~Arrow();
        trace[0] = Arrow(arrow.getX(), arrow.getY(), arrow.getAngle());
        arrow.turn(PI / 180);
        break;
        case Qt::Key_Escape:
        arrow.resetState();
        break;
    }
}

void Lab2::paintEvent(QPaintEvent* e)
{
    QPainter qp(this);
    qp.setPen(QPen(Qt::blue, 4));
    double x1 = arrow.getX();
    double y1 = arrow.getY();
    double x2 = arrow.getX() + arrow.getLength() * cos(arrow.getAngle());
    double y2 = arrow.getY() + arrow.getLength() * sin(arrow.getAngle());
    qp.drawLine(x1, y1, x2, y2);
    for (int i = 0; i < 100; i++)
    {
        qp.setOpacity(1.0 / ((double)i + 1.0));
        x1 = trace[i].getX();
        y1 = trace[i].getY();
        x2 = trace[i].getX() + trace[i].getLength() * cos(trace[i].getAngle());
        y2 = trace[i].getY() + trace[i].getLength() * sin(trace[i].getAngle());
        qp.drawLine(x1, y1, x2, y2);
    }
}

void Lab2::timerEvent(QTimerEvent* e)
{
    for (int i = 99; i > 0; i--)
    {
        trace[i].~Arrow();
        trace[i] = Arrow(trace[i - 1].getX(), trace[i - 1].getY(), trace[i - 1].getAngle());
    }
    trace[0].~Arrow();
    trace[0] = Arrow(arrow.getX(), arrow.getY(), arrow.getAngle());
    repaint();
}
