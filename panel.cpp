#include "panel.h"
#include <QtWidgets>

Panel::Panel(QWidget *parent): QGraphicsView(parent)
{
	setScene(&scene);

	// scene has to be smaller than view (window) by one pixel horizontally and
	// two pixels vertically in order to fit.  This is taken care of in main.cpp.
	scene.setSceneRect(0, 0, g.panelWidth, g.panelHeight);
	scene.setItemIndexMethod(QGraphicsScene::NoIndex);

	setRenderHint(QPainter::Antialiasing);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setStyleSheet("background-color: transparent;");
	setAttribute(Qt::WA_TranslucentBackground);
	setAttribute(Qt::WA_X11NetWmWindowTypeDock, true);

	// setStyleSheet("border-style: none; border-width: 0 px;") achieve nothing
	// here. Borders are turned off by:
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint);

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
		DockItem *d = new DockItem(g.itemWidth, g.panelHeight - (2 * g.itemPadding),
					   clients.name.at(i).toLatin1());
		d->setPos(g.itemPadding + (g.itemWidth + g.itemPadding) * i, g.itemPadding);
		scene.addItem(d);
	}
}
