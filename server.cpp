#include <QWidget>
#include <QX11Info>
#include "globals.h"
#include "server.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>


Server::Server()
{
	// Initiate Atoms
	m_utf8_string =		XInternAtom(QX11Info::display(), "UTF8_STRING", False);
	m_net_client_list =	XInternAtom(QX11Info::display(), "_NET_CLIENT_LIST", False);
	m_net_wm_visible_name =	XInternAtom(QX11Info::display(), "_NET_WM_VISIBLE_NAME", False);

	get_client_list();
}

Server::~Server()
{
}

void Server::print_list()
{
	QString t, s;
	for (int i=0; i < clients.value.size(); i++) {
		t.setNum(clients.value.at(i), 16);
		s = s + "[" + t + "] " + clients.name.at(i).mid(0,8) + "  ";
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

int Server::get_client_list()
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

	if (data) {
		clients.value.clear();
		for(unsigned int i = 0; i < num; i++) {
			clients.value.append(data[i]);
		}
	}
	XFree(data);

	// put the following in seperate function.

	QString tmp;
	clients.name.clear();
	for (int i=0; i < clients.value.size(); i++) {
		tmp = get_win_prop(clients.value.at(i), m_net_wm_visible_name);

		if (tmp.contains("johan@arch")) tmp = "terminal";
		if (tmp.contains("Firefox")) tmp = "firefox";

		clients.name.append(tmp);
	}

	emit clientListUpdated();

	print_list();

	return 0;
}

