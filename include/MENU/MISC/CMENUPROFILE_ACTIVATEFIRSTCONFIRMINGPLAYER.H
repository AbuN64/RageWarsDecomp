#ifndef MENU_MISC_CMENUPROFILE_ACTIVATEFIRSTCONFIRMINGPLAYER_H
#define MENU_MISC_CMENUPROFILE_ACTIVATEFIRSTCONFIRMINGPLAYER_H
#include "MENU/PLAYERSETTINGS.H"
#include "COMMON/LONE/PROFILE_CONFIRMATION_ELAPSED_TIME.H"
/* Frame timer of the menu, in seconds. */
extern void CMenuProfile_ActivateFirstConfirmingPlayer(void);
extern s32 CMenuProfile_ResetPlayerControllerProfile(s32 unused0, PlayerProfileMenuContext *menu);
extern s32 CMenuProfile_HasSavedRoundProgress(void);
extern s32 CMenuProfile_UpdateRoundEndDelay(void);
extern s32 CMenuProfile_HasRoundProgress(void);
extern void CMenuProfile_ResetRoundEndDelay(void);
extern ControllerProfile *CMenuProfile_FindConfirmingController(s32 *out);
#endif
