#ifndef AI_WEAPONAI_H
#define AI_WEAPONAI_H
#include "types.h"
#include "Common/measured_storage.h"
#include "Common/weapon_marker_and_profile_views.h"
#include "Weapons/weapon_switch_actions.h"

struct Shared_Actor;
struct WeaponFireState;
extern u8 *g_weaponLockedNoticeTextEu[];

extern u8 *g_weaponLockedNoticeTextEuX[];

/* Measured 4-byte access; storage view, complete object unknown. */
struct WeaponAlternateFireFlagsView { unsigned char padding[1708]; s32 value; };
/* Measured 4-byte access; storage view, complete object unknown. */
struct WeaponReleasedFireLevelView { unsigned char padding[64]; f32 value; };

extern void Weaponai_DecaySpinAndActivateEffect(struct Shared_Actor *actor, struct WeaponFireState *weapon);

extern void Weaponai_ForwardActorStateRequest(void *actor, void *stateController, s32 action);
struct LevelActor;
struct Dest;
extern void Weaponai_UpdateChargeAndRepeatCue(struct LevelActor *actor, struct Dest *attack);
#endif
