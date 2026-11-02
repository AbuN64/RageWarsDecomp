#include "TYPES.H"

extern char g_defaultActorCollisionInfo[];

#include "DATA/ACTION_CALLBACKS/DAMAGEAI_GETACTIVATIONSOUND.H"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CD4C4_unclaimed_CE0F0_unclaimed_CE104_unclaimed_CE10C_unclaimed_CE124_unclaimed_CE130_unclaimed_CE144_unclaimed_CE148_unclaimed_CE1F8_unclaimed_CE210_unclaimed_CE21C_unclaimed_CE230_unclaimed_CE234_unclaimed_CE29C */
#if defined(VERSION_US_REV1)
void * g_ConstantsEncodedWordsBlock8[2] = {
    (void *)&g_defaultActorCollisionInfo, (void *)&addrLow_DamageAI_GetActivationSound
};
#endif
#endif
