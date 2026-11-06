#ifndef COMMON_GAME_PLAYER_AND_MENU_STATE_H
#define COMMON_GAME_PLAYER_AND_MENU_STATE_H
#include "types.h"
#include "Common/menu_match_globals.h"

struct SharedPlayer;

typedef struct SpecialPickupMatchModeView SpecialPickupMatchModeView;
struct SpecialPickupMatchModeView {
    char pad0[0x24];
    s32 teamMode;
    char pad28[0x2C];
    s32 flagPickupEnabled;
    char pad58[0x1C];
    s32 flagReturnState;
    char pad78[0x8];
    s32 flagCarried;
    s32 flagDropped;
};

typedef struct SpecialPickupLinkedPlayerOptions SpecialPickupLinkedPlayerOptions;
struct SpecialPickupLinkedPlayerOptions {
    char pad0[0x92];
    u8 team;
};

typedef struct SpecialPickupLinkedPlayerView SpecialPickupLinkedPlayerView;
struct SpecialPickupLinkedPlayerView {
    char pad0[0x5D8];
    struct SpecialPickupLinkedPlayerOptions * options;
    void * messageCamera;
    char pad5E0[0xBFC];
    f32 bonusDuration;
    char pad11E0[0x4C];
    s32 reactionFlags;
    char pad1230[0x4B0];
    struct SpecialPickupLinkedPlayerView * nextPlayer;
    char pad16E4[0x4];
};

/* g_gamePlayerAndMenuState is the game root: the player records, the list of active players, then the match globals
   g_frontendScreenStatus, whose modes block g_gameSettings.counters the pickup commands write. */
struct GamePlayerAndMenuState {
    struct SharedPlayer * entries; /* player records */
    s32 count;
    u8 pad8[0x14];
    struct SpecialPickupLinkedPlayerView * players; /* active players, linked through nextPlayer */
    u8 pad20[0x24];
    union {
        MenuMatchGlobals match; /* g_frontendScreenStatus */
        struct {
            u8 pad0[0x1818];
            SpecialPickupMatchModeView modes; /* g_gameSettings.counters */
        } view;
    } game __attribute__((packed, aligned(4))); /* The menu owner follows the player list directly, so it is not aligned to eight bytes. */
};

extern struct GamePlayerAndMenuState g_gamePlayerAndMenuState;

#endif
