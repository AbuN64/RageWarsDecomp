#include "TYPES.H"

#include "DATA/OVLTBL/ACTOR_MOTION_CALLBACK_ADDRESSES.H"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_actor_state_entry_CE570_us_rev1.c */
#if defined(VERSION_US_REV1)
struct {
    s32 id;
    void * enter;
    void * update;
} g_actorStateEntry9_us_rev1 __attribute__((aligned(4))) = {
    3,
    (void *)&g_actorStateEntry10_us_rev1,
    (void *)&g_actorStateEntry11_us_rev1
};
typedef char g_actorStateEntry9_us_rev1SizeCheck[(sizeof(g_actorStateEntry9_us_rev1) == 12) ? 1 : -1];
#endif
#endif
