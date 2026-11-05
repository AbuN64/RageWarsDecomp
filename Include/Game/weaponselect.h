#ifndef GAME_WEAPONSELECT_H
#define GAME_WEAPONSELECT_H
#include "types.h"
#include "Common/weapon_select_brain.h"
struct SharedPlayer;
struct WeaponSelectBrain {
    struct SharedPlayer *player;
    char pad4[0x2E0];
    s32 switchTimer;
};
struct AiController;
extern s32 Nav_SelectPlayerState(struct AiController *controller);
#endif
