#include "splash.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

SplashItem::SplashItem()
{
}

SplashItem::~SplashItem()
{
}

QRectF SplashItem::boundingRect() const
{
	return QRectF(0, 0, 1022, 28);
}

void SplashItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	painter->setPen(Qt::NoPen);
	painter->setBrush(QColor(255, 255, 255, 200));
	painter->drawRect(boundingRect());
}

