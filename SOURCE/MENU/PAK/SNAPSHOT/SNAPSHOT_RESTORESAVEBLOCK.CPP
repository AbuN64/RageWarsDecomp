#include "COMMON/AIPROFILE.H"
#include "MENU/PAK/SAVE_SNAPSHOT.H"
#include "COMMON/WORLD.H"
#include "include_asm.h"
#include "COMMON/MENURECAT24.H"
#include "MENU/PAK_PROFILE_PROMPT_VIEWS.H"

#include "COMMON/MENURECAT24.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "TYPES.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "AI/PLAYER/PLAYER_GETAMMOCAPACITY.H"
#include "MENU/MENU_CREATEMENUFROMPARAMETERS.H"
#include "MENU/PAK/MENU_CREATEMENUFROMTEMPLATE.H"
#include "SNAPSHOT/SNAPSHOT_CHECKSTATUSPROMPT.H"

/* Reloads a saved controller-pak block when Snapshot_CheckStatusPrompt reports no problem for the selected
   channel: with g_pakAlternateOptionEnabled set it loads the block g_controllerPakSnapshotPayload points to onto the player found at
   g_playerViewRenderContext - the 0x18 Block70 into the player's 0x5E0 block, the 352 words at 0x88 into the option
   block g_gameSettings plus the word at its 0x580 (keeping the byte g_frontendSavedVideoModeIndex there), the four floats at
   0x8 (the game clock) into g_matchRoundCounters, g_controllerPakPreviewSeconds, g_controllerPakPreviewMinutes and g_controllerPakPreviewHours, the word at g_world_AchieveUpdateresultsscreen+0x44 as a byte
   count for the block at 0x60C copied into g_worldSnapshotNoteData - then shows the g_pakRestoreBlockPromptText prompt through
   Menu_OpenDialog; otherwise it retries Note_DeleteNote on note g_controllerPakOverwriteNoteIndex and shows the
   g_pakNoteDeleteSucceededDialogResource/g_pakNoteDeleteFailedDialogResource result. Pak_ConfirmPendingOperation's state 4 flow with the load path added; returns 1. */



extern s32 g_pakUseScannedChannel;
extern s32 g_pakAlternateOptionEnabled;
extern char g_pakRestoreBlockPromptText[];
extern char g_playerViewRenderContext[];
extern char g_matchEndingTeamWheelClose[];
extern s32 g_gameStateBlock[];
extern s32 g_persistedOptionUnlockFlags;
extern u8 g_frontendSavedVideoModeIndex[]; /* g_gameSettings+0x580, kept across the options reload */
/* The ROM stores the clock's seconds/minutes/hours through three separate objects (no shared base
   register, each store ordered after the block load), not through g_gameSettings.counters. */
extern f32 g_controllerPakPreviewSeconds[];
extern f32 g_controllerPakPreviewMinutes[];
extern f32 g_controllerPakPreviewHours[];
extern u8 g_worldSnapshotNoteData[];
extern SaveSnapshot *g_controllerPakSnapshotPayload;


extern s32 Note_DeleteNote(s32 ch, s32 index);



extern s32 g_menuOptionAvailabilityFlags; /* MIXED Snapshot_RestoreSaveBlock */
s32 Snapshot_RestoreSaveBlock(void *unused, PakPromptContext *menu) {
    Player *owner;
    s32 channel;
    Shared_World *world;
    u8 kept;
    u8 *src;
    u8 *dst;
    s32 i;

    if (g_pakUseScannedChannel != 0) {
        channel = g_introSelectedItem;
    } else {
        channel = menu->slot->controllerPort;
    }
    if (Snapshot_CheckStatusPrompt(menu, channel, 0) != 0) {
        g_pakMenuPromptAccepted = 1;
        return 1;
    }
    if (g_pakAlternateOptionEnabled != 0) {
        owner = Playerai_FindPlayerByController(g_playerViewRenderContext, menu->slot);
        world = &g_world;
        kept = g_frontendSavedVideoModeIndex[0];
        *(Copy70 *)&owner->state = g_controllerPakSnapshotPayload->player;
        *(Copy584 *)&g_gameSettings = g_controllerPakSnapshotPayload->world;
        g_gameSettings.counters.m_GameTimeFifteenth = g_controllerPakSnapshotPayload->view[0];
        g_controllerPakPreviewSeconds[0] = g_controllerPakSnapshotPayload->view[1];
        g_controllerPakPreviewMinutes[0] = g_controllerPakSnapshotPayload->view[2];
        g_controllerPakPreviewHours[0] = g_controllerPakSnapshotPayload->view[3];
        g_persistedOptionUnlockFlags = g_menuOptionAvailabilityFlags;
        g_frontendSavedVideoModeIndex[0] = kept;
        src = g_controllerPakSnapshotPayload->name;
        dst = g_worldSnapshotNoteData;
        for (i = 0; i < world->noteCount; i++) {
            *dst++ = *src++;
        }
        g_gameStateBlock[0] = 0;
        g_gameStateBlock[1] = 0;
        Menu_OpenDialog(&g_gameStateBlock[362], g_pakRestoreBlockPromptText, owner, owner->weaponAnimation, 0);
    } else if (Note_DeleteNote(channel, g_controllerPakOverwriteNoteIndex) == 0) {
        Menu_OpenDialog(g_matchEndingTeamWheelClose, g_pakNoteDeleteSucceededDialogResource, menu->player, menu->slot, menu->prompt);
    } else {
        Menu_OpenDialog(g_matchEndingTeamWheelClose, g_pakNoteDeleteFailedDialogResource, menu->player, menu->slot, menu->prompt);
    }
    return 1;
}

#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* Writes the 11-character rank title for the score g_pakProfileRankScore into the end of the item's text:
   the title comes from the band the score falls in (below 50, 150, 300, 500, 800, 1300, 2000,
   3000, 4500, 6500 and 9999 and above), and the text position is the text length from
   Menu_CountLineChars minus 11; returns 0. */
#include "TYPES.H"



extern u16 g_pakProfileRankScore;



























s32 Snapshot_UpdateScoreTitle(PakNoteTextEntry *item) {
    char *title;
    u8 *dest;
    s32 i;
    s32 score;

    title = 0;
    score = g_pakProfileRankScore;
    if (g_pakProfileRankScore < 50) {
        title = g_pakScoreBelow50Title;
    } else if (score >= 50 && score < 150) {
        title = g_pakScoreBelow150Title;
    } else if (score >= 150 && score < 300) {
        title = g_pakScoreBelow300Title;
    } else if (score >= 300 && score < 500) {
        title = g_pakScoreBelow500Title;
    } else if (score >= 500 && score < 800) {
        title = g_pakScoreBelow800Title;
    } else if (score >= 800 && score < 1300) {
        title = g_pakScoreBelow1300Title;
    } else if (score >= 1300 && score < 2000) {
        title = g_pakScoreBelow2000Title;
    } else if (score >= 2000 && score < 3000) {
        title = g_pakScoreBelow3000Title;
    } else if (score >= 3000 && score < 4500) {
        title = g_pakScoreBelow4500Title;
    } else if (score >= 4500 && score < 6500) {
        title = g_pakScoreBelow6500Title;
    } else if (score >= 6500 && score < 9999) {
        title = g_pakScoreBelow9999Title;
    } else if (score >= 9999) {
        title = g_pakScoreAtLeast9999Title;
    }
    dest = *item->text;
    dest += Menu_CountLineChars(item) - 11;
    if (title != 0) {
        for (i = 0; i < 11; i++) {
            *dest++ = *title++;
        }
    }
    return 0;
}
#endif
