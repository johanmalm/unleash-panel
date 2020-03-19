#pragma once

#include "types.h"
#include <QGraphicsItem>

class BackgroundItem : public QGraphicsItem
{
public:
    enum { Type = UserType + PANEL_TYPE_BACKGROUND };
    int type() const override { return Type; }
    BackgroundItem();
    ~BackgroundItem();
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) Q_DECL_OVERRIDE;

private:
    QColor color;
};

// vim: set ts=4 sw=4 et:
