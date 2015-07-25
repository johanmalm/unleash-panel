#ifndef PANEL_H
#define PANEL_H

#include <QGraphicsView>
#include "globals.h"
#include "splash.h"
#include "dock.h"

class Panel: public QGraphicsView
{
	Q_OBJECT

public:
	Panel(QWidget *parent = 0);
	~Panel();

public slots:
	void drawPanel();

private:
	QGraphicsScene scene;
};

#endif // PANEL_H
