#ifndef PFS_CONTROLLER_H
#define PFS_CONTROLLER_H
#include "TYPES.H"
#include "COMMON/LEVEL_TRACK.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/AUDIO_CALLBACKS.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/PACKED.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/LEVEL_INPUT.H"
extern s16 Ovlgame_InitializeControllerSession(void);
extern s32 Ovlgame_ResetControllerProfile(ControllerProfile *, s32);
#endif
