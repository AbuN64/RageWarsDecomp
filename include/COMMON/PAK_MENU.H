#ifndef COMMON_PAK_MENU_H
#define COMMON_PAK_MENU_H
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
/* Controller Pak menu items are 0x28-byte records. */
struct PakNotesMenuItem {
    char pad0[8];
    u32 flags;
    char padC[0x1C];
};
/* Shared menu passed to note enumeration and note selection callbacks. */
typedef struct Shared_PakMenu {
    s16 state;
    char pad02[0xA];
    struct PakNotesMenuItem *items;
    char pad10[4];
    char *dialogData;
    char pad18[4];
    ActorOwnerView *player;
    union {
        PakMenuSlot *owner;
        PakMenuSlot *slot;
    };
    void *dialogText;
} Shared_PakMenu;
void Snapshot_MarkSaveNotes(Shared_PakMenu *menu);
#endif
