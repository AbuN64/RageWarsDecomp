#ifndef AI_WEAPONSELECT_H
#define AI_WEAPONSELECT_H
#include "types.h"
struct Player;
extern s32 Player_GetMaxHealth(void *player);
extern s32 Player_GetAmmoCapacity(struct Player *actor, s16 index, s32 capacityMode);
#endif
