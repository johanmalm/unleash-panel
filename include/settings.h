#pragma once

#include <QColor>

struct Globals
{
    /* Obtained from system */
    int screenWidth;
    int screenHeight;

    /* Based on config file */
    QString fontFamily;
    int fontSize;

    int panelWidth;
    int panelHeight;
    int panelPaddingX;
    int panelPaddingY;
    QColor panelColorBackground;
    QColor panelColorBorder;

    int taskWidth;
    int taskSpacing;
    int taskPaddingX;
    QColor taskColorBackground;
    QColor taskColorHoverBackground;
    QColor taskColorFont;
};

extern Globals g;

void initSettings(void);

// vim: set ts=4 sw=4 et:
