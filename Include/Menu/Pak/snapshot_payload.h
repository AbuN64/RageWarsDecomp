#ifndef MENU_PAK_SNAPSHOT_PAYLOAD_H
#define MENU_PAK_SNAPSHOT_PAYLOAD_H
#include "types.h"
#include "Menu/Pak/save_snapshot.h"
#include "Menu/pak_preview_views.h"

/* A snapshot payload starts with its total length (the last word of that length is the stored checksum),
   followed by the number of note bytes it saved. */
typedef struct PakSnapshotHeader {
    s32 length;
    s32 noteBytes;
} PakSnapshotHeader;

/* The text value of a pak preview: a halfword shown as a number. */
struct PreviewTextValue {
    char pad[0x22];
    s16 value;
};

/* The block the Controller Pak menus currently work on. Each reader sees it as one record kind:
   the raw bytes read from a note, its header, the saved game snapshot, or a preview shown in the menu. */
typedef union ControllerPakPayload {
    u8 bytes[1];
    PakSnapshotHeader header;
    SaveSnapshot save;
    struct PakPreview preview;
    struct PreviewTextValue previewText;
} ControllerPakPayload;

/* The payload being read or restored; cleared when the note browser closes or a save ends. */
extern ControllerPakPayload *g_controllerPakSnapshotPayload;
#endif
