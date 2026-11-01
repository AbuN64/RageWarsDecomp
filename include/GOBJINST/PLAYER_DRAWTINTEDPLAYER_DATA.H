#ifndef GOBJINST_PLAYER_DRAWTINTEDPLAYER_DATA_H
#define GOBJINST_PLAYER_DRAWTINTEDPLAYER_DATA_H
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/OBJRECV5.H"
extern void Gobjinst_DrawActorPartsWithViewEffects(LevelActor *actor, PlayerControllerView *player, s32 animationContext, Draw *params);
extern void Gobjinst_DrawBlendPartsWithViewEffects(TintedPlayerRenderActor *actor, s32 drawView, s32 animationContext, Lookup *params);
#endif
