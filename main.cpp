/* main.cpp
 *
 * Copyright (C) Johan Malm 2014
 *
 * jgpanel is inspired by tint2 and written in qt5 from scratch
 */

#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>

#include "globals.h"
#include "server.h"
#include "filter.h"
#include "panel.h"


int main(int argv, char **args)
{
	init_globals();

	QApplication app(argv, args);

//	QDesktopWidget *desktop = app.desktop();
//	qDebug() << "Width: " << desktop->screenGeometry(-1).width();
//	qDebug() << "Height: " << desktop->screenGeometry(-1).height();

	// GTK+ style creates a border around the window.
	// Cannot find the stylesheet property associated with this,
	// so force Fusion style to avoid the issue.
	app.setStyle("Fusion");

	EventFilter filter;
	app.installNativeEventFilter(&filter);

	Server server;

	QObject::connect(&filter, &EventFilter::caughtEvent,
			 &server, &Server::clientListChanged);

	// This creates the QGraphicsView (and also the window)
	Panel panel;

	// These are required to position the QGraphicsScene correctly.
	// This is due to a hardcoded scene margin built into the qt5 libs.
	// It is overcome here by position the window marginally outside the screen.
	int horizontalMargin = 1;
	int verticalMargin = 2;
	panel.resize(g.panelWidth + horizontalMargin * 2, g.panelHeight + verticalMargin * 2);
	panel.move(-horizontalMargin, g.screenHeight - g.panelHeight - verticalMargin);
	panel.show();

	QObject::connect(&server, &Server::clientListUpdated,
			 &panel, &Panel::drawPanel);

	return app.exec();
}
