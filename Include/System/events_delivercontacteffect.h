#ifndef SYSTEM_EVENTS_DELIVERCONTACTEFFECT_H
#define SYSTEM_EVENTS_DELIVERCONTACTEFFECT_H
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Common/box_contact.h"
#include "Common/vector.h"
/* Spawns the effect `effect` for the pair (source, target) at `position`. The final eight bytes are an opaque
 * payload: the function only copies them to its frame and forwards them by value to the per-effect handler. */
extern void Events_DeliverContactEffect(void *source, void *target, s32 effect, s32 delay, CVector3 position, ContactEffectStyle payload);
#endif
