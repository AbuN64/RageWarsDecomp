#ifndef CAMERA_COLLISION_SWEEP_VIEWS_H
#define CAMERA_COLLISION_SWEEP_VIEWS_H
#include "COMMON/GROUP.H"
#include "COMMON/LEGACY_COLLISION_ACTOR.H"
#include "COMMON/MOTION_STEP.H"
#include "COMMON/SHAREDPLAYER.H"
struct CollisionState {
    s32 active0;
    u8 pad[0x98];
    s32 active9c;
};
struct UnicolMotionSettings {
    s32 flags;
    u8 ground_behavior;
    u8 instance_behavior;
    u8 pad[2];
    s32 w[5];
};
struct Access_s32_C4 {
    char pad[0xC4];
    s32 field;
};
struct Access_s32_D0 {
    char pad[0xD0];
    s32 field;
};
struct Group {
    void *lead;
    char pad4[0x24];
    char members[1];
};
struct VectorPair {
    CVector3 first;
    CVector3 second;
    char pad[8];
};
struct CollisionSweepWork {
    char data[440];
};
struct UnicolCurrentActorRoom {
    u8 pad[216]; /* +0x0: src/Unicol_MoveActorWithCollision_CollisionSweepViews.c */
    s32 x; /* +0xD8: src/Unicol_MoveActorWithCollision_CollisionSweepViews.c */
    f32 y; /* +0xDC: src/Unicol_MoveActorWithCollision_CollisionSweepViews.c */
    s32 z; /* +0xE0: src/Unicol_MoveActorWithCollision_CollisionSweepViews.c */
};
struct Access_s8_E6 {
    char pad[0xE6];
    s8 field;
};
struct Range;
extern s32 CCollision_TraceActorMotion(ActorMotion *object);
extern void CCollision_SetSweepRange(struct Range *range, f32 low, f32 mid, f32 high, f32 extra);
extern s32 Unicol_MoveActorWithCollision(UnicolActor *actor, CVector3 position, u32 *flags);
extern s32 CCollision_SweepUniformExtent(char *actorStorage, CVector3 startPosition, CVector3 endPosition, struct CCollisionInfo2_t *sweepSurfaceSettings, f32 sweepExtent);
#endif
