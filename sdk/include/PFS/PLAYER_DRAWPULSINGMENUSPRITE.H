#ifndef PFS_PLAYER_DRAWPULSINGMENUSPRITE_H
#define PFS_PLAYER_DRAWPULSINGMENUSPRITE_H
#include "COMMON/ACTORRECAT260.H"
extern s32 Player_RespawnItemPlayer(void *unused0, PlayerRespawnMenuContext *menuState);
extern int Player_ResumePlayerFromMenu(int unused, PlayerMenuResumeContext *player);
extern void Player_DrawPulsingMenuSprite(PulsingMenuSpriteView *spriteState, CaptionEntry *caption, s32 unusedEventKind, MenuStyle *menuStyle);
extern s32 Player_SetNestedItemFlag(void *unused, struct NestedPlayerMenuFlagContext *root);
extern s32 Player_UpdatePlayerRespawnDelay(PlayerRespawnMenuContext *menuState);
#endif
