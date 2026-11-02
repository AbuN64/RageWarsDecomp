#include "TYPES.H"

extern char g_defaultActorCollisionInfo[];

#include "DATA/ACTION_CALLBACKS/BREAKABLE_PROXIMITY_AND_HEALTH_CALLBACK_ADDRESSES.H"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CD4C4_unclaimed_CE0F0_unclaimed_CE104_unclaimed_CE10C */
#if defined(VERSION_US_REV1)
void * g_ActorStateAnimationFragmentEncodedWords[3] = {
    (void *)&addrLow_Action_UpdateBreakableProximity, (void *)&g_defaultActorCollisionInfo, (void *)&addrLow_Actionai_UpdateHealthFlag
};
#endif

/* ROM-grounded data: src/rw_actor_state_animation_CE118_us_rev1.c */
#if defined(VERSION_US_REV1)
struct {
    f32 scale;
    s32 threshold;
    u32 flags;
} g_overlayThreeActorStateAnimationFragment10 __attribute__((aligned(4))) = {
    1.0f,
    0,
    0x0
};
typedef char g_overlayThreeActorStateAnimationFragment10SizeCheck[(sizeof(g_overlayThreeActorStateAnimationFragment10) == 12) ? 1 : -1];
#endif
#endif
