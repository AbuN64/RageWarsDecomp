#ifndef ENGINE_CINEMA_CINEMA_H
#define ENGINE_CINEMA_CINEMA_H
#include "Common/shared_menureply.h"
#include "Common/group.h"
struct ScreenRectangle;
extern void Cinema_EndSequence(void);
extern void Cinema_RequestSequenceFade(void);
extern int Cinema_IsFadeAllowed(void);
extern int Cinema_HasSequenceResource(void);
extern s32 Cinema_HasSequenceEnded(void);
extern void Cinema_UpdateSequenceTrack(void *camera);
extern unsigned int Cinema_GetPlaybackFlag(void);
extern void Cinema_ClearPlaybackPauseState(void);
extern int Cinema_IsSequenceFlagTwoSet(void);
extern int Cinema_GetActiveSettingOne(void);
extern int Cinema_GetActiveSettingZero(void);
extern void Cinema_SetLetterboxState(void *letterboxEnabled);
extern void Cinema_SetResponse(float responseValue);
extern void Cinema_ClearResponse(void);
extern void Cinema_SetLoopMode(int loopMode);
extern void Cinema_ResetViewport(void);
extern void Cinema_SetViewport(int viewportWidth, int viewportHeight, int viewportLeft, int viewportTop);
extern void Cinema_ClearMessageCount(void);
extern float Cinema_GetScaledSequenceValue(void);
extern void Cinema_InitializeSequenceOnce(s32 sequenceMode);
extern void Cinema_CloseSequenceOnce(void);
extern void Cinema_AdvanceSequenceTime(void);
extern int Cinema_GetSequenceActiveState(void);
void Cinema_DrawSequenceOverlay(struct ScreenRectangle *view);
extern void Cinema_AddMessage(int goal);
extern s32 Cinema_IsSequenceIdle(void);
#endif
