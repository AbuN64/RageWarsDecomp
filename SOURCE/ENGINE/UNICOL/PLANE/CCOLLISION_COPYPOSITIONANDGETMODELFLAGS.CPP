#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/BOX_CONTACT.H"
#include "TYPES.H"
#include "COMMON/RENDERSORTRECORD.H"
#include "GAME/CCOLLISION_COPYPOSITIONANDGETMODELFLAGS.H"

s32 CCollision_CopyProbePosition(void *unusedActor, Triple t, s32 room, s32 unusedRadius, void *outputPoint) {
    char unused[0xB60];
    *(Triple *)outputPoint = t;
    return 1;
}

s32 CCollision_CopyPositionAndGetModelFlags(void *modelStorage, s32 unusedFlags, CVector3 t, s32 unusedRoom, s32 unusedRadius, void *outputStorage) {
    struct Model *model = modelStorage;
    CVector3 *output = outputStorage;
    Triple unused1;
    Triple unused2;
    *output = t;
    return model->flags;
}
