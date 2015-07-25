#ifndef SPLASH_H
#define SPLASH_H

#include <QGraphicsItem>

class SplashItem : public QObject, public QGraphicsItem
{
	Q_OBJECT
	Q_INTERFACES(QGraphicsItem)
public:
	SplashItem();
	~SplashItem();
	QRectF boundingRect() const Q_DECL_OVERRIDE;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
		   QWidget *widget) Q_DECL_OVERRIDE;

private:
	QColor color;
};

#endif // SPLASH_H
