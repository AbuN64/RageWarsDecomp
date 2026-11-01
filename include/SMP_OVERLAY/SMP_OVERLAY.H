#ifndef SMP_OVERLAY_SMP_OVERLAY_H
#define SMP_OVERLAY_SMP_OVERLAY_H
#include "COMMON/ANIMATION.H"
#include "COMMON/OWNERRECAT8V1.H"
#include "COMMON/NAME.H"
extern void SmpOverlay_RegisterOverlayClass(void);
extern s32 SmpOverlay_CountUsedSlots(struct MenuCountedSlotValueArrayView *object);
extern void SmpOverlay_ShowSlotNodeById(sm_dlmultiuser *context, s32 index, s32 id);
extern void SmpOverlay_SetObjectValue(struct Object6C *object, s32 value);
extern s32 SmpOverlay_DispatchSlotEvent(void *, s32, s32, s32, s32);
extern void SmpOverlay_DrawOverlayWidget(Shared_Item *widget, Args args);
extern s32 SmpOverlay_ReturnUnhandledEvent(void);
extern s32 SmpOverlay_FollowSlotTarget34(struct sm_dlmultiuser_t *owner, s32 unused1, s32 slot, s32 kind);
extern s32 SmpOverlay_FollowSlotTarget2c(struct sm_dlmultiuser_t *owner, s32 unused1, s32 slot, s32 kind);
extern s32 SmpOverlay_FollowSlotTarget38(struct sm_dlmultiuser_t *owner, s32 unused1, s32 slot, s32 kind);
extern s32 SmpOverlay_FollowSlotTarget30(struct sm_dlmultiuser_t *owner, s32 unused1, s32 slot, s32 kind);
extern int SmpOverlay_ForwardSlotEvent(Mixer *mixer, int unused, int channel, int value, int extra);
extern s32 SmpOverlay_FreeEventObject(void *);
extern int SmpOverlay_SetListWidgetFlag40(OverlayWidgetListView *list);
#endif
