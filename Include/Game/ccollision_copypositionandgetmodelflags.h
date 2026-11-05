#ifndef GAME_CCOLLISION_COPYPOSITIONANDGETMODELFLAGS_H
#define GAME_CCOLLISION_COPYPOSITIONANDGETMODELFLAGS_H
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
#include "Common/resident_event_handler.h"
#include "Common/box_contact.h"
extern s32 CCollision_CopyPositionAndGetModelFlags(void *modelStorage, s32 unusedProbeContext, CVector3 t, s32 unusedModelState, s32 unusedProbeFlags, void *outputStorage);
#endif
