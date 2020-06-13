#pragma once

#include <string>

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QWidget>

using namespace std;

class MenuItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
        
public:
    MenuItem(QGraphicsItem* parent = nullptr);
    MenuItem(int id, int width, int height, QString text, QGraphicsItem* parent = nullptr);

    unsigned int getID() { return _itemID; }

signals:
    void mousePressSignal();

private:
    unsigned int    _itemID;
    QString         _text;
    int             _width;
    int             _height;

private:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QRectF boundingRect() const override;

    void mousePressEvent(QGraphicsSceneMouseEvent* event);


};