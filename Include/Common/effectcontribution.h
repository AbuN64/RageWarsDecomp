#ifndef COMMON_EFFECTCONTRIBUTION_H
#define COMMON_EFFECTCONTRIBUTION_H
#include "types.h"
#include "Common/small_records.h"
struct EffectContribution;
struct RibbonWorld;
/* Reset and accumulate the scale, weight and displacement of an effect. */
typedef struct EffectContribution {
    s32 id;
    s32 state;
    u8 reserved8[4];
    s32 stateC;
    s32 state10;
    f32 scale;
    u8 reserved18[0xC];
    f32 weight;
    u8 reserved28[0xC];
    f32 x, y, z;
} EffectContribution;

#include "Common/sharedplayer.h"
#include "Common/vector4f.h"
#include "Common/aiprofile.h"
#include "Common/hud_effects.h"












struct Shade;
typedef struct Shade Shade;








struct Transform;
struct Transform {
    union {
        FixedPointMatrix matrix;
        struct {
            char pad0[0x18];
            s16 position[3];
        };
    };
};

extern void Fx_RibbonNoop(void);

extern void Fx_ResetEffectContribution(struct EffectContribution *contribution, s32 effectId);


extern float g_ribbonDistancePhaseScale;


struct RibbonActor;
typedef struct RibbonActor RibbonActor;






extern float g_particleRibbonActorScale;

struct Morph;
typedef struct Morph Morph;


struct Shade;
struct Shade {
    u8 a;
    u8 b;
    u8 g;
    u8 r;
};

struct Blend;
struct Blend {
    Shade from;
    Shade to;
    u16 first;
    u16 second;
};





struct CROMSwoosh_t;
struct CROMSwoosh_t {
    f32 initialLifetime;
    f32 minimumLifetime;
    f32 segmentLifetime;
    s32 matrixIndex; /* 0x0C: attached actor bone matrix */
    s16 textureId; /* 0x10 */
    u8 closed;
    char pad13[0x16 - 0x13];
    u8 prim[3];
    u8 env[3];
    u8 kind;
    u8 textureScale;
    u8 mode; /* 0x1E: animation playback */
    u8 firstBlend; /* 0x1F */
    u8 secondBlend; /* 0x20 */
    u8 scaleS, scaleT, count;
    struct Blend blends[1];
};
struct RibbonActor;
struct CROMSwoosh_t;





struct Blend;
typedef struct Blend Blend;



























struct Blend;
struct Key;
struct Morph;

extern float g_particleQuadMatrixAxisScale;

extern float g_particleRibbonSpecialActorScale;

extern float g_particleQuadMatrixScale;



extern void Fx_DetachEffectOwner(struct RibbonWorld *owner, int object);







/* Shared four-vertex particle quad initialized by Match_InitParticleQuad. */
extern Vtx g_particleQuadVertices[4];




extern float g_effectUpQuaternionConstants;






extern CQuatern *Fx_BuildUpAxisQuaternion(CQuatern *out, u32 bx, u32 by, u32 bz);


extern f32 g_detachedRibbonActorScale;
extern f32 g_detachedRibbonSpecialActorScale;
extern f32 g_detachedRibbonEntityScale;
extern f32 g_detachedRibbonSpecialEntityScale;
#endif
