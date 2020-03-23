#pragma once

#include <QColor>

struct Globals
{
    /* Based on system */
    int screenWidth;
    int screenHeight;

    /* Based on config file */
    int panelWidth;
    int panelHeight;
    int panelPaddingX;
    int panelPaddingY;

    int taskWidth;
    int taskSpacing;
    QColor taskColorFill;
};

extern Globals g;

void initSettings(void);

// vim: set ts=4 sw=4 et:
