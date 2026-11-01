#ifndef GAME_CCOLLISION_COPYPOSITIONANDGETMODELFLAGS_H
#define GAME_CCOLLISION_COPYPOSITIONANDGETMODELFLAGS_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/BOX_CONTACT.H"
extern s32 CCollision_CopyPositionAndGetModelFlags(void *modelStorage, s32 unusedProbeContext, CVector3 t, s32 unusedModelState, s32 unusedProbeFlags, void *outputStorage);
#endif
