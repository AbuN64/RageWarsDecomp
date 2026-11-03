#include "include_asm.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/OBJRECAT5F14.H"
#include "COMMON/S1.H"
#include "ENGINE/CACHE/LIST.H"
#include "SOURCE/OVLGAME.H"

/* OVLGAME.CPP */
void Ovlgame_InitializeSceneEffectPool(struct CAnimPool *animationPool) {
    SceneEffect *sceneEffect;
    s32 i;

    List_InitializeIntrusive(&animationPool->FreeList, 744, 748);
    List_InitializeIntrusive(&animationPool->UsedList, 744, 748);
    i = 0;
    sceneEffect = animationPool->DynAnims;
    do {
        List_AppendIntrusive(&animationPool->FreeList, sceneEffect);
        i += 1;
        sceneEffect += 1;
    } while (i < 32);
}
