#ifndef DATA_OVERLAYS_CONTROLLER_LINKTABLES_ADDRESSES_H
#define DATA_OVERLAYS_CONTROLLER_LINKTABLES_ADDRESSES_H
/* Overlay symbols known only by address in the version symbol maps. */
extern char addrLow_Playerai_StartExplosiveDeathSequence_us[];
extern char addrLow_Playerai_StartRunningDeathSequence_us[];
extern char addrLow_Playerai_StartBackwardMovingDeathSequence_us[];
extern char addrLow_Playerai_StartClimbingDeathSequence_us[];
extern char addrLow_Playerai_StartQuicksandDeathSequence_us[];
extern char addrLow_Playerai_StartLavaDeathSequence_us[];
extern char addrLow_Playerai_StartPrimagenDeathSequence_us[];
extern char addrLow_Playerai_UpdateGroundDeathSequenceWait_us[];
extern char g_playerSequenceRunEndUpdateCallbackRecords[][0x38]; /* one 0x38-byte record per sequence-run-end row, base per version in symbol_addrs */
extern unsigned int g_playerStateNoOperationCallbackWords[]; /* player-state no-operation callback slots, word-indexed */
extern char g_playerUntimedStateEmptyHookAddress[];
extern char g_Player_AimPreviousPositionAtResetAddress_de_us_rev1[];
extern char addrLow_Playerai_ResetPlayerAfterDeath_us[];
extern char addrLow_Playerai_StartImpalementDeathSequence_us[];
extern char addrLow_Playerai_StartChestbursterDeathSequence_us[];
extern char addrLow_Playerai_UpdateImpalementDeathSequenceWait_us[];
extern char g_playerNormalAuxiliaryStateLeadingTarget[];
#endif
