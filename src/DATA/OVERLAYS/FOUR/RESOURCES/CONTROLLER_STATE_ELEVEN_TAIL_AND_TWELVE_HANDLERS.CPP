#include "TYPES.H"

#include "DATA/ACTOR_STATE_CALLBACKS/ACTOR_STATE_CALLBACK_LABELS.H"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CDA3C_unclaimed_CE6E0_unclaimed_CE750_unclaimed_CEBCC_unclaimed_CEC6C_unclaimed_CEC8C_unclaimed_CECAC_unclaimed_CECCC_unclaimed_CECEC_unclaimed_CED0C_unclaimed_CED2C_unclaimed_CED4C_unclaimed_CED6C_unclaimed_CED8C_unclaimed_CEDAC_unclaimed_CEDCC */
#if defined(VERSION_US_REV1)
struct {
    u32 reserved[2];
    f32 scale;
    s32 threshold;
    u32 flags;
} g_controllerState11TrailerWords __attribute__((aligned(4))) = {
    { 0x00000000, 0x00000000 },
    1.0f,
    5,
    0x00000000
};
#endif

#if defined(VERSION_US_REV1)
struct {
    s32 id;
    void * enter;
    void * update;
} g_controllerState12HandlerWords __attribute__((aligned(4))) = {
    12,
    (void *)&addrLow_Nav_InitNearbyUnrestrictedGoal,
    (void *)&addrLow_Nav_SeekNearbyUnrestrictedGoal
};
#endif
#endif
