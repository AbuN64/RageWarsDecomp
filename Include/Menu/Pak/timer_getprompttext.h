#ifndef MENU_PAK_TIMER_GETPROMPTTEXT_H
#define MENU_PAK_TIMER_GETPROMPTTEXT_H
#include "Common/pak_preview_selection.h"
#include "Menu/pak_preview_views.h"
extern s32 Timer_FindNextAvailableChannel(s32 currentChannel);
extern char *Timer_GetPromptByKind(int promptOwner, int kind);
extern void Timer_ProbeMenuChannel(struct Shared_PakMenu *record);
extern s32 Timer_GetChannelAndResult(struct PakChannelResultView *record, s32 *out);
extern char *Timer_GetPromptText(struct Shared_PakMenu *menu);
#endif
