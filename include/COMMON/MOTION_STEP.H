#ifndef COMMON_MOTION_STEP_H
#define COMMON_MOTION_STEP_H
#include "TYPES.H"
#include "COMMON/CCOLLISIONINFO2_T.H"
#include "COMMON/SHAREDPLAYER.H"
/* Contact positions and interpolation outputs used by the movement solver. */
/* Contact result beginning at ActorMotion.collisionState; also passed separately
 * by the actor collision resolver to the contact flag helpers. */
typedef struct MotionContactResult {
    s32 state;
    f32 damping;
    s32 mode;
    s32 material;
    s32 flags;
} MotionContactResult;
typedef struct ActorMotion {
    void *actor; /* 0x00 */
    s32 actorFlags; /* 0x04 */
    f32 sweepExtentFirst; /* 0x08 */
    f32 radius; /* 0x0C */
    f32 height; /* 0x10 */
    f32 bottom; /* 0x14 */
    f32 sweepExtentLast; /* 0x18 */
    s32 iteration; /* 0x1C */
    s32 candidate; /* 0x20 */
    s32 grounded;
    s32 candidateIndex; /* 0x28 */
    s32 orientationActive;
    s32 horizontalTicks;
    s32 verticalTicks;
    s32 transitionActive;
    u32 flags;
    CCollisionInfo2_t *surface;
    CVector3 start;
    CVector3 end;
    CVector3 velocity;
    CVector3 direction;
    CVector3 orientation;
    f32 distance;
    CVector3 boundsMin;
    CVector3 boundsMax;
    f32 horizontalBounds[4];
    s32 queryFlags; /* 0xAC */
    s32 collisionState;
    f32 damping;
    s32 mode;
    u8 reservedBC[8];
    s32 contactCount;
    CVector3 contacts[4];
    CVector3 normal;
    struct LevelActor *specialCandidate; /* 0x104: skipped when it is the special collision candidate */
    u8 reserved108[0x74];
    f32 blend;
    CVector3 interpolated;
    u8 reserved18C[12];
    CVector3 position;
    CVector3 projectedOrientation;
} ActorMotion;
#endif
