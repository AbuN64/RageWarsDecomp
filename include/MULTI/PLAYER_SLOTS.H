#ifndef MULTI_PLAYER_SLOTS_H
#define MULTI_PLAYER_SLOTS_H
#include "TYPES.H"

/* The four 2920-byte multiplayer slot records the Ovldat10 overlay code walks; only the state word is read here.
   The state names are read off how the counting functions treat them (0 unused, 14 staged, 17 released). */
enum {
    PLAYER_SLOT_EMPTY = 0,
    PLAYER_SLOT_STAGED = 14,
    PLAYER_SLOT_RELEASED = 17
};

typedef struct PlayerSlot {
    u8 head[0x58];
    s32 state;
    u8 tail[0xB68 - 0x5C];
} PlayerSlot;

typedef struct PlayerSlotTable {
    PlayerSlot slots[4];
} PlayerSlotTable;

extern PlayerSlotTable *g_playerSlotTable;
#endif
