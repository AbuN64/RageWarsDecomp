#include "TYPES.H"

#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* behavior kind (0-8) per actor type, two weapon gears each: indexed [selectedAction * 2 + gear - 1] and switched on by Portal_DispatchActorBehavior */
s32 g_actorBehaviorDispatchModes[40] = {
    0, 4,
    0, 3,
    1, 0,
    5, 5,
    0, 3,
    0, 2,
    6, 6,
    1, 0,
    1, 8,
    0, 3,
    0, 8,
    0, 8,
    7, 7,
    1, 4,
    5, 5,
    0, 3,
    0, 8,
    0, 8,
    0, 8,
    0, 8,
};
#endif
