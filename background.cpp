#include "background.h"

#include "settings.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QPen>
#include <QStyleOption>

BackgroundItem::BackgroundItem() {}

BackgroundItem::~BackgroundItem() {}

QRectF BackgroundItem::boundingRect() const
{
    return QRectF(0.5, 0.5, g.panelWidth - 1.0, g.panelHeight - 1.0);
}

void BackgroundItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                           QWidget *)
{
    /* Panel background */
    painter->setBrush(g.panelColorBackground);
    painter->setPen(g.panelColorBackground);
    painter->drawRect(boundingRect());

    /* Panel border */
    QPen pen(g.panelColorBorder);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(1.0);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(boundingRect());
}

// vim: set ts=4 sw=4 et:
