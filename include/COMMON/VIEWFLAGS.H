#ifndef COMMON_VIEWFLAGS_H
#define COMMON_VIEWFLAGS_H
#include "TYPES.H"
#include "COMMON/STATERECAT10.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
/* The camera view fade timer, the word after the view flags g_cameraRenderFlagState (its own global: read with its own lui). */
extern f32 g_cameraFramingTransitionTimer;
struct Triple;
struct CameraObjectPositionView;


struct RacerViewport;
typedef struct RacerViewport RacerViewport;

struct Overlay;
typedef struct Overlay Overlay;

typedef CShakeAxis AxisWave;


extern float g_cameraShakeDistanceComplement;



struct ShakeEmitterChannelView;
typedef struct ShakeEmitterChannelView ShakeEmitterChannelView;



struct CameraObjectPositionView;
typedef struct CameraObjectPositionView CameraObjectPositionView;

extern float k_cameraInitialBobAmplitudeY;


struct Overlay;


struct ShakeEmitterChannelView;

struct CShake_t;
typedef struct CShake_t CShake;

struct CShake_t;
struct CShake_t {
    s32 m_pLast;
    CShake *next;
    CVector3 m_vPos;
    f32 m_Radius;
    AxisWave x;
    AxisWave y;
    AxisWave z;
};


struct ThreeChannels;
typedef struct ThreeChannels ThreeChannels;

extern float k_cameraInitialBobAmplitudeX;

struct LensFlareEffectState;
typedef struct LensFlareEffectState LensFlareEffectState;

struct Race;
typedef struct Race Race;


struct UnitVp;
struct UnitVp {
    s16 vscale[4];
    s16 vtrans[4];
};



struct WorldCameraDrawActiveViews;
typedef struct WorldCameraDrawActiveViews WorldCameraDrawActiveViews;



struct UnitVp;
typedef struct UnitVp UnitVp;

struct RacerViewport;
struct RacerViewport {
    char pad0[4];
    struct RacerViewport *next;
    char pad8[4];
    f32 screenScaleX; /* 0xC */
    f32 screenScaleY; /* 0x10 */
    char pad14[0x50];
    s32 visibilityFlags; /* 0x64 */
    u16 perspectiveNorm; /* 0x68 */
    char pad6A[0xA6];
    f32 viewportScaleX; /* 0x110 */
    f32 viewportScaleY; /* 0x114 */
    char pad118[8];
    s32 effect;
    u16 pad124;
    u16 effectArg;
    char pad128[0x174];
    f32 viewportWidth; /* 0x29C */
    f32 viewportHeight;
    f32 viewportX;
    f32 viewportY;
    char pad2AC[4];
    UnitVp viewports[2];
    char pad2D0[0x80];
    CVector3 clipBounds[2]; /* 0x350 */
    CVector3 volumeBounds[2]; /* 0x368 */
    u32 projectionMatrices[2][16]; /* 0x380 */
    u32 lights[2][8]; /* 0x400 */
    char pad440[0xE0];
    u8 hit;
    u8 boost;
    u8 spin;
    char pad523[0x19];
    s32 fogNear; /* 0x53C: word storage; fog command uses its low 16 bits. */
    char pad540[8];
    s8 mode548; /* 0x548 */
    s8 mode549; /* 0x549 */
    char pad54A[0xA];
    char sound[64];
    char pad594[0xE40 - 0x594];
    IntrusiveList activeMessages; /* 0xE40 */
};

struct WorldCameraDrawActiveViews;
struct WorldCameraDrawActiveViews {
    char pad0[0x12A5];
    u8 replay;
};

struct Race;
struct RacerViewport;
typedef struct RaceHeader {
    s32 music;
    char pad4[0x1C];
    IntrusiveList views;
    u32 lastMode;
    s32 layoutTimer;
    char pad3C[4];
} RaceHeader;
struct Race {
    RaceHeader header;
    RacerViewport self;
    char padRaceTail[0xF24 - 0x40 - sizeof(RacerViewport)];
    IntrusiveList freeMessages; /* 0xF24 */
};




extern float g_cameraShakeYAngleScale;

extern float k_cameraInputSurfaceDistanceScale;




struct LensFlareEffectState;




extern float g_cameraShakeXAngleScale;

extern float g_cameraShakeZAngleScale;


struct ThreeChannels;

struct GameplayCamera;




extern float k_cameraInputSurfaceLowerDistance;


extern float k_cameraInputSurfaceUpperDistance;

extern void Gsky_StartFade(void *view, s32 red, s32 green, s32 blue, s32 mode, s32 alpha, s32 duration, s32 delay);


extern f32 g_cameraViewportLeftInset;

extern Box g_cameraClipBounds;

extern s32 Cinema_IsSequenceActive(void);
#endif
