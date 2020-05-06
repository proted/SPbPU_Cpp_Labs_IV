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
    timerID = startTimer(5);
    arrow = Arrow();
    trace = Trace(arrow);
}

void Lab2::keyPressEvent(QKeyEvent* e)
{
    switch (e->key())
    {
        case Qt::Key_Up:
        trace.updateTrace(arrow);
        arrow.move(15);
        break;
        case Qt::Key_Down:
        trace.updateTrace(arrow);
        arrow.move(-15);
        break;
        case Qt::Key_Left:
        trace.updateTrace(arrow);
        arrow.turn(- PI / 90);
        break;
        case Qt::Key_Right:
        trace.updateTrace(arrow);
        arrow.turn(PI / 90);
        break;
        case Qt::Key_Escape:
        trace.updateTrace(arrow);
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
        x1 = trace.getArrow(i).getX();
        y1 = trace.getArrow(i).getY();
        x2 = trace.getArrow(i).getX() + trace.getArrow(i).getLength() * cos(trace.getArrow(i).getAngle());
        y2 = trace.getArrow(i).getY() + trace.getArrow(i).getLength() * sin(trace.getArrow(i).getAngle());
        qp.drawLine(x1, y1, x2, y2);
    }
}

void Lab2::timerEvent(QTimerEvent* e)
{
    trace.updateTrace(arrow);
    repaint();
}
