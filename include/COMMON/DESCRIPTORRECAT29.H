#ifndef COMMON_DESCRIPTORRECAT29_H
#define COMMON_DESCRIPTORRECAT29_H
#include "TYPES.H"
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "TEXTLOAD/TEXTLOAD_LOCATETEXTURERESOURCE.H"
#include "TEXTLOAD/TEXTLOAD_READTEXTUREANIMATIONINFO.H"

struct CROMSkyLayer;
typedef struct CROMSkyLayer CROMSkyLayer;

extern float g_skyRotorAngleWrap;

struct ClipView;
typedef struct ClipView ClipView;


struct Scene;

struct Host;
struct Host {
    char pad0[0x24];
    s32 stalled;
    char pad28[0x104];
    f32 speed;
};


struct CROMSkyLayer;
struct CROMSkyLayer {
    s16 texture; /* +0: Sky_UpdateSceneEffects passes it to Textload_LocateTextureResource */
    u8 red, green, blue;
    u8 envRed, envGreen, envBlue;
    f32 spinRate;
    f32 textureScale;
    f32 phaseRate;
    f32 baseSpeed;
    f32 fadeDepth;
    f32 hostScale;
    f32 throttleRate;
    char pad24[4];
    u8 alpha;
    u8 flags;
};

struct SkyEffectSortValueView;
typedef struct SkyEffectSortValueView SkyEffectSortValueView;

struct Effect;
struct Effect {
    char pad00[0xC];
    s16 *definition;
    s16 mask;
    char pad12[2];
    s32 resource; /* 0x14: initialized from the effect definition */
    char pad18[4];
    s32 angle0;
    s32 angle1;
    char pad24[0x1E4];
    s32 timer;
    s32 velocity;
    char pad210[4];
    f32 scale;
    f32 offset0;
    f32 offset1;
    f32 offset2;
};

struct Host;
typedef struct Host Host;




extern float g_skyRotorSpinScale;


struct ClipView;
struct ClipView {
    char gap0[0x8];
    s32 index;
    char gapC[0x120 - 0xC];
    s32 hidden;
    char gap124[8];
    f32 depth;
    char gap130[0x1E0 - 0x130];
    f32 viewProjection[16];
    char gap220[0x260 - 0x220];
    CVector3 fan[5];
    char gap29C[0x74];
    f32 clipPlane[4];
};

struct SkyLayerRuntimeView;

struct Scene;

extern float g_skyRotorMaximumThrottle;

struct Effect;
typedef struct Effect Effect;

struct Rotor;
typedef struct Rotor Rotor;

extern float g_skyRotorAngleAScale;

struct CROMSkyLayer;
struct Rotor;

struct SkyEffectSortValueView;

struct SkyLayerRuntimeView;
struct Scene;

struct Scene;




extern void Sky_SwapEntryCallback();
extern void Sky_CompareRotorSpeedsDescendingCallback();
extern void Sky_CompareRotorSpeedsAscendingCallback();


extern void Gsky_ClearScreenMessage(void *owner);
#endif
