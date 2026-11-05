#include "Common/packed_callback_symbols.h"
#include "Common/ccollisionsetup_t.h"
#include "Ai/player.h"
#include "Ai/Player/player_landing_and_motion_resets.h"
#include "Common/aiprofile.h"
#include "types.h"
#include "Ai/Player/playerai_offsetactorforforcemarker_data.h"
#include "Common/effectrender.h"
#include "Common/player_sequence_state.h"
#include "Data/Overlays/encoded_callback.h"
#include "Data/Overlays/Playerstate/constants_addresses.h"
#include "Data/Player_stun/player_resetstunflags.h"
#include "Data/Player_stun/player_stun_reset_address.h"

/* PLAYER_SPECIAL_STATE_17_AUXILIARY.CPP */
#if defined(VERSION_US_REV1)
void *g_playerSpecialAuxiliaryStateCollisionContextWord[1] = {
    (void *)&g_secondaryCollisionContext[6],
};
#endif

/* PLAYER_SPECIAL_STATE_17_TIMING.CPP */
#if defined(VERSION_US_REV1)
struct {
    s32 timer;
    s32 parameter;
} g_playerSpecialAuxiliaryStateTiming __attribute__((aligned(4))) = {
    1048576,
    24100
};
#endif

/* PLAYER_SPECIAL_UNTIMED_STATES.CPP */
#if defined(VERSION_US_REV1)
/* Player special states 18-21 without a timing pair, in ROM order: 24 bytes each, the auxiliary words zero after the first. */
struct {
    u32 header;
    unsigned int callbacks[2];
    void *auxiliary[3];
} g_playerSpecialUntimedStates[4] __attribute__((aligned(4))) = {
    { 0x00020000, { (unsigned int)addrLow_Playerai_ResetPlayerAfterDeath_us, (unsigned int)g_playerUntimedStateEmptyHookAddress }, { (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 0 } }, /* state 18 */
    { 0x00010000, { (unsigned int)&Player_ResetStunAndReleaseHandles, 0 }, { g_defaultActorCollisionInfo, 0, 0 } }, /* state 19 */
    { 0x00010000, { (unsigned int)Player_ResetStunFlags, (unsigned int)g_playerUntimedStateTrailingCallbackTarget }, { g_defaultActorCollisionInfo, 0, 0 } }, /* state 20 */
    { 0x00010000, { (unsigned int)Playerai_BeginRoundEndWait, ENCODED_CALLBACK_ADDRESS(Playerai_UpdateRoundEndWait) }, { g_defaultActorCollisionInfo, 0, 0 } }, /* state 21 */
};
#endif

/* PLAYER_SPECIAL_TIMED_STATES.CPP */
#if defined(VERSION_US_REV1)
/* Player special states 22-32 with a timing pair, in ROM order: 24 bytes each. */
struct {
    u32 header;
    unsigned int callbacks[2];
    void *auxiliary;
    s32 timer;
    s32 parameter;
} g_playerSpecialTimedStates[11] __attribute__((aligned(4))) = {
    { 0x00010000, { (unsigned int)addrLow_Playerai_UpdateGroundDeathSequenceWait_us, (unsigned int)addrLow_Playerai_StartSequence50_us }, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7000 }, /* state 22 */
    { 0x00010000, { (unsigned int)g_playerSequenceRunEndUpdateCallbackRecords[1], (unsigned int)addrLow_Playerai_StartLavaDeathSequence_us }, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7100 }, /* state 23 */
    { 0x00010000, { (unsigned int)g_playerSequenceRunEndUpdateCallbackRecords[9], (unsigned int)addrLow_Playerai_StartImpalementDeathSequence_us }, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7101 }, /* state 24 */
    { 0x00010000, { (unsigned int)g_playerSequenceRunEndUpdateCallbackRecords[3], (unsigned int)addrLow_Playerai_StartSequence12_us }, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7200 }, /* state 25 */
    { 0x00010000, { (unsigned int)addrLow_Playerai_UpdateImpalementDeathSequenceWait_us, (unsigned int)addrLow_Playerai_StartChestbursterDeathSequence_us }, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7201 }, /* state 26 */
    { 0x00010000, { (unsigned int)g_playerSequenceRunEndUpdateCallbackRecords[2], (unsigned int)addrLow_Playerai_StartExplosiveDeathSequence_us }, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7400 }, /* state 27 */
    { 0x00010000, { (unsigned int)g_playerSequenceRunEndUpdateCallbackRecords[4], (unsigned int)addrLow_Playerai_StartRunningDeathSequence_us }, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7005 }, /* state 28 */
    { 0x00010000, { (unsigned int)g_playerSequenceRunEndUpdateCallbackRecords[5], (unsigned int)addrLow_Playerai_StartBackwardMovingDeathSequence_us }, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7500 }, /* state 29 */
    { 0x00010000, { (unsigned int)g_playerSequenceRunEndUpdateCallbackRecords[6], (unsigned int)addrLow_Playerai_StartClimbingDeathSequence_us }, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7505 }, /* state 30 */
    { 0x00010000, { (unsigned int)g_playerSequenceRunEndUpdateCallbackRecords[0], (unsigned int)addrLow_Playerai_StartQuicksandDeathSequence_us }, (void *)((char *)&g_supportingPlatformCollisionQuery + 4), 0, 7020 }, /* state 31 */
    { 0x00010000, { (unsigned int)g_playerSequenceRunEndUpdateCallbackRecords[8], (unsigned int)addrLow_Playerai_StartPrimagenDeathSequence_us }, (void *)((char *)&g_supportingPlatformCollisionQuery + 4), 0, 7010 }, /* state 32 */
};
#endif

/* PLAYER_SPECIAL_STATE_33_HEADER.CPP */
#if defined(VERSION_US_REV1)
u32 g_playerSpecialRunEndStateHeaderWord = 0x00010000;
#endif

/* PLAYER_SPECIAL_STATE_33_CALLBACKS.CPP */
#if defined(VERSION_US_REV1)
unsigned int g_playerSpecialRunEndThenSequenceStartCallbacks[2] = {
    (unsigned int)g_playerSequenceRunEndUpdateCallbackRecords[7],
    (unsigned int)addrLow_Playerai_StartFallingDeathSequence_us,
};
#endif
