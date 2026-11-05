#ifndef PFS_CONTROLLER_H
#define PFS_CONTROLLER_H
#include "types.h"
#include "Common/level_track.h"
#include "Common/resident_event_handler.h"
#include "Common/audio_callbacks.h"
#include "Common/sharedplayer.h"
#include "Common/packed.h"
#include "Common/vector4f.h"
#include "Common/level_input.h"
extern s16 Ovlgame_InitializeControllerSession(void);
extern s32 Ovlgame_ResetControllerProfile(ControllerProfile *, s32);
#endif
