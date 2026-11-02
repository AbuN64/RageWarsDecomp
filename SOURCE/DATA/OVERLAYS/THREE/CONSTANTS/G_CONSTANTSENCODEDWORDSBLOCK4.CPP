#include "TYPES.H"


#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CD4C4_unclaimed_CE0F0_unclaimed_CE104_unclaimed_CE10C_unclaimed_CE124_unclaimed_CE130_unclaimed_CE144_unclaimed_CE148_unclaimed_CE1F8_unclaimed_CE210_unclaimed_CE21C_unclaimed_CE230_unclaimed_CE234_unclaimed_CE29C_unclaimed_CE2B0_unclaimed_CE2B4_unclaimed_CE2D0_unclaimed_CE2D4_unclaimed_CE2F0_unclaimed_CE2F4_unclaimed_CE3C8_unclaimed_CE3DC_unclaimed_CE3E0_unclaimed_CE3FC_unclaimed_CE400_unclaimed_CE46C_unclaimed_CE480_unclaimed_CE484 */
extern char addrLow_MovingAI_InitializeMotionDispatch[];
extern char addrLow_MovingAI_InitializeDeviceHealth[];
extern char addrLow_Triggered_StartTriggerAnimation[];
extern char addrLow_Triggered_ClearCollisionAndActivate[];
extern char addrLow_Triggered_EnableTriggeredActorState[];
extern char addrLow_Triggered_DeactivateForSequence[];
extern char addrLow_Triggered_DisableTriggeredActorState[];
extern char addrLow_Triggered_SetPairedDefinitionBytes[];
extern char addrLow_Link_RequestOwnerTrack[];
extern char addrLow_Link_RequestGlobalTrack[];
extern char addrLow_Link_DispatchTriggerAudio[];
extern char addrLow_Link_PlayTriggerSoundCallback[];
extern char addrLow_Link_SelectTriggerMusic[];
extern char addrLow_Link_PlayTriggerSound[];
extern char addrLow_Link_SetTriggerTrackCallback[];
extern char addrLow_Link_SetTriggerTrack[];
#if defined(VERSION_US_REV1)
void * g_ConstantsEncodedWordsBlock4[35] = {
    0, 0, 0, 0, 0, 0, 0, (void *)&addrLow_MovingAI_InitializeMotionDispatch,
    (void *)&addrLow_MovingAI_InitializeDeviceHealth, 0, 0, (void *)&addrLow_Triggered_StartTriggerAnimation, 0, (void *)&addrLow_Triggered_ClearCollisionAndActivate, (void *)&addrLow_Triggered_EnableTriggeredActorState, (void *)&addrLow_Triggered_DeactivateForSequence,
    (void *)&addrLow_Triggered_DisableTriggeredActorState, (void *)&addrLow_Link_RequestOwnerTrack, (void *)&addrLow_Link_RequestGlobalTrack, (void *)&addrLow_Link_PlayTriggerSoundCallback, (void *)&addrLow_Link_PlayTriggerSound, (void *)&addrLow_Link_DispatchTriggerAudio, (void *)&addrLow_Link_SelectTriggerMusic, (void *)&addrLow_Link_SetTriggerTrackCallback,
    (void *)&addrLow_Link_SetTriggerTrack, (void *)&addrLow_Triggered_SetPairedDefinitionBytes, 0, 0, 0, 0, 0, 0,
    0, 0, 0
};
#endif

/* ROM-grounded data: src/rw_actor_state_entry_CE510_us_rev1.c */
extern char addrLow_PlayerMatrix_ClearUnsupportedOpenFlag[];
extern char addrLow_PlayerMatrix_UpdateOpeningDelay[];
#if defined(VERSION_US_REV1)
void * g_ConstantsEncodedWordsBlock11[3] = {
    0, (void *)&addrLow_PlayerMatrix_ClearUnsupportedOpenFlag, (void *)&addrLow_PlayerMatrix_UpdateOpeningDelay
};
#endif
#endif
