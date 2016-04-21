#include "dock.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <QFont>

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
	return QRectF(0, 0, m_width - 2, m_height - 2);
}

void DockItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	painter->setRenderHint(QPainter::Antialiasing, true);
	painter->setPen(Qt::NoPen);
	painter->setBrush(QColor(255, 194, 34, 200)); //#ffbb22
	painter->drawRect(0, 0, m_width, m_height);

	int padding = 3;
	QFont font("Ubuntu Condensed", 10);
	painter->setFont(font);
	painter->setPen(QColor(255, 255, 255, 255));

	// The -2 for the height is because otherwise the font sits to low
	// Interestingly cairo needs the same adjustment.
	QRect rect(padding, 0, m_width - padding * 2, m_height -2);
	painter->drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, m_clientName);
}
