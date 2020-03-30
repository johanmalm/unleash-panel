#include "task.h"

#include <QFont>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

#include "x11.h"
#include "settings.h"

TaskItem::TaskItem(unsigned long wid)
{
    m_wid = wid;
    m_width = g.taskWidth;
    m_height = g.panelHeight - (2 * g.panelPaddingY);
    m_clientName = x11WinName(m_wid);
    m_hover = false;

    setAcceptHoverEvents(true);
}

TaskItem::~TaskItem() {}

QRectF TaskItem::boundingRect() const
{
    return QRectF(0, 0, m_width, m_height);
}

void TaskItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                     QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing, true);

    /* background */
    painter->setBrush(g.taskColorBackground);
    painter->setPen(g.taskColorBackground);
    painter->drawRect(boundingRect());

    /* hover */
    if (m_hover) {
        painter->setBrush(g.taskColorHoverBackground);
        painter->drawRect(boundingRect());
    }

    /* text */
    QFont font(g.fontFamily, g.fontSize);
    painter->setFont(font);
    painter->setPen(g.taskColorFont);
    QRect rect(g.taskPaddingX, 0, m_width - g.taskPaddingX * 2, m_height);
    QFontMetrics metrics(font);
    QString elidedText =
            metrics.elidedText(m_clientName, Qt::ElideRight, rect.width());
    painter->drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, elidedText);
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
