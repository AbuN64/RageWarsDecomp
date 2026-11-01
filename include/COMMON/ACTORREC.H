#ifndef COMMON_ACTORREC_H
#define COMMON_ACTORREC_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
struct ActorRec;
typedef struct ActorRec ActorRec;

extern const float g_pointCentroidUnitScale;

struct ObjNavComputeScaledPointCentroid;
struct ObjNavComputeScaledPointCentroid {
    char pad0[0x38];
    s32 count;
    char pad3C[0x138-0x3C];
    CVector3 points[10];
    CVector3 result;
    char pad1BC[0x1C4-0x1BC];
    s32 infoIndex;
};

extern float g_ballisticInverseDistanceScale;

struct NavigationStage;
struct NavigationStage {
    s32 to;
    s32 from;
    f32 distance;
};

struct NavigationStage;
typedef struct NavigationStage NavigationStage;

struct SelectionNavAppendDirectionalRouteStage;
struct SelectionNavAppendDirectionalRouteStage {
    char pad0[0xC];
    s32 node;
    char pad10[4];
    s32 ids[4];
    char pad24[0x14];
    s32 objectCount;
    Player *objects[33];
    NavigationStage stages[10];
    CVector3 dirs[10];
    CVector3 result;
    s32 stageCount;
    s32 id;
    s32 lastNode;
    s32 failed;
};


/* The trajectory mode belongs to the full instance, beyond its 20-byte header. */
typedef struct BallisticInstance {
    InstanceHdr header;
    u8 pad014[0x62E - 0x14];
    s16 trajectoryMode;
} BallisticInstance;

struct ActorRec;
struct ActorRec {
    BallisticInstance *instance;
    u8 pad004[0x248 - 4];
    f32 initialPitch;
    f32 previousPitch;
    f32 pitchDelta;
    f32 previousPitchDelta;
    union {
        struct { f32 destinationX; f32 destinationY; f32 destinationZ; };
        CVector3 destination;
    };
    f32 trajectoryDistance;
    s32 trajectoryInitialized;
    s32 trajectoryMode;
    s32 trajectoryPending;
    s32 trajectoryComplete;
    f32 targetPitch;
    f32 upperPitchBound;
    f32 lowerPitchBound;
    s32 pitchSearchStep;
};


struct SelectionNavAppendDirectionalRouteStage;
typedef struct SelectionNavAppendDirectionalRouteStage SelectionNavAppendDirectionalRouteStage;

extern float g_ballisticAccelerationScale;

struct WeightSource;

struct WeightedAttackSelectionBrainView;
typedef struct WeightedAttackSelectionBrainView WeightedAttackSelectionBrainView;

extern float g_teamMarkerSeekRandomRange;

extern float g_ballisticArcSampleRate;

struct ObjNavFindSpecialLinkedCandidate;
struct ObjNavFindSpecialLinkedCandidate {
    char pad0[0x14];
    int nodes[4];
    char pad24[0x1BC - 0x24];
    int hits;
    int node;
    char pad1C4[4];
    int pending;
};

struct WeightedAttackSelectionBrainView;

struct ObjNavFindSpecialLinkedCandidate;
typedef struct ObjNavFindSpecialLinkedCandidate ObjNavFindSpecialLinkedCandidate;

struct ObjNavComputeScaledPointCentroid;
typedef struct ObjNavComputeScaledPointCentroid ObjNavComputeScaledPointCentroid;

extern float g_teamMarkerAggressionScale;

struct WeightSource;
typedef struct WeightSource WeightSource;


/* Resource sections returned by SetN64_GetPackSection, selectors 1 and 2. */
#include "COMMON/BALLISTICPARAMS.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
typedef struct BallisticResourceKeys {
    s32 tag;
    s32 count;
    u32 keys[1];
} BallisticResourceKeys;
typedef struct BallisticResourceRecords {
    s32 tag;
    s32 count;
    BallisticParamsHolder records[1];
} BallisticResourceRecords;

extern s32 *g_ballisticParameterResource;
#endif
