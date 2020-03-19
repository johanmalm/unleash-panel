#pragma once

#include "types.h"
#include <QGraphicsItem>

class TaskItem : public QGraphicsItem
{
public:
    enum { Type = UserType + PANEL_TYPE_TASK };
    int type() const override { return Type; }
    TaskItem(unsigned long wid);
    ~TaskItem();
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) Q_DECL_OVERRIDE;
    QString m_clientName;
    unsigned long m_wid;
    bool m_hover;

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *) override;

private:
    int m_width;
    int m_height;
};

// vim: set ts=4 sw=4 et:
