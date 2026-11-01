#ifndef WEAPONS_STARTUP_CUES_AND_SIDE_YAW_H
#define WEAPONS_STARTUP_CUES_AND_SIDE_YAW_H
#include "WEAPONS/PLAYERRECAT1450V1.H"
extern void Weapon_ReleaseHandlesAndExitState39(void *actor);
extern void Weapon_ApplySideDependentYaw(void *object, Event *event);
extern void Weapon_ApplyScaledSideYaw(void *obj, Event *event);
extern void Weapon_PlayStartupCue9E2(void *actor);
extern void Weapon_InitializeChargeAndStartupCues(struct Shared_ActorView *actor, struct WeaponFireState *fireState);
#endif
