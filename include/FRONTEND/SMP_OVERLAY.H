#ifndef FRONTEND_SMP_OVERLAY_H
#define FRONTEND_SMP_OVERLAY_H
#include "COMMON/MENURECAT24.H"
#include "COMMON/LABEL.H"
extern s32 SmpOverlay_HandlePakDialogChoice(void);
extern s32 SmpOverlay_DispatchPakDialogEvent(void *eventObject, s32 eventId, s32 eventPayload, s32 eventValue, s32 eventExtra);
extern s32 SmpOverlay_FinishPakDialog(void);
extern void SmpOverlay_ProbePakDialogPorts(void);
#endif
