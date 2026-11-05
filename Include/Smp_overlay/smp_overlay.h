#ifndef SMP_OVERLAY_SMP_OVERLAY_H
#define SMP_OVERLAY_SMP_OVERLAY_H
struct MenuCountedSlotValueArrayView;
struct MenuObjectSlotArrayView;
struct sm_dlmultiuser_t;
struct NodeMenuShowSlotById;
#include "Menu/widget_records.h"
#include "Common/animation.h"
#include "Common/menu_overlay.h"
#include "Common/name.h"
struct Mixer;
struct OverlayWidgetListView;
struct Shared_Item;
extern void SmpOverlay_RegisterOverlayClass(void);
extern s32 SmpOverlay_GetSlotNodeId(struct MenuObjectSlotArrayView *object, s32 index);
extern void SmpOverlay_ShowSlotNode(struct sm_dlmultiuser_t *context, s32 index, struct NodeMenuShowSlotById *node);
extern s32 SmpOverlay_CountUsedSlots(struct MenuCountedSlotValueArrayView *object);
extern void SmpOverlay_ShowSlotNodeById(struct sm_dlmultiuser_t *context, s32 index, s32 id);
struct Object6C;
extern void SmpOverlay_SetObjectValue(struct Object6C *object, s32 value);
extern s32 SmpOverlay_DispatchSlotEvent(void *, s32, s32, s32, s32);
extern void SmpOverlay_DrawOverlayWidget(struct Shared_Item *widget, Args args);
extern s32 SmpOverlay_ReturnUnhandledEvent(void);
extern s32 SmpOverlay_FollowChildSlotTarget(struct sm_dlmultiuser_t *owner, s32 eventId, s32 slot, s32 kind);
extern s32 SmpOverlay_FollowListSlotTarget(struct sm_dlmultiuser_t *owner, s32 eventId, s32 slot, s32 kind);
extern s32 SmpOverlay_FollowOverlaySlotTarget(struct sm_dlmultiuser_t *owner, s32 eventId, s32 slot, s32 kind);
extern s32 SmpOverlay_FollowTextSlotTarget(struct sm_dlmultiuser_t *owner, s32 eventId, s32 slot, s32 kind);
extern int SmpOverlay_ForwardSlotEvent(struct Mixer *mixer, int eventId, int channel, int value, int extra);
extern s32 SmpOverlay_FreeEventObject(void *);
extern int SmpOverlay_SelectListWidgets(struct OverlayWidgetListView *list);
extern void SmpOverlay_SetSlotValue(struct MenuSlotValueArrayView *, s32, s32);
struct WidgetNode *SmpOverlay_GetSlotValue(struct SmpOverlaySlotsView *object, s32 index);
#endif
