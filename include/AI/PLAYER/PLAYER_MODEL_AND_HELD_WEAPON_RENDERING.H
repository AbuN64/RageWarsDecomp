#ifndef AI_PLAYER_PLAYER_MODEL_AND_HELD_WEAPON_RENDERING_H
#define AI_PLAYER_PLAYER_MODEL_AND_HELD_WEAPON_RENDERING_H
#include "COMMON/OBJRECV5.H"
extern void Player_DrawPlayerModel(void *player, void *renderContext);
extern void Player_DrawHeldWeapon(void *player, struct WeaponMenuView *weaponView);
#endif
