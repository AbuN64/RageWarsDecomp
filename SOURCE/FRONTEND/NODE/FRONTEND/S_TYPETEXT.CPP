#include "DATA/GFXDATA/EVENT_HANDLER_CODE_TARGETS.H"
#include "DATA/UI/TYPE_TEXT_EVENT_TABLE.H"

#if defined(VERSION_US)
TypeTextEventTable s_typeText = {
    {
        { 5, 30000, g_eventHandlerCodeTargetId5 },
        { 6, 30000, g_eventHandlerCodeTargetId6 },
        { 7, 30000, g_eventHandlerCodeTargetId7 },
        { 8, 30000, g_eventHandlerCodeTargetId8 },
        { 0xE03, 30000, g_eventHandlerCodeTargetIdE03 },
        { 0, 0, 0 },
    },
    "T_TYPE_F",
};
#endif
