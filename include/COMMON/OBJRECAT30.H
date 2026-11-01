#ifndef COMMON_OBJRECAT30_H
#define COMMON_OBJRECAT30_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VECTOR4F.H"
struct Trigger;

struct ActionTrackCallbackRecord;

struct ActorModelIndexView;
typedef struct ActorModelIndexView ActorModelIndexView;

extern float k_breakableDamageScale;


struct BreakableHitContext;
struct BreakableHitContext {
    char pad0[0x8];
    CVector3 position;
    char pad8[0x18 - 0x8 - sizeof(CVector3)];
    char * descriptor;
    char pad18[0xE6 - 0x18 - sizeof(char*)];
    s8 forced;
    char padE6[0x100 - 0xE6 - sizeof(s8)];
    s32 flags;
    char pad100[0x104 - 0x100 - sizeof(s32)];
    f32 hitLimit;
    char pad104[0x108 - 0x104 - sizeof(f32)];
    s16 teamIdFirst;
    char pad108[0x10A - 0x108 - sizeof(s16)];
    s16 teamIdSecond;
    char pad10A[0x10C - 0x10A - sizeof(s16)];
    s16 hitCount;
    char pad10C[0x12C - 0x10C - sizeof(s16)];
    s16 flaggedHitCount;
    char pad12C[0x134 - 0x12C - sizeof(s16)];
    f32 flaggedHitLimit;
};








struct BreakableHitStateView;
struct BreakableHitStateView {
    char pad0[0xCA];
    s8 team;
    char padCA[0xCB - 0xCA - sizeof(s8)];
    s8 active;
};

struct Dest;


struct ActorMotionState;
struct LevelActor;

extern float k_actionMotionThreshold;





struct ActionTrackCallbackRecord;
typedef struct ActionTrackCallbackRecord ActionTrackCallbackRecord;

struct BreakableHitStateView;
typedef struct BreakableHitStateView BreakableHitStateView;

struct BreakableHitContext;
typedef struct BreakableHitContext BreakableHitContext;

struct TurretTargetVisibilityView;
typedef struct TurretTargetVisibilityView TurretTargetVisibilityView;




struct TurretTargetVisibilityView;
struct TurretTargetVisibilityView {
    char pad0[0x130];
    CVector3 aim;
};


struct LevelActor;




struct FadedActorRenderView;
struct ActionFadeInput;
struct Lookup;

/* Definition fields used by breakable-actor flag setup. */
typedef struct BreakableDefinition {
    u8 reserved0[0x14];
    s32 flags;
    u8 reserved18[8];
    s16 triggerValue; /* 0x20: kind-10 state callback result */
    u8 reserved22[6];
    s16 health; /* 0x28 */
} BreakableDefinition;
#endif
