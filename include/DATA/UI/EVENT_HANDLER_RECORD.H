#ifndef DATA_UI_EVENT_HANDLER_RECORD_H
#define DATA_UI_EVENT_HANDLER_RECORD_H
#include "TYPES.H"

/* One entry of a screen's event handler table: the event id, the id of the screen it is addressed to, and the handler
   (a text address inside the screen's overlay, 0 when the event is only acknowledged). */
typedef struct EventHandlerRecord {
    u32 event;
    u32 target;
    void *handler;
} EventHandlerRecord;
#endif
