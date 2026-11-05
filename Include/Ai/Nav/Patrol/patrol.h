#ifndef AI_NAV_PATROL_PATROL_H
#define AI_NAV_PATROL_PATROL_H
#include "types.h"
#include "Common/small_records.h"

struct Clip;
struct Clip {
    s16 mode;
    s16 frames;
};
typedef struct Clip Clip;

struct PatrolActor;
extern void Nav_UpdatePatrolRoute(struct PatrolActor *actor);
#endif
