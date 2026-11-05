#ifndef WEAPONS_PITCH_TRANSLATION_AND_SPIN_ACTIONS_H
#define WEAPONS_PITCH_TRANSLATION_AND_SPIN_ACTIONS_H
#include "Weapons/weapon_switch_actions.h"
#include "Common/weapon_special_fire.h"
extern void Weapon_EmptyChargeStateHook(void);
extern void Weapon_TranslateEventSixByPitch(void *matrix, void *eventStorage);
extern void Weapon_EmptyAlternateFireHook(void);
extern void Weapon_EaseSpinAndUpdateFeedback(struct WeaponActorStateView *actor, void *fireState);
extern void Weapon_PlayStartupCue80C(void *weaponActor);
#endif
