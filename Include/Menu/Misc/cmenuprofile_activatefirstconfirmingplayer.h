#ifndef MENU_MISC_CMENUPROFILE_ACTIVATEFIRSTCONFIRMINGPLAYER_H
#define MENU_MISC_CMENUPROFILE_ACTIVATEFIRSTCONFIRMINGPLAYER_H
struct MenuBuildEntry;
#include "Menu/playersettings.h"
#include "Common/Lone/profile_confirmation_elapsed_time.h"
struct ControllerProfile;
struct PlayerProfileMenuContext;
/* Frame timer of the menu, in seconds. */
extern void CMenuProfile_ActivateFirstConfirmingPlayer(void);
extern s32 CMenuProfile_ResetPlayerControllerProfile(s32 entry, struct PlayerProfileMenuContext *menu);
extern s32 CMenuProfile_HasSavedRoundProgress(void);
extern s32 CMenuProfile_UpdateRoundEndDelay(void);
extern s32 CMenuProfile_HasRoundProgress(void);
extern void CMenuProfile_ResetRoundEndDelay(void);
extern struct ControllerProfile *CMenuProfile_FindConfirmingController(s32 *out);
extern s32 CMenuProfile_ControllerSelectionReturnZero(void);
extern s32 CMenuProfile_SetFirstResultLabel(struct MenuBuildEntry *labelItem);
extern s32 CMenuProfile_SetSecondResultLabel(struct MenuBuildEntry *labelItem);
#endif
