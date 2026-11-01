#ifndef AI_WEAPONAI_H
#define AI_WEAPONAI_H
#include "TYPES.H"
#include "COMMON/MEASURED_STORAGE.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "WEAPONS/PLAYERRECAT1450V1.H"

extern u8 *g_weaponLockedNoticeTextEu[];

extern u8 *g_weaponLockedNoticeTextEuX[];

/* Measured 4-byte access at 0x6AC; storage view, complete object unknown. */
struct WeaponAlternateFireFlagsView { unsigned char padding[1708]; s32 value; };
/* Measured 4-byte access at 0x40; storage view, complete object unknown. */
struct WeaponReleasedFireLevelView { unsigned char padding[64]; f32 value; };

extern void Weaponai_DecaySpinAndActivateEffect(Shared_Actor *actor, WeaponFireState *weapon);

extern void Weaponai_ForwardActorStateRequest(void *actor, void *stateController, s32 action);
#endif
