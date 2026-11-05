#include "types.h"
#include "Ai/player_team_score.h"
#include "Common/aiprofile.h"
#include "Common/effectrender.h"
#include "Common/player_action_and_pose_views.h"
#include "Common/player_sequence_state.h"
#include "Common/runtime_declarations.h"
#include "Data/Overlays/Playerstate/resources_addresses.h"
#include "Data/Player_callbacks/playerstate_callback_rom_entry.h"
#include "Data/Player_callbacks/playerstate_link_record_rom_link_targets.h"
#include "Data/Player_callbacks/player_empty_action_hook_addresses.h"
#include "Data/Player_callbacks/player_sequence_callback_addresses.h"

/* PLAYER_NORMAL_LATE_STATES.CPP */
#if defined(VERSION_US_REV1)
/* Player normal states 33-46, in ROM order: 24 bytes each; a state without a timing pair has a 12-byte auxiliary, so its timer and parameter hold the zero words after the auxiliary pointer. */
extern struct {
    u32 header;
    unsigned int callbacks[2];
    void *auxiliary;
    s32 timer;
    s32 parameter;
} g_playerNormalLateStates[14] __attribute__((aligned(4)));
#endif

/* PLAYERAI_UPDATEWALKINGMOVEMENT_DATA.CPP */
#if defined(VERSION_US_REV1)
void * g_playerSpecialZeroVelocityFlyModeCallbacks[2] = {
    (void *)&g_Player_ZeroBodyVelocityAddress_us_rev1, (void *)&g_Player_UpdateFlyModeAddress_us_us_rev1
};
#endif

/* Pointer to entry 6 of the secondary collision context. */
#if defined(VERSION_US_REV1)
void *g_secondaryCollisionContextSlotPointer[1] = {
    (void *)&g_secondaryCollisionContext[6],
};
#endif

/* PLAYER_STATE_SPECIAL_TIMING_00_DATA.CPP */
#if defined(VERSION_US_REV1)
struct {
    s32 timer;
    s32 parameter;
} g_playerSpecialFlyModeTiming __attribute__((aligned(4))) = {
    0,
    1
};
#endif

/* PLAYER_STATE_SPECIAL_CALLBACKS_01_DATA.CPP */
#if defined(VERSION_US_REV1)
char g_playerSpecialFlyModeTrailerWords[8] __attribute__((aligned(4))) = "\000\000\000\000\000\"@x";
#endif
