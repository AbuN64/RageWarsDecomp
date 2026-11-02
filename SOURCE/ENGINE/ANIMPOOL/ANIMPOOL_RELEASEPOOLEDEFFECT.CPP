#include "COMMON/OBJRECAT5F14.H"
#include "COMMON/S1.H"
#include "TYPES.H"
#include "ENGINE/CACHE/LIST.H"





void AnimPool_ReleasePooledEffect(struct CAnimPool *animationPool, struct SceneEffect *effectNode) {
    s32 *referenceCount;

    referenceCount = effectNode->ref;
    effectNode->angle = 0;
    if (referenceCount != 0) {
        *referenceCount -= 1;
    }
    List_RemoveIntrusive(&animationPool->UsedList, effectNode);
    List_AppendIntrusive(&animationPool->FreeList, effectNode);
}
