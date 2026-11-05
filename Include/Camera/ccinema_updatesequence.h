#ifndef CAMERA_CCINEMA_UPDATESEQUENCE_H
#define CAMERA_CCINEMA_UPDATESEQUENCE_H
#include "Engine/scene.h"
#include "Ai/player_symbols.h"
#include "Ai/playerai_symbols.h"
#include "Common/group.h"
extern void CCinema_UpdateSequence(void);
extern s32 CCinema_ProcessPendingTrack(void);
extern void CCinema_EnterSequenceScene(void);
extern void Playerai_ResetControllerMotion(void *);
extern s32 Track_HasNoTrackRequestItems(void);
extern s32 g_gameFrameCounter;
extern void Cache_SetResourceActivityState(unsigned int);
#endif
