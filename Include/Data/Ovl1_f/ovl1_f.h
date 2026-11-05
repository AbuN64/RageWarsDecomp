#ifndef DATA_OVL1_F_OVL1_F_H
#define DATA_OVL1_F_OVL1_F_H
struct Shared_Actor;
struct WeaponFireState;
extern void * g_weaponSlotUpdateSpinAndRepeatCueFireStateSlots[];
extern void * g_weaponDelayedFireStateSlots[];
extern void Weapon_EnterChargeStateWithCues(struct Player *actor, struct WeaponFireState *fireState);
extern void Weapon_SetDelayAndRequestAlternateFireState(void *actor, struct Shared_Particle *particle);
extern void Weapon_UpdateSpecialFireAndAmmo(void *weaponActor, void *attack);
extern void Weaponai_ToggleFiringModeWithAmmoCheck(struct Shared_Actor *actor, struct WeaponFireState *fireState);
extern void Weaponai_TryEnterAlternateFireState(struct Shared_Actor *actor, void *attack);
extern void Weaponai_TryEnterAmmoCostState(struct Shared_Actor *actor, struct WeaponFireState *fireState);
extern void Weaponai_UpdateAnimatedFiringMode(struct Shared_Actor *actor, struct WeaponFireState *fireState);
extern void Weaponai_UpdateHeldFire(struct Shared_Actor *actor, struct WeaponFireState *attack);
extern void Weaponai_UpdateSpinAndRepeatCue(struct Shared_Actor *actor, struct WeaponFireState *attack);
#endif
