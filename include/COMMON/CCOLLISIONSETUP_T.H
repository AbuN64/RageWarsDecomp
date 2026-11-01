#ifndef COMMON_CCOLLISIONSETUP_T_H
#define COMMON_CCOLLISIONSETUP_T_H
#include "TYPES.H"
#include "COMMON/CCOLLISIONINFO2_T.H"

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

#endif
