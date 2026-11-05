#ifndef MENU_PAK_PROFILE_PREVIEW_AND_LINE_TEXT_H
#define MENU_PAK_PROFILE_PREVIEW_AND_LINE_TEXT_H
#include "Common/pak_preview_selection.h"
#include "Menu/pak_preview_views.h"
#include "Menu/menu_createmenufromparameters.h"
extern void Timer_EnableProfilePreview(void);
extern void Timer_ClearProfilePreview(void);
extern void Timer_DisablePreviewSelection(struct PakPreviewSelectionView *record);
extern s32 Timer_OpenSelectedPrompt(void *owner, struct PakSelectedPromptView *record);

#endif
