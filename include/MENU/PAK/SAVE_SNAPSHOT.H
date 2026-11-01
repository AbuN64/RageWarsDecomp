#ifndef MENU_PAK_SAVE_SNAPSHOT_H
#define MENU_PAK_SAVE_SNAPSHOT_H
#include "TYPES.H"
/* The Controller Pak game snapshot Snapshot_CreateSaveSnapshot fills: a header, the 0x70-byte player block,
 * the 0x584-byte world copy and a 4-byte name. g_worldSnapshotNoteBytes bytes of note data follow it, so a saved
 * snapshot note is g_worldSnapshotNoteBytes + sizeof(SaveSnapshot) bytes (Snapshot_SaveSnapshotAndClose, Snapshot_CheckControllerPak). */
typedef struct Copy70 { s32 words[28]; } Copy70;
typedef struct Copy584 { s32 words[353]; } Copy584;
typedef struct SaveSnapshot {
    s32 size;
    s32 dataSize;
    f32 view[4];
    Copy70 player;
    Copy584 world;
    u8 name[4];
} SaveSnapshot;
/* The snapshot being saved; Snapshot_SaveSnapshotAndClose and the pak menu exits clear it. */
extern SaveSnapshot *g_pakSaveSnapshot;
#endif
