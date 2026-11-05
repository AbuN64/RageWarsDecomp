#ifndef COMMON_SNAPSHOT_ACTOR_H
#define COMMON_SNAPSHOT_ACTOR_H
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
#include "World/collision_records.h"
struct Snapshot;
struct SampledEffectCurveState;
struct SnapshotActorView;
struct SnapshotActorView {
    char pad0[8];
    Triple position;
    s32 id;
    char pad18[0x6C - 0x18];
    f32 yaw;
    char pad70[0x5E0 - 0x70];
    Block70 block;
    char pad650[0x16E8 - 0x650];
};

struct ActorList;
struct SnapshotActorView;

struct Snapshot;
struct Snapshot {
    s32 active;
    s32 mode;
    s32 countdown;
    s32 savedActorId;
    Block70 blocks[8];
    Triple positions[8];
    f32 values[8];
    s32 handles[8];
};

struct SampledCurve;
struct SampledCurve {
    int type;
    unsigned char samples[16];
    float length;
};

struct SampledCurve;

struct SampledEffectCurveState;
struct SampledEffectCurveState {
    struct SampledCurve *curve;
    float time;
    float value;
};

extern void Control_DeactivateActorSnapshot(void);


struct SampledEffectCurveState;
typedef struct SampledEffectCurveState SampledEffectCurveState;

struct Snapshot;
typedef struct Snapshot Snapshot;
extern struct Snapshot g_controllerActorSnapshot;

struct Snapshot;

extern void Control_SaveActorSnapshot(void);

struct Snapshot;

extern s32 Control_FindConnectedControllerPort(s32 controllerOwner);


extern void Control_RestoreActorSnapshot(void);


extern void Control_TickSnapshotCountdown(void);

struct SnapshotActorView;
typedef struct SnapshotActorView SnapshotActorView;

extern void Control_ClearMenuControlFlag(void);

extern void Control_EnableAllControllerPaks(void);


extern void Control_CycleActorSnapshotMode(void);

struct ActorList;
typedef struct ActorList ActorList;

extern void Control_ResetControllerProfiles(void);

extern void Control_ResetActorSnapshot(void);


extern void Control_RestoreControllerSetup(void);


extern s32 Control_AdvanceEffectCurve(struct SampledEffectCurveState *curvePlayer);

struct SampledCurve;
typedef struct SampledCurve SampledCurve;

extern void Control_SetMenuControlFlag(void);
#endif
