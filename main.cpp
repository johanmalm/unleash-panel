/* main.cpp
 *
 * Copyright (C) Johan Malm 2014
 *
 * jgpanel is inspired by tint2 and written in qt5 from scratch
 */

#include <QApplication>
#include "globals.h"
#include "server.h"
#include "filter.h"
#include "panel.h"

int main(int argv, char **args)
{
	init_globals();

	QApplication app(argv, args);

	EventFilter filter;
	app.installNativeEventFilter(&filter);

	Server server;

	QObject::connect(&filter, &EventFilter::caughtEvent,
			 &server, &Server::clientListChanged);

	Panel panel;    // this creates the QGraphicsView (and also the window)

	panel.resize(g.panelWidth, g.panelHeight);
	panel.move(0, g.screenHeight - g.panelHeight - 40);
	panel.show();

	QObject::connect(&server, &Server::clientListUpdated,
			 &panel, &Panel::drawPanel);

	return app.exec();
}
