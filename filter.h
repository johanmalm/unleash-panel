#ifndef FILTER_H
#define FILTER_H

#include <QObject>
#include <QAbstractNativeEventFilter>


class EventFilter : public QObject, public QAbstractNativeEventFilter
{
	Q_OBJECT

public:
	EventFilter();
	~EventFilter();
	virtual bool nativeEventFilter(const QByteArray &eventType,
				       void *message, long *) Q_DECL_OVERRIDE;

signals:
	void caughtEvent(unsigned long atom_name);
};

#endif	// FILTER_H
