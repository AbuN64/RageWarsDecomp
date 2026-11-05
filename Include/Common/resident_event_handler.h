#ifndef COMMON_RESIDENT_EVENT_HANDLER_H
#define COMMON_RESIDENT_EVENT_HANDLER_H
#include "types.h"

/* Actor kind in a handler entry that matches every actor. */
#define ANY_ACTOR_KIND 30000
typedef s32 (*ResidentEventHandler)(void *, s32, s32, s32, s32);
typedef struct ResidentEventHandlerEntry {
    s32 event;
    s32 actorKind;
    ResidentEventHandler handler;
} ResidentEventHandlerEntry;

/* The load-relative form of a resident handler: its address with the 0x80000000 segment base removed. */
#define ResidentCodeOffset(handlerFunction) ((ResidentEventHandler)(void *)((char *)&(handlerFunction) - 0x80000000U))
/* Handler stored as a function address with the KSEG0 base removed (24-bit packed form). */
#define RESIDENT_HANDLER_PACKED(fn) ((ResidentEventHandler)(void *)((char *)&(fn) - 0x80000000U))

/* Handler address as stored in overlay link tables: the function address without the KSEG0 base. */
#define RESIDENT_HANDLER_ADDRESS(function) ((ResidentEventHandler)(void *)((char *)&(function) - 0x80000000U))
#endif
