#ifndef MENU_MISC_CMENUPROFILE_OPENTIMEDPLAYERDIALOG_H
#define MENU_MISC_CMENUPROFILE_OPENTIMEDPLAYERDIALOG_H
#include "MENU/PLAYERSETTINGS.H"
extern s32 CMenuProfile_OpenTimedPlayerDialog(void *unused0, Arg1Struct *menuContext);
extern void CMenuProfile_EnableControllerPakAndClearState(struct Shared_PakMenu *pakMenu);
extern void CMenuProfile_EnableOwnerControllerPak(ControllerPortOwnerView *menuOwner);
extern s32 CMenuProfile_HasProfileRoundProgress(void);
#endif
