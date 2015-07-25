#include "panel.h"
#include <QtWidgets>

Panel::Panel(QWidget *parent): QGraphicsView(parent)
{
	setScene(&scene);

// scene has to be smaller than view (window) by two pixels in order to fit
	scene.setSceneRect(0, 0, g.panelWidth-2, g.panelHeight-2);
	scene.setItemIndexMethod(QGraphicsScene::NoIndex);

	setRenderHint(QPainter::Antialiasing);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setStyleSheet("border-style: none;");
	setStyleSheet("background-color: transparent");
	setAttribute(Qt::WA_TranslucentBackground);
	setAttribute(Qt::WA_X11NetWmWindowTypeDock, true);
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

	drawPanel();
}


Panel::~Panel()
{
}

void Panel::drawPanel()
{

// DRAW PANEL AND PANEL ITEMS
	scene.clear();

	SplashItem *p = new SplashItem;
	p->setPos(0, 0);
	scene.addItem(p);

	for (int i=0; i < clients.value.size(); i++) {
        	DockItem *d = new DockItem(g.itemWidth,
					   g.panelHeight - (2 * g.itemPadding) - 2,
					   clients.name.at(i).toLatin1());

        	d->setPos(g.itemPadding + (g.itemWidth + g.itemPadding) * i,
			  g.itemPadding);

        	scene.addItem(d);
	}
}
