#include "TYPES.H"

#include "DATA/ACTION_CALLBACKS/DEVICE_SPAWN_AND_MOTION_ROM_ENTRIES.H"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CD4C4_unclaimed_CE0F0_unclaimed_CE104_unclaimed_CE10C_unclaimed_CE124_unclaimed_CE130_unclaimed_CE144_unclaimed_CE148_unclaimed_CE1F8_unclaimed_CE210_unclaimed_CE21C_unclaimed_CE230_unclaimed_CE234_unclaimed_CE29C_unclaimed_CE2B0_unclaimed_CE2B4_unclaimed_CE2D0_unclaimed_CE2D4_unclaimed_CE2F0_unclaimed_CE2F4_unclaimed_CE3C8_unclaimed_CE3DC_unclaimed_CE3E0_unclaimed_CE3FC_unclaimed_CE400 */
unsigned int g_ActorStateEntryFragmentEncodedWords[24] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, (unsigned int)addrLow_SpawnAI_InitializeActorDispatch,
    (unsigned int)addrLow_SpawnAI_InitializeActionDelay, 0x00000000, 0x00000000, (unsigned int)addrLow_MovingAI_SetActorStateActive, (unsigned int)addrLow_MovingAI_EnableTriggerActor, (unsigned int)addrLow_MovingAI_ClearActorStateActive, (unsigned int)addrLow_MovingAI_DisableTriggerActor, 0x41D70A3E,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

/* ROM-grounded data: src/rw_actor_state_entry_CE460_us_rev1.c */
#if defined(VERSION_US_REV1)
char g_overlayThreeActorStateEntryFragment6[12] __attribute__((aligned(4))) = "\000\000\000\000\000\000\000\000\000 gd";
#endif
#endif
