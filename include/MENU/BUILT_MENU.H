#ifndef MENU_BUILT_MENU_H
#define MENU_BUILT_MENU_H
#include "TYPES.H"
#include <ultra64.h>
struct MessageList;
struct PakMenuInputStateView;
typedef struct MenuBuildState MenuBuildState;
typedef struct MenuBuildEntry MenuBuildEntry;
/* The hold result requests closing. Update results are ignored; activate returns
   zero to keep the menu open. Construction invokes that same activate callback. */
typedef s32 (*MenuBuildHoldCallback)(MenuBuildState *, void *);
typedef s32 (*MenuBuildItemCallback)(MenuBuildEntry *, MenuBuildState *, void *);
/* One row of a menu definition's item table (0x24 bytes). */
typedef struct MenuBuildItem {
    s16 type;
    u16 reserved02;
    u32 flags;
    s16 x, y;
    u8 red, green, blue, alpha;
    s32 resource;
    u32 resourceCallback; /* encoded cartridge callback */
    MenuBuildItemCallback update;
    MenuBuildItemCallback activate;
    s32 parameter;
} MenuBuildItem;
/* The definition a menu is built from: its item table and count, an optional setup callback and its
   screen position (unit view of struct Dialog). */
typedef struct MenuBuildDefinition {
    MenuBuildItem *items;
    s16 count;
    u16 reserved06;
    void (*initialize)(MenuBuildState *, struct MessageList *);
    void (*finalize)(MenuBuildState *, struct MessageList *);
    u32 drawCallback; /* encoded cartridge callback */
    MenuBuildHoldCallback hold;
    s16 x, y, kind;
    u16 reserved1E;
    s32 value;
} MenuBuildDefinition;
/* A live menu entry built from one item (0x28 bytes); `extra` points at its private block. */
struct MenuBuildEntry {
    s32 index;
    s16 type;
    u16 reserved06;
    u32 flags;
    s16 x, y;
    u8 red, green, blue, alpha;
    s32 resource;
    MenuBuildItem *definition;
    s32 selection;
    u8 *extra;
    MenuBuildState *menu;
};
/* The menu block: this header, then `count` entries, then the private blocks of the entries that
   need one. */
struct MenuBuildState {
    s16 selected, y, kind;
    u16 reserved06;
    void **allocation;
    MenuBuildEntry *entries;
    s32 count;
    MenuBuildDefinition *definition;
    s32 value18, value1C;
    struct PakMenuInputStateView *input;
    s32 value24;
    s16 state;
    u16 ownerSlot;
    f32 fade, openA, openB;
    s32 value38, value3C;
    void *context;
    struct MessageList *owner;
    Vtx_t vertices[2][8];
    u8 reserved148[0x1C8 - 0x148];
    s32 pulseFrame, pulseActive;
    u32 reserved1D0;
    MenuBuildState *next;
};
#endif
