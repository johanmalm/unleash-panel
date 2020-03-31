/*
 * main.cpp
 *
 * Copyright (C) Johan Malm 2014
 */

#include <QApplication>
#include <QDebug>
#include <QScreen>

#include "x11-event-filter.h"
#include "settings.h"
#include "panel.h"
#include "settings.h"

int main(int argv, char **args)
{
    QApplication app(argv, args);
    QCoreApplication::setOrganizationName("unleash-panel");
    QCoreApplication::setApplicationName("unleash");
    initSettings();

    /*
     * GTK+ style creates a border around the window. I cannot find the
     * stylesheet property associated with this, so force Fusion style to
     * avoid the issue.
     */
    app.setStyle("Fusion");

    EventFilter filter;
    app.installNativeEventFilter(&filter);

    /* Create QGraphicsView - which is also the main window */
    Panel panel;
    panel.show();

    QObject::connect(&filter, &EventFilter::caughtEvent, &panel, &Panel::reactToX11Event);

    return app.exec();
}

// vim: set ts=4 sw=4 et:
