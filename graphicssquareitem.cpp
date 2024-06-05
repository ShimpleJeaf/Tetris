#include "graphicssquareitem.h"
#include "headfile.h"

GraphicsSquareItem::GraphicsSquareItem(unsigned size, QGraphicsItem* parent) :
    QGraphicsRectItem(0, 0, size, size, parent)
{}

GraphicsSquareItem::~GraphicsSquareItem()
{

}

void GraphicsSquareItem::setColor(QColor color)
{
    m_color = color;
}

void GraphicsSquareItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    painter->setPen(m_color);
    QGraphicsRectItem::paint(painter, option, widget);
}
