#ifndef RENDER_RANGENODE_H
#define RENDER_RANGENODE_H
struct CAnimPool;
#ifndef RENDER_RANGENODE_DECLARATIONS_H
#define RENDER_RANGENODE_DECLARATIONS_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/OBJRECAT5F14.H"
struct SceneEffect;
struct RangeNode;
typedef struct RangeNode RangeNode;

struct Blast;
typedef struct Blast Blast;

extern float k_teamClipFlagFortyScale;

struct EventCounterPlayerView;
struct EventCounterPlayerView {
    char pad0[8];
    CVector3 pos;
    char pad14[0x16D4 - 0x14];
    s32 alive;
};

struct EventCounterActorView;
struct EventCounterPlayerView;
struct EventCounterActorView {
    u8 kind;
    char pad1[0x100 - 1];
    s32 flags;
    char pad104[0x1D8 - 0x104];
    struct EventCounterPlayerView *owner;
};

struct Limit;
typedef struct Limit Limit;

extern void Events_IgnoreEvent(int unusedActor, int unusedEvent, int unusedValue, int unusedContext, ...);

struct EventCounterParameters;
typedef struct EventCounterParameters EventCounterParameters;

struct EventCounterActorView;
typedef struct EventCounterActorView EventCounterActorView;

struct Blast;
struct Blast {
    char pad0[0xC];
    s32 radius;
    s32 damage;
};

extern void Events_IncrementNearbyPlayerCounter(EventCounterActorView *actor, Player *player, s32 event, Blast blast);

struct ParamsEventsStartActorEmitter;
struct ParamsEventsStartActorEmitter {
    s32 value;
    s16 angle;
    u8 scale;
    u8 pad;
};

struct EventMaskActorView;
typedef struct EventMaskActorView EventMaskActorView;

struct EventCounterPlayerView;
typedef struct EventCounterPlayerView EventCounterPlayerView;

extern float k_eventUpperHeightRange;

extern float k_eventLowerHeightRange;

extern float k_teamClipFlagTwentyScale;

struct RangeNode;
struct RangeNode {
    char pad0[4];
    struct RangeNode *next;
    u16 *radius;
    char padC[4];
    s16 x;
    s16 y;
    s16 z;
    s16 active;
};

struct ContextEventsStartActorEmitter;
typedef struct ContextEventsStartActorEmitter ContextEventsStartActorEmitter;

struct EventCounterParameters;
struct EventCounterParameters {
    s16 halfBeforeValue;
    s16 value;
    s32 team;
};

extern void Events_SetActorEventBit(void *sourceActor, s32 unused1, s32 unused2, s32 eventPositionBase, s32 unused4, s32 unused5, s32 unused6);

struct Kind;
struct Kind {
    s32 value;
    u8 pad4[0xA];
    s8 team;
};
struct Kind;
struct EventMaskActorView;
struct EventMaskActorView {
    u8 type;
    u8 pad1[0x17];
    struct Kind *kind;
    u8 pad1C[0xB4];
    s32 value;
    u8 padD4[0xA8];
    u32 mask;
};

struct Filter;
struct Filter {
    u8 type;
    u8 pad[0x17B];
    s32 mask;
};

extern float g_dynamicLightFalloffUnit;

struct ParamsEventsStartActorEmitter;
typedef struct ParamsEventsStartActorEmitter ParamsEventsStartActorEmitter;

struct Filter;
typedef struct Filter Filter;

struct Inner;
struct Inner {
    char pad[0x698];
    char *resource;
};
struct ContextEventsStartActorEmitter;
struct Inner;
struct ContextEventsStartActorEmitter {
    char pad[0x1D8];
    struct Inner *inner;
};

extern float g_dynamicLightDirectionScale;

extern void Events_ClearActorEventBit(void *actor, s32 unused1, s32 unused2, s32 context, s32 unused4, s32 unused5, s32 unused6);

extern void Events_SetActorEffectMode(LevelActor *actor, int unusedTarget, int unusedKind, Blast blast);

typedef CVector3 Vec3f;
extern struct SceneEffect *Animpool_SpawnAnimationObject(struct CAnimPool *scene, s32 variant, s32 owner, CVector3 position, f32 scale, CVector3 direction,
                      CVector3 color, s32 *ref);

#endif
#endif
