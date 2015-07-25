#ifndef DOCK_H
#define DOCK_H

#include <QGraphicsItem>

class DockItem : public QObject, public QGraphicsItem
{
	Q_OBJECT
	Q_INTERFACES(QGraphicsItem)

public:
	DockItem(int w, int h, QString clientName);
	~DockItem();
	QRectF boundingRect() const Q_DECL_OVERRIDE;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

private:
	QString m_clientName;
	int m_width;
	int m_height;
};

#endif // DOCK_H
