#ifndef MENU_PAK_PROMPT_OPERATIONS_H
#define MENU_PAK_PROMPT_OPERATIONS_H
#include "Common/player_message_menu.h"
#include "Menu/pak_profile_prompt_views.h"
#include "Snapshot/snapshot_checkstatusprompt.h"
/* Plays the pak menu entry for a channel; quiet suppresses the prompt. */

extern int Pak_ConfirmPendingOperation(void * owner, struct PakPromptContext * menu, void * arg);
extern s32 Pak_ClosePromptByKind(void *owner, struct PakPromptContext *menu);
#endif
