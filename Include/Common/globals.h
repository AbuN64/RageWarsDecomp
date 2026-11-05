#ifndef COMMON_GLOBALS_H
#define COMMON_GLOBALS_H
#include "Common/world.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Common/sharedtrackobjectprefix.h"
#include "Common/track_requesttrackbykey.h"
#include "Common/shared_menureply.h"








struct GlobalsMenuSetOptionsSceneSelection;
extern f32 g_cameraAspectRatios[];

extern struct GlobalsMenuSetOptionsSceneSelection g_gameplayCameraList;



extern int Cache_GetResourceActivityState(void);
#endif
