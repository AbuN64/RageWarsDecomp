#ifndef COMMON_GAMEPLAY_CAMERA_H
#define COMMON_GAMEPLAY_CAMERA_H
#include "TYPES.H"
#include "COMMON/VIEWFLAGS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/TEXTLAYERMETRICS.H"
/* Complete camera records and callback ABI from origin/legacy Camera_UpdateViewProjectionAndEffects_GameplayCamera.c. */
typedef struct CameraRuntimeMode CameraRuntimeMode;
struct CameraRuntimeMode {
    s32 mode; /* +0x0: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
};


typedef struct Lights Lights;
struct Lights {
    s8 light0R; /* +0x0: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    s8 light0G; /* +0x1: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    s8 light0B; /* +0x2: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    s8 light0PadA; /* +0x3: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    s8 light0CopyR; /* +0x4: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    s8 light0CopyG; /* +0x5: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    s8 light0CopyB; /* +0x6: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    s8 light0PadB; /* +0x7: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    s8 light0DirX; /* +0x8: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    s8 light0DirY; /* +0x9: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    s8 light0DirZ; /* +0xA: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    char padB[0x5];
    s8 light1R; /* +0x10: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    u8 light1G; /* +0x11: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    s8 light1B; /* +0x12: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    s8 light1PadA; /* +0x13: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    s8 light1CopyR; /* +0x14: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    u8 light1CopyG; /* +0x15: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    s8 light1CopyB; /* +0x16: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    s8 light1PadB; /* +0x17: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    s8 light1DirX; /* +0x18: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    s8 light1DirY; /* +0x19: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    s8 light1DirZ; /* +0x1A: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    char pad1B[0x5];
};


typedef struct SharedCameraOwnerView SharedCameraOwnerView;
struct SharedCameraOwnerView {
    char pad0[0x5DC];
    s32 camera; /* +0x5DC: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    char pad5E0[0x84];
    s32 movementFlags; /* +0x664: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    char pad668[0x60];
    f32 bobSpeed; /* +0x6C8: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    char pad6CC[0x1014];
    void * nextActor; /* +0x16E0: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
};


typedef struct GameplayCamera GameplayCamera;
struct GameplayCamera {
    char pad0[4];
    GameplayCamera *next; /* 0x04: camera list link */
    s32 index; /* 0x08: which of the split-screen views this is (CCamera_t m_Index) */
    f32 pixelXScale; /* 0x0C */
    f32 pixelYScale; /* 0x10 */
    s16 mode; /* +0x14: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    char pad16[0x2];
    f32 elapsed; /* +0x18: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    s16 state; /* 0x1C */
    u8 pad1E[2];
    s32 stateCounter; /* 0x20 */
    s32 bobSuppressed; /* +0x24: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    f32 lensFlareInputOne;
    f32 lensFlareInputTwo;
    f32 lensFlareInputThree;
    f32 lensFlareInputFour;
    f32 floorSampleX; /* +0x38: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    f32 floorSampleY; /* +0x3C: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    f32 floorSampleZ; /* +0x40: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    f32 floorHeightOffset; /* +0x44: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    Shared_Quad floorSampleData;
    struct CameraFloorSurfaceView *floorPoly; /* +0x58: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    f32 zoomBlend; /* +0x5C: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    f32 zoomFov; /* +0x60: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    s32 floorSurface; /* +0x64: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    u16 perspNorm; /* +0x68: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    char pad6A[0x2];
    f32 fovY; /* +0x6C: vertical field of view in degrees, the angle the projection is built with */
    f32 aspect; /* +0x70: projection aspect ratio (width over height) */
    f32 farHalfWidth; /* +0x74: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    f32 farHalfHeight; /* +0x78: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    s32 dirty; /* +0x7C: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    f32 stretchX; /* +0x80: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    f32 stretchY; /* +0x84: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    f32 bobAmplitudeX; /* +0x88: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    f32 bobAmplitudeY; /* +0x8C: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    f32 bobPhaseX; /* +0x90: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    f32 bobPhaseY; /* +0x94: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    f32 bobRateX; /* +0x98: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    f32 bobRateY; /* +0x9C: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    char padA0[0x18];
    char shakeAxisX[20]; /* +0xB8: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    char shakeAxisY[20]; /* +0xCC: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    char shakeAxisZ[20]; /* 0xE0: third CShakeAxis */
    f32 shakeHorizontal; /* 0xF4 */
    f32 shakeVertical; /* 0xF8 */
    s32 fadeParameterMode;
    s32 fadeParameterState;
    s32 fadeParameterOne;
    s32 fadeParameterTwo;
    s32 fadeParameterThree;
    f32 fadeScalarOne;
    f32 fadeScalarTwo;
    s32 fadeParameterFour;
    char pad11C[4];
    s32 monochrome; /* 0x120: ribbons draw grey while set */
    u16 kickStep; /* +0x124: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    s16 reservedHalf;
    CVector3 position; /* +0x128: camera position */
    char pad134[0x4];
    f32 roll; /* +0x138: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    char pad13C[4];
    CQuatern orientation;
    f32 billboardQuaternion; /* +0x150: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    char pad154[0xC];
    f32 viewOrient[16]; /* 0x160: view-to-world rotation (CCamera_t m_mfViewOrient) */
    f32 inverseViewOrient[16]; /* 0x1A0: world-to-view rotation (m_mfInverseViewOrient) */
    f32 viewProjection[16]; /* 0x1E0: float projection the fixed one at 0x380 is packed from (m_mfProjection) */
    f32 worldToView[16]; /* 0x220: world-to-view transform; its z is a point's depth (m_mfView) */
    CVector3 corners[5];
    f32 viewWidth; /* +0x29C: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    f32 viewHeight; /* +0x2A0: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    f32 viewLeft;
    f32 viewTop;
    char pad2AC[0x44];
    CQuatern clipPlanes[6];
    CVector3 clipBounds[2];
    CVector3 volumeBounds[2];
    char projection[2][64]; /* +0x380: double-buffered projection matrices */
    Lights lights[2]; /* +0x400: double-buffered lights */
    u16 hudPerspNorm; /* +0x440: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    char pad442[0x6];
    char hudProjection[3][64]; /* +0x448: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    char pad508[0x10];
    s32 reservedWord;
    f32 reservedFloat;
    u8 reservedByteA;
    u8 reservedByteB;
    u8 reservedByteC;
    u8 reservedByteD;
    u8 reservedByteE;
    u8 reservedByteF;
    u8 reservedByteG;
    u8 reservedByteH;
    f32 farPlane; /* +0x528: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    f32 reservedFloatB;
    f32 verticalFieldOfView;
    f32 reservedFloatC;
    s32 fadeCounter; /* 0x538 */
    s32 fogNear; /* 0x53C */
    s32 reservedWordB;
    s32 fadeEnabled; /* 0x544 */
    u8 reservedByteI;
    u8 pad549;
    s8 fadeMode; /* 0x54A */
    s8 fadeRed, fadeGreen, fadeBlue;
    s8 fadeStart, fadeEnd, fadeStep, fadeState;
    u8 pad552[2];
    MessageList messageList; /* 0x554 */
    u8 pad56C[4];
    s8 sceneEffects; /* +0x570: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    char pad571[0xE40 - 0x571];
    IntrusiveList objects;
    f32 faceScreen[16]; /* 0xE54: billboard rotation facing the screen (m_mfFaceScreen) */
    f32 faceScreenUpright[16]; /* 0xE94: billboard rotation about Y only, keeping Y up (m_mfFaceScreenYAxisUp) */
    u8 alignED4[4]; /* CCamera_t is 0xED8 bytes: its packed-matrix members align it to 8 */
};



