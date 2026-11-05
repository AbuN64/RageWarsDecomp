#ifndef COMMON_ANIMATION_POOL_H
#define COMMON_ANIMATION_POOL_H
#include "Engine/folded_constants.h"
struct EffectDesc;
struct SceneEffect;
struct CAnimPool;
#ifndef COMMON_OBJRECAT5F14_BODY_H
#define COMMON_OBJRECAT5F14_BODY_H
#include "types.h"
#include "Common/world.h"

#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
#include "Animpool/animpool_spawndescribedsceneeffect.h"






struct EffectDesc;
typedef struct EffectDesc EffectDesc;


struct EffectDesc;
struct EffectDesc {
    u8 id;
    char pad1[7];
    CVector3 position;
    s32 owner;
    s32 count;
    CVector3 direction;
    char pad28[0x28];
    CVector3 color;
    char pad5C[0x10];
    f32 scale;
    char pad70[0x74];
    u16 variant;
};

extern struct SceneEffect *Animpool_SpawnDescribedSceneEffect(struct CAnimPool *scene, struct EffectDesc *desc);

extern void *Animpool_AcquireSceneEffect(s32 effectPool, s32 *referenceCount);

struct RecordAnimPoolSpawnAnimationObject;
struct RecordAnimPoolSpawnAnimationObject {
    char pad0[0x1C];
    u16 count;
    u16 angle;
};


struct ResourceEntry;
typedef struct ResourceEntry ResourceEntry;



struct Six;
struct Six {
    int a;
    int b;
    int c;
    int d;
    int e;
    int f;
};








struct RecordAnimPoolSpawnAnimationObject;
typedef struct RecordAnimPoolSpawnAnimationObject RecordAnimPoolSpawnAnimationObject;


struct AnimationResourceHandleView;
extern void Gastate_ReleaseAnimationResource(struct AnimationResourceHandleView *animationState);






struct ResourceEntry;
struct ResourceEntry {
    u16 reservedHalf;
    u16 span;
    u16 reservedHalf2;
    u16 count;
};

struct Six;
typedef struct Six Six;

/* The list Animpool_ReleaseSceneEffect appends its record to. */


/* Eight-byte easing parameters returned for a motion animation segment. */
typedef struct AnimationBlendEntry {
    u16 frames;
    u8 reserved2[3];
    u8 start;
    u8 reserved6;
    u8 end;
} AnimationBlendEntry;

#endif
#endif
