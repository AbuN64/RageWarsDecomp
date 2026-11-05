#if defined(VERSION_US_REV1)

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


struct {
    u32 header;
    unsigned int callbacks[2];
    void *auxiliary;
    s32 timer;
    s32 parameter;
} g_playerNormalLateStates[14] __attribute__((aligned(4))) = {
    { 0x00010000, { (unsigned int)g_playerSequenceRunEndUpdateCallbackRecords[7], (unsigned int)&addrLow_Playerai_StartFallingDeathSequence_us }, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7004 }, /* rom 0xCF7DC */
    { 0x00010000, { (unsigned int)&g_playerLateStateLinkRecordLeadingTarget, 0 }, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 0 }, /* rom 0xCF7F4 */
    { 0x00010000, { (unsigned int)&Playerai_InitializeActorModelEffect, (unsigned int)&g_PlayerInterpolateTravelTargetCallbackAddressUs }, (void *)&g_collisionSurfaceExcludedFromTrace[64], 0, 2030 }, /* rom 0xCF80C */
    { 0x00010000, { (unsigned int)&Playerai_ClearPlayerWeaponLock, (unsigned int)&Playerai_EnterMovingSequenceState }, (void *)((char *)&g_portalDefaultCollisionQuery + 32), 32768, 2010 }, /* rom 0xCF824 */
    { 0x00020000, { (unsigned int)&g_playerStateLinkRecordRomLinkTarget_ResetPlayerWeaponLock, (unsigned int)&g_playerStateLinkRecordRomLinkTarget_EnterStoppedSequenceState }, (void *)((char *)&g_portalDefaultCollisionQuery + 32), 32768, 2010 }, /* rom 0xCF83C */
    { 0x00030000, { (unsigned int)&Playerai_OffsetActorForForceMarker, (unsigned int)&g_PlayerUpdateHeldActorReleaseCallbackAddressUs }, (void *)&g_secondaryCollisionContext[32], 0, 9200 }, /* rom 0xCF854 */
    { 0x00020000, { (unsigned int)&g_playerLateStateEmptyHookAddress, (unsigned int)&g_PlayerTrackNearbyAimTargetCallbackAddressUs }, (void *)&g_secondaryCollisionContext[32], 0, 1 }, /* rom 0xCF86C */
    { 0x00020000, { (unsigned int)&g_playerLateStateNoOperationPairLeadingTarget, (unsigned int)&g_playerStateNoOperationCallbackWords[0x2C9] }, (void *)&g_secondaryCollisionContext[32], 0, 1 }, /* rom 0xCF884 */
    { 0x00020000, { (unsigned int)&addrLow_Playerai_UpdateChestbursterDeathSequenceWait_us, (unsigned int)&addrLow_Playerai_StartSwimmingChestbursterDeathSequence_us }, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7043 }, /* rom 0xCF89C */
    { 0x00010000, { (unsigned int)&addrLow_Playerai_UpdateSwimmingChestbursterDeathSequenceWait_us, (unsigned int)&addrLow_Playerai_StartRaptorChestbursterDeathSequence_us }, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7044 }, /* rom 0xCF8B4 */
    { 0x00010000, { (unsigned int)&addrLow_Playerai_UpdateRaptorChestbursterDeathSequenceWait_us, (unsigned int)&addrLow_Playerai_StartSwimmingRaptorChestbursterDeathSequence_us }, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7045 }, /* rom 0xCF8CC */
    { 0x00010000, { (unsigned int)&addrLow_Playerai_UpdateSwimmingRaptorChestbursterDeathSequenceWait_us, (unsigned int)&g_Playerai_InitializeActorModelEffectCallbackAddressUs }, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7046 }, /* rom 0xCF8E4 */
    { 0x00010000, { (unsigned int)&Playerai_NoopBastilleSquatStart, (unsigned int)&Playerai_NoopBastilleSquatUpdate }, (void *)&g_secondaryCollisionContext[32], 0, 23300 }, /* rom 0xCF8FC */
    { 0x00020000, { (unsigned int)&g_playerStateNoOperationCallbackWords[0x2F5], (unsigned int)&g_PlayerSetRunEndFlagCallbackAddressDe }, (void *)&g_secondaryCollisionContext[32], 0, 23301 }, /* rom 0xCF914 */
};
#endif
