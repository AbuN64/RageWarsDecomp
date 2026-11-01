#ifndef COMMON_SHAREDCALLBACK5_H
#define COMMON_SHAREDCALLBACK5_H
#include "TYPES.H"
#include "COMMON/BRAIN.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"

extern float g_difficultyAimAmountScale;


struct PlayerAimActorView;
typedef struct PlayerAimActorView PlayerAimActorView;






struct PlayerAimActorView;
struct PlayerAimActorView {
    char pad0[0x594];
    s32 gear;
    char pad598[0x104];
    f32 steer;
};






struct PlayerAimBrainView;
typedef struct PlayerAimBrainView PlayerAimBrainView;

struct PlayerAimBrainView;
struct PlayerAimActorView;
struct PlayerAimBrainView {
    struct PlayerAimActorView *player;
    char pad4[0x244];
    f32 speed[4];
};









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
struct PlayerProfileStatusView;
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

struct Behaviour;
struct Behaviour {
    char pad0[8];
    void (*update)(SharedPlayer *, s32);
};
struct Behaviour;





extern float g_difficultyAimHeightOffset;

typedef struct PitchProfile { char pad00[0x8F]; u8 scaled; } PitchProfile;
typedef struct PitchModel { char pad00[0x12C]; f32 height; } PitchModel;
typedef struct PitchPlayer {
    char pad00[8]; CVector3 position; char pad14[0x5C4];
    PitchProfile *profile; PitchModel *model;
    char pad5E0[0xE70]; s32 transformed;
} PitchPlayer;
typedef struct PitchTarget { char pad00[0x1D8]; PitchPlayer *player; } PitchTarget;
typedef struct PitchBrain {
    PitchPlayer *player; char pad04[0x60]; PitchTarget *target;
    char pad68[0x1E0]; f32 angle, previousAngle; char pad250[8];
    CVector3 targetPosition; f32 distance;
} PitchBrain;
extern f32 g_targetPitchDownAngle;
extern f32 g_targetPitchUpAngle;


#include "COMMON/AIPROFILE.H"
typedef struct AiTarget {
    u8 pad0[0x8];
    CVector3 position; /* 0x8 */
    u8 pad14[0xEC];
    u32 flags; /* 0x100: 0x300000 = may be targeted */
    u8 pad104[0xD4];
    Player * player; /* 0x1D8 */
} AiTarget;
typedef struct AiBehaviourEntry { s32 id; void (*enter)(Player *,s32); void (*update)(Player *,s32); u8 reserved[0x14]; } AiBehaviourEntry;
typedef struct AiBehaviourTable { struct AiBehaviourTable *next; u8 reserved[0xC]; s32 defaultAnimation; u8 pad14[0xC]; AiBehaviourEntry entries[1]; } AiBehaviourTable;
typedef struct AiController {
    Player * player; /* 0x0 */
    s32 current; /* 0x4 */
    s32 previous; /* 0x8 */
    s32 mode; /* 0xC */
    s32 fallback; /* 0x10 */
    s32 queue[4]; /* 0x14 */
    u8 pad24[4];
    s32 routeGoal; /* 0x28 */
    CVector3 destination; /* 0x2C */
    s32 candidateCount; /* 0x38 */
    AiTarget * candidates[10]; /* 0x3C */
    AiTarget * target; /* 0x64 */
    Player *routeObject; /* 0x68 */
    s32 candidateAccepted[10]; /* 0x6C */
    s32 candidateDistances[10]; /* 0x94: weighted by Nav_EvaluateAttackTarget */
    s32 routeState; /* 0xBC */
    u8 padC0[0xF0];
    CVector3 home; /* 0x1B0 */
    u8 pad1BC[0x14];
    f32 reach[8]; /* 0x1D0: free distance along each wheel ray (Wheel_MeasureWheelReach) */
    f32 clearance[8]; /* 0x1F0: ground found along each wheel ray (Wheel_MeasureWheelClearance) */
    f32 length; /* 0x210: wheel ray length */
    AiBehaviourTable * table; /* 0x214 */
    AiBehaviourEntry * behaviour; /* 0x218 */
    s32 state; /* 0x21C */
    s32 handlerIndex; /* 0x220 */
    u8 pad224[0x18];
    s32 fireRequested; /* 0x23C */
    s32 actionFlagFrames; /* 0x240 */
    f32 aim; /* 0x244 */
    f32 speed[4]; /* 0x248 */
    CVector3 targetPosition; /* 0x258 */
    f32 distance; /* 0x264 */
    u8 pad268[0x24];
    AiTarget * preferred; /* 0x28C */
    u8 pad290[0x54];
    s32 actionDelay; /* 0x2E4 */
    s32 actionDuration; /* 0x2E8 */
    s32 alternateCountdown; /* 0x2EC */
    u8 pad2F0[0x4];
    s32 behaviorStateWordA; /* 0x2F4 */
    s32 behaviorStateWordB; /* 0x2F8 */
    s32 behaviorResetFlag; /* 0x2FC */
    s32 routeComplete; /* 0x300 */
    s32 airPitchNode; /* 0x304 */
    s32 jumpLinkActive; /* 0x308 */
    s32 kindFourLinkActive; /* 0x30C */
    s32 holdMovement; /* 0x310 */
    s32 linkTraversalPhase; /* 0x314 */
    s32 reservedWord; /* 0x318 */
    s32 reservedWord1; /* 0x31C */
    s32 reservedWord2; /* 0x320 */
    s32 attackedTimer; /* 0x324: set to 500 when hit, counts down */
    Player * lastAttacker; /* 0x328 */
    s32 previousPortalLink; /* 0x32C */
} AiController;

extern void OnScreen_SetFirstBarTarget(char *, s32);


extern void *Playerai_FindPlayerWithMarker(char *);
#endif
