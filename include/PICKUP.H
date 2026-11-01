#ifndef PICKUP_H
#define PICKUP_H
#include "COMMON/ACTORREC.H"
#include "TYPES.H"
#include "COMMON/RESPONSE.H"
#include "COMMON/ENTRYRECATE.H"
extern s32 Nav_AdvancePickupRouteSelection(Selection *sel);
extern s32 Nav_AppendDirectionalRouteStage(SelectionNavAppendDirectionalRouteStage *sel);
extern s32 Nav_InsertPickupRouteNode(SelectionNavAppendDirectionalRouteStage *sel);

/* Timed pickup family: common effect payload followed by a word amount. */
typedef struct TimedItemEffect {
    void *resource;
    s16 id;
    s16 sound;
    s16 callback;
    s16 reservedA;
    s32 amount;
} TimedItemEffect;

extern int Pickup_HandleItemUpdate(void);

extern s32 Pickup_ToggleEffectAndFlash(struct Shared_ActorView *actorView);
#endif
