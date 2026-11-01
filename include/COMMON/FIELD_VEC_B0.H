#ifndef COMMON_FIELD_VEC_B0_H
#define COMMON_FIELD_VEC_B0_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"






struct s_CTargetInfo;
typedef struct s_CTargetInfo CTargetInfo;




extern float k_barrelPrimarySoundRandomMaximum;

struct BarrelAnchorActorView;
typedef struct BarrelAnchorActorView BarrelAnchorActorView;



struct SourceBarrelUpdateActorController;
struct SourceBarrelUpdateActorController {
    char pad0[8];
    Triple position;
    char pad14[4];
    s32 *kind;
    char pad1c[0x50];
    f32 height;
    char pad70[0x90];
    s32 flags;
    char pad104[0x98];
    s32 active;
};

struct CActor_t;
typedef struct CActor_t CActor_t;

struct BarrelAnchorActorView;
struct s_CTargetInfo;
struct s_CTargetInfo {
    s32 kind;
    struct BarrelAnchorActorView *target;
    f32 m_DeltaAngle;
    CVector3 m_vTargetPos;
    CVector3 m_vDeltaTargetPos;
    f32 m_DistFrom;
    CVector3 m_vXZTargetPos;
    CVector3 m_vXZDeltaTargetPos;
    f32 m_XZDistFrom;
};







struct CAIMovementInfo;
struct CAIMovementInfo {
    CVector3 first;
    CVector3 first_normalized;
    f32 first_length;
    CVector3 flat;
    CVector3 flat_normalized;
    f32 flat_length;
    f32 height;
};

struct BarrelWordPair;
typedef struct BarrelWordPair BarrelWordPair;


struct ActorProfileImpulseFlagsView;
struct ActorProfileImpulseFlagsView {
    char pad0[0x100];
    u32 profileFlags;
    char pad100[0x5D8 - 0x100 - sizeof(u32)];
    char * characterProfile;
    char pad5D8[0x122C - 0x5D8 - sizeof(char*)];
    u32 impulseFlags;
};

struct CTeamSelectTeam_t;
struct CTeamSelectTeam_t {
    s32 reservedWord0;
    s32 reservedWord4;
    f32 x;
    f32 y;
    f32 z;
};



extern float g_barrelClearAimClearance;




struct DestBarrelUpdateActorController;
typedef struct DestBarrelUpdateActorController DestBarrelUpdateActorController;

struct CActor_t;
struct CActor_t {
    u8 type;
    u8 pad001[0x1B];
    CVector3 position;
    u8 pad028[0xBC];
    u16 objectId;
    u8 pad0E6[0x10A];
    s32 eventValue;
    u8 pad1F4[0xA8];
    s32 eventCount;
};



struct BarrelWordPair;
struct BarrelWordPair {
    int words[2];
};

struct SourceBarrelUpdateActorController;
typedef struct SourceBarrelUpdateActorController SourceBarrelUpdateActorController;




struct Location;
struct Location {
    CVector3 pos;
    s32 room;
    f32 heading; /* 0x10 */
    u16 flags; /* 0x14 */
};





extern void Barrel_IgnoreEffectCallback(void *unused0, void *unused1, BarrelWordPair unused2);


struct Tracker;
typedef struct Tracker Tracker;




extern float g_barrelFlaggedAimProbeScale;



struct BarrelSequenceCursor;
typedef struct BarrelSequenceCursor BarrelSequenceCursor;

struct BarrelSequenceCursor;
struct BarrelSequenceCursor {
    void *base;
    u16 *cur;
};

extern s16 Barrel_ReadLoopingSequenceValue(BarrelSequenceCursor *cursor);



extern float k_barrelSecondarySoundRandomMaximum;

struct Location;
typedef struct Location Location;

struct LevelActor;
struct RouteChaseBot;




struct CTeamSelectTeam_t;
typedef struct CTeamSelectTeam_t CTeamSelectTeam;


struct BarrelAnchorActorView;
struct Tracker;
struct Tracker {
    s32 flags;
    s32 active;
    u8 pad8[0x2C];
    s8 mode; /* 0x34 */
    u8 pad35[2];
    s8 targetingDisabled;
    u8 pad38[0x30];
    struct BarrelAnchorActorView *self;
    CVector3 offset;
    struct BarrelAnchorActorView *lockedTarget; /* 0x78 */
    f32 targetTimer; /* 0x7C */
    struct BarrelAnchorActorView *anchor;
    u8 pad84[4];
    struct BarrelAnchorActorView *target;
    f32 angle;
    f32 height;
    s8 slot;
    u8 pad95[7];
    f32 homeYaw; /* 0x9C */
    u8 padA0[0x10];
    CVector3 homePos;
    s32 homeRoom;
    u8 padC0[0xE];
    s8 team;
};











struct DestBarrelUpdateActorController;
struct DestBarrelUpdateActorController {
    char pad0[0x40];
    f32 value;
    char pad44[4];
    Triple old_position;
    Triple position;
    f32 height;
    char pad64[0x69];
    u8 timer;
    char padce[0x2E];
    CompactOptionsPageView *aux;
    char pad100[8];
    void (*callback)(SourceBarrelUpdateActorController *, struct DestBarrelUpdateActorController *);
};




struct ActorProfileImpulseFlagsView;
typedef struct ActorProfileImpulseFlagsView ActorProfileImpulseFlagsView;

struct CAIMovementInfo;
typedef struct CAIMovementInfo CAIMovementInfo;



#endif
