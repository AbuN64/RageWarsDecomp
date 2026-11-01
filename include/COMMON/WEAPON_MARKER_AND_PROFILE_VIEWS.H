#ifndef COMMON_WEAPON_MARKER_AND_PROFILE_VIEWS_H
#define COMMON_WEAPON_MARKER_AND_PROFILE_VIEWS_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
struct WeaponMarkerControllerView;
struct WeaponMarkerControllerView {
    char pad0[0x30];
    void * callback_owner;
    char pad30[0x130 - 0x30 - sizeof(void*)];
    f32 timeRemainingB;
    char pad130[0x148 - 0x130 - sizeof(f32)];
    f32 timeRemainingA;
};



struct WeaponHandOffsetView;
typedef struct WeaponHandOffsetView WeaponHandOffsetView;


union PlayerProfileOwnerReference;
union PlayerProfileOwnerReference {
    s32 v0;
    char * v1;
};

union PlayerProfileOwnerReference;
typedef union PlayerProfileOwnerReference PlayerProfileOwnerReference;

struct PlayerProfileWeaponView;
struct PlayerProfileWeaponView {
    char pad0[0x5DC];
    PlayerProfileOwnerReference camera;
    char pad5DC[0x62E - 0x5DC - sizeof(PlayerProfileOwnerReference)];
    s16 selectedAction;
};


extern float g_weaponChargeCooldownLimit;

extern float g_alternateAmmoFirstMessageDuration;

struct ObjectWeaponsNextAvailableWeapon;
typedef struct ObjectWeaponsNextAvailableWeapon ObjectWeaponsNextAvailableWeapon;

struct WeaponMarkerActorContext;
struct WeaponMarkerActorContext {
    char pad0[0x1];
    u8 stateFlag;
    char pad1[0x1D8 - 0x1 - sizeof(u8)];
    void * owner;
};

extern int g_weaponHandMirrorX;


extern float g_weaponMarkerDeltaScale;

struct WeaponMarkerCallbackView;
struct WeaponMarkerCallbackView {
    unsigned char padding_0[92];
    void (*callback)(void *, void *);
};

extern void Weaponai_InitializeSwitchForSingleRound(void *actor, WeaponFireState *fireState);


struct ObjectWeaponsNextAvailableWeapon;
struct ObjectWeaponsNextAvailableWeapon {
    s8 pad603[0x603];
    s8 values[43];
    s16 selected;
};


struct WeaponHandOffsetView;
struct WeaponHandOffsetView {
    unsigned char padding_0[56];
    CVector3 handOffset;
};

struct PlayerProfileWeaponView;
typedef struct PlayerProfileWeaponView PlayerProfileWeaponView;


struct WeaponMarkerActorView;
typedef struct WeaponMarkerActorView WeaponMarkerActorView;

struct WeaponMarkerControllerView;
typedef struct WeaponMarkerControllerView WeaponMarkerControllerView;


struct WeaponMarkerActorView;
struct WeaponMarkerActorView {
    char pad0[0x62E];
    s16 selectedAction;
    char pad62E[0x650 - 0x62E - sizeof(s16)];
    s16 pose;
    char pad650[0x770 - 0x650 - sizeof(s16)];
    s16 weapon;
    char pad770[0x7E8 - 0x770 - sizeof(s16)];
    s32 state7E8;
    char pad7E8[0x11D8 - 0x7E8 - sizeof(s32)];
    f32 cooldown;
    char pad11D8[0x122C - 0x11D8 - sizeof(f32)];
    s32 reactionFlags;
};

extern float g_ammoCostSecondMessageDuration;


struct WeaponMarkerActorContext;
typedef struct WeaponMarkerActorContext WeaponMarkerActorContext;



struct WeaponAnimationState;
struct WeaponAnimationState {
    char pad0[0x168];
    f32 speed;
};

extern float g_alternateAmmoSecondMessageDuration;

extern float g_weaponSecondAlternateChargeScale;



extern float g_weaponAlternateFireDelayLimit;

extern float g_weaponAlternateStunLimit;
extern float g_weaponFirstAlternateChargeScale;
extern float g_weaponAlternateChargeCueInterval;




extern float g_weaponChargeSpinScale;

struct PlayerProfileAttachmentView;
typedef struct PlayerProfileAttachmentView PlayerProfileAttachmentView;


extern int g_weaponHandMirrorZ;

struct WeaponMarkerCallbackView;
typedef struct WeaponMarkerCallbackView WeaponMarkerCallbackView;

struct WeaponAnimationState;
typedef struct WeaponAnimationState WeaponAnimationState;




extern int g_weaponHandMirrorY;

struct PlayerProfileAttachmentView;
struct PlayerProfileAttachmentView {
    char pad0[0x50];
    CVector3 scale;
    char pad50[0x1D8 - 0x50 - sizeof(CVector3)];
    char * owner;
};



extern float g_ammoCostFirstMessageDuration;



typedef struct MarkerNode { u8 pad0[0x1214]; s32 active; u8 pad1218[0x264]; s32 extra; u32 matrices[4][16], extraMatrices[4][16]; } MarkerNode;
typedef struct MarkerActor { u8 pad0[0x1D8]; MarkerNode *node; } MarkerActor;
extern s32 g_lightingBufferIndex;
extern struct UnitVtx g_weaponRedMarkerVertices[];
extern s32 Geometry_SetModePreset(s32);
extern void Geometry_SetCombineMode(u32);
extern void Fx_DrawRedParticleQuad(u32);

extern s32 Weapon_IsSecondarySwitchGroup(s32);

extern s32 Weaponai_CanStartFiring(void *, void *);


extern void Playerai_EndHeldAlternateFire(void *actor);
#endif
