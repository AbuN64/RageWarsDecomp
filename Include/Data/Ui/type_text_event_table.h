#ifndef DATA_UI_TYPE_TEXT_EVENT_TABLE_H
#define DATA_UI_TYPE_TEXT_EVENT_TABLE_H
#include "Data/Ui/event_handler_record.h"

/* Node_DispatchTypedWidgetEvent advances by 12 bytes and tests the handler
 * at +8 for the sentinel. The six rows are followed by the retained tag. */
typedef struct TypeTextEventTable {
    EventHandlerRecord entries[6];
    char tag[8];
} TypeTextEventTable;

extern TypeTextEventTable s_typeText;

typedef char TypeTextEventRecordSize[(sizeof(EventHandlerRecord) == 12) ? 1 : -1];
typedef char TypeTextEventTableSize[(sizeof(TypeTextEventTable) == 80) ? 1 : -1];
#endif
