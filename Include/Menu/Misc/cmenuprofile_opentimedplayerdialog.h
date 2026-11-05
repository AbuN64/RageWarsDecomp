#ifndef MENU_MISC_CMENUPROFILE_OPENTIMEDPLAYERDIALOG_H
#define MENU_MISC_CMENUPROFILE_OPENTIMEDPLAYERDIALOG_H
#include "Menu/playersettings.h"
struct Arg1Struct;
struct ControllerPortOwnerView;
extern s32 CMenuProfile_OpenTimedPlayerDialog(void *entry, struct Arg1Struct *menuContext);
extern void CMenuProfile_EnableControllerPakAndClearState(struct Shared_PakMenu *pakMenu);
extern void CMenuProfile_EnableOwnerControllerPak(struct ControllerPortOwnerView *menuOwner);
extern s32 CMenuProfile_HasProfileRoundProgress(void);
typedef struct ControllerPortOwnerView {
    u8 pad0[0x20];
    struct ControllerPortView *controller;
} ControllerPortOwnerView;
typedef struct Arg1Struct {
    char pad0[0x1C];
    s32 player;
    char pad1[0x20 - 0x1C - 4];
    s32 controller;
} Arg1Struct;

#endif
