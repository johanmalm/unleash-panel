#include "splash.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <QPen>
#include "globals.h"

SplashItem::SplashItem()
{
}

SplashItem::~SplashItem()
{
}

QRectF SplashItem::boundingRect() const
{
	return QRectF(0.5, 0.5, g.panelWidth - 1.0, g.panelHeight - 1.0);
}

void SplashItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	// set pen properties to create panel border
//	painter->setPen(Qt::NoPen);
	QPen pen(QColor(255,0,0,255));
	pen.setStyle(Qt::SolidLine);
	pen.setWidth(1.0);
	pen.setBrush(QColor(255, 255, 255, 128));

	painter->setPen(pen);
	painter->setBrush(QColor(0, 0, 0, 80));
	painter->drawRect(boundingRect());
}

