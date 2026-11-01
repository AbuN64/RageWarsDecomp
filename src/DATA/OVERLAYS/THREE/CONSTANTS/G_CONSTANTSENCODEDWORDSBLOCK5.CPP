#include "TYPES.H"


#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CD4C4_unclaimed_CE0F0_unclaimed_CE104_unclaimed_CE10C_unclaimed_CE124_unclaimed_CE130_unclaimed_CE144_unclaimed_CE148_unclaimed_CE1F8_unclaimed_CE210_unclaimed_CE21C_unclaimed_CE230_unclaimed_CE234_unclaimed_CE29C_unclaimed_CE2B0_unclaimed_CE2B4_unclaimed_CE2D0_unclaimed_CE2D4_unclaimed_CE2F0_unclaimed_CE2F4 */
extern char addrLow_DamageAI_InitializeDispatch[];
extern char addrLow_DamageAI_RequestCurrentActorState[];
extern char addrLow_Device_RequestAndSetActiveState[];
extern char addrLow_Device_EnableTriggerActor[];
extern char addrLow_Link_ClearActorFlagMask[];
extern char addrLow_Link_SetActorFlagMask[];
extern char addrLow_Link_CaptureActorTransform[];
extern char addrLow_Link_DeactivateActorState[];
extern char addrLow_Link_ClearActorStateBit[];
extern char addrLow_Link_SetActorStateBit[];
struct {
    unsigned int w0[27];
    unsigned short h1[30];
    unsigned int w2[8];
} D_blob_45a0bfc7f85d1dc84410 = {
    {
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        (unsigned int)addrLow_DamageAI_InitializeDispatch, (unsigned int)addrLow_DamageAI_RequestCurrentActorState, 0x00000000, 0x00000000,
        (unsigned int)addrLow_Device_RequestAndSetActiveState, (unsigned int)addrLow_Device_EnableTriggerActor, (unsigned int)addrLow_Link_ClearActorStateBit, 0x00000000,
        (unsigned int)addrLow_Link_SetActorStateBit, 0x00000000, (unsigned int)addrLow_Link_ClearActorFlagMask, 0x00000000,
        (unsigned int)addrLow_Link_SetActorFlagMask, 0x00000000, (unsigned int)addrLow_Link_CaptureActorTransform, 0x00000000,
        (unsigned int)addrLow_Link_DeactivateActorState, 0x00000000, 0x420A3D70, 0x3FDD2F1C,
    },
    {
        0xFFFF, 0x0000, 0xFFFF, 0x0000, 0x06A5, 0x03E8, 0x06A6, 0x01F4, 0x06A7, 0x000A, 0xFFFF, 0x0000,
        0x06A6, 0x01F4, 0x06A7, 0x000A, 0xFFFF, 0x0000, 0x06B8, 0x03E8, 0x06BA, 0x01F4, 0x06BB, 0x000A,
        0xFFFF, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000,
    },
    {
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    },
};

/* ROM-grounded data: src/rw_actor_state_entry_CE3BC_us_rev1.c */
extern char addrLow_MovingAI_ChooseTriggerDelay[];
extern char addrLow_MovingAI_UpdateTriggerDelay[];
#if defined(VERSION_US_REV1)
void * g_ConstantsEncodedWordsBlock5[3] = {
    0, (void *)&addrLow_MovingAI_ChooseTriggerDelay, (void *)&addrLow_MovingAI_UpdateTriggerDelay
};
#endif
#endif
