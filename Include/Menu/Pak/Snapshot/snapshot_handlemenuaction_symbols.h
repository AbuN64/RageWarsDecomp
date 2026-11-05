#ifndef MENU_PAK_SNAPSHOT_SNAPSHOT_HANDLEMENUACTION_SYMBOLS_H
#define MENU_PAK_SNAPSHOT_SNAPSHOT_HANDLEMENUACTION_SYMBOLS_H
#include "Data/Overlays/Menu/linktables_addresses.h"
#include "Menu/Pak/Snapshot/snapshot_checkeuropeansaveavailability_symbols.h"
#include "Frontend/frontend_address_symbols.h"
#include "types.h"
struct Digits;
extern char *g_pakEmptyNoteNameFixed;
extern struct Digits k_pakDigitsInitial;
extern u8 *g_pakSpaceLabelText;
extern u8 *g_pakSpaceLabelScannedText;
extern char g_pakOverwriteNoteDialogResource[];
#if (defined(VERSION_EU) || defined(VERSION_EU_X))
extern char *g_pakEmptyNoteNamesLocalized_eu[];
extern u8 *g_pakSpaceLabelScannedLocalized_eu[];
extern char *g_pakSnapshotGameNames[];
extern char g_pakOverwriteNoteDialogResource_eu[];
#endif
#endif
