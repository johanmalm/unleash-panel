#ifndef GLOBAL_H
#define GLOBAL_H

#include <QtCore>

struct Client {
	QVector<unsigned long> value;
	QVector<QString> name;
};

extern Client clients;


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
