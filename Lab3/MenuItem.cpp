#include "MenuItem.h"

MenuItem::MenuItem(QGraphicsItem* parent)
{

}

MenuItem::MenuItem(int id, int width, int height, QString text, QGraphicsItem* parent)
{
    _itemID = id;
    _width = width;
    _height = height;
    _text = text;
}

void MenuItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(QBrush(QColor(Qt::black)));
    QRectF rect = boundingRect();
    painter->drawLine(QLineF(rect.bottomLeft(), rect.topLeft()));
    painter->drawLine(QLineF(rect.bottomLeft(), rect.bottomRight()));
    painter->drawLine(QLineF(rect.topLeft(), rect.topRight()));
    painter->drawLine(QLineF(rect.bottomRight(), rect.topRight()));
    painter->drawText(rect.center().x() - 2 * _text.size(), rect.center().y(), _text);
}

QRectF MenuItem::boundingRect() const
{
    return QRectF(QPoint(-_width / 2, -_height / 2), QPoint(_width / 2, _height / 2));
}

void MenuItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    emit mousePressSignal();
}

