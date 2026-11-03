#ifndef COMMON_VIEWFLAGS_H
#define COMMON_VIEWFLAGS_H
#include "TYPES.H"
#include "COMMON/STATERECAT10.H"
#include "COMMON/CAMERA_SHAKE.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/GAMEPLAY_CAMERA.H"
/* The camera view fade timer, the word after the view flags g_cameraRenderFlagState (its own global: read with its own lui). */
extern f32 g_cameraFramingTransitionTimer;
struct Triple;
struct CameraObjectPositionView;


struct GameplayCamera;

struct Overlay;
typedef struct Overlay Overlay;




extern float g_cameraShakeDistanceComplement;



struct ShakeEmitterChannelView;
typedef struct ShakeEmitterChannelView ShakeEmitterChannelView;



struct CameraObjectPositionView;
typedef struct CameraObjectPositionView CameraObjectPositionView;

extern float k_cameraInitialBobAmplitudeY;


struct Overlay;


struct ShakeEmitterChannelView;




struct ThreeChannels;
typedef struct ThreeChannels ThreeChannels;

extern float k_cameraInitialBobAmplitudeX;

struct LensFlareEffectState;
typedef struct LensFlareEffectState LensFlareEffectState;

struct ScreenMessageOwner;


struct WorldCameraDrawActiveViews;
typedef struct WorldCameraDrawActiveViews WorldCameraDrawActiveViews;



struct WorldCameraDrawActiveViews;
struct WorldCameraDrawActiveViews {
    char pad0[0x12A5];
    u8 replay;
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
