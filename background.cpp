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
    /*
     * Panel border (Pen) and fill (Brush)
     * TODO: use painter->setPen(Qt::NoPen) for no border
     */
    QPen pen(QColor(255, 0, 0, 255));
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(1.0);
    pen.setBrush(QColor(255, 255, 255, 128));

    painter->setPen(pen);
    painter->setBrush(QColor(0, 0, 0, 80));
    painter->drawRect(boundingRect());
}

// vim: set ts=4 sw=4 et:
