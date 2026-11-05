#ifndef FRONTEND_SMP_OVERLAY_H
#define FRONTEND_SMP_OVERLAY_H
#include "Common/player_message_menu.h"
#include "Common/label.h"
extern s32 SmpOverlay_HandlePakDialogChoice(void);
extern s32 SmpOverlay_DispatchPakDialogEvent(void *eventObject, s32 eventId, s32 eventPayload, s32 eventValue, s32 eventExtra);
extern s32 SmpOverlay_FinishPakDialog(void);
extern void SmpOverlay_ProbePakDialogPorts(void);
struct MenuOverlayOwnerView;
struct NodeMenuCreateOverlayNode *SmpOverlay_CreateOverlayNode(struct MenuOverlayOwnerView *owner, s32 value);
struct MenuMultiUserOwnerView;
void SmpOverlay_ShowSlotById(struct MenuMultiUserOwnerView *owner, s32 index, s32 id);
#endif
