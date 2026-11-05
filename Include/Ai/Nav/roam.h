#ifndef AI_NAV_ROAM_H
#define AI_NAV_ROAM_H
#include "types.h"
#include "Common/small_records.h"

struct PlayerProfileStatusView;
struct PlayerProfileStatusView {
    char pad0[0x80];
    s8 kind;
    char pad81[0x13];
    u8 display;
};

#include "Ai/source.h"
struct Shared_Actor;
extern void Nav_InitRoamingWithJumps(struct Shared_Actor *actor);
extern void Nav_ChooseNewRoamingGoal(void *actor);
extern void Nav_UpdateRoamingWithJumps(struct Shared_Actor *actor);
#endif
