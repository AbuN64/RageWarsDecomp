#include "TYPES.H"

extern char g_defaultActorCollisionInfo[];

#include "DATA/ACTION_CALLBACKS/MOVINGAI_GETDEVICEHEALTH_ADDRESS.H"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CD4C4_unclaimed_CE0F0_unclaimed_CE104_unclaimed_CE10C_unclaimed_CE124_unclaimed_CE130_unclaimed_CE144_unclaimed_CE148_unclaimed_CE1F8_unclaimed_CE210_unclaimed_CE21C_unclaimed_CE230_unclaimed_CE234_unclaimed_CE29C_unclaimed_CE2B0_unclaimed_CE2B4_unclaimed_CE2D0_unclaimed_CE2D4_unclaimed_CE2F0_unclaimed_CE2F4_unclaimed_CE3C8_unclaimed_CE3DC_unclaimed_CE3E0_unclaimed_CE3FC_unclaimed_CE400_unclaimed_CE46C */
#if defined(VERSION_US_REV1)
void * g_ConstantsEncodedWordsBlock6[2] = {
    (void *)&g_defaultActorCollisionInfo, (void *)&addrLow_MovingAI_GetDeviceHealth
};
#endif
#endif
