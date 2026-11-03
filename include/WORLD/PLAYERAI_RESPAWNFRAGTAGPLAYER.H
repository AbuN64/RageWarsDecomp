#ifndef WORLD_PLAYERAI_RESPAWNFRAGTAGPLAYER_H
#define WORLD_PLAYERAI_RESPAWNFRAGTAGPLAYER_H
#include "COMMON/RESOURCELOADSTATE.H"


extern void Playerai_ResetMotionAndSelectIdleAnimation(Player *actor);
extern void Playerai_SelectMovementAnimation(Player *object);
extern void Playerai_ReleasePlayerResource(ResourceLoadState *resourceLoadState);
extern void Playerai_EmptyMovementAnimationHook(void);
extern void Playerai_ToggleActionFlagMode(Player *player);
extern void Playerai_AdvanceCurrentRunEndState(void);
extern void Playerai_EmptyPlayerResourceHook(void);
extern void Playerai_EmptySurfaceHeightEffectHook(void);
extern void Playerai_UpdateStoredRunEndPlayer(void);
extern s32 Playerai_CountTrailingSpaces(s32 textAddress, s32 lastIndex);
#endif
