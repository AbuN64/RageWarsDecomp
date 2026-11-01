#ifndef RENDER_MOVINGAI_H
#define RENDER_MOVINGAI_H
#include "COMMON/REC.H"
#include "COMMON/SHAREDPLAYER.H"
struct MovingPlatformMotionStateView {
    char pad0[0x35];
    s8 animation;
    char pad36;
    s8 state;
    char pad38[4];
    s32 flags;
    char pad40[4];
    f32 timer;
    char pad48[0xC];
    CVector3 pos;
    char pad60[4];
    f32 throttle;
    char pad68[0x34];
    f32 baseYaw;
    CVector3 base;
    char padAC[0x78];
    f32 triggerTime;
    CVector3 shake;
    char pad134[8];
    f32 phase;
};
struct PathMotionInterpolationState {
    char pad0[0x54];
    f32 nextPositionX;
    f32 nextPositionY;
    f32 nextPositionZ;
    char pad5C[0x34];
    u8 pathCursor;
    char pad94[0x9F];
    f32 secondaryAngle;
    f32 tertiaryAngle;
    char pad138[0x4];
    f32 previousDirectionX;
    f32 previousDirectionY;
    f32 previousDirectionZ;
    f32 directionBlend;
    f32 directionX;
    f32 directionY;
    f32 directionZ;
    f32 initialSecondaryAngle;
    f32 initialHeading;
    f32 initialTertiaryAngle;
    f32 movementSpeed;
    f32 pauseRemaining;
};
struct Rec {
    char pad0[0xC];
    void *a;
    void *b;
};
struct PathMotionActorView {
    char pad0[0x8];
    TriggeredPathActorPositionWords positionX;
    f32 positionY;
    f32 positionZ;
    char pad10[0x24];
    s32 inputFlags;
    char pad38[0x30];
    f32 heading;
};
struct PathMotionWaypoint {
    Triple pos;
    char pad8[0x4];
    f32 headingDegrees;
    WaypointFlags flags;
    char pad14[0x4];
    f32 arrivalRadius;
    f32 directionBlendRate;
    f32 targetSpeed;
    f32 secondaryAngleDegrees;
    f32 tertiaryAngleDegrees;
    f32 speedCurvePhase;
    f32 pauseDuration;
};
struct MovingPlatformTrackView {
    char prefix[20];
    struct CPlatformIntelligence segment;
};
struct MovingActorGameFlagView {
    u8 gameFlag;
};
struct MovingPlatformActorView {
    char pad0[8];
    f32 x;
    f32 y;
    f32 z;
    s32 model;
    union { char *track; struct MovingPlatformTrackView *motionTrack; };
    char pad1C[0x1C];
    u32 inputFlags;
    char pad3C[0x30];
    f32 yaw;
    char pad70[0x90];
    u32 flags;
};
extern int MovingAI_GetDeviceHealth(void *unused0, struct Dest *deviceState);
extern void MovingAI_DisableTriggerActor(struct Trigger *trigger);
extern void MovingAI_InitializeMotionDispatch(struct LevelActor *actor, struct ActorMotionState *motionState);
extern void MovingAI_DeviceHealthNoOp(void);
extern s32 MovingAI_CanSpawnActorKind(s32 actorKind);
extern void MovingAI_EnableTriggerActor(struct Trigger *trigger);
extern void MovingAI_RequestMotionAnimation(void *a, struct ActorMotionState *b, s32 c);
#endif
