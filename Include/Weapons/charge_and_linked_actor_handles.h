#ifndef WEAPONS_CHARGE_AND_LINKED_ACTOR_HANDLES_H
#define WEAPONS_CHARGE_AND_LINKED_ACTOR_HANDLES_H
#include "Weapons/weapon_switch_actions.h"
extern void Weapon_ReleaseLinkedActorHandles(void *weaponActor);
extern void Weapon_InitializeChargeForWeaponEight(struct Player *actorView, struct WeaponFireState *fireState);
#endif
