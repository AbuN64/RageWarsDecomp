#ifndef MENU_SMP_RECORDS_H
#define MENU_SMP_RECORDS_H
#include "types.h"

typedef struct SmpControlItemView {
    s32 pad0;
    struct SmpControlItemView *next;
    char pad8[0xE - 8];
    u16 kind;
    u8 alpha;
} SmpControlItemView;

typedef struct SmpControlItemListView {
    char pad0[8];
    struct SmpControlItemView *items;
    char padC[0x54 - 0xC];
    s32 state;
} SmpControlItemListView;

struct Key {
    u8 text[20];
};

typedef struct Key Key;

struct SmpButtonOwnerView {
    char pad[0x38];
    struct Key *selected;
};

struct SmpOverlaySlotsView {
    char pad[0x4C];
    struct WidgetNode *values[1];
};

struct Access_s32_5C {
    char pad[0x5C];
    s32 field;
};

typedef struct Access_s32_5C Access_s32_5C;

struct StateBlock {
    char pad0[0x84];
    s32 flickerPending;
};

typedef struct StateBlock StateBlock;

struct ResourceSmpFlickerCreateFlickerWidget {
    char pad[0x10];
    unsigned char value;
    char pad11[0x1B];
    signed int frame;
};

typedef struct ResourceSmpFlickerCreateFlickerWidget ResourceSmpFlickerCreateFlickerWidget;

#endif
