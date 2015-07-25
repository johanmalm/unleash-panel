#include "dock.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>


DockItem::DockItem(int w, int h, QString clientName)
{
	m_width = w;
	m_height = h;
	m_clientName = clientName;
}

DockItem::~DockItem()
{
}

QRectF DockItem::boundingRect() const
{
	return QRectF(0, 0, m_width-2, m_height-2);
}

void DockItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	painter->setRenderHint(QPainter::Antialiasing, true);
	painter->setPen(Qt::NoPen);
	painter->setBrush(QColor(0, 0, 255, 200));
	painter->drawRect(0, 0, m_width, m_height);
	painter->setPen(QColor(255,255,255,255));
	QRect rect(0, 0, m_width-2, m_height-2);
	painter->drawText(rect, Qt::AlignCenter, m_clientName);
}
