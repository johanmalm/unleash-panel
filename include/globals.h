#pragma once

#include <QtCore>

struct Globals
{
    int panelWidth;
    int panelHeight;
    int screenHeight;
    int itemPadding;
    int itemWidth;
};

extern Globals g;
void init_globals();

// vim: set ts=4 sw=4 et:
