#ifndef MATCH_REASON_MATCH_REASON_H
#define MATCH_REASON_MATCH_REASON_H
s32 Frontend_DestroyMatchResults(void);
s32 Frontend_HandleResultsConfirmation(s32 context);
s32 Frontend_UpdateMatchResultsTransition(void *window, void *eventKind, s32 event);
extern void Frontend_ContinueCupOrOpenResults(void);
extern void Frontend_OpenControllerModeResults(void);
#endif
