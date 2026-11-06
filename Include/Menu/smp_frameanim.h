#ifndef MENU_SMP_FRAMEANIM_H
#define MENU_SMP_FRAMEANIM_H
#include "Common/animation.h"
extern s32 SmpFrameAnim_GetFrameCount(struct FrameSequence *sequence);
extern s32 SmpFrameAnim_DispatchEvent(void *eventTarget, s32 eventId, s32 eventCode, s32 eventValue, s32 repeatCount);
extern void SmpFrameAnim_IgnoreEvent(s32 widget, struct Triple eventData);
extern s32 SmpFrameAnim_GetLoopCount(struct FrameSequence *sequence);
extern s32 SmpFrameAnim_GetSequenceFrame(struct FrameSequence *sequence);
extern s32 SmpFrameAnim_DestroyController(void *allocation);
extern s32 SmpFrameAnim_UpdateFrameSequence(struct FrameSequence *sequence, s32 eventId, s32 elapsed);
struct FrameSequence;
extern s32 SmpFrameAnim_HasSequenceFlags(struct FrameSequence *sequence, s32 bits);
#endif
