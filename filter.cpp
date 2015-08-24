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
		if ((ev->response_type  & ~(0x80)) == XCB_PROPERTY_NOTIFY) {
		        xcb_property_notify_event_t *p = reinterpret_cast<xcb_property_notify_event_t *>(ev);
			emit caughtEvent(p->atom);
		}
	}
	return false;
}
