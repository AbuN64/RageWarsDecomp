#ifndef UI_SMP_LIST_H
#define UI_SMP_LIST_H
#include "types.h"

extern s32 SmpList_DestroyController(void *allocation);
extern s32 SmpList_HandleDecrementInput(struct SliderStepRecord *menu, void *second, void *third, s32 active, s32 fifth);
extern s32 SmpList_HandleIncrementInput(struct SliderStepRecord *menu, void *second, void *third, s32 active, s32 fifth);
extern s32 SmpList_HandleStopEvent(struct SliderStepRecord *object, void *eventKind, u32 event, s32 value);
extern s32 SmpList_ResetEntryCommands(struct CommandListMenu *commandListMenu);
extern s32 SmpList_UpdateSliderMotion(struct SliderStepRecord *menu);
#endif
