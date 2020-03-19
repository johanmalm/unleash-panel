#include "globals.h"
#include <QDebug>

Globals g;

void init_globals()
{
    g.panelWidth = 1024;
    g.panelHeight = 30;
    g.screenHeight = 600;
    g.itemPadding = 3;
    g.itemWidth = 80;
}

// vim: set ts=4 sw=4 et:
