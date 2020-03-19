#pragma once

#include <QAbstractNativeEventFilter>
#include <QObject>

class EventFilter : public QObject, public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    EventFilter();
    ~EventFilter();
    virtual bool nativeEventFilter(const QByteArray &eventType, void *message,
                                   long *) Q_DECL_OVERRIDE;

signals:
    void caughtEvent(unsigned long atom_name);
};

// vim: set ts=4 sw=4 et:
