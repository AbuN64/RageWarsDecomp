#ifndef MENU_SNAPSHOT_SAVECONTROLLERRECORD_H
#define MENU_SNAPSHOT_SAVECONTROLLERRECORD_H
#include "types.h"
struct Shared_PakMenu;
struct PakPromptContext;
extern s32 Snapshot_SaveControllerRecord(s32 owner, struct Shared_PakMenu *menu, s32 unusedEvent);
extern s32 Snapshot_SaveSnapshotAndClose(void *owner, struct Shared_PakMenu *menu);
#endif
