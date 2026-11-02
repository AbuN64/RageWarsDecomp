#include "ANIM/RAY180.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "ENGINE/UNICOL/PLTFMCOL.H"

extern void Graphu64_AddVec3(CVector3 *, CVector3 *, CVector3 *);

/** Set flag 8 in the first object and flag 0x10 in the second. */
void CPlatformCollision_MarkBlocked(void *first, void *second) {
    PlatformSavedCollisionQueryView *actor = first;
    InputCPlatformCollisionLiftActorToSurface *input = second;
    actor->flags |= 8;
    input->flags38 |= 0x10;
}

void CPlatformCollision_ApplyMovement(void *platformMotion, void *levelActor) {
    ActorCPlatformCollisionPushActorFromBox *actor = platformMotion;
    LevelActor *target = levelActor;
    CVector3 *position = &target->position1;
    actor->flags |= 8;
    Graphu64_AddVec3(position, position, &actor->movement);
}
