#ifndef AI_WEAPON_WEAPON_H
#define AI_WEAPON_WEAPON_H
#include "types.h"
extern void *Pickup_FindBonusEntry(s32 bonusId);
#include "types.h"

#include "types.h"
#include "Common/small_records.h"

struct WeaponInfo;
struct WeaponInfo {
    void **resource;
    u16 model;
    u16 icon; /* 0x06: weapon icon selected by the team menu */
    s16 capacity;
    char padA[2];
    s16 alternate;
    char padE[6];
    u32 flags; /* +0x14: weapon pickup availability */
    f32 chargeRate; /* 0x18 */
    char pad1C[4];
    s16 *weaponClass;
    s16 *alternateClass;
    s16 *thirdClass;
    s16 *computerClasses[3];
    char pad38[0xC];
    f32 scopeBounds[4]; /* 0x44 */
    struct AiBehaviourTable *animation; /* 0x54 */
    s32 animationCount;
};
typedef struct WeaponInfo WeaponInfo;

extern void Weapon_UpdateHeldAlternateFire(void *weaponActor, void *attack);
struct WeaponNormalFireActionView;
extern void Weapon_UpdateNormalFireAction(void *actor, struct WeaponNormalFireActionView *attack);
#endif
