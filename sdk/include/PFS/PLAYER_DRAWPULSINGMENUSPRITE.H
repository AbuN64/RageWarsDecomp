#ifndef PFS_PLAYER_DRAWPULSINGMENUSPRITE_H
#define PFS_PLAYER_DRAWPULSINGMENUSPRITE_H
#include "Common/respawn_menu_actor.h"
extern s32 Player_RespawnItemPlayer(void *entry, PlayerRespawnMenuContext *menuState);
extern int Player_ResumePlayerFromMenu(int unused, PlayerMenuResumeContext *player);
extern void Player_DrawPulsingMenuSprite(PulsingMenuSpriteView *spriteState, CaptionEntry *caption, s32 unusedEventKind, MenuStyle *menuStyle);
extern s32 Player_SetNestedItemFlag(void *unused, struct NestedPlayerMenuFlagContext *root);
extern s32 Player_UpdatePlayerRespawnDelay(PlayerRespawnMenuContext *menuState);
#endif
