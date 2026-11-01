#ifndef MENU_PAK_PROFILE_PREVIEW_AND_LINE_TEXT_H
#define MENU_PAK_PROFILE_PREVIEW_AND_LINE_TEXT_H
#include "COMMON/RECORDRECATCV1.H"
#include "MENU/PAK_PREVIEW_VIEWS.H"
extern void Timer_EnableProfilePreview(void);
extern void Timer_ClearProfilePreview(void);
extern void Timer_DisablePreviewSelection(struct PakPreviewSelectionView *record);
extern s32 Timer_OpenSelectedPrompt(void *unused, struct PakSelectedPromptView *record);
extern s32 Menu_CountLineChars(struct Field *);
#endif
