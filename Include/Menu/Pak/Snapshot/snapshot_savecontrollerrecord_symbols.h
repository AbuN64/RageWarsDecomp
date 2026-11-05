#ifndef MENU_PAK_SNAPSHOT_SNAPSHOT_SAVECONTROLLERRECORD_SYMBOLS_H
#define MENU_PAK_SNAPSHOT_SNAPSHOT_SAVECONTROLLERRECORD_SYMBOLS_H
#include "Menu/Pak/Snapshot/snapshot_checkeuropeansaveavailability_symbols.h"
#include "Frontend/frontend_address_symbols.h"
#include "types.h"
#if !((defined(VERSION_EU) || defined(VERSION_EU_X))) && !((defined(VERSION_US_REV1))) && (defined(VERSION_US))
extern s32 g_pakSnapshotCapacityPromptUsRevision;
#endif
#if !((defined(VERSION_EU) || defined(VERSION_EU_X))) && !((defined(VERSION_US_REV1))) && !((defined(VERSION_US)))
#endif
#endif
