#include "filter.h"
#include <xcb/xcb.h>

EventFilter::EventFilter()
{
}

EventFilter::~EventFilter()
{
}

bool EventFilter::nativeEventFilter(const QByteArray &eventType, void *message, long *)
{
	QString pad1;

	if (eventType == "xcb_generic_event_t") {
		xcb_generic_event_t* ev = static_cast<xcb_generic_event_t *>(message);
		if ((ev->response_type == 28) && (ev->pad[1] != 320)) {
			pad1.setNum(ev->pad[1], 10);
			qDebug("pad[1]: " + pad1.toLatin1());

			// pad[1]:
			// 319 - app started / exited
			// 326 - window changed state

			// ev->pad[2] is the sequential number;

			emit caughtEvent();
		}
	}
	return false;
}
