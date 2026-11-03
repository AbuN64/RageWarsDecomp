#ifndef RENDER_PLAYER_CONTROLLER_RESET_VIEWS_H
#define RENDER_PLAYER_CONTROLLER_RESET_VIEWS_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"

struct PlayerControllerResetStateView;
typedef struct PlayerControllerResetStateView PlayerControllerResetStateView;

struct PlayerMarkerPrismView;
struct PlayerMarkerPrismView {
    char pad0[0x1214];
    s32 marker;
    char pad1218[0x147C - 0x1218];
    s32 second;
    char pad1480[0x1500 - 0x1480];
    UnitMtx views[2];
    UnitMtx markers[2];
};

extern float g_playerInitialAimScale;

struct PlayerControllerReleaseView;
struct PlayerControllerReleaseView {
    char pad0[0x8];
    CVector3 position;
    char pad8[0x18 - 0x8 - sizeof(CVector3)];
    ObjectLinks4_3 model;
    char pad18[0x5D4 - 0x18 - sizeof(ObjectLinks4_3)];
    s32 playerIndex;
    char pad5D4[0x5D8 - 0x5D4 - sizeof(s32)];
    char * profile;
    char pad5D8[0x658 - 0x5D8 - sizeof(char*)];
    s32 stride;
    char pad658[0x668 - 0x658 - sizeof(s32)];
    s32 reservedWord668;
    char pad668[0x66C - 0x668 - sizeof(s32)];
    s32 reservedWord66C;
    char pad66C[0x6C0 - 0x66C - sizeof(s32)];
    s32 forwardSpeed;
    char pad6C0[0x6C4 - 0x6C0 - sizeof(s32)];
    s32 lateralSpeed;
    char pad6C4[0x6C8 - 0x6C4 - sizeof(s32)];
    s32 landing;
    char pad6C8[0x6CC - 0x6C8 - sizeof(s32)];
    s32 reservedWord6CC;
    char pad6CC[0x6D0 - 0x6CC - sizeof(s32)];
    s32 active;
    char pad6D0[0x6D4 - 0x6D0 - sizeof(s32)];
    s32 reservedWord6D4;
    char pad6D4[0x6D8 - 0x6D4 - sizeof(s32)];
    s32 reservedWord6D8;
    char pad6D8[0x6DC - 0x6D8 - sizeof(s32)];
    s32 reservedWord6DC;
    char pad6DC[0x6E4 - 0x6DC - sizeof(s32)];
    s32 reservedWord6E4;
    char pad6E4[0x6E8 - 0x6E4 - sizeof(s32)];
    CVector3 previousPosition;
    char pad6E8[0x6F4 - 0x6E8 - sizeof(CVector3)];
    FloatOrWord heightDelta;
    char pad6F4[0x6F8 - 0x6F4 - sizeof(FloatOrWord)];
    CVector3 previousTarget;
    char pad6F8[0x704 - 0x6F8 - sizeof(CVector3)];
    f32 reservedFloat704;
    char pad704[0x708 - 0x704 - sizeof(f32)];
    s32 reservedWord708;
    char pad708[0x70C - 0x708 - sizeof(s32)];
    s32 reservedWord70C;
    char pad70C[0x710 - 0x70C - sizeof(s32)];
    s32 reservedWord710;
    char pad710[0x714 - 0x710 - sizeof(s32)];
    s32 reservedWord714;
    char pad714[0x718 - 0x714 - sizeof(s32)];
    s32 crouchDepth;
    char pad718[0x71C - 0x718 - sizeof(s32)];
    s32 forceCrouch;
    char pad71C[0x720 - 0x71C - sizeof(s32)];
    s32 eyeOffset;
    char pad720[0x724 - 0x720 - sizeof(s32)];
    s32 pitchOffset;
    char pad724[0x728 - 0x724 - sizeof(s32)];
    s32 kickYaw;
    char pad728[0x72C - 0x728 - sizeof(s32)];
    s32 kickRoll;
    char pad72C[0x730 - 0x72C - sizeof(s32)];
    s32 swayPitch;
    char pad730[0x734 - 0x730 - sizeof(s32)];
    s32 swayYaw;
    char pad734[0x738 - 0x734 - sizeof(s32)];
    s32 swayRoll;
    char pad738[0x73C - 0x738 - sizeof(s32)];
    s32 sideOffset;
    char pad73C[0x740 - 0x73C - sizeof(s32)];
    f32 weaponHeight;
    char pad740[0x744 - 0x740 - sizeof(f32)];
    s32 forwardOffset;
    char pad744[0x748 - 0x744 - sizeof(s32)];
    Triple velocity;
    char pad748[0x754 - 0x748 - sizeof(Triple)];
    f32 velocityScale;
    char pad754[0x758 - 0x754 - sizeof(f32)];
    s32 bobStrength;
    char pad758[0x75C - 0x758 - sizeof(s32)];
    s32 bobSpeed;
    char pad75C[0x780 - 0x75C - sizeof(s32)];
    s32 cameraOffset;
    char pad780[0x784 - 0x780 - sizeof(s32)];
    f32 cameraScale;
    char pad784[0x788 - 0x784 - sizeof(f32)];
    s32 controllerMode;
    char pad788[0x78C - 0x788 - sizeof(s32)];
    s32 controllerTimer;
    char pad78C[0x790 - 0x78C - sizeof(s32)];
    s32 reservedWord790;
    char pad790[0x794 - 0x790 - sizeof(s32)];
    s32 controllerOwner;
    char pad794[0x798 - 0x794 - sizeof(s32)];
    s32 reservedWord798;
    char pad798[0x79C - 0x798 - sizeof(s32)];
    s32 reservedWord79C;
    char pad79C[0x7A0 - 0x79C - sizeof(s32)];
    s32 reservedWord7A0;
    char pad7A0[0x7A4 - 0x7A0 - sizeof(s32)];
    s32 reservedWord7A4;
    char pad7A4[0x7A8 - 0x7A4 - sizeof(s32)];
    s32 reservedWord7A8;
    char pad7A8[0x7AC - 0x7A8 - sizeof(s32)];
    s32 reservedWord7AC;
    char pad7AC[0x7B0 - 0x7AC - sizeof(s32)];
    WordOrFloat reservedWord7B0;
    char pad7B0[0x7B4 - 0x7B0 - sizeof(WordOrFloat)];
    s32 reservedWord7B4;
    char pad7B4[0x7B8 - 0x7B4 - sizeof(s32)];
    s32 reservedWord7B8;
    char pad7B8[0x7C0 - 0x7B8 - sizeof(s32)];
    f32 reservedFloat7C0;
    char pad7C0[0x7C4 - 0x7C0 - sizeof(f32)];
    f32 reservedFloat7C4;
    char pad7C4[0x7C8 - 0x7C4 - sizeof(f32)];
    f32 reservedFloat7C8;
    char pad7C8[0x7CC - 0x7C8 - sizeof(f32)];
    f32 reservedFloat7CC;
    char pad7CC[0x7D0 - 0x7CC - sizeof(f32)];
    f32 reservedFloat7D0;
    char pad7D0[0x7D4 - 0x7D0 - sizeof(f32)];
    f32 reservedFloat7D4;
    char pad7D4[0x7D8 - 0x7D4 - sizeof(f32)];
    CVector3 reservedVector7D8;
    char pad7D8[0x7E4 - 0x7D8 - sizeof(CVector3)];
    f32 aimScale;
    char pad7E4[0x7E8 - 0x7E4 - sizeof(f32)];
    s32 reservedWord7E8;
    char pad7E8[0x7EC - 0x7E8 - sizeof(s32)];
    s32 weaponChargeBlend;
    char pad7EC[0x7F0 - 0x7EC - sizeof(s32)];
    s32 reservedWord7F0;
    char pad7F0[0x80C - 0x7F0 - sizeof(s32)];
    s32 controllerEnabled;
    char pad80C[0x838 - 0x80C - sizeof(s32)];
    f32 reservedFloat838;
    char pad838[0x83C - 0x838 - sizeof(f32)];
    f32 reservedFloat83C;
    char pad83C[0x840 - 0x83C - sizeof(f32)];
    f32 recoveryTime;
    char pad840[0x848 - 0x840 - sizeof(f32)];
    s32 collisionState;
    char pad848[0x11B4 - 0x848 - sizeof(s32)];
    s32 locked;
    char pad11B4[0x11B8 - 0x11B4 - sizeof(s32)];
    s32 lockState;
    char pad11B8[0x1450 - 0x11B8 - sizeof(s32)];
    s32 computerControlled;
    char pad1450[0x16D4 - 0x1450 - sizeof(s32)];
    s32 score;
};

struct RouteCursorState;
typedef struct RouteCursorState RouteCursorState;

extern float g_playerHeightScalePair_us;

extern float g_playerAnimatedSpriteScaleYZ;

struct Cursor;
struct Cursor {
    s8 state;
    u8 clip;
    s16 frame;
    s16 previous;
};

extern float g_playerInitialMotionScale;

struct PlayerControllerResetStateView;
struct PlayerControllerResetStateView {
    unsigned char padding[141];
    s8 state;
};

struct Cursor;
typedef struct Cursor Cursor;

struct RouteCursorState;
#include "COMMON/ROUTE_CURSOR.H"
#include "PARTICLE/PARTICLE_UPDATESYSTEM.H"

struct PlayerMarkerPrismView;
typedef struct PlayerMarkerPrismView PlayerMarkerPrismView;

struct PlayerControllerReleaseView;
typedef struct PlayerControllerReleaseView PlayerControllerReleaseView;

typedef struct CompactAnimationState {
    s32 state;
    s32 active;
    u8 reserved8[4];
    s16 cursor;
    u8 flags;
    u8 reservedF[3];
    s8 clip;
    u8 reserved13;
} CompactAnimationState;

typedef struct AnimationSprite {
    u8 reserved0[8];
    s32 model;
    u8 reservedC[4];
    u8 matrices[2][0x40];
    f32 scaleX, scaleY, scaleZ;
    f32 pitch, yaw;
    u8 reservedA4[4];
    CVector3 position;
    s32 active;
} AnimationSprite;


void Player_ApplyPlayerDamage();
extern s32 g_teamScores[];

struct Shared_ActorView;
s32 Playerai_SelectCharacterSound(struct Shared_ActorView *, s32);
void Playerai_ResetDamageTimers(s32);
extern void *g_fragTagObjectiveActor;

extern void Geometry_SetColorDither(s32 ditherMode);
extern void Geometry_SetPrimitiveAlphaOverride(s32 enabled, s32 alpha);
extern void YawMatrix(void *matrix, f32 yawAngle);
#endif
