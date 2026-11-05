#ifndef COMMON_VIEWFLAGS_H
#define COMMON_VIEWFLAGS_H
#include "types.h"
#include "Common/weapon_special_fire.h"
#include "Common/camera_shake.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "Common/resident_event_handler.h"
#include "Common/gameplay_camera.h"
struct Box;
/* The camera view fade timer, the word after the view flags g_cameraRenderFlagState (its own global: read with its own lui). */
extern f32 g_cameraFramingTransitionTimer;
struct Triple;


struct GameplayCamera;

struct Overlay;
typedef struct Overlay Overlay;




extern float g_cameraShakeDistanceComplement;



struct ShakeEmitterChannelView;
typedef struct ShakeEmitterChannelView ShakeEmitterChannelView;




extern float k_cameraInitialBobAmplitudeY;


struct Overlay;


struct ShakeEmitterChannelView;




struct ThreeChannels;
typedef struct ThreeChannels ThreeChannels;

extern float k_cameraInitialBobAmplitudeX;

struct LensFlareEffectState;
typedef struct LensFlareEffectState LensFlareEffectState;

struct ScreenMessageOwner;












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

extern struct Box g_cameraClipBounds;

extern s32 Cinema_IsSequenceActive(void);
#endif
