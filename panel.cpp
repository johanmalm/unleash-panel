#include <QDebug>
#include <QTextStream>
#include <QtWidgets>

#include "panel.h"
#include "x11.h"
#include "settings.h"

Panel::Panel(QWidget *parent) : QGraphicsView(parent)
{
    setScene(&scene);

    scene.setSceneRect(0, 0, g.panelWidth, g.panelHeight);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    setRenderHint(QPainter::Antialiasing);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet("background-color: transparent;");
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_X11NetWmWindowTypeDock, true);

    /*
     * Turn off window borders. Note that
     * setStyleSheet("border-style: none; border-width: 0 px;")
     * achieves nothing here.
     */
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint
                   | Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint);

    /*
     * The QGraphicsScene has hard-coded margins built into the qt5 libraries,
     * forcing the QGraphicsScene to be smaller than the QGraphcsView (which is
     * also the window) by one pixel horizontally and two pixels vertically. As
     * a result, correct positioning of the QGraphicsScene can only be achieved
     * by placing the window slightly outside the screen.
     */
    resize(g.panelWidth + 2, g.panelHeight + 4);
    move(-1, g.screenHeight - g.panelHeight - 2);

    BackgroundItem *p = new BackgroundItem;
    p->setPos(0, 0);
    scene.addItem(p);

    updatePanel();
}

Panel::~Panel() {}

void Panel::updateClientPositions()
{
    int i = 0;
    foreach (QGraphicsItem *item, items()) {
        if (TaskItem *p = qgraphicsitem_cast<TaskItem *>(item)) {
            p->setPos(g.panelPaddingX + (g.taskWidth + g.taskSpacing) * i,
                      g.panelPaddingY);
            i++;
        }
    }
}

void Panel::printTasks()
{
    qDebug() << "Current scene tasks:";
    foreach (QGraphicsItem *item, items())
        if (TaskItem *p = qgraphicsitem_cast<TaskItem *>(item))
            qDebug() << " - " << p->m_clientName;
}

void Panel::updatePanel()
{
    /*
     * Create two QVectors with clients' Window IDs:
     *   - one based on what the X11 server says (i.e. the truth!)
     *   - the other to reflect what's currently on the QGraphicsScene
     */
    QVector<unsigned long> serverClients = x11ClientList();
    QVector<unsigned long> sceneClients;
    foreach (QGraphicsItem *item, items()) {
        if (TaskItem *p = qgraphicsitem_cast<TaskItem *>(item))
            sceneClients.append(p->m_wid);
    }

    /* Add 'new' clients to the QGraphicsScene */
    foreach (unsigned long new_item, serverClients) {
        if (sceneClients.contains(new_item))
            continue;
        if (x11IsHidden(new_item))
            continue;
        TaskItem *d = new TaskItem(new_item);
        scene.addItem(d);
    }

    /* Remove 'dead' clients from the QGraphicsScene */
    foreach (unsigned long c, sceneClients) {
        if (serverClients.contains(c))
            continue;
        removeTask(c);
    }

    updateClientPositions();
    printTasks();
}

void Panel::reactToX11Event(unsigned long atom_name)
{
    if (atom_name == x11AtomNetClientList())
        updatePanel();
}

void Panel::removeTask(unsigned long wid)
{
    foreach (QGraphicsItem *item, items()) {
        if (TaskItem *p = qgraphicsitem_cast<TaskItem *>(item)) {
            if (p->m_wid != wid)
                continue;
            scene.removeItem(p);
            delete (p);
            break;
        }
    }
}

TaskItem *Panel::taskUnderMouse(void)
{
    foreach (QGraphicsItem *item, items())
        if (TaskItem *p = qgraphicsitem_cast<TaskItem *>(item))
            if (p->m_hover)
                return p;
    return nullptr;
}

void Panel::mousePressEvent(QMouseEvent *event)
{
    TaskItem *p = taskUnderMouse();
    if (!p)
        return;
    if (event->button() == Qt::LeftButton)
        qDebug() << "left click: " << p->m_clientName;
    else if (event->button() == Qt::RightButton)
        qDebug() << "right click: " << p->m_clientName;
}

// vim: set ts=4 sw=4 et:
