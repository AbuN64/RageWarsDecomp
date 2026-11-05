#ifndef COMMON_AIPROFILE_H
#define COMMON_AIPROFILE_H
#include "Ai/ai_shared_symbols.h"
#include "types.h"
struct AiProfile;
struct GameplayCamera;
#include <platform_sdk.h>
#include "Common/model_instance.h"
#include "Common/sharedplayer.h"
#include "Common/vector4f.h"
#include "Common/level_actor.h"
#include "Common/hud_effects.h"
#include "onscrn.h"
#include "Ai/Player/player_buildplayerviewtransform.h"
#include "Ai/Player/player_placeplayerforround.h"
#include "Engine/gdynlight.h"
struct Player;
struct RangeNode;
/* The reset record of the HUD effect block inside the player record. */
typedef struct PlayerHudEffect {
    s32 slot; /* 0x00 */
    s32 owner;
    s32 state;
    u8 padC[0x84];
    f32 scaleX; /* 0x90 */
    f32 scaleY;
    f32 scaleZ;
    s32 frame;
    f32 angle;
    s32 phase;
    s32 mode;
    f32 positionX;
    f32 positionY;
    s32 flags;
    s32 count;
} PlayerHudEffect;


struct CDLight_t;
typedef struct AiProfile {
    s16 roundTotals[6]; /* +0x00: round-reset totals */
    s16 roundCounts[4][8]; /* +0x0C */
    u8 pad4C[0x78 - 0x4C];
    u8 loadFlagFirst; /* +0x78: together with loadFlagSecond, selects navigation reset */
    u8 yawSensitivity; /* 0x79: Player_UpdateViewAngles */
    u8 sensitivity; /* 0x7A: ContPad_BuildControllerState */
    s8 controlMode; /* 0x7B */
    u8 remap; /* 0x7C */
    u8 pitchMode; /* 0x7D */
    u8 pad7E[2];
    s8 character; /* 0x80 */
    s8 variant; /* 0x81: Geometry_DrawCharacterEffectParts */
    u8 weaponWheelMode; /* 0x82: weapon wheel input mode */
    u8 menuSelection; /* +0x83: profile controller selection */
    char name[9]; /* +0x84: source-effect owner display name (unsure: one lane read 10 bytes, which overlaps roundFlags) */
    u8 roundFlags[2]; /* 0x8D: cleared on round reset; [1] is also the round-ended flag */
    u8 bonus; /* 0x8F: Geometry_DrawCharacterEffectParts, Player_UpdateRunEndPlayer */
    s8 state90; /* 0x90 */
    u8 sessionApplied; /* 0x91: profile unlocks applied this session; also the level-load navigation reset flag */
    u8 team; /* 0x92: Target_UpdateTargetSelection (team play) */
    u8 difficulty; /* 0x93 */
    u8 enabled; /* 0x94: Geometry_DrawCharacterEffectParts */
} AiProfile;


/* Handle and bookkeeping words cleared together when releasing this resource. */
typedef struct ResourceLoadState {
    s32 handle;
    s32 state4;
    s32 state8;
} ResourceLoadState;

struct Player {
    union {
        LevelActor actorParts[2]; /* +0x000, +0x2E8 */
        struct {
    u8 kind; /* 0x0 */
    u8 pad1[2];
    u8 playerId; /* 0x3 */
    u8 pad4[4];
    CVector3 pos; /* 0x8 */
    u8 pad14[0x4];
    void * definition; /* 0x18 */
    s32 actorMotionWords[3]; /* +0x1C */
    u8 pad28[0x10];
    s32 movementFlags; /* +0x38 */
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
    union {
        u8 motion[368]; /* +0x170: controller state; actorParts[0] owns its fields */
        struct { s32 motionState; s32 actorHealth; }; /* +0x174: remaining health, 8 fractional bits */
    };
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
    u8 pad598[4];
    s32 effectResetFlag; /* +0x59C: owned effect completion requests a reset */
    u8 pad5A0[4];
    s32 ammoRewardType; /* +0x5A4: ammo granted when the owned effect finishes */
    s32 ammoRewardAmount; /* +0x5A8 */
    u8 pad5AC[0x24];
        };
    };
    s32 actorState; /* +0x5D0 */
    s32 slot; /* 0x5D4 */
    struct AiProfile * profile; /* 0x5D8 */
    struct GameplayCamera *camera; /* 0x5DC: the camera following this player */
    s32 state; /* 0x5E0 */
    s32 health; /* 0x5E4 */
    u16 healthFraction; /* +0x5E8 */
    s16 respawnHealth; /* +0x5EA: sequence-actor state */
    s32 model; /* 0x5EC: Player_UpdateRunEndPlayer passes it to Player_PlacePlayerAtSpawnPoint */
    s32 reservedWord5F0; /* +0x5F0: cleared on pool initialization */
    s16 ammo[7]; /* 0x5F4 */
    union { s8 actions[22][2]; Shared_Slot weaponSlots[22]; }; /* +0x602 */
    s16 selectedAction; /* 0x62E */
    s16 queuedAction; /* 0x630 */
    s16 lastAction; /* 0x632 */
    u8 pad634[4];
    u32 trackEventBits; /* +0x638: Menu_TriggerTrackEvent bit set; Player_ResetPlayerForRound zeroes it */
    s32 roundStateB; /* 0x63C */
    s32 roundStateC; /* 0x640 */
    u8 eventCounters[2][6]; /* +0x644, +0x64A: round-reset counters */
    s16 pose; /* 0x650 */
    u8 pad652[6];
    f32 poseTimer; /* 0x658 */
    u8 pad65C[4];
    s32 flags660; /* 0x660 */
    s32 sequenceFlags; /* +0x664: motion-transition and short-sequence gates */
    u8 pad668[8];
    f32 damageCooldown; /* 0x670 */
    f32 europeanEffectTimer; /* 0x674: Pickup_ApplyEuropeanExtendedPowerup, powerup 1801 */
    f32 rangeTimer; /* 0x678: Player_UpdatePlayerEffectLights */
    struct CDLight_t *rangeNodes[3]; /* 0x67C: created by Gdynlight_AllocateLightNode */
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
    f32 lateralSpeed; /* +0x6C4: leap direction and landing damping */
    f32 landing; /* 0x6C8 */
    s32 landingLateral; /* 0x6CC */
    s32 active; /* 0x6D0 */
    s32 activeElapsed;
    s32 activeBlend;
    s32 activeResidual;
    f32 movementScale; /* 0x6E0 */
    f32 jumpDelay; /* +0x6E4: grounded jump delay */
    CVector3 previousPosition; /* 0x6E8 */
    f32 heightDelta; /* 0x6F4 */
    CVector3 previousTarget; /* 0x6F8 */
    u8 pad704[4];
    f32 pitchBias;
    f32 pitchBlendStart;
    f32 pitchBlendTarget;
    f32 pitchBlendProgress;
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
    CQuatern cameraOrientation; /* +0x760: copied from the following camera at HUD initialization */
    s16 weapon; /* 0x770 */
    u8 pad772[2];
    CVector3 requestedPosition; /* 0x774 */
    f32 cameraOffset; /* 0x780 */
    f32 cameraScale; /* 0x784 */
    s32 controllerMode; /* 0x788 */
    f32 controllerTimer; /* 0x78C */
    u8 pad790[4];
    void *controllerOwner; /* +0x794: controlled-actor owner */
    u8 pad798[0x24];
    s32 cinemaTimer; /* 0x7BC */
    u8 pad7C0[0x28];
    s32 state7E8; /* 0x7E8: ContPad_BuildControllerState */
    f32 state7EC; /* 0x7EC */
    u8 pad7F0[4];
    union { s32 modelState; f32 travelElapsed; }; /* +0x7F4: model-effect state or travel timer */
    f32 modelDistance; /* +0x7F8: horizontal angle of model-effect displacement */
    void *effectModel; /* +0x7FC: model entry returned for the effect */
    CVector3 effectPosition; /* +0x800: model-effect origin */
    s32 controllerEnabled; /* 0x80C */
    u8 pad810[0x30];
    f32 recoveryTime; /* +0x840: Playerai_ApplyDamageOverTime tick accumulator */
    u8 pad844[4];
    s32 collisionState; /* +0x848: landing / damage reaction state */
    u8 pad84C[4];
    s32 shortSequenceState; /* +0x850: gates the short round-end sequence */
    u8 pad854[8];
    s32 playerStateDirty; /* +0x85C: menu controller-profile state needs refresh */
    f32 roundEndWait; /* +0x860: elapsed round-end wait */
    s32 reservedWord864; /* +0x864: cleared at spawn */
    s32 reservedWord868; /* +0x868: cleared at spawn */
    s32 animation; /* 0x86C */
    s32 secondEffectId; /* 0x870 */
    u8 pad874[4];
    PlayerHudEffect hud; /* 0x878 */
    u8 pad934[4];
    s32 weaponBusy; /* 0x938 */
    u8 pad93C[0x37C];
    s32 weaponLocked; /* 0xCB8 */
    u8 padCBC[4];
    s32 pendingWeapon; /* 0xCC0: weapon to switch to (Player_AddAmmo_PickupApplyspecialpickup, Pickup_HandlePowerWeaponPickup) */
    u8 padCC4[0xD40 - 0xCC4];
    CItemMenu itemMenu; /* +0xD40 */
    u8 padMenuEnd[0xE2C - 0xD40 - sizeof(CItemMenu)];
    struct COverlay hudMovers[15]; /* +0xE2C: round-reset HUD widgets */
    s32 deathCount; /* 0x11B0 */
    s32 locked; /* 0x11B4 */
    s32 lockState; /* 0x11B8 */
    void *firstHandle; /* 0x11BC */
    void *secondHandle; /* 0x11C0 */
    s32 killCount; /* 0x11C4 */
    u8 pad11C8[4];
    s32 reservedWord11CC; /* +0x11CC: cleared on pool initialization */
    u8 pad11D0[8];
    f32 cooldown; /* 0x11D8 */
    f32 impulse; /* +0x11DC: accumulated impulse */
    u8 pad11E0[4];
    f32 pending; /* 0x11E4 */
    s32 reservedWord11E8; /* +0x11E8: cleared on pool initialization */
    f32 glow; /* 0x11EC: Geometry_DrawCharacterEffectParts */
    s32 weaponDraftHold; /* +0x11F0: cleared when the requested weapon changes */
    f32 fireSpin; /* 0x11F4 */
    s32 fireFrame; /* 0x11F8 */
    union { f32 zoom; s32 idleAnimationState; }; /* +0x11FC */
    CVector3 aimPosition; /* 0x1200 */
    s32 zoomMode; /* 0x120C */
    s32 overlay; /* 0x1210 */
    u8 pad1214[4];
    s32 reservedWord1218; /* +0x1218: zeroed on pool initialization and death */
    s32 projectileBase; /* +0x121C: ammo-drop definition group */
    s32 projectileIndex; /* +0x1220: alternating ammo-drop slot */
    void *projectiles[2]; /* +0x1224: Pickup_DispatchHandler clears lock-on targets */
    s32 reactionFlags; /* 0x122C */
    s32 reservedWord1230; /* +0x1230: cleared on death */
    s32 reservedWord1234; /* +0x1234: cleared on death */
    s32 reservedWord1238; /* +0x1238: set to -1 on death */
    u8 color[3]; /* 0x123C: Player_DrawPlayerBodyAndWeapon */
    u8 pad123F;
    f32 opacity; /* 0x1240 */
    u8 pad1244[0x12C0 - 0x1244];
    f32 reserve; /* +0x12C0: reserve depleted before damage dispatch */
    s32 reservedWord12C4; /* +0x12C4: cleared on pool initialization */
    s32 reservedWord12C8; /* +0x12C8: cleared on pool initialization */
    s32 reset12CC[8]; /* +0x12CC: pool-initialized record words */
    struct Player *partner; /* 0x12EC: Player_FormatPlayerPartnerStatus */
    u32 partnerStatus; /* 0x12F0: localized partner-status selector */
    s32 reset12F4[8]; /* +0x12F4: pool-initialized record words */
    u8 pad1314[0x20];
    s32 reservedWord1334; /* +0x1334: cleared on pool initialization */
    s32 reservedWord1338; /* +0x1338: initialized to -1 */
    s32 countdown; /* 0x133C: Player_UpdateRunEndPlayer */
    s32 resetState; /* 0x1340 */
    u8 messageHistory[5][0x15]; /* +0x1344: circular message text buffers */
    u8 pad13AD[3];
    s32 messageIndex; /* +0x13B0: circular message slot */
    void *animationTable; /* 0x13B4 */
    s32 weaponChanged; /* +0x13B8: Weaponai_ApplyWeaponSwitch */
    s32 secondaryChanged; /* +0x13BC */
    s32 specialChanged; /* +0x13C0 */
    u8 specialState; /* +0x13C4 */
    u8 pad13C5[3];
    s32 overkill; /* 0x13C8: Player_ApplyPlayerDamage, Player_DrawPlayerBodyAndWeapon */
    u8 pad13CC[8];
    s32 toggle; /* 0x13D4 */
    void *reactionOwner; /* 0x13D8 */
    u8 pad13DC[4];
    struct Player *effectSource; /* +0x13E0: Player_StartSourceEffect */
    s32 attachedSpecialEffectCount; /* +0x13E4: limited type 298/306 contact attachment */
    s32 scoreResetFlag; /* 0x13E8 */
    u8 effectPayload[100]; /* +0x13EC: formatted source-effect message */
    s32 computer; /* 0x1450 */
    struct AiController * controller; /* 0x1454 */
    CVector3 aimPoint; /* +0x1458 */
    CVector3 aimPoint2; /* +0x1464 */
    CVector3 aimNormal; /* +0x1470 */
    void *aimTarget; /* +0x147C */
    Matrix beams[2]; /* +0x1480 */
    Matrix lasers[2]; /* +0x1500 */
    Matrix dots[2]; /* +0x1580 */
    f32 transform1600[16]; /* +0x1600 */
    u8 pad1640[0x80];
    f32 turnAccumulator; /* +0x16C0 */
    CVector3 resetPosition; /* +0x16C4 */
    u8 pad16D0[4];
    s32 pickupEffectToggle; /* +0x16D4: Pickup_ToggleEffectAndFlash */
    u16 pendingBonus; /* +0x16D8 */
    u8 pad16DA[6];
    struct Player *next; /* +0x16E0: g_transientPlayerList link */
    u8 pad16E4[4]; /* Allocation stride: 0x16E8. */
};



extern struct Player *g_playerSequenceActor;


struct MenuValueStepView;

struct ScreenMessageTextView;
struct ScreenMessageTextView {
    u8 * text;
};
#include "Common/screenmessagesubstitution.h"


struct Player;
typedef struct Player Player;


struct Course;
struct Course {
    char pad0[0x28];
    u8 laps;
};

struct CollisionQuery;
typedef struct CollisionQuery CollisionQuery;





typedef struct CCameraText_t {
    struct CCameraText_t *prev; /* 0x00 */
    struct CCameraText_t *next; /* 0x04: traversal from the message pool head */
    f32 m_Time; /* 0x08 */
    f32 m_DisplayTime;
    f32 alpha;
    s32 kind;
    s32 m_nAlpha;
    s32 target;
    s32 forceScaledText; /* 0x20: flagged posts force the scaled-text draw branch. */
    u8 *text;
    f32 m_ModeTime;
    /* 0x2C: reset on posting; five-region census: four zero-store writer sites per region, no message-pointer read. */
    s32 postResetWord;
    f32 x;
    f32 y;
    f32 m_XScale;
    f32 m_YScale;
} CCameraText_t;




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


extern int g_fragTagModelId;


typedef struct CCameraText_t CCameraText;









struct ScreenMessageTextView;
typedef struct ScreenMessageTextView ScreenMessageTextView;

struct ModelBlend;
struct ModelBlend {
    s32 kind; /* 0x00 */
    char pad4[0x24];
    s16 modelIndex; /* +0x28: kind-3 actor definition selects a model */
    u8 pad2A[2];
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













struct ModelBlend;
typedef struct ModelBlend ModelBlend;

struct Course;
typedef struct Course Course;






struct ResourceKeyView;
struct ResourceKeyView {
    char pad0[0x4];
    s32 key;
};








extern int g_characterModelIds[];

struct MenuValueStepView;
typedef struct MenuValueStepView MenuValueStepView;

struct PlayerProfileStatusView;
typedef struct PlayerProfileStatusView PlayerProfileStatusView;



struct CollisionQuery;
struct CollisionQuery {
    s32 w[7];
};


struct ResourceKeyView;
typedef struct ResourceKeyView ResourceKeyView;


#endif
