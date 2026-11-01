#ifndef COMMON_PROBE_H
#define COMMON_PROBE_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"



extern float g_actorBoneAimSourceY;

extern float g_actorBoneAimAngleScale;





extern float g_actorAffineMatrixHomogeneousUnit;


struct Probe;
typedef struct Probe Probe;

struct SoundRequest;
struct SoundRequest {
    s32 kind;
    CVector3 position;
    char pad[0x148];
    s32 owner;
    s32 flags;
};

extern float g_actorBoneAimUpY;







struct ActorDirectionTiltInput;
typedef struct ActorDirectionTiltInput ActorDirectionTiltInput;

struct ActorDirectionTiltInput;
struct ActorDirectionTiltInput {
    u8 state;
    u8 pad[0x43];
    CVector3 direction;
};


struct Probe;
struct Probe {
    char pad0[0x18];
    CVector3 start;
    char pad24[0x24];
    CVector3 dir;
    char pad54[0x8C];
};

struct SoundRequest;
typedef struct SoundRequest SoundRequest;


typedef struct {
    s32 kind;
    u8 pad4[0x10];
    s32 flags14; /* 0x14 */
    f32 radius; /* 0x18: scalar-radius resource kinds */
    f32 value1C;
    f32 value20;
    u8 pad24[4];
    f32 value28;
    f32 value2C; /* 0x2C */
    f32 value30; /* 0x30: class-specific height */
    f32 value34; /* 0x34 */
    u8 pad38[4];
    f32 value3C; /* 0x3C */
    u8 pad40[0xC];
    s32 flags4C; /* 0x4C */
    f32 value50; /* 0x50 */
    u8 pad54[0x98];
    f32 valueEC;
    f32 collisionExtent; /* +0xF0: 8024E464 returns this for kind 11 collision queries. */
    f32 valueF4; /* 0xF4: player descriptor height */
    f32 valueF8; /* 0xF8 */
} Resource_u1;

/* Kind 2 uses a collision-mode halfword followed by three shape dimensions. */
typedef struct CollisionShapeResource {
    s32 kind;
    u8 pad4[0x14];
    u16 mode; /* 0x18 */
    u8 pad1A[2];
    f32 height; /* 0x1C */
    f32 width; /* 0x20 */
    u8 pad24[4];
    f32 depth; /* 0x28 */
} CollisionShapeResource;
typedef struct {
    u8 pad0[0x6F4];
    f32 heightDelta; /* 0x6F4: AiProfile.heightDelta */
    u8 pad6F8[0x80C - 0x6F8];
    s32 active; /* 0x80C */
} State_u1;
typedef struct {
    u8 kind;
    u8 pad1[7];
    CVector3 position;
    u32 reservedWord;
    Resource_u1 *resource;
    u8 pad1C[0x50];
    f32 yaw;
    u8 pad70[0x90];
    u32 flags;
    u8 pad104[0x174 - 0x104];
    s32 active; /* 0x174 */
    u8 pad178[0x1D8 - 0x178];
    State_u1 *state;
} Actor_u1;
extern f32 g_activePlayerActorRadius;
extern f32 g_collisionShapeRadiusScale;
#endif
