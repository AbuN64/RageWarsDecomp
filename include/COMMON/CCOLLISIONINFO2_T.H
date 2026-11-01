#ifndef COMMON_CCOLLISIONINFO2_T_H
#define COMMON_CCOLLISIONINFO2_T_H
#include "TYPES.H"

/* An object's collision response (SN debug type CCollisionInfo2_t, 28 bytes): the three
 * behaviours are signed bytes, the five response constants floats. The movement
 * solver and collision setup tables share this fixed-width record. */
typedef struct CCollisionInfo2_t {
    u32 dwFlags;
    s8 InstanceBehavior;
    s8 WallBehavior;
    s8 GroundBehavior;
    u8 unusedpad;
    f32 GravityAcceleration;
    f32 BounceReturnEnergy;
    f32 GroundFriction;
    f32 AirFriction;
    f32 WaterFriction;
} CCollisionInfo2_t;

#endif
