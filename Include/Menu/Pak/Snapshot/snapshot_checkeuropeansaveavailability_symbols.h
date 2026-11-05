#ifndef MENU_PAK_SNAPSHOT_SNAPSHOT_CHECKEUROPEANSAVEAVAILABILITY_SYMBOLS_H
#define MENU_PAK_SNAPSHOT_SNAPSHOT_CHECKEUROPEANSAVEAVAILABILITY_SYMBOLS_H
#include "Frontend/frontend_address_symbols.h"
#include "Common/sessionhandlerrow.h"
#include "types.h"
extern s32 g_worldSnapshotNoteBytes;
extern char g_pakDialogDamagedPak[];
extern char g_pakDialogIdRepair_SnapshotCheckeuropeansaveavailability[];
#if (defined(VERSION_DE))
extern s32 g_pakSnapshotNoPakPromptDe, g_pakSnapshotNoControllerPromptDe, g_pakSnapshotCapacityPromptDe, g_pakSnapshotLowSpacePromptDe;
#endif
#if !((defined(VERSION_DE))) && (defined(VERSION_US))
extern s32 g_pakSnapshotNoPakPromptUs, g_pakSnapshotNoControllerPromptUs, g_pakSnapshotCapacityPromptUsRevision, g_pakSnapshotLowSpacePromptUs;
#endif
#if !((defined(VERSION_DE))) && !((defined(VERSION_US))) && (defined(VERSION_EU))
extern s32 g_pakSnapshotNoPakPromptEu, g_pakSnapshotNoControllerPromptEu, g_pakSnapshotCapacityPromptEu, g_pakSnapshotLowSpacePromptEu;
#endif
#if !((defined(VERSION_DE))) && !((defined(VERSION_US))) && !((defined(VERSION_EU))) && (defined(VERSION_EU_X))
extern s32 g_pakSnapshotNoPakPromptEuX, g_pakSnapshotNoControllerPromptEuX, g_pakSnapshotCapacityPromptEu, g_pakSnapshotLowSpacePromptEuX;
#endif
#if (defined(VERSION_EU) || defined(VERSION_EU_X))
extern char *g_pakSnapshotGameNames[];
#endif
#endif
