#ifndef DATA_UI_NUMERIC_WIDGET_EVENT_TABLE_H
#define DATA_UI_NUMERIC_WIDGET_EVENT_TABLE_H
#include "Data/Ui/event_handler_record.h"

extern char N64Eng_CancelSelectionRepeat_EventHandlerAddress[];
extern char N64Eng_FreeNumericWidget_EventHandlerAddress[];
extern char N64Eng_HandleNumericDecrement_EventHandlerAddress[];
extern char N64Eng_HandleNumericIncrement_EventHandlerAddress[];
extern char N64Eng_SetLinkedCommand100WithSound_EventHandlerAddress[];
extern char N64Eng_SetLinkedCommand100_EventHandlerAddress[];
extern char N64Eng_SetLinkedCommand200_EventHandlerAddress[];
extern char TickSelectionRepeat_EventHandlerAddress[];

/* Eight handlers and the sentinel, then a retained object-boundary word.
 * N64Eng_DispatchNumericWidgetEvent reads event/target/handler at +0/+4/+8. */
typedef struct NumericWidgetEventTable {
    EventHandlerRecord entries[9];
    u32 retainedTail;
} NumericWidgetEventTable;
typedef char NumericWidgetEventTableSize[(sizeof(NumericWidgetEventTable) == 112) ? 1 : -1];
#endif
