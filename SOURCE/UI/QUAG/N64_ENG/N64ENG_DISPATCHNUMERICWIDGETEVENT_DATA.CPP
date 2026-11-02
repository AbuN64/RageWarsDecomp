#include "include_asm.h"
#include "DATA/UI/NUMERIC_WIDGET_EVENT_TABLE.H"

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE)
NumericWidgetEventTable g_n64EngDispatchNumericWidgetEventWords = {
    {
        { 0xe07, 30000, N64Eng_SetLinkedCommand100_EventHandlerAddress },
        { 0xf, 30000, N64Eng_SetLinkedCommand200_EventHandlerAddress },
        { 0x10, 30000, N64Eng_SetLinkedCommand100WithSound_EventHandlerAddress },
        { 0x8, 30000, N64Eng_HandleNumericIncrement_EventHandlerAddress },
        { 0x7, 30000, N64Eng_HandleNumericDecrement_EventHandlerAddress },
        { 0xe03, 30000, N64Eng_FreeNumericWidget_EventHandlerAddress },
        { 0xb, 30000, N64Eng_CancelSelectionRepeat_EventHandlerAddress },
        { 0xe08, 30000, TickSelectionRepeat_EventHandlerAddress },
        { 0x0, 0, 0 },
    },
    0x1,
};
#endif
#if defined(VERSION_EU)
NumericWidgetEventTable g_n64EngDispatchNumericWidgetEventWords = {
    {
        { 0xe07, 30000, N64Eng_SetLinkedCommand100_EventHandlerAddress },
        { 0xf, 30000, N64Eng_SetLinkedCommand200_EventHandlerAddress },
        { 0x10, 30000, N64Eng_SetLinkedCommand100WithSound_EventHandlerAddress },
        { 0x8, 30000, N64Eng_HandleNumericIncrement_EventHandlerAddress },
        { 0x7, 30000, N64Eng_HandleNumericDecrement_EventHandlerAddress },
        { 0xe03, 30000, N64Eng_FreeNumericWidget_EventHandlerAddress },
        { 0xb, 30000, N64Eng_CancelSelectionRepeat_EventHandlerAddress },
        { 0xe08, 30000, TickSelectionRepeat_EventHandlerAddress },
        { 0x0, 0, 0 },
    },
    0x0,
};
#endif
#if defined(VERSION_EU_X)
NumericWidgetEventTable g_n64EngDispatchNumericWidgetEventWords = {
    {
        { 0xe07, 30000, N64Eng_SetLinkedCommand100_EventHandlerAddress },
        { 0xf, 30000, N64Eng_SetLinkedCommand200_EventHandlerAddress },
        { 0x10, 30000, N64Eng_SetLinkedCommand100WithSound_EventHandlerAddress },
        { 0x8, 30000, N64Eng_HandleNumericIncrement_EventHandlerAddress },
        { 0x7, 30000, N64Eng_HandleNumericDecrement_EventHandlerAddress },
        { 0xe03, 30000, N64Eng_FreeNumericWidget_EventHandlerAddress },
        { 0xb, 30000, N64Eng_CancelSelectionRepeat_EventHandlerAddress },
        { 0xe08, 30000, TickSelectionRepeat_EventHandlerAddress },
        { 0x0, 0, 0 },
    },
    0x496e7669,
};
#endif
#if defined(VERSION_US)
NumericWidgetEventTable g_n64EngDispatchNumericWidgetEventWords = {
    {
        { 0xe07, 30000, N64Eng_SetLinkedCommand100_EventHandlerAddress },
        { 0xf, 30000, N64Eng_SetLinkedCommand200_EventHandlerAddress },
        { 0x10, 30000, N64Eng_SetLinkedCommand100WithSound_EventHandlerAddress },
        { 0x8, 30000, N64Eng_HandleNumericIncrement_EventHandlerAddress },
        { 0x7, 30000, N64Eng_HandleNumericDecrement_EventHandlerAddress },
        { 0xe03, 30000, N64Eng_FreeNumericWidget_EventHandlerAddress },
        { 0xb, 30000, N64Eng_CancelSelectionRepeat_EventHandlerAddress },
        { 0xe08, 30000, TickSelectionRepeat_EventHandlerAddress },
        { 0x0, 0, 0 },
    },
    0x400,
};
#endif
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded us-rev1 data; explicit withholding in other holders. */
extern char N64Eng_SetLinkedCommand100_Address[];
extern char N64Eng_SetLinkedCommand200_Address[];
extern char N64Eng_SetLinkedCommand100WithSound_Address[];
extern char N64Eng_HandleNumericIncrement_Address[];
extern char N64Eng_HandleNumericDecrement_Address[];
extern char N64Eng_CancelSelectionRepeat_Address[];
extern char TickSelectionRepeat_Address[];
extern char N64Eng_FreeNumericWidget_Address[];
EventHandlerRecord g_numericWidgetEventIds_StorageWords[9] = {
    { 3591, 30000, N64Eng_SetLinkedCommand100_Address },
    { 15, 30000, N64Eng_SetLinkedCommand200_Address },
    { 16, 30000, N64Eng_SetLinkedCommand100WithSound_Address },
    { 8, 30000, N64Eng_HandleNumericIncrement_Address },
    { 7, 30000, N64Eng_HandleNumericDecrement_Address },
    { 3587, 30000, N64Eng_FreeNumericWidget_Address },
    { 11, 30000, N64Eng_CancelSelectionRepeat_Address },
    { 3592, 30000, TickSelectionRepeat_Address },
    { 0, 0, 0 },
};
#endif
