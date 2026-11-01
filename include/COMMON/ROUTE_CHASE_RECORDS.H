#ifndef COMMON_ROUTE_CHASE_RECORDS_H
#define COMMON_ROUTE_CHASE_RECORDS_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
/* Chase and patrol records retained by the legacy US revision C and its exact
 * native identity measurements. Named members preserve those measured offsets. */
typedef struct RouteChaseThing {
    u8 pad0[8];
    CVector3 pos;
} RouteChaseThing;
typedef struct RouteChaseBot {
    RouteChaseThing *self;
    s32 node;
    u8 pad8[4];
    s32 goal;
    u8 pad10[0x1C];
    CVector3 dest;
    u8 pad38[0x30];
    RouteChaseThing *target;
    u8 pad6C[0x28];
    s8 routeReady; /* 0x94 */
    u8 pad95[0x27];
    s32 targetId;
    u8 padC0[0x160];
    s32 resetWord220;
    s32 resetWord224;
    u8 pad228[0x10];
    s32 arrived;
} RouteChaseBot;
typedef struct RouteChasePlayer {
    u8 pad0[0x1454];
    RouteChaseBot *bot;
} RouteChasePlayer;
typedef struct RouteChaseActor {
    u8 pad0[0x1D8];
    RouteChasePlayer *player;
} RouteChaseActor;
typedef struct RouteChaseGraph RouteChaseGraph;
typedef struct RoutePatrolNodes {
    u8 pad0[4];
    s32 count;
} RoutePatrolNodes;
#endif
