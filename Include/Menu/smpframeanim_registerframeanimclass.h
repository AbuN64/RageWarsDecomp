#ifndef MENU_SMPFRAMEANIM_REGISTERFRAMEANIMCLASS_H
#define MENU_SMPFRAMEANIM_REGISTERFRAMEANIMCLASS_H
#include "Common/animation.h"
#include "types.h"
struct FrameSequence;
extern void SmpFrameAnim_RegisterFrameAnimClass(void);
extern void SmpFrameAnim_SetSequenceFrame(struct FrameSequence *sequence, s32 frame);
extern void SmpFrameAnim_SetSequenceDuration(struct FrameSequence *sequence, s32 duration);
extern void SmpFrameAnim_SetLoopCount(struct FrameSequence *sequence, s32 loops);
extern void SmpFrameAnim_AddSequenceFlags(struct FrameSequence *sequence, s32 bits);
extern void SmpFrameAnim_ClearSequenceFlags(struct FrameSequence *sequence, s32 bits);
#endif
