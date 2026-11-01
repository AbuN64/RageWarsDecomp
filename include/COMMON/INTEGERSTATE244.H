#ifndef COMMON_INTEGERSTATE244_H
#define COMMON_INTEGERSTATE244_H
struct SharedPlayer;
#ifndef COMMON_INTEGERSTATE244_DECLARATIONS_H
#define COMMON_INTEGERSTATE244_DECLARATIONS_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/LIBSN_AND_RESIDENT_CALLBACKS.H"
struct PlayerSequenceRunEndStateView;
typedef struct PlayerSequenceRunEndStateView PlayerSequenceRunEndStateView;



extern void Playerai_NoopRoundEndViewAngles_de(void);

extern void Playerai_SetRunEndFlag(struct SharedPlayer *player);

struct PlayerSequenceRunEndActorView;
typedef struct PlayerSequenceRunEndActorView PlayerSequenceRunEndActorView;

extern void Player_AimPreviousPositionAtReset(void *aimPlayerState);

extern void Player_EmptyHandlerAfterResetStunAndReleaseHandles_de(void);


extern float g_playerLateralLeapVerticalSpeed;





extern float g_playerRunEndTransitionDelay;


extern void Playerai_NoopShortSequenceWaitFirst_de(void);

extern float g_playerShortSequenceWaitLimit;

extern float g_playerFloatPoseMinimumDuration;






extern float g_playerMotionDamping;

extern float g_playerLateralLeapInitialVerticalSpeed;

extern float g_playerFloatForwardAnimationThreshold;

extern float g_playerLateralLeapDuration;





struct PlayerSequenceRunEndStateView;
struct PlayerSequenceRunEndStateView {
    unsigned char padding_0[572];
    s32 burstRequest;
    s32 actionFlagFrames;
};

extern float g_playerLateralLeapNegativeInputSpeed;

extern void Player_ClearGlobalFlagBit(void);


extern void Player_EmptyHandlerAfterAimPreviousPositionAtReset_de(void);


extern void Playerai_NoopRoundEndWaitSecond_de(void);




extern float g_playerRunEndModelScale;


extern void Player_EmptyHandlerAfterResetStunFlags_de(void);

extern void Playerai_NoopShortSequenceWaitSecond_de(void);



extern void Player_EmptyHandlerAfterStartMovingOnStickInput_de(void);


extern float g_playerLateralLeapPositiveInputSpeed;

struct PlayerStrafeVelocityView;
typedef struct PlayerStrafeVelocityView PlayerStrafeVelocityView;


extern void Player_EmptyHandlerBeforeUpdateGroundMoveState_de(void);

extern void Player_ResetStunFlags(void *actorState);




extern void Player_EmptyHandlerBeforeAimPreviousPositionAtReset_de(void);

struct PlayerSequenceRunEndActorView;
struct PlayerSequenceRunEndActorView {
    char pad0[0x50];
    f32 scaleX;
    char pad50[0x54 - 0x50 - sizeof(f32)];
    f32 scaleY;
    char pad54[0x58 - 0x54 - sizeof(f32)];
    f32 scaleZ;
    char pad58[0x658 - 0x58 - sizeof(f32)];
    f32 poseTimer;
    char pad658[0x122C - 0x658 - sizeof(f32)];
    s32 reactionFlags;
    char pad122C[0x1230 - 0x122C - sizeof(s32)];
    s32 tintTime;
    char pad1230[0x1238 - 0x1230 - sizeof(s32)];
    s32 tintMode;
    char pad1238[0x13C8 - 0x1238 - sizeof(s32)];
    s32 overkill;
    char pad13C8[0x1454 - 0x13C8 - sizeof(s32)];
    void * controller;
};


extern float g_playerFloatReverseAnimationThreshold;


struct PlayerStrafeVelocityView;
struct PlayerStrafeVelocityView {
    unsigned char padding_0[1700];
    f32 strafe;
    unsigned char padding_6A8[28];
    f32 lateralLeapSpeed;
};









extern float g_playerJumpInitialSpeedScale;

extern void Player_EmptyHandlerAfterResetObjectVelocity_de(void);

extern void Playerai_NoopRoundEndWaitFirst_de(void);

extern void Graphu64_EaseValueToward(f32 *value, f32 target, f32 rate);
extern void Player_UpdateLeapMotion(s32 player, s32 body);

extern void Player_UpdateRunEndPlayer(void *);
struct PlayerSequenceActorView;
extern void Playerai_TryStartPlayerSequence(struct PlayerSequenceActorView *a, void *b, int c);

s32 Playerai_ApplyProjectileStatus(s32, void *, s32, s32);


#endif
#endif
