#ifndef COMMON_OBJ_H
#define COMMON_OBJ_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
struct Obj;
typedef struct Obj Obj;


struct TurretSetupState;
struct TurretSetupState {
    char pad0[0x2C];
    void *table;
    char pad30[7];
    s8 state; /* 0x37 */
    char pad38[0x64 - 0x38];
    f32 threshold; /* 0x64 */
    char pad68[0x108 - 0x68];
    void *first;
    s32 pad10C;
    void *second;
    char pad114[0x11C - 0x114];
    void *third;
    void *fourth;
    f32 speed;
    s32 pad128;
    s32 rate;
    s32 a;
    f32 range;
    s32 b;
    s32 c;
};

extern float k_turretInitialRange;

extern float k_turretVerticalAimLowerLimit;

struct CTurretIntelligence_t;
typedef struct CTurretIntelligence_t CTurretIntelligence;




extern float k_turretIdentityQuaternionW;


struct Result;
typedef struct Result Result;






extern float k_turretVerticalAimUpperLimit;

struct TurretPlayerRelation;
typedef struct TurretPlayerRelation TurretPlayerRelation;

struct Hook;
struct Obj;
struct Obj {
    char pad0[0x30];
    struct Hook *hook;
    char pad34[0x12C - 0x34];
    int count;
    char pad130[0x13C - 0x130];
    float timer;
};

struct TurretRiderTargetView;
typedef struct TurretRiderTargetView TurretRiderTargetView;

struct TurretPlayerRelation;
struct TurretPlayerRelation {
    char pad[0x1D8];
    struct TurretPlayerRelation *linked;
    char pad1DC[0x5D8 - 0x1DC];
    Record *info;
    char pad5DC[0x5E4 - 0x5DC];
    int active;
};


struct Segment;
struct Segment {
    char pad0[0x5C];
    f32 rise;
    f32 radius;
    f32 angle;
    f32 length;
};

struct Result;
struct Result {
    char pad0[4];
    SharedPlayer *target;
    char pad8[0x38];
    f32 distance;
};

struct CTurretIntelligence_t;
struct CTurretIntelligence_t {
    char pad0[0x3C];
    s32 m_GunNode; /* 0x3C: rotation event selector */
    s32 m_RotNode;
    f32 rate;
    f32 limit;
    f32 m_SightRadius;
    s32 pad50;
    f32 range;
    f32 m_FireAngle;
    char pad5C[0x70-0x5C];
    u8 m_TargetVisibleMotionType;
    u8 m_TargetNotVisibleMotionType;
};

struct NavigationTrack {
    u8 prefix[4];
    u32 flags; /* 0x4 */
    u8 pad8[0xC];
    CTurretIntelligence segment;
};


extern float k_turretStateTimeout;

extern f32 g_turretAimSine;

struct TurretAimOwnerView;
struct TurretAimOwnerView {
    char pad0[0x18];
    char * definition;
    char pad18[0x6C - 0x18 - sizeof(char*)];
    f32 heading; /* 0x6C */
    char pad70[0x20C - 0x70];
    f32 targetHeading; /* 0x20C */
    char pad210[0x294 - 0x210];
    f32 pitch;
};

extern float k_turretTurnAngleScale;

struct Segment;
typedef struct Segment Segment;

struct ItemMenuSelectionView;
struct TurretSetupState;

struct TurretAimOwnerView;
typedef struct TurretAimOwnerView TurretAimOwnerView;

struct Rider;
typedef struct Rider Rider;

extern void Libsn_InstallDebuggerExceptionHooks();
extern int Libgultra_TrwGetSr();
extern void Libgultra_TrwSetSr(int sampleRate);

typedef union NavActor { SharedPlayer player; BarrelTrackActorView input; TrackerAimActorView actor; struct Owner owner; } NavActor;
typedef struct NavVec { CVector3 v; f32 fourth; } NavVec;


/* Shared object layout established by rotation consumers. */
struct RotationObject {
    u8 padding000[0x130];
    f32 angleX; /* 0x130 */
    f32 angleY; /* 0x134 */
    f32 angleZ; /* 0x138 */
};


/* Shared object layout established by weapon-events consumers. */
struct WeaponEventSource {
    u8 padding000[0xCB];
    char eventEnabled; /* 0xCB */
};
#endif
