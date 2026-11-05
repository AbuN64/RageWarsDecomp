#ifndef DATA_OVERLAYS_PLAYERSTATE_LINKTABLES_ADDRESSES_H
#define DATA_OVERLAYS_PLAYERSTATE_LINKTABLES_ADDRESSES_H
/* Overlay symbols known only by address in the version symbol maps. */
extern char g_PlayerInterpolateTravelTargetCallbackAddressUs[];
extern char g_PlayerSetRunEndFlagCallbackAddressDe[];
extern char g_playerLateStateEmptyHookAddress[];
extern char g_playerSequenceRunEndUpdateCallbackRecords[][0x38]; /* one 0x38-byte record per sequence-run-end row, base per version in symbol_addrs */
extern unsigned int g_playerStateNoOperationCallbackWords[]; /* player-state no-operation callback slots, word-indexed */
extern char g_PlayerTrackNearbyAimTargetCallbackAddressUs[];
extern char g_PlayerUpdateHeldActorReleaseCallbackAddressUs[];
extern char g_Playerai_InitializeActorModelEffectCallbackAddressUs[];
extern char addrLow_Playerai_StartRaptorChestbursterDeathSequence_us[];
extern char addrLow_Playerai_StartSwimmingRaptorChestbursterDeathSequence_us[];
extern char addrLow_Playerai_UpdateSwimmingChestbursterDeathSequenceWait_us[];
extern char addrLow_Playerai_UpdateRaptorChestbursterDeathSequenceWait_us[];
extern char addrLow_Playerai_UpdateSwimmingRaptorChestbursterDeathSequenceWait_us[];
extern char g_playerLateStateNoOperationPairLeadingTarget[];
#endif
