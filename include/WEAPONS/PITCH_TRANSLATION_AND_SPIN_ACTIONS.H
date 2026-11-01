#ifndef WEAPONS_PITCH_TRANSLATION_AND_SPIN_ACTIONS_H
#define WEAPONS_PITCH_TRANSLATION_AND_SPIN_ACTIONS_H
#include "WEAPONS/PLAYERRECAT1450V1.H"
#include "COMMON/STATERECAT10.H"
extern void Weapon_EmptyChargeStateHook(void);
extern void Weapon_TranslateEventSixByPitch(void *matrix, void *eventStorage);
extern void Weapon_EmptyAlternateFireHook(void);
extern void Weapon_EaseSpinForActionFive(struct WeaponActorStateView *actor, void *fireState);
extern void Weapon_PlayStartupCue80C(void *weaponActor);
#endif
