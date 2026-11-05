#ifndef RENDER_LINKED_DRAWTEXTUREDRIBBON_H
#define RENDER_LINKED_DRAWTEXTUREDRIBBON_H
#include "types.h"
#include "Common/sharedplayer.h"
#include "Render/ribbon_draw.h"




void *Linked_AppendRibbonSegment(void *effectSystem, void *ribbon, void *local);
struct RibbonWorld;
struct RibbonActor;
struct GameplayCamera;
void Linked_DrawTexturedRibbon(struct RibbonWorld *pool, struct RibbonActor *actor, struct GameplayCamera *camera);
struct LinkOwner802A;
void Linked_UpdateLinkedNodeTransforms(struct LinkOwner802A *owner);
struct StateSmpUpdateRibbonLifetime;
s32 Linked_UpdateRibbonLifetime(s32 owner, struct StateSmpUpdateRibbonLifetime *state);
void Linked_UpdateRibbonMatrices(void *ribbon, void *camera);
#endif
