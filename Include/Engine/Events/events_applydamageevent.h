#ifndef ENGINE_EVENTS_EVENTS_APPLYDAMAGEEVENT_H
#define ENGINE_EVENTS_EVENTS_APPLYDAMAGEEVENT_H
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Common/vector.h"

extern void Events_DispatchCallback(void *sourceActor, void *targetActor, s32 eventKind, CVector3 eventPosition, ResourceManagerState eventParams);

#endif
