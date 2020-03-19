#include "task.h"

#include <QFont>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

#include "x11.h"
#include "globals.h"

TaskItem::TaskItem(unsigned long wid)
{
    m_wid = wid;
    m_width = g.itemWidth;
    m_height = g.panelHeight - (2 * g.itemPadding);
    m_clientName = x11WinName(m_wid);
    m_hover = false;

    setAcceptHoverEvents(true);
}

TaskItem::~TaskItem() {}

QRectF TaskItem::boundingRect() const
{
    return QRectF(0, 0, m_width - 2, m_height - 2);
}

void TaskItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                     QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(255, 194, 34, 200)); //#ffbb22
    painter->drawRect(0, 0, m_width, m_height);

    int padding = 3;
    QFont font("Ubuntu Condensed", 10);
    painter->setFont(font);
    painter->setPen(QColor(255, 255, 255, 255));

    // The -2 for the height is because otherwise the font sits to low
    // Interestingly cairo needs the same adjustment.
    QRect rect(padding, 0, m_width - padding * 2, m_height - 2);
    painter->drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, m_clientName);
}

void TaskItem::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    m_hover = true;
    update();
}

void TaskItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    m_hover = false;
    update();
}

// vim: set ts=4 sw=4 et:
