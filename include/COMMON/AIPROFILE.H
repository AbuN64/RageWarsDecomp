#ifndef COMMON_AIPROFILE_H
#define COMMON_AIPROFILE_H
#include "TYPES.H"
struct GameplayCamera;
#include <ultra64.h>
#include "COMMON/MODEL_INSTANCE.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VECTOR4F.H"
struct Player;
struct RangeNode;
typedef struct AiProfile {
    u8 pad0[0x79];
    u8 yawSensitivity; /* 0x79: Player_UpdateViewAngles */
    u8 sensitivity; /* 0x7A: ContPad_BuildControllerState */
    s8 controlMode; /* 0x7B */
    u8 remap; /* 0x7C */
    u8 pitchMode; /* 0x7D */
    u8 pad7E[2];
    s8 character; /* 0x80 */
    s8 variant; /* 0x81: Geometry_DrawCharacterEffectParts */
    u8 pad82[0xD];
    u8 bonus; /* 0x8F: Geometry_DrawCharacterEffectParts, Player_UpdateRunEndPlayer */
    s8 state90; /* 0x90 */
    u8 pad91[1];
    u8 team; /* 0x92: Target_UpdateTargetSelection (team play) */
    u8 difficulty; /* 0x93 */
    u8 enabled; /* 0x94: Geometry_DrawCharacterEffectParts */
} AiProfile;


struct Player {
    u8 kind; /* 0x0 */
    u8 pad1[2];
    u8 playerId; /* 0x3 */
    u8 pad4[4];
    CVector3 pos; /* 0x8 */
    u8 pad14[0x4];
    void * definition; /* 0x18 */
    u8 pad1C[0x1C];
    s32 movementFlags; /* 0x38 */
    u8 pad3C[0x14];
    CVector3 scale; /* 0x50 */
    CQuatern orientation; /* 0x5C */
    f32 heading; /* 0x6C */
    u8 pad70[0x4];
    f32 matrix[16]; /* 0x74 */
    u8 padB4[0x30];
    u16 objectId; /* 0xE4 */
    u8 padE6[0x1A];
    s32 weaponFlags; /* 0x100 */
    u8 pad104[0xA];
    s8 animationDone; /* 0x10E */
    u8 pad10F[0x61];
    u8 motion[368]; /* 0x170 */
    u8 pad2E0[8];
    struct ObjectSceneChangeInstanceModel weaponModel; /* 0x2E8 */
    u8 pad3CE[0xB6];
    struct AiBehaviourTable *weaponAnimationTable; /* 0x484 */
    u8 pad488[0xF0];
    s32 weaponAnimationCount; /* 0x578 */
    f32 weaponSpinStep; /* 0x57C: weapon state +0x124 */
    f32 weaponSpin; /* 0x580: weapon state +0x128 */
    u8 pad584[0xC];
    s32 weaponReset; /* 0x590: weapon state +0x138 */
    s32 gear; /* 0x594 */
    u8 pad598[0x3C];
    s32 slot; /* 0x5D4 */
    AiProfile * profile; /* 0x5D8 */
    struct GameplayCamera *camera; /* 0x5DC: the camera following this player */
    s32 state; /* 0x5E0 */
    s32 health; /* 0x5E4 */
    u8 pad5E8[4];
    s32 model; /* 0x5EC: Player_UpdateRunEndPlayer passes it to Player_PlacePlayerAtSpawnPoint */
    u8 pad5F0[4];
    s16 ammo[7]; /* 0x5F4 */
    s8 actions[22][2]; /* 0x602 */
    s16 selectedAction; /* 0x62E */
    s16 queuedAction; /* 0x630 */
    s16 lastAction; /* 0x632 */
    u8 pad634[0x1C];
    s16 pose; /* 0x650 */
    u8 pad652[6];
    f32 poseTimer; /* 0x658 */
    u8 pad65C[4];
    s32 flags660; /* 0x660 */
    u8 pad664[0xC];
    f32 damageCooldown; /* 0x670 */
    f32 europeanEffectTimer; /* 0x674: Pickup_ApplyEuropeanExtendedPowerup, powerup 1801 */
    f32 rangeTimer; /* 0x678: Player_UpdatePlayerEffectLights */
    struct RangeNode *rangeNodes[3]; /* 0x67C: created by Gdynlight_AllocateLightNode */
    u8 tuning[16]; /* 0x688 */
    void *weaponAnimation; /* 0x698 */
    f32 steer; /* 0x69C */
    f32 pitch; /* 0x6A0 */
    f32 strafe; /* 0x6A4 */
    f32 forward; /* 0x6A8 */
    s32 inputFlags; /* 0x6AC */
    s32 actionFlags; /* 0x6B0 */
    u8 pad6B4[0xC];
    f32 stick; /* 0x6C0 */
    s32 state6C4; /* 0x6C4 */
    f32 landing; /* 0x6C8 */
    s32 state6CC; /* 0x6CC */
    s32 active; /* 0x6D0 */
    s32 state6D4;
    s32 state6D8;
    s32 state6DC;
    f32 movementScale; /* 0x6E0 */
    s32 state6E4;
    CVector3 previousPosition; /* 0x6E8 */
    f32 heightDelta; /* 0x6F4 */
    CVector3 previousTarget; /* 0x6F8 */
    u8 pad704[4];
    f32 state708;
    f32 state70C;
    f32 state710;
    f32 state714;
    f32 crouchDepth; /* 0x718 */
    s32 forceCrouch; /* 0x71C */
    f32 eyeOffset; /* 0x720 */
    f32 pitchOffset; /* 0x724 */
    f32 kickYaw; /* 0x728: Player_BuildPlayerViewTransform adds it to the heading */
    f32 lean; /* 0x72C: kick roll */
    f32 sway[3]; /* 0x730: pitch, yaw, roll sway angles */
    f32 sideOffset; /* 0x73C: weapon side offset (x) */
    f32 baseHeight; /* 0x740 */
    f32 forwardOffset; /* 0x744: weapon forward offset (z) */
    CVector3 velocity; /* 0x748 */
    f32 velocityScale; /* 0x754 */
    s32 state758;
    s32 state75C;
    u8 pad760[0x10];
    s16 weapon; /* 0x770 */
    u8 pad772[2];
    CVector3 requestedPosition; /* 0x774 */
    f32 cameraOffset; /* 0x780 */
    f32 cameraScale; /* 0x784 */
    s32 controllerMode; /* 0x788 */
    f32 controllerTimer; /* 0x78C */
    u8 pad790[0x58];
    s32 state7E8; /* 0x7E8: ContPad_BuildControllerState */
    f32 state7EC; /* 0x7EC */
    u8 pad7F0[0x1C];
    s32 controllerEnabled; /* 0x80C */
    u8 pad810[0x5C];
    s32 animation; /* 0x86C */
    u8 pad870[0xC8];
    s32 weaponBusy; /* 0x938 */
    u8 pad93C[0x37C];
    s32 weaponLocked; /* 0xCB8 */
    u8 padCBC[4];
    s32 pendingWeapon; /* 0xCC0: weapon to switch to (Player_AddAmmo_PickupApplyspecialpickup, Pickup_HandlePowerWeaponPickup) */
    u8 padCC4[0x4F0];
    s32 locked; /* 0x11B4 */
    s32 lockState; /* 0x11B8 */
    void *firstHandle; /* 0x11BC */
    void *secondHandle; /* 0x11C0 */
    u8 pad11C4[0x14];
    f32 cooldown; /* 0x11D8 */
    u8 pad11DC[8];
    f32 pending; /* 0x11E4 */
    u8 pad11E8[4];
    f32 glow; /* 0x11EC: Geometry_DrawCharacterEffectParts */
    u8 pad11F0[4];
    f32 fireSpin; /* 0x11F4 */
    s32 fireFrame; /* 0x11F8 */
    f32 zoom; /* 0x11FC */
    CVector3 aimPosition; /* 0x1200 */
    s32 zoomMode; /* 0x120C */
    s32 overlay; /* 0x1210 */
    u8 pad1214[0x18];
    s32 reactionFlags; /* 0x122C */
    u8 pad1230[0xC];
    u8 color[3]; /* 0x123C: Player_DrawPlayerBodyAndWeapon */
    u8 pad123F;
    f32 opacity; /* 0x1240 */
    u8 pad1244[0xF8];
    s32 countdown; /* 0x133C: Player_UpdateRunEndPlayer */
    s32 resetState; /* 0x1340 */
    u8 pad1344[0x70];
    void *animationTable; /* 0x13B4 */
    u8 pad13B8[0x10];
    s32 overkill; /* 0x13C8: Player_ApplyPlayerDamage, Player_DrawPlayerBodyAndWeapon */
    u8 pad13CC[8];
    s32 toggle; /* 0x13D4 */
    void *reactionOwner; /* 0x13D8 */
    u8 pad13DC[0x74];
    s32 computer; /* 0x1450 */
    struct AiController * controller; /* 0x1454 */
};



struct ActionTargetPlayerView;
typedef struct ActionTargetPlayerView ActionTargetPlayerView;

struct MenuValueStepView;

struct ScreenMessageTextView;
struct ScreenMessageTextView {
    u8 * text;
};


struct Player;
typedef struct Player Player;


struct Course;
struct Course {
    char pad0[0x28];
    u8 laps;
};

struct CollisionQuery;
typedef struct CollisionQuery CollisionQuery;


struct MenuActorInputView;
typedef struct MenuActorInputView MenuActorInputView;

struct MenuActorInputView;
struct MenuActorInputView {
    char pad0[0xC];
    s16 input;
};


struct CCameraText_t;
struct CCameraText_t {
    struct CCameraText_t *prev; /* 0x00 */
    struct CCameraText_t *next; /* 0x04: traversal from the message pool head */
    f32 m_Time; /* 0x08 */
    f32 m_DisplayTime;
    f32 alpha;
    s32 kind;
    s32 m_nAlpha;
    s32 target;
    s32 pad20;
    u8 *text;
    f32 m_ModeTime;
    s32 pad2C;
    f32 x;
    f32 y;
    f32 m_XScale;
    f32 m_YScale;
};

struct CCameraText_t;



struct Body;
struct Character;
struct Controller;
struct Controls;
struct Ctrl;
struct Held;
struct Mode;
struct Model;
struct Mount;
struct Profile;
struct Record;
struct Rider;
struct Settings;
struct Shared_Body;
struct Shared_Hud;
struct Shared_Model;
struct Shared_Profile;
struct Shared_StateInfo;
struct Shared_Voice;
struct StateInfo;
struct TeamInfo;
struct View;

struct ActorDefinitionPointerView;
struct ActorDefinitionPointerView {
    char pad0[0x18];
    void * definition;
};

extern int g_fragTagModelId;


struct CCameraText_t;
typedef struct CCameraText_t CCameraText;


struct CCameraText_t;



struct PlayerCameraMotionView;
typedef struct PlayerCameraMotionView PlayerCameraMotionView;


struct PlayerNameProfileView;
typedef struct PlayerNameProfileView PlayerNameProfileView;

struct PlayerNameProfileView;
struct PlayerNameProfileView {
    char pad0[0x5D8];
    void * profile;
};

struct ScreenMessageTextView;
typedef struct ScreenMessageTextView ScreenMessageTextView;

struct ModelBlend;
struct ModelBlend {
    s32 kind; /* 0x00 */
    char pad4[0x28];
    f32 blend; /* 0x2C: model-specific player interpolation target */
    u8 pad30[4];
    CVector3 effectOffset; /* 0x34 */
    u8 pad40[4];
    s32 collisionFlags; /* 0x44: model collision eligibility */
    char pad48[4];
    u32 collisionOptions; /* 0x4C */
    char pad50[2];
    u16 materialFlags; /* 0x52 */
    char pad54[4];
    u8 byte58; /* model byte queried by Region_GetModelBlendByte58 */
    u8 byte59; /* model byte queried by Region_GetModelBlendByte59 */
    char pad5A[0x9A];
    f32 height;
};

struct GamePlayerListView;
struct GamePlayerListView {
    char pad0[0x20];
    char * players;
};






struct CCameraText_t;

struct ActorFlagsWordView;
struct ActorFlagsWordView {
    char pad0[0x38];
    s32 flags;
};

struct ActorFlagsWordView;
typedef struct ActorFlagsWordView ActorFlagsWordView;




struct ModelBlend;
typedef struct ModelBlend ModelBlend;

struct Course;
typedef struct Course Course;

struct PlayerCameraMotionView;
struct PlayerCameraMotionView {
    char pad0[0x18];
    char * definition;
    char pad18[0x38 - 0x18 - sizeof(char*)];
    s32 flags;
};


struct ActorModelIndexView;
struct ActorModelIndexView {
    char pad0[0x28];
    s16 modelIndex;
};


struct ActionTargetPlayerView;
struct ActionTargetPlayerView {
    char pad0[0x1D8];
    char * player;
};

struct ResourceKeyView;
struct ResourceKeyView {
    char pad0[0x4];
    s32 key;
};




struct WorldPlayerHeadView;
struct WorldPlayerHeadView {
    char pad0[0x20];
    void * players;
};

struct GamePlayerListView;
typedef struct GamePlayerListView GamePlayerListView;



extern int g_characterModelIds[];

struct MenuValueStepView;
typedef struct MenuValueStepView MenuValueStepView;

struct PlayerProfileStatusView;
typedef struct PlayerProfileStatusView PlayerProfileStatusView;


struct ActorDefinitionPointerView;
typedef struct ActorDefinitionPointerView ActorDefinitionPointerView;

struct CollisionQuery;
struct CollisionQuery {
    s32 w[7];
};


struct ResourceKeyView;
typedef struct ResourceKeyView ResourceKeyView;

struct WorldPlayerHeadView;
typedef struct WorldPlayerHeadView WorldPlayerHeadView;

#endif
