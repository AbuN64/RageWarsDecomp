#ifndef UI_TSMOS_SMP_SMP_FADE_H
#define UI_TSMOS_SMP_SMP_FADE_H
extern void SmpFade_RegisterFadeClass(void);
struct MenuFadeWidget *SmpFade_CreateFadeWidget(s32 frameId, s32 itemId);
#endif
