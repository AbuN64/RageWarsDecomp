#ifndef COMMON_LEVEL_ACTOR_H
#define COMMON_LEVEL_ACTOR_H
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/PARTICLE_LIGHTING.H"
#include "COMMON/ACTOR_DEFINITION.H"
#include "COMMON/ROUTE_CURSOR.H"
typedef struct LevelActor LevelActor;
struct LevelActor {
    u8 kind;
    s8 team;
    char pad2;
    s8 renderPass;
    s16 modelIndex;
    u16 pad6;
    CVector3 position0;
    s32 model; /* 0x14 */
    ActorDefinitionHeader *definition; /* 0x18 */
    CVector3 position1;
    CVector3 motionAngles; /* 0x28 */
    void *attached; /* 0x34 */
    s32 motionState; /* 0x38 */
    s32 motionIndex; /* 0x3C */
    f32 floorHeight; /* 0x40 */
    CVector3 floorDirection; /* 0x44 */
    CVector3 scale; /* 0x50 */
    CQuatern rotation;
    f32 yaw; /* 0x6C */
    f32 eyeHeight; /* 0x70 */
    f32 transform[16]; /* 0x74 */
    void *animationMatrices; /* animation matrix buffer */
    s32 alternateAnimationMatrices;
    void *shadow; /* 0xBC */
    u8 padC0[4];
    s32 resource; /* 0xC4 */
    s32 resourceKey; /* 0xC8 */
    s32 animationKey; /* 0xCC */
    s32 resourceFlags; /* 0xD0 */
    s32 resourceAlignment; /* 0xD4 */
    s32 resourceHandle; /* 0xD8 */
    s32 resourceState; /* 0xDC */
    s32 resourceWindow; /* 0xE0 */
    u16 type; /* 0xE4 */
    u8 stateE6;
    u8 stateE7;
    Box bounds; /* 0xE8: world-space box the visibility scan tests */
    s32 flags; /* 0x100 */
    f32 animationTime; /* 0x104 */
    s16 animation; /* 0x108 */
    s16 nextAnimation; /* 0x10A */
    u8 pad10C[2];
    s8 animationPending; /* 0x10E */
    s8 animationChanged; /* 0x10F */
    u8 pad110[8];
    s32 animationReference; /* Gastate_ResetAnimationReference */
    u8 pad11C[0x138 - 0x11C];
    u8 state138;
    u8 state139;
    u8 shadowAlpha; /* 0x13A */
    u8 state13B;
    u8 pad13C[4];
    Shared_ParticleLighting lighting[2]; /* 0x140 */
    s32 behaviorFlags; /* 0x170 */
    s32 active; /* 0x174 */
    u8 pad178[4];
    s32 mask;
    u8 pad180[0x20];
    s32 collisionEnabled; /* 0x1A0 */
    u8 pad1A4;
    s8 animationState; /* 0x1A5 */
    u8 pad1A6[0xA];
    f32 motionThreshold; /* 0x1B0 */
    u8 pad1B4[4];
    CVector3 aimPosition; /* 0x1B8 */
    CVector3 referencePosition; /* 0x1C4: reset alongside position0 for menu rendering */
    u8 pad1D0[8];
    void *controller; /* 0x1D8: linked actor */
    u8 pad1DC[0x14];
    char *lockOn; /* 0x1F0 */
    u8 pad1F4[0x10];
    struct RouteCursorState routeCursor; /* 0x204: Playerai_InitializeRouteCursor */
    u8 pad20A[0x23A - 0x20A];
    s8 lean; /* 0x23A */
    u8 updateCount; /* 0x23B */
    s32 actionReady; /* 0x23C */
    u8 pad240[0x30];
    u8 effectMode; /* 0x270 */
    u8 pad271[0xB];
    void *update; /* 0x27C */
    u8 pad280[0xC];
    void (*controllerUpdate)(void *, void *); /* 0x28C */
    u8 pad290[4];
    f32 pitch; /* 0x294 */
    u8 pad298[0xC];
    f32 restPitch; /* 0x2A4 */
    u8 pad2A8[4];
    s32 gear; /* player actor offset 0x594 */
    u8 pad2B0[0x30];
    s32 renderFlags; /* 0x2E0 */
    s32 flags2E4;
};
#endif
