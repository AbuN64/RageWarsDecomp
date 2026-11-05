#ifndef N64ENG_N64ENG_H
#define N64ENG_N64ENG_H
#include "types.h"
#include "Common/record.h"
extern void N64Eng_SetNumericWidgetValue(struct RecordN64EngCreateNumericWidget *widget, s32 value);
extern s32 N64Eng_GetNumericWidgetValue(void *);
struct RecordN64EngCreateNumericWidget *N64Eng_CreateNumericWidget(s32 sourceResourceId, s32 childResourceId, s32 minimumValue, s32 maximumValue, s32 wrapEnabled);
#endif
