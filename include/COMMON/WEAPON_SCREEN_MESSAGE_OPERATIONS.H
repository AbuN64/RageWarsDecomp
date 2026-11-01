#ifndef COMMON_WEAPON_SCREEN_MESSAGE_OPERATIONS_H
#define COMMON_WEAPON_SCREEN_MESSAGE_OPERATIONS_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"


extern f32 g_frameElapsedTime;

#include "COMMON/MENU_UI_PROVIDERS.H"

extern s32 g_resultExitPending;
extern s32 Tsmos_IsFrontendActive(void);
extern void Onscrn_SetupSpriteMode(s32);
extern void Playerai_DrawProjectedAimIcon(struct View *view, struct CVector3_t *point, s32 icon, f32 frame, f32 scale, f32 size);
#endif
