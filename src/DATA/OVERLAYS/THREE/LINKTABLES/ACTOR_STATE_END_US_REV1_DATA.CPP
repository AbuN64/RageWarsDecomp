#include "TYPES.H"


#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_actor_state_end_CE5B0_us_rev1.c */
#if defined(VERSION_US_REV1)
struct {
    s32 endState;
} g_actorStateEnd_us_rev1 __attribute__((aligned(4))) = {
    -1
};
typedef char g_actorStateEnd_us_rev1SizeCheck[(sizeof(g_actorStateEnd_us_rev1) == 4) ? 1 : -1];
#endif

/* ROM-grounded data: rodata/unresolved/800CD4C4_unclaimed_CE0F0_unclaimed_CE104_unclaimed_CE10C_unclaimed_CE124_unclaimed_CE130_unclaimed_CE144_unclaimed_CE148_unclaimed_CE1F8_unclaimed_CE210_unclaimed_CE21C_unclaimed_CE230_unclaimed_CE234_unclaimed_CE29C_unclaimed_CE2B0_unclaimed_CE2B4_unclaimed_CE2D0_unclaimed_CE2D4_unclaimed_CE2F0_unclaimed_CE2F4_unclaimed_CE3C8_unclaimed_CE3DC_unclaimed_CE3E0_unclaimed_CE3FC_unclaimed_CE400_unclaimed_CE46C_unclaimed_CE480_unclaimed_CE484_unclaimed_CE51C_unclaimed_CE530_unclaimed_CE53C_unclaimed_CE550_unclaimed_CE55C_unclaimed_CE570_unclaimed_CE57C_unclaimed_CE590_unclaimed_CE59C_unclaimed_CE5B0_unclaimed_CE5B4 */
extern char addrLow_Triggered_InitializeMotionState[];
extern char addrLow_Triggered_ResetMotionState[];
extern char addrLow_PlayerMatrix_RequestOpen[];
extern char addrLow_PlayerMatrix_RequestClose[];
extern char addrLow_PlayerMatrix_ActivateMotion[];
extern char addrLow_PlayerMatrix_EnableEventActor[];
extern char addrLow_PlayerMatrix_DeactivateMotion[];
extern char addrLow_PlayerMatrix_DisableEventActor[];
extern char addrLow_PlayerMatrix_EnableCollisionFlags[];
extern char addrLow_PlayerMatrix_MarkOpenAndResetTimer[];
extern char addrLow_PlayerMatrix_MarkCloseRequested[];
extern char addrLow_PlayerMatrix_ClearCollisionBit[];
extern char addrLow_Link_CaptureActorTransform[];
extern char addrLow_Link_DeactivateActorState[];
#if defined(VERSION_US_REV1)
void * g_ActorStateEndUsRev1EncodedWords[31] = {
    0, 0, 0, 0, 0, 0, 0, (void *)&addrLow_Triggered_InitializeMotionState,
    (void *)&addrLow_Triggered_ResetMotionState, 0, 0, (void *)&addrLow_PlayerMatrix_RequestOpen, 0, (void *)&addrLow_PlayerMatrix_RequestClose, 0, (void *)&addrLow_PlayerMatrix_DeactivateMotion,
    (void *)&addrLow_PlayerMatrix_DisableEventActor, (void *)&addrLow_PlayerMatrix_ActivateMotion, (void *)&addrLow_PlayerMatrix_EnableEventActor, (void *)&addrLow_PlayerMatrix_EnableCollisionFlags, 0, (void *)&addrLow_PlayerMatrix_MarkOpenAndResetTimer, 0, (void *)&addrLow_PlayerMatrix_MarkCloseRequested,
    0, (void *)&addrLow_PlayerMatrix_ClearCollisionBit, 0, (void *)&addrLow_Link_CaptureActorTransform, 0, (void *)&addrLow_Link_DeactivateActorState, 0
};
#endif
#endif
