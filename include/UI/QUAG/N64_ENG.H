#ifndef UI_QUAG_N64_ENG_H
#define UI_QUAG_N64_ENG_H
#include "TYPES.H"
#include "COMMON/RECORD.H"

struct CommandListController {
    u8 padding000[8];
    struct LinkedCommandEntry *entries; /* 0x08 */
    u8 padding00C[0x3C];
    s32 progress; /* 0x48 */
    u8 padding04C[0x10];
    s32 state; /* 0x5C */
};
extern u32 g_numericWidgetClipLeft;
extern u32 g_numericWidgetClipTop;
extern u32 g_numericWidgetClipRight;
extern u32 g_numericWidgetClipBottom;
extern void N64Eng_SetClipBounds(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);
/* Elapsed game time in seconds; callers must preserve the floating return ABI. */
extern f64 N64Eng_GetTimeSeconds(void);

extern void N64Eng_RenderNoop(void);
extern void N64Eng_ResetRenderState(void);

extern void N64Eng_AdvanceFrameCounter(void);
extern void N64Eng_RegisterNumericWidgetClass(void);
extern int N64Eng_GetFrameCounter(void);

extern char g_ribbonBlendResourceSecond_us[];
extern char g_ribbonBlendResourceThird_us[];
extern char g_ribbonBlendResourceFourthBase_us[];
extern char g_ribbonBlendResourceFifthBase_us[];

extern double Gfx_GetConvertedCounterRatio(void);

extern s32 N64Eng_DispatchNumericWidgetEvent(struct Tree *widget, s32 event, s32 eventData, s32 eventValue, s32 eventContext);
extern void N64Eng_DecrementNumericWidget(void *widget);
#endif
