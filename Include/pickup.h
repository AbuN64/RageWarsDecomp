#ifndef PICKUP_H
#define PICKUP_H
#include "Common/actorrec.h"
#include "types.h"
#include "Common/response.h"
#include "Common/pickup_entry_tables.h"
struct Selection;
struct SelectionNavAppendDirectionalRouteStage;
extern s32 Nav_AdvancePickupRouteSelection(struct Selection *sel);
extern s32 Nav_AppendDirectionalRouteStage(struct SelectionNavAppendDirectionalRouteStage *sel);
extern s32 Nav_InsertPickupRouteNode(struct SelectionNavAppendDirectionalRouteStage *sel);

extern int Pickup_HandleItemUpdate(void);

extern s32 Pickup_ToggleEffectAndFlash(struct Player *actorView);
#endif
