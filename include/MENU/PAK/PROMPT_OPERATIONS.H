#ifndef MENU_PAK_PROMPT_OPERATIONS_H
#define MENU_PAK_PROMPT_OPERATIONS_H
#include "COMMON/MENURECAT24.H"
#include "MENU/PAK_PROFILE_PROMPT_VIEWS.H"
/* Plays the pak menu entry for a channel; quiet suppresses the prompt. */
extern s32 Snapshot_CheckStatusPrompt(PakPromptContext *menu, s32 channel, s32 quiet);
extern int Pak_ConfirmPendingOperation(void * owner, struct PakPromptContext * menu, void * arg);
extern s32 Pak_ClosePromptByKind(void *owner, PakPromptContext *menu);
#endif
