#ifndef MENU_PAK_SNAPSHOT_SNAPSHOT_CHECKSTATUSPROMPT_SYMBOLS_H
#define MENU_PAK_SNAPSHOT_SNAPSHOT_CHECKSTATUSPROMPT_SYMBOLS_H
#include "Frontend/frontend_address_symbols.h"
#include "Menu/Pak/Snapshot/snapshot_checkeuropeansaveavailability_symbols.h"
#include "Engine/geometry.h"
#include "types.h"
extern char g_pakChangeBusyDialog[], g_pakChannelNotReadyDialog_SnapshotCheckstatusprompt[], g_pakChannelReadyMessage_SnapshotCheckstatusprompt[], g_pakDialogDamagedPak[], g_pakScannedChannelReadyMessage[];
extern u8 g_controllerPakPreviewProfilePadAfterFlags, g_controllerPakPreviewProfilePadMiddle, g_controllerPakPreviewProfilePadBeforeName;
#if (defined(VERSION_EU) || defined(VERSION_EU_X))
extern char *g_pakCompanyCodes[];
extern char *g_pakSnapshotGameNames[];
#endif
#endif
