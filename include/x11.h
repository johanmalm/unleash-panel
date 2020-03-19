#pragma once

#include <QString>

unsigned long x11AtomNetClientList(void);
QString x11WinName(unsigned long window);
QVector<unsigned long> x11ClientList(void);
bool x11IsHidden(unsigned long window);

// vim: set ts=4 sw=4 et:
