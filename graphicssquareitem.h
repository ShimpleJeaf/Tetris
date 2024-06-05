#ifndef GRAPHICSSQUAREITEM_H
#define GRAPHICSSQUAREITEM_H

#include <QGraphicsRectItem>

class GraphicsSquareItem : public QGraphicsRectItem
{
    QColor m_color;
public:
    GraphicsSquareItem(unsigned size, QGraphicsItem* parent = nullptr);
    virtual ~GraphicsSquareItem();

    void setColor(QColor color);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

#endif // GRAPHICSSQUAREITEM_H
