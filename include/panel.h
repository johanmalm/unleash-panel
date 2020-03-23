#pragma once

#include "task.h"
#include "settings.h"
#include "background.h"
#include <QGraphicsView>

class Panel : public QGraphicsView
{
    Q_OBJECT

public:
    Panel(QWidget *parent = 0);
    ~Panel();
    void updatePanel();

public slots:
    void reactToX11Event(unsigned long atom_name);

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    QGraphicsScene scene;
    void printTasks();
    void updateClientPositions();
    void removeTask(unsigned long wid);
    TaskItem *taskUnderMouse(void);
};

// vim: set ts=4 sw=4 et:
