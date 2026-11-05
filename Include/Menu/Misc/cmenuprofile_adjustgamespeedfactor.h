#ifndef MENU_MISC_CMENUPROFILE_ADJUSTGAMESPEEDFACTOR_H
#define MENU_MISC_CMENUPROFILE_ADJUSTGAMESPEEDFACTOR_H
#include "Menu/playersettings.h"
struct PlayerDialogMenuContext;
extern s32 CMenuProfile_HasDialogRoundProgress(void);
extern s32 CMenuProfile_OpenAlternatePlayerDialog(void *entry, struct PlayerDialogMenuContext *menuContext);
extern s32 CMenuProfile_OpenPrimaryPlayerDialog(void *entry, struct PlayerDialogMenuContext *menuContext);
#endif
