#include <QWidget>
#include <QX11Info>
#include "globals.h"
#include "server.h"
#include "client.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <QDebug>

Server::Server()
{
	// Initiate Atoms
	m_utf8_string         = XInternAtom(QX11Info::display(), "UTF8_STRING", False);
	m_net_client_list     = XInternAtom(QX11Info::display(), "_NET_CLIENT_LIST", False);
	m_net_wm_visible_name = XInternAtom(QX11Info::display(), "_NET_WM_VISIBLE_NAME", False);

	sync_list();
}

Server::~Server()
{
}

void Server::print_list()
{
	QString t, s;

	foreach (Client *c, master_list) {
		t.setNum(c->getWID(), 16);
		s = s + "[" + t + "]:" + c->getName().mid(0,4) + " ";
	}

	qDebug(s.toLatin1());
}


QString Server::get_win_prop(unsigned long window, unsigned long atom)
{

	char* data = 0;
	unsigned long type_ret, num, bytes;
	int format;

	int status = XGetWindowProperty(QX11Info::display(), window,
					atom, 0L, ~(0L), False, m_utf8_string,
					&type_ret, &format, &num, &bytes,
					reinterpret_cast<unsigned char**>(&data));

	if(status)
		qDebug("Warning: get_win_prop() returned error.");

	QString value = QString::fromUtf8(data);
	XFree(data);
	return value;
}

QVector<unsigned long> Server::get_client_list()
{
	unsigned long *data = 0;
	unsigned long type_ret, num, bytes;
	int format;

	int status = XGetWindowProperty(QX11Info::display(),
					QX11Info::appRootWindow(),
					m_net_client_list, 0L, ~(0L), False, XA_WINDOW,
					&type_ret, &format, &num, &bytes,
					reinterpret_cast<unsigned char**>(&data));

	if(status)
		qDebug("Warning: get_client_list() returned error.");


	QVector<unsigned long> list;
	list.clear();		// FIXME: Is this needed?

	if (data) {
		for(unsigned int i = 0; i < num; i++) {
			list.append(data[i]);
		}
	}
	XFree(data);

	return list;
}

void Server::sync_list()
{
	QVector<unsigned long> new_list;

	new_list = get_client_list();

	foreach (Client *c, master_list)
		delete c;
	master_list.clear();

	foreach (unsigned long new_item, new_list) {
		Client *w = new Client;
		w->setWID(new_item);
		master_list.append(w);
	}

	QString tmp;
	foreach (Client *c, master_list) {
		tmp = get_win_prop(c->getWID(), m_net_wm_visible_name);
//		if (tmp.contains("johan@a1")) tmp = "terminal";
//		if (tmp.contains("Firefox")) tmp = "firefox";
//		if (tmp.contains("NetSurf")) tmp = "netsurf";
		c->setName(tmp);
	}

	emit clientListUpdated();

	print_list();
}


int Server::clientListChanged(unsigned long atom_name)
{
	if (atom_name == m_net_client_list)
		sync_list();

	return 0;
}
