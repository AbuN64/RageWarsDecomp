#ifndef MENU_SMP_FRAMEANIM_H
#define MENU_SMP_FRAMEANIM_H
#include "COMMON/ANIMATION.H"
extern s32 SmpFrameAnim_GetFrameCount(struct FrameSequence *sequence);
extern s32 SmpFrameAnim_DispatchEvent(void *eventTarget, s32 eventId, s32 eventCode, s32 eventValue, s32 repeatCount);
extern void SmpFrameAnim_IgnoreEvent(s32 unused0, struct Triple unused1);
extern s32 SmpFrameAnim_GetLoopCount(struct FrameSequence *sequence);
extern s32 SmpFrameAnim_GetSequenceFrame(struct FrameSequence *sequence);
#endif
