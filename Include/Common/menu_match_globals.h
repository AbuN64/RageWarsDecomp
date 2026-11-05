#ifndef COMMON_MENU_MATCH_GLOBALS_H
#define COMMON_MENU_MATCH_GLOBALS_H
#include "Ai/Playerai/playerai_playerai.h"
#include "types.h"
#include "Common/gameplay_camera.h"

struct MenuMatchGlobals;
struct GameplayCamera;
/* The retained match-state consumers identify the same resident root:
 * US-rev1 g_frontendScreenStatus, input byte +0x125D, status word +0x180C.
 * These are persistent state fields, with the actual root storage between. */
/* Match game-mode switches: the reaction messages pick their text from these. */
typedef struct MatchModes {
    u8 unobserved0[84];
    s32 tag; /* +0x54: tag match (US-rev1 0x801468F4) */
    u8 unobserved58[0x78 - 0x58];
    s32 captureFlag; /* +0x78: capture-the-flag match (US-rev1 0x80146918) */
    u8 unobserved7C[0xAC - 0x7C];
    s32 remoteSession; /* +0xAC: nonzero when the round runs for a remote player; Player_ResetPlayerForRound copies it to the actor */
} MatchModes;
typedef struct MenuMatchGlobals {
    u8 unobserved0[32];
    struct GameplayCamera *cameras; /* 0x20 */
    u8 unobserved24[0x40 - 0x24];
    GameplayCamera fallbackCamera; /* 0x40 */
    u8 unobservedF18[0x1200 - 0xF18];
    s32 useFallbackCamera; /* 0x1200 */
    u8 unobserved1204[4];
    s32 suppressFlaggedActions; /* Playerai_ToggleActionFlagMode / SelectAlternateWeapon */
    u8 unobserved120C[0x1240 - 0x120C];
    MenuSettings settings; /* 0x1240, menu input byte at settings.local (+0x125D) */
    u8 unobserved17C4[0x17F0 - 0x17C4];
    s32 status[8];
    u8 unobserved1810[0x1818 - 0x1810];
    MatchModes modes; /* 0x1818 */
} MenuMatchGlobals;
extern struct MenuMatchGlobals g_frontendScreenStatus;
#endif
