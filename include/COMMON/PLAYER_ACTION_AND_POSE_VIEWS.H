#ifndef COMMON_PLAYER_ACTION_AND_POSE_VIEWS_H
#define COMMON_PLAYER_ACTION_AND_POSE_VIEWS_H
struct SharedPlayer;
#ifndef PLAYER_ACTION_AND_POSE_DECLARATIONS_H
#define PLAYER_ACTION_AND_POSE_DECLARATIONS_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"

extern f32 Playerai_EvaluateCubicComplement(f32 curveInput);

struct Shared_ActorView;
extern s32 Playerai_IsSpeedAboveThreshold(struct Shared_ActorView *actor);


struct WeaponChargeAmmunitionView;
struct WeaponChargeAmmunitionView {
    unsigned char padding_0[8];
    short ammunition;
};

struct Marker;
typedef struct Marker Marker;


extern void Playerai_ApplyRangedPitchToMatrix(void *matrix, void *player);

struct EntryPlayerHasLinkedWorldFlagSix;
struct EntryPlayerHasLinkedWorldFlagSix {
    char pad[0x52];
    u16 flags;
};



struct Object126;
typedef struct Object126 Object126;



extern int Playerai_IsStateFifteen(struct SharedPlayer *player);

extern float Playerai_SumActivePlayerDistances(void * roundContext, float * point);

struct PlayerRangedPitchStateView;
typedef struct PlayerRangedPitchStateView PlayerRangedPitchStateView;

extern float g_playerStateFifteenPitchOffset;

extern void Playerai_EmptyHandlerAfterInitializeStateBlendToZero_de(void);


extern float g_playerWeaponChargeBlendCutoff;

extern u8 Playerai_GetImpactSoundEnabled(s32 unused0, s32 actorType);

struct Actor126;
typedef struct Actor126 Actor126;

extern float g_playerForceMarkerBasisScale;



extern void Playerai_UpdateSequence74RunEndPose(void *);

extern float g_sceneMinimumActorHeight;

struct PlayerRangedPitchLimits;
typedef struct PlayerRangedPitchLimits PlayerRangedPitchLimits;

extern void Playerai_ResetPlayerWeaponLock(void *lockedPlayerState);

extern float g_playerOffsetMarkerScale;

struct PlayerRangedPitchStateView;
struct PlayerRangedPitchStateView {
    char pad0[0x650];
    s16 action;
    char pad650[0x724 - 0x650 - sizeof(s16)];
    f32 rangedPitch;
};



struct Player;
extern void Playerai_InitializeStateBlendToZero(struct Player *player);


struct PlayerRangedPitchLimits;
struct PlayerRangedPitchLimits {
    char pad0[0x18];
    s8 firstEventIndex;
    char pad18[0x19 - 0x18 - sizeof(s8)];
    s8 lastEventIndex;
    char pad19[0x1A - 0x19 - sizeof(s8)];
    s8 pitchDivisor;
};

struct PlayerRangedPitchEventView;
struct PlayerRangedPitchEventView {
    char pad0[0x4];
    s32 eventIndex;
    char pad4[0x8 - 0x4 - sizeof(s32)];
    void * actor;
    char pad8[0x1C - 0x8 - sizeof(void*)];
    void * pitchLimits;
};

extern float g_playerForceMarkerTilt;








extern void Playerai_EmptyImpactSoundHook(void);

extern float g_playerCrouchClearanceBounds;

extern void Playerai_ClearPlayerWeaponLock(void *lockedPlayerState);

extern void Playerai_InitializeStateBlendTarget(struct Player *player);


struct Marker;
struct Marker {
    char pad0[0xC];
    f32 scale;
    s16 x;
    s16 y;
    s16 z;
    s16 active;
};

struct Actor126;
struct Actor126 {
    u8 pad0[0x100];
    s32 flags;
    u8 pad104[0xD0];
    f32 value1D4;
    u8 pad1D8[0x47A];
    s16 state652;
    u8 pad654[0xD4];
    f32 offset728;
};


struct PlayerWeaponChargeEffectView;
typedef struct PlayerWeaponChargeEffectView PlayerWeaponChargeEffectView;


extern float g_playerActionBlendMinimumRise;

struct PlayerWeaponChargeEffectView;
struct PlayerWeaponChargeEffectView {
    char pad0[0x5D8];
    char * profile;
    char pad5D8[0x5E4 - 0x5D8 - sizeof(char*)];
    s32 chargeRequested;
    char pad5E4[0x62E - 0x5E4 - sizeof(s32)];
    s16 weaponType;
    char pad62E[0x7E8 - 0x62E - sizeof(s16)];
    s32 chargeEnabled;
    char pad7E8[0x7EC - 0x7E8 - sizeof(s32)];
    f32 chargeBlend;
    char pad7EC[0x7F0 - 0x7EC - sizeof(f32)];
    f32 chargeBlendTarget;
    char pad7F0[0x878 - 0x7F0 - sizeof(f32)];
    char effect;
};




extern float k_playerState15EffectValue;

extern s32 Playerai_IsStateThreeLowerAnimationGroup(struct SharedPlayer *player);

extern void Playerai_ApplyLinkedProjectileStatus(void * unused1, int unused2, int projectileEvent);

struct Object126;
struct Object126 {
    u8 pad0[0x1C];
    f32 x;
    u8 pad20[4];
    f32 y;
    u8 pad28[0x44];
    f32 angle;
};

extern void Playerai_OffsetActorForState15(Actor126 *actor, Object126 *positionedObject);




struct LinkedWorldFlagsView;
extern s32 Playerai_HasLinkedWorldFlagSix(struct LinkedWorldFlagsView *object);

extern float g_playerStateBlendTarget;



extern void Playerai_ReleaseMarkerSlot(void *unused0, s32 *markerSlot);



extern s32 Playerai_IsStateThreeUpperAnimationGroup(struct SharedPlayer *player);

struct PlayerRangedPitchEventView;
typedef struct PlayerRangedPitchEventView PlayerRangedPitchEventView;

extern void Playerai_UpdateActionTransitionBlend(struct Shared_ActorView *actor);

extern float g_playerWeaponChargeBlendTarget;


extern void Playerai_UpdateWeaponEffectBlend(void *player);

#endif
#endif
