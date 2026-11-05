#ifndef WEAPONS_STARTUP_CUES_AND_SIDE_YAW_H
#define WEAPONS_STARTUP_CUES_AND_SIDE_YAW_H
#include "Weapons/weapon_switch_actions.h"
struct Event;
extern void Weapon_ReleaseHandlesAndExitState39(void *actor);
extern void Weapon_ApplySideDependentYaw(void *object, struct Event *event);
extern void Weapon_ApplyScaledSideYaw(void *obj, struct Event *event);
extern void Weapon_PlayStartupCue9E2(void *actor);
extern void Weapon_InitializeChargeAndStartupCues(struct Player *actor, struct WeaponFireState *fireState);
#endif
