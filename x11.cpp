#include "x11.h"

#include <QDebug>
#include <QWidget>
#include <QX11Info>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

static Atom utf8String;
static Atom netClientList;

/* Client Name */
static Atom netWmName;
static Atom netWmVisibleName;

/* Client type - needed to avoid showing the 'wrong' type */
static Atom netWmWindowType;
static Atom netWmWindowTypeDock;
static Atom netWmWindowTypeDesktop;
static Atom netWmWindowTypeToolbar;
static Atom netWmWindowTypeMenu;
static Atom netWmWindowTypeSplash;

static Atom getAtom(const char *atomName)
{
    return XInternAtom(QX11Info::display(), atomName, False);
}

static void initAtoms(void)
{
    static bool hasRun;

    if (hasRun)
        return;
    hasRun = true;
    utf8String = getAtom("UTF8_STRING");
    netClientList = getAtom("_NET_CLIENT_LIST");
    netWmName = getAtom("_NET_WM_NAME");
    netWmVisibleName = getAtom("_NET_WM_VISIBLE_NAME");
    netWmWindowType = getAtom("_NET_WM_WINDOW_TYPE");
    netWmWindowTypeDock = getAtom("_NET_WM_WINDOW_TYPE_DOCK");
    netWmWindowTypeDesktop = getAtom("_NET_WM_WINDOW_TYPE_DESKTOP");
    netWmWindowTypeToolbar = getAtom("_NET_WM_WINDOW_TYPE_TOOLBAR");
    netWmWindowTypeMenu = getAtom("_NET_WM_WINDOW_TYPE_MENU");
    netWmWindowTypeSplash = getAtom("_NET_WM_WINDOW_TYPE_SPLASH");
}

unsigned long x11AtomNetClientList(void)
{
    initAtoms();
    return netClientList;
}

static void xgwp(unsigned long window, Atom atom, Atom atom_type, char **data,
                 unsigned long *nr_items)
{
    unsigned long type_ret, bytes_after_return;
    int format, status;
    status = XGetWindowProperty(QX11Info::display(), window, atom, 0L, ~(0L),
                                False, atom_type, &type_ret, &format, nr_items,
                                &bytes_after_return,
                                reinterpret_cast<unsigned char **>(data));
    if (status)
        qDebug("warn: XGetWindowProperty()");
}

static QString winProp(unsigned long window, Atom atom)
{
    char *data = 0;
    unsigned long nr_items;
    initAtoms();
    xgwp(window, atom, utf8String, &data, &nr_items);
    QString value = QString::fromUtf8(data);
    XFree(data);
    return value;
}

QString x11WinName(unsigned long window)
{
    initAtoms();
    QString s;
    s = winProp(window, netWmVisibleName);
    if (s.isEmpty())
        s = winProp(window, netWmName);
    return s;
}

QVector<unsigned long> x11ClientList(void)
{
    unsigned long *data = 0, nr_items;
    initAtoms();
    xgwp(QX11Info::appRootWindow(), netClientList, XA_WINDOW,
         reinterpret_cast<char **>(&data), &nr_items);
    QVector<unsigned long> clients;
    if (!data)
        return clients;
    for (unsigned int i = 0; i < nr_items; i++)
        clients.append(data[i]);
    XFree(data);
    return clients;
}

bool x11IsHidden(unsigned long window)
{
    initAtoms();
    unsigned long *data = 0, nr_items;
    xgwp(window, netWmWindowType, XA_ATOM, reinterpret_cast<char **>(&data),
         &nr_items);
    if (!data)
        return false;
    for (unsigned int i = 0; i < nr_items; i++) {
        if (data[i] == netWmWindowTypeDock || data[i] == netWmWindowTypeDesktop
            || data[i] == netWmWindowTypeToolbar
            || data[i] == netWmWindowTypeMenu
            || data[i] == netWmWindowTypeSplash) {
            XFree(data);
            return true;
        }
    }
    XFree(data);
    return false;
}

// vim: set ts=4 sw=4 et:
