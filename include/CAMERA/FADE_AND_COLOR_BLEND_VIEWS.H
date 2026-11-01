#ifndef CAMERA_FADE_AND_COLOR_BLEND_VIEWS_H
#define CAMERA_FADE_AND_COLOR_BLEND_VIEWS_H
#include "COMMON/VIEWFLAGS.H"
#include "COMMON/SHAREDPLAYER.H"
/* XYZ minimum and maximum bounds, copied as a single record. */
typedef struct ViewFlags { s32 flags; } ViewFlags;
struct CameraObjectPositionView {
    char pad0[0x260];
    struct Triple position;
};
/* Color keyframe payload in a 0x64-byte model-section record. */
typedef struct ColorBlendRecord {
    u8 color[4];
    u8 heldColor[4];
    u32 n, heldN;
    f32 a, b, heldA, heldB;
    u8 reservedBytes[4];
    f32 period;
    u8 reservedBytes1[0x64 - 0x28];
} ColorBlendRecord;
struct Overlay {
    char pad0[0x538];
    f32 timer;
    char pad53C[8];
    u32 state;
    char pad548[2];
    u8 alphaMax;
    u8 fadeIn;
    u8 hold;
    u8 fadeOut;
    char pad54E[3];
    u8 alpha;
};
struct ShakeEmitterChannelView {
    char pad0[0xA8];
    CVector3 position;
    char padA8[0xB4 - 0xA8 - sizeof(CVector3)];
    f32 scale;
    char padB4[0xB8 - 0xB4 - sizeof(f32)];
    s32 firstValue;
    char padB8[0xBC - 0xB8 - sizeof(s32)];
    f32 firstRate;
    char padBC[0xCC - 0xBC - sizeof(f32)];
    s32 secondValue;
    char padCC[0xD0 - 0xCC - sizeof(s32)];
    f32 secondRate;
    char padD0[0xE0 - 0xD0 - sizeof(f32)];
    s32 thirdValue;
    char padE0[0xE4 - 0xE0 - sizeof(s32)];
    f32 thirdRate;
};
struct LensFlareEffectState {
    s32 enabled;
    s32 stateWordOne;
    s32 stateWordTwo;
    s32 stateWordThree;
    s32 stateWordFour;
    s32 stateWordFive;
    s32 stateWordSix;
    s32 stateWordSeven;
    union {s32 i; f32 f;} initialScalar;
    CVector3 v;
    f32 scale;
    s32 stateWordEight;
    f32 scalarOffset;
    f32 defaultAngle;
    s32 defaultStateValue;
};
struct ThreeChannels {
    char pad0[0x520];
    u8 first;
    u8 second;
    u8 third;
};
typedef union Rotation { f32 f[4]; u32 word[4]; } Rotation;
typedef union TransformVector { CVector3 value; u32 word[3]; } TransformVector;
extern void Camera_AdvanceOverlayFade(Overlay *overlay);
extern void Camera_AccumulateDistanceScaledShake(CShake *shake, CVector3 position, CVector3 *out);
#endif
