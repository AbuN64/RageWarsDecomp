#include "TYPES.H"

#include "DATA/ACTION_CALLBACKS/ACTOR_STATE_CALLBACK_LABELS.H"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CD4C4_unclaimed_CE0F0_unclaimed_CE104_unclaimed_CE10C_unclaimed_CE124_unclaimed_CE130_unclaimed_CE144_unclaimed_CE148_unclaimed_CE1F8_unclaimed_CE210_unclaimed_CE21C_unclaimed_CE230_unclaimed_CE234_unclaimed_CE29C_unclaimed_CE2B0_unclaimed_CE2B4_unclaimed_CE2D0_unclaimed_CE2D4_unclaimed_CE2F0_unclaimed_CE2F4_unclaimed_CE3C8_unclaimed_CE3DC_unclaimed_CE3E0 */
#if defined(VERSION_US_REV1)
struct {
    void * enter;
    void * update;
    void * reserved;
    s32 animation;
} g_ActorStateAnimationFragmentEncodedWordsBlock3 __attribute__((aligned(4))) = {
    (void *)&addrLow_SpawnAI_DispatchSpawnChoice,
    (void *)&addrLow_MovingAI_RequestInactiveOnEvent,
    0,
    21210
};
typedef char g_ActorStateAnimationFragmentEncodedWordsBlock3SizeCheck[(sizeof(g_ActorStateAnimationFragmentEncodedWordsBlock3) == 16) ? 1 : -1];
#endif

/* ROM-grounded data: src/rw_actor_state_animation_CE3F0_us_rev1.c */
#if defined(VERSION_US_REV1)
struct {
    f32 scale;
    s32 threshold;
    u32 flags;
} g_overlayThreeActorStateAnimationFragment7 __attribute__((aligned(4))) = {
    1.0f,
    0,
    0x400
};
typedef char g_overlayThreeActorStateAnimationFragment7SizeCheck[(sizeof(g_overlayThreeActorStateAnimationFragment7) == 12) ? 1 : -1];
#endif
#endif
