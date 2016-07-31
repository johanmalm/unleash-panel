#include "globals.h"
#include <QDebug>

Client_t clients;

QVector<Client*> master_list;

Globals g;

void init_globals()
{
	g.panelWidth = 1024;
	g.panelHeight = 30;
	g.screenHeight = 600;
	g.itemPadding = 3;
	g.itemWidth = 80;
}
