#ifndef COMMON_CCOLLISIONSETUP_T_H
#define COMMON_CCOLLISIONSETUP_T_H
#include "types.h"
#include "Common/ccollisioninfo2_t.h"

struct CCollisionInfo2_t;
/* One row of a collision setup table (SN debug type CCollisionSetup_t, 40 bytes): the
 * collision info it fills and the values copied into it; the behaviours are ints here
 * and bytes in CCollisionInfo2_t. A row whose m_pCollInfo is 0 ends the table. */
typedef struct CCollisionSetup_t {
    struct CCollisionInfo2_t *m_pCollInfo;
    u32 m_dwFlags;
    int m_InstanceBehavior;
    int m_WallBehavior;
    int m_GroundBehavior;
    float m_GravityAcceleration;
    float m_BounceReturnEnergy;
    float m_GroundFriction;
    float m_AirFriction;
    float m_WaterFriction;
} CCollisionSetup_t;

/* Collision infos the setup table points at. */
extern struct CCollisionInfo2_t g_portalDefaultCollisionQueryTail;
extern struct CCollisionInfo2_t g_collisionSurfaceExcludedFromTraceJumpEntry;
extern struct CCollisionInfo2_t g_collisionSurfaceExcludedFromTraceTravelEntry;

extern struct CCollisionInfo2_t g_groundFrictionCollisionInfo;
extern struct CCollisionInfo2_t g_lowGravityWaterDragCollisionInfo;
extern struct CCollisionInfo2_t g_weightlessCollisionInfo;
extern struct CCollisionInfo2_t g_bounceFrictionCollisionInfo;
extern struct CCollisionInfo2_t g_bounceNoFrictionCollisionInfo;
/* One collision info slot of the collision region: slots sit 0x20 apart, the info and a tail word nothing reads. */
typedef struct CollisionSlot {
    struct CCollisionInfo2_t info;
    u32 tail;
} CollisionSlot;
typedef char CollisionSlotSizeCheck[(sizeof(CollisionSlot) == 0x20) ? 1 : -1];
/* The two setup rows with wall behaviour 6, bounce 0.3 and ground friction 0.7. */
extern CollisionSlot g_bounceFrictionAltWallCollisionSlots[2];
/* The secondary collision context: eight slots; slot 1 and slot 6 are the setup table targets. */
extern CollisionSlot g_secondaryCollisionContext[8];
/* The supporting-platform collision query: eight slots just below the secondary context; the setup table fills each slot's info. */
extern CollisionSlot g_supportingPlatformCollisionQuery[8];

#endif