typedef struct SharedCameraRenderView SharedCameraRenderView;
struct SharedCameraRenderView {
    s32 renderMode; /* +0x0: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    s32 reservedWord; /* +0x4: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    s32 alternateViewEnabled; /* +0x8: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    char padC[4];
    RacerViewport view; /* +0x10: g_fallbackScreenMessageEmitter, the render view embedded in g_playerWeaponClassMode */
    char padView[0x122F - 0x10 - sizeof(RacerViewport)];
    u8 sequenceViewReady; /* +0x122F: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    char pad1230[0x590];
    CameraRuntimeMode state; /* +0x17C0: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
};



typedef struct CameraFloorSurfaceView CameraFloorSurfaceView;
struct CameraFloorSurfaceView {
    char pad0[0x1C];
    s32 surfaceType; /* +0x1C: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
};


typedef struct Shared_CameraModeCallback Shared_CameraModeCallback;
struct Shared_CameraModeCallback {
    s32 (*fn)(s8 *); /* +0x0: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
    s32 pad; /* +0x4: src/Camera_UpdateViewProjectionAndEffects_GameplayCamera.c */
};


/* The list header and complete primary camera, followed by the effect pools. */
typedef struct RaceViewportState {
    RaceHeader header;
    GameplayCamera self;
    char padAfterCamera[0x11D8 - sizeof(RaceHeader) - sizeof(GameplayCamera)];
    IntrusiveList freeEffects;
    IntrusiveList activeEffects;
} RaceViewportState;
#endif
