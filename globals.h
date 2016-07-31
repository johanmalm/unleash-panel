#ifndef GLOBAL_H
#define GLOBAL_H

#include <QtCore>
#include "client.h"

struct Client_t {
	QVector<unsigned long> value;
	QVector<QString> name;
};

extern Client_t clients;

// Only serveri.cpp can change the master_list.
// Others (e.g. panel.cpp) read it.
extern QVector<Client*> master_list;

struct Globals {
	int panelWidth;
	int panelHeight;
	int screenHeight;
	int itemPadding;
	int itemWidth;
};

extern Globals g;

void init_globals();

#endif // GLOBAL_H
