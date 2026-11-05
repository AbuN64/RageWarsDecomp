#ifndef AI_PLAYER_PLAYER_GETAMMOCAPACITY_H
#define AI_PLAYER_PLAYER_GETAMMOCAPACITY_H
#include "Common/aiprofile.h"
#include "Common/loadout.h"
s32 Player_GetPlayerIndex(void *world, unsigned int playerAddress);
int Playerai_BeginRoundEnd(char *forcePlayerList);
struct Context;
s32 Playerai_CountLocalActivePlayers(struct Context *context);
struct CVector3_t;
void *Playerai_FindNearestLivePlayer(struct Context *context, struct CVector3_t position, void *excludedPlayer);
void *Playerai_FindNearestPlayer(void *world, struct CVector3_t point);
void *Playerai_FindPlayerByController(char *object, s32 controllerAddress);
struct AimPlayer;
s32 Playerai_GetWeaponFireMode(struct AimPlayer *aimPlayer, s32 weaponId);
extern s32 Player_GetMaxHealth(void *player);
extern void *Playerai_GetPlayerByIndex(void *world, u32 playerIndex);
#endif
