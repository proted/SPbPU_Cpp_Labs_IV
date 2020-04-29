#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lab2.h"
#include "Arrow.h"

class Lab2 : public QMainWindow
{
    Q_OBJECT

public:
    Lab2(QWidget *parent = Q_NULLPTR);

protected:
    void keyPressEvent(QKeyEvent* e);
    void paintEvent(QPaintEvent* e);
    void timerEvent(QTimerEvent* e);

private:
    int timerID;
    Arrow arrow;
    Arrow trace[1000];
};
