#ifndef COMMON_REC_H
#define COMMON_REC_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"





union TriggeredPathActorPositionWords;
union TriggeredPathActorPositionWords {
    u8 v0;
    f32 v1;
};

struct Dest;

struct Trigger;

struct MovingPlatformMotionStateView;




struct Rec;
typedef struct Rec Rec;


struct PathMotionActorView;
typedef struct PathMotionActorView PathMotionActorView;


extern float k_deviceInitialCharge;


struct ActorMotionState;
struct LevelActor;

struct PathMotionInterpolationState;


struct Rec;





struct Settings;
typedef struct Settings Settings;

union TriggeredPathActorPositionWords;
typedef union TriggeredPathActorPositionWords TriggeredPathActorPositionWords;

struct PathMotionActorView;





struct MovingPlatformActorView;
typedef struct MovingPlatformActorView MovingPlatformActorView;


struct MovingActorGameFlagView;
typedef struct MovingActorGameFlagView MovingActorGameFlagView;






union WaypointFlags;
union WaypointFlags {
    u16 half;
    s32 word;
};


struct PathMotionWaypoint;
typedef struct PathMotionWaypoint PathMotionWaypoint;

union WaypointFlags;
typedef union WaypointFlags WaypointFlags;


struct MovingPlatformActorView;


struct PathMotionWaypoint;



struct MovingPlatformMotionStateView;
typedef struct MovingPlatformMotionStateView MovingPlatformMotionStateView;




struct CPlatformIntelligence;
struct CPlatformIntelligence {
    char pad0[4];
    u16 moving;
    char pad6[0x1E];
    u32 flags;
    u8 bobMode;
    u8 linear;
    u8 yawMode;
    char pad2B;
    f32 rise;
    f32 radius;
    f32 angle;
    char pad38[4];
    f32 yaw;
    char pad40[4];
    f32 bob;
    char pad48[0xC];
    f32 triggerDelay;
    f32 displacement;
    f32 duration;
};



struct CPlatformIntelligence;
typedef struct CPlatformIntelligence CPlatformIntelligence;




struct PathMotionInterpolationState;
typedef struct PathMotionInterpolationState PathMotionInterpolationState;


struct MovingActorGameFlagView;


struct TriggeredMotionSoundOption;

typedef struct ActorMotionDefinition {
    s32 flags; /* 0x0 */
    u16 radial; /* 0x4 */
    u8 pad6[2];
    u8 pad8[4];
    s32 eventMask; /* 0xC */
    s32 secondaryEventMask; /* 0x10 */
    u8 pad14[2];
    s16 soundEnabled; /* 0x16 */
    s16 soundIndex; /* 0x18 */
    u8 pad1A[0xA];
    s32 transitionFlags; /* 0x24 */
    u8 pad28[0x4];
    f32 height; /* 0x2C */
    f32 radius; /* 0x30 */
    f32 heading; /* 0x34 */
    f32 transitionTime; /* 0x38 */
    u8 pad3C[0x4];
    f32 speed; /* 0x40 */
    u8 pad44[0x4];
    f32 progressScale; /* 0x48 */
    f32 openThreshold; /* 0x4C */
    f32 closeThreshold; /* 0x50 */
    u8 pad54[0x18];
    f32 eventThreshold; /* 0x6C */
} ActorMotionDefinition;
typedef struct ActorMotionResource {
    s32 kind; /* 0x0 */
    u8 pad4[0x10];
    ActorMotionDefinition motion; /* 0x14 */
} ActorMotionResource;
typedef struct ActorMotionHooks { void *reserved[2]; void (*onStep)(void *, void *); u8 padC[0x10]; s32 flags; } ActorMotionHooks;
typedef struct ActorMotionState {
    s32 flags; /* 0x0 */
    u8 pad4[0x28];
    void * table; /* 0x2C */
    ActorMotionHooks * hooks; /* 0x30 */
    s8 mode; /* 0x34 */
    s8 action; /* 0x35 */
    u8 pad36;
    s8 state; /* 0x37 */
    u8 pad38[0x8];
    f32 timer; /* 0x40 */
    u8 pad44[0x4];
    CVector3 position; /* 0x48 */
    u8 pad54[0xC];
    f32 height; /* 0x60 */
    f32 speed; /* 0x64 */
    struct Player *target; /* 0x68 */
    u8 pad6C[0x28];
    s8 routeMode; /* 0x94 */
    u8 route; /* 0x95 */
    u16 start; /* 0x96 */
    u16 destination; /* 0x98 */
    u8 pad9A[0x6];
    CVector3 base; /* 0xA0 */
    u8 padAC[0x1F];
    s8 actionPending; /* 0xCB */
    u8 padCC[0x3C];
    void * update; /* 0x108 */
    void * secondaryUpdate; /* 0x10C */
    void * event; /* 0x110 */
    u8 pad114[8];
    void * transform; /* 0x11C */
    u8 pad120[0x4];
    s32 animation; /* 0x124 */
    s32 remainingCount; /* 0x128 */
    s32 reservedWord12C; /* 0x12C */
    s32 reservedWord130; /* 0x130 */
    f32 yaw; /* 0x134 */
    f32 pitch; /* 0x138 */
    f32 progress; /* 0x13C */
    s32 reservedWord140; /* 0x140 */
    s32 reservedWord144; /* 0x144 */
    s32 reservedWord148; /* 0x148 */
    s32 reservedWord14C; /* 0x14C */
    u8 pad150[0x18];
    s32 reservedWord168; /* 0x168 */
    s32 openTimer; /* 0x16C */
} ActorMotionState;
#endif
