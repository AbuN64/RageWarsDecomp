#include "TYPES.H"

extern char g_defaultActorCollisionInfo[];

#include "DATA/ACTION_CALLBACKS/DAMAGEAI_GETDEFINITIONVALUE.H"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CD4C4_unclaimed_CE0F0_unclaimed_CE104_unclaimed_CE10C_unclaimed_CE124_unclaimed_CE130_unclaimed_CE144_unclaimed_CE148_unclaimed_CE1F8_unclaimed_CE210_unclaimed_CE21C_unclaimed_CE230_unclaimed_CE234_unclaimed_CE29C_unclaimed_CE2B0_unclaimed_CE2B4_unclaimed_CE2D0_unclaimed_CE2D4 */
#if defined(VERSION_US_REV1)
void * g_ActorStateAnimationFragmentEncodedWordsBlock2[4] = {
    (void *)&addrLow_Device_RespondToActivation, (void *)&addrLow_Device_ClearCollisionFlagsOnHit, (void *)&g_defaultActorCollisionInfo, (void *)&addrLow_DamageAI_GetDefinitionValue
};
#endif

/* ROM-grounded data: src/rw_actor_state_animation_CE2E4_us_rev1.c */
#if defined(VERSION_US_REV1)
struct {
    f32 scale;
    s32 threshold;
    u32 flags;
} g_overlayThreeActorStateAnimationFragment4 __attribute__((aligned(4))) = {
    1.0f,
    0,
    0x0
};
typedef char g_overlayThreeActorStateAnimationFragment4SizeCheck[(sizeof(g_overlayThreeActorStateAnimationFragment4) == 12) ? 1 : -1];
#endif
#endif
