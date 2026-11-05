#ifndef WORLD_PLAYERAI_RESPAWNFRAGTAGPLAYER_H
#define WORLD_PLAYERAI_RESPAWNFRAGTAGPLAYER_H
#include "Common/resourceloadstate.h"


struct ResourceLoadState;
struct Player;
extern void Playerai_ResetMotionAndSelectIdleAnimation(struct Player *actor);
extern void Playerai_SelectMovementAnimation(struct Player *object);
extern void Playerai_ReleasePlayerResource(struct ResourceLoadState *resourceLoadState);
extern void Playerai_EmptyMovementAnimationHook(void);
extern void Playerai_ToggleActionFlagMode(struct Player *player);
extern void Playerai_AdvanceCurrentRunEndState(void);
extern void Playerai_EmptyPlayerResourceHook(void);
extern void Playerai_EmptySurfaceHeightEffectHook(void);
extern void Playerai_UpdateStoredRunEndPlayer(void);
extern s32 Playerai_CountTrailingSpaces(s32 textAddress, s32 lastIndex);
extern s32 Playerai_PlayerHasAmmoForWeapon(void *player, s32 requestedWeaponType);

#endif
