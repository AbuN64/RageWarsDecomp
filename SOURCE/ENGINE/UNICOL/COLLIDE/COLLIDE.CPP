#include "COMMON/DESCRIPTORRECAT29.H"
#include "COMMON/LONE/COLLISION_CURRENT_ACTOR.H"
#include "COMMON/OUTPUT.H"
#include "SCHED/SKY_POSTSCREENMESSAGE.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/CCOLLISIONSETUP_T.H"
#include "ENGINE/UNICOL/COLLIDE.H"
#include "include_asm.h"

/* 8023A284_29.CPP */
/* Points the active collision state at g_currentActorInstance and fills the collision infos from the setup table
 * g_collisionSetupTableResource (the KUSEG alias of g_collisionSetupTable). */

extern u8 g_currentActorInstance[];

extern CCollisionSetup_t g_collisionSetupTableResource[];

void CCollision_Initialize(void) {
    g_collisionCurrentActor = g_currentActorInstance;
    CCollision_ApplySetupTable(g_collisionSetupTableResource);
}

/** Reset the selected fields of the current global record. */
void CCollision_ResetResult(void) {
    Reusable *record = g_collisionCurrentActor;
    record->reservedWord = 0;
    record->collisionCounter = -1;
    record->reservedWord2 = 0;
    record->reservedWord3 = 0;
    record->reservedWord4 = 0;
    record->reservedWord5 = 0;
    record->reservedWord6 = 0;
}

/* 8023A284_32.CPP */
/* Fills every collision info named by a collision setup table from its row, resetting the
 * active collision state g_collisionCurrentActor before each one; the table ends at a row without info. */
void CCollision_ApplySetupTable(CCollisionSetup_t *setupTable)
{
    CCollisionSetup_t *setup = setupTable;
    s32 counter = -1;

    if (setup->m_pCollInfo != 0) {
        do {
            CCollisionInfo2_t *info = setup->m_pCollInfo;

            ((Reusable *)g_collisionCurrentActor)->reservedWord = 0;
            ((Reusable *)g_collisionCurrentActor)->collisionCounter = counter;
            ((Reusable *)g_collisionCurrentActor)->reservedWord2 = 0;
            ((Reusable *)g_collisionCurrentActor)->reservedWord3 = 0;
            ((Reusable *)g_collisionCurrentActor)->reservedWord4 = 0;
            ((Reusable *)g_collisionCurrentActor)->reservedWord5 = 0;
            ((Reusable *)g_collisionCurrentActor)->reservedWord6 = 0;

            info->dwFlags = setup->m_dwFlags;
            info->InstanceBehavior = setup->m_InstanceBehavior;
            info->WallBehavior = setup->m_WallBehavior;
            info->GroundBehavior = setup->m_GroundBehavior;
            info->GravityAcceleration = setup->m_GravityAcceleration;
            info->BounceReturnEnergy = setup->m_BounceReturnEnergy;
            info->GroundFriction = setup->m_GroundFriction;
            info->AirFriction = setup->m_AirFriction;
            info->WaterFriction = setup->m_WaterFriction;
            setup += 1;
        } while (setup->m_pCollInfo != 0);
    }
}



/* 8023A284_34.CPP */
