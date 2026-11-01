#ifndef COMMON_RESIDENT_EVENT_HANDLER_H
#define COMMON_RESIDENT_EVENT_HANDLER_H
#include "TYPES.H"

typedef s32 (*ResidentEventHandler)(void *, s32, s32, s32, s32);
typedef struct ResidentEventHandlerEntry {
    s32 event;
    s32 actorKind;
    ResidentEventHandler handler;
} ResidentEventHandlerEntry;
#endif
