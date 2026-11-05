#include "Menu/Pak/Snapshot/snapshot_handlemenuaction_symbols.h"
#include "include_asm.h"
#include "Snapshot/pak_timer_preview_value_format.h"
#include "Snapshot/g_pakformatdottedtriple.h"
#include "Snapshot/pak_profile_rank_score_format.h"
#include "Snapshot/g_digitdotformat.h"
#include "Common/aiprofile.h"
#include "Common/gameplay_transition.h"
#include "Common/gameplay_camera.h"
#include "../../../sdk/include/LIBC.H"
#include "Resmgr/resmgr_string_memory.h"
#include "Common/Lone/g_pakdialogpromptscannedchannel.h"
#include "Common/Lone/g_pakdialogidrepair_snapshotcheckeuropeansaveavailability.h"
#include "Common/Lone/g_languageindex.h"
#include "Common/pak_menu.h"
#include "Common/world.h"
#include "Menu/Pak/save_snapshot.h"
#include "Common/cache_releaseresource.h"
#include "Common/runtime_declarations.h"
#include "Common/resourcelockstate.h"
#include "Common/cache_allocateresource.h"
#include "Common/pak_save_text.h"
#include "Common/name.h"
#include "Common/player_message_menu.h"
#include "Common/note_state.h"
#include "Common/pak_preview_selection.h"
#include "Engine/control.h"
#include "Menu/pak_load.h"
#include "Common/sessionhandlerrow.h"
#include "Menu/pak_probestatus.h"
#include "Menu/pak_allocaterenderbuffers.h"
#include "Common/shared_gameslot.h"
#include "Menu/Pak/menu_createmenufromtemplate.h"
#include "Note/note_readnoteinfo.h"
#include "Snapshot/snapshot_checkstatusprompt.h"
#include "Ui/X_files/x_plus.h"
#include "Menu/Pak/Snapshot/snapshot_checkstatusprompt_symbols.h"
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/pak_profile_load.h"
#include "Menu/pak_profile_prompt_views.h"
#include "Common/Lone/g_pakprofileactiondialogresource.h"
#include "Note/note_readnotedata.h"
#include "Note/pak_allocaterenderbuffers.h"
#include "Menu/note_readnotedata.h"
#include "Menu/Pak/Snapshot/snapshot_evaluatesavechannel_symbols.h"
#include <platform_sdk.h>
#include "Menu/Pak/Snapshot/snapshot_checkeuropeansaveavailability_symbols.h"
#include "Common/game_session.h"
#include "Menu/Pak/Snapshot/snapshot_evaluatesavechannel.h"
#include "Menu/Pak/snapshot_payload.h"
#include "Common/Lone/g_controllerpakreadydialogresource.h"
#include "Menu/Pak/Snapshot/snapshot_savecontrollerrecord_symbols.h"
#include "Menu/Pak/Snapshot/snapshot_selectnote_symbols.h"
#include "Menu/Pak/snapshot_handlemenuaction.h"
#include "Engine/defs.h"
#if ((defined(VERSION_EU) || defined(VERSION_EU_X)))
#include "Menu/snapshot_savecontrollerrecord.h"
#endif
#if ((defined(VERSION_EU) || defined(VERSION_EU_X)))
#include "Menu/Pak/Snapshot/snapshot_handlemenuaction_symbols.h"
#endif
#include "Common/shared_optionsscreen.h"
#include "Common/vector4f.h"
#include "Menu/Pak/snapshot_closenotebrowser.h"
#include "Ai/Player/player_getammocapacity.h"
#include "Common/ballisticparams.h"
#include "Menu/Pak/Snapshot/snapshot_closenotebrowser_symbols.h"
#include "Menu/menu_createmenufromparameters.h"
#include "Common/cheatcode.h"
#include "Menu/note_readnoteinfo.h"
#include "Menu/Pak/profile.h"
#include "Menu/Pak/Snapshot/snapshot_restoresaveblock_symbols.h"
#include "Menu/Pak/Snapshot/snapshot_updatethresholdlabel_symbols.h"

const char g_pakSingleSaveBlockName[18] = "Single Save Block";

const char g_pakPaddedCountFormat[4] =
    "%3d\000";

#if !(defined(VERSION_US_REV1))
const char k_pakFormatIntBlankText[4] =
    "   \000";
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
const char g_pakChannelSnapshotDigitFormat[4] =
    "%1d";
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
const char g_pakTimerPreviewValueFormat[4] =
    "%2d";
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
const char s_snapshotDottedNumberFormat[14] =
    "%3d.%02d.%02d\000";
#endif

#if defined(VERSION_US_REV1)
const char k_pakFormatIntBlankText[4] =
    "   \000";
#endif

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
const char g_pakChannelDigitFormat[4] =
    "%1d\000";
#endif

#if defined(VERSION_DE) || defined(VERSION_US)
const char k_pakFormatIntDecimalText[4] =
    "%2d";
#endif

#if defined(VERSION_US_REV1)
const char k_pakFormatIntDecimalText[4] =
    "%2d";
#endif

#if defined(VERSION_DE) || defined(VERSION_US)
const char s_snapshotDottedNumberFormatCopy[14] =
    "%3d.%02d.%02d";
#endif

#if defined(VERSION_US_REV1)
const char g_pakFormatDottedTriple[14] =
    "%3d.%02d.%02d";
#endif

#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
const char g_pakProfileRankScoreFormat[5] =
    "%04d";
#endif

#if defined(VERSION_DE) || defined(VERSION_US)
const char k_GDigitdotformatEncodedBytes[5] =
    "%1d.";
#endif

#if defined(VERSION_US)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_DE)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
const char g_digitDotFormat[5] =
    "%1d.";
#endif

/* g_worldSnapshotNoteBytes is the noteCount member of the achievements results screen. The tail reads it through that member, which stops the compiler folding
 * its loads across the snapshot header stores; the two head reads are plain scalar loads. */

/* eu-x splits this function one word late (its leading lui sits in the
 * preceding data blob), so that version keeps the split asm. */
void Snapshot_CreateSaveSnapshot(u8 *player) {
    s32 snapshotSize = g_worldSnapshotNoteBytes + 1552;
    s32 allocationSize;
    SaveSnapshot **snapshotHandle;
    SaveSnapshot *snapshot;
    if (g_pakSnapshotResourceHandle != 0) {
        Cache_DrainAndCompactResources(0);
        Cache_ReleaseResource(0, g_pakSnapshotResourceHandle);
    }
    allocationSize = g_worldSnapshotNoteBytes + 1552;
    snapshotHandle = Cache_AllocateResource(0, allocationSize, 51, g_pakSingleSaveBlockName);
    g_pakSaveSnapshot = *snapshotHandle;
    g_pakSnapshotResourceHandle = snapshotHandle;
    XPlus_FillMemory(g_pakSaveSnapshot, 0, allocationSize);
    g_pakSaveSnapshot->player = *(Copy70 *)(&((Player *)player)->state);
    g_pakSaveSnapshot->world = *(Copy584 *)&g_gameSettings;
    snapshot = g_pakSaveSnapshot;
    snapshot->view[0] = g_matchRoundCounters.m_GameTimeFifteenth;
    snapshot->view[1] = g_matchRoundCounters.m_GameTimeSeconds;
    snapshot->view[2] = g_matchRoundCounters.m_GameTimeMinutes;
    snapshot->view[3] = g_matchRoundCounters.m_GameTimeHours;
    snapshot->size = snapshotSize;
    snapshot->dataSize = g_world.noteCount;
    Libc_CopyBytes(snapshot->name, g_worldSnapshotNoteData, g_world.noteCount);
}

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#define PAK_CODE g_pakLegacySnapshotGameNames[g_languageIndex]
#define PAK_COMPANY g_pakCompanyCodes[g_languageIndex]
#define PAK_TITLE1 g_pakProfileGameNames[getSettings_snapshotCheckstatusprompt()->language]
#define PAK_TITLE2 g_pakSnapshotGameNames[getSettings_snapshotCheckstatusprompt()->language]
#else
#define PAK_CODE g_pakLegacySnapshotGameNameFixed
#define PAK_COMPANY g_pakCompanyCodeFixed
#define PAK_TITLE1 g_pakProfileGameNameFixed
#define PAK_TITLE2 g_pakSnapshotGameNameFixed
#endif

/* Inlined into each title lookup: the loop pass merges the two address loads into one hoisted register,
 * which then outranks the loop-hoisted length constants 4 and 2 (a local pointer loses that race). */
static __inline__ Shared_Game *getSettings_snapshotCheckstatusprompt(void) {
    return &g_gameSettings;
}

void Snapshot_MarkSaveNotes(Shared_PakMenu *menu) {
    s32 ch;
    s32 i;
    s32 other;
    s32 result;
    s32 match;
    char ext[8];
    char company[8];
    char code[8];
    char name[16];
    s32 exists;
    s32 size;

    if (g_pakUseScannedChannel != 0) {
        ch = g_introSelectedItem;
    } else {
        ch = menu->owner->controllerPort;
    }
    for (i = 0; i < 16; i++) {
        result = Note_ReadNoteInfo(ch, i, &exists, name, ext, &size, company, code);
        other = 1;
        if (result == 0 && exists != 0) {
            switch (g_pakNoteTitleSelector) {
                case 1:
                    if (XPlus_StringLength(code) == 4 && XPlus_StringLength(company) == 2 &&
                        XPlus_CompareStrings(code, PAK_CODE) == 0 && XPlus_CompareStrings(company, PAK_COMPANY) == 0) {
                        match = 1;
                    } else {
                        match = 0;
                    }
                    if (XPlus_CompareStrings(name, PAK_TITLE1) == 0 && match != 0) {
                        other = 0;
                    }
                    break;
                case 2:
                    if (XPlus_StringLength(code) == 4 && XPlus_StringLength(company) == 2 &&
                        XPlus_CompareStrings(code, PAK_CODE) == 0 && XPlus_CompareStrings(company, PAK_COMPANY) == 0) {
                        match = 1;
                    } else {
                        match = 0;
                    }
                    if (XPlus_CompareStrings(name, PAK_TITLE2) == 0 && match != 0) {
                        other = 0;
                    }
                    break;
                case 0:
                default:
                    other = 0;
                    break;
            }
        }
        if (other) {
            menu->items[i + 3].flags &= ~0x1000000;
        } else {
            menu->items[i + 3].flags |= 0x1000000;
        }
    }
}

static __inline__ char *pakPrompt_snapshotCheckstatusprompt(s32 *channel) {
    char *result;
    switch (*channel) {
    case 0:
    default: result = g_pakControllerPortPrompts[0]; break;
    case 1: result = g_pakControllerPortPrompts[1]; break;
    case 2: result = g_pakControllerPortPrompts[2]; break;
    case 3: result = g_pakControllerPortPrompts[3]; break;
    }
    return result;
}

s32 Snapshot_CheckStatusPrompt(MenuPakBeginProfileLoad *menu, s32 channel, s32 quiet)
{
    s32 result, busy, slot;
    char *prompt, *sel;
    char *message;
    Note_ProbeStatus(channel);
    result = Note_GetStatus(channel);
    sel = 0;
    if (g_pakSaveMenuActiveDe) {
        if (g_pakProfileLoadMode_de) {
            if (g_pakUseScannedChannel) slot = g_introSelectedItem;
            else slot = menu->slot->controllerPort;
            sel = pakPrompt_snapshotCheckstatusprompt(&slot);
        }
    } else if (g_pakProfileLoadActive) {
        sel = g_controllerPakNotReadyDialogResource;
        if (g_pakProfileLoadMode_de) sel = g_pakStatusPromptAlternate;
    } else if (g_pakUseScannedChannel) sel = g_pakDialogPromptScannedChannel;
    prompt = sel;
    if (!prompt) return 0;
    busy = Control_TakePakChange(channel);
    if ((result == 0 || busy != 0) && result != -2) {
        if (busy) {
            Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, g_pakChangeBusyDialog, menu->player, menu->slot, prompt);
            return -1;
        }
        return result;
    }
    if (Note_IsChannelReady(channel)) {
        g_pakMenuPromptAccepted = 1;
        if (g_pakUseScannedChannel) message = g_pakScannedChannelReadyMessage;
        else {
            if (g_pakSaveMenuActiveDe) message = g_pakDialogDamagedPak;
            else message = g_pakChannelReadyMessage_SnapshotCheckstatusprompt;
        }
        Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, message, menu->player, menu->slot, prompt);
    } else if (!quiet) {
        g_pakMenuPromptAccepted = 1;
        if (Note_NeedsIdRepair(channel))
            Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, g_pakDialogIdRepair_SnapshotCheckeuropeansaveavailability, menu->player, menu->slot, prompt);
        else Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, g_pakChannelNotReadyDialog_SnapshotCheckstatusprompt, menu->player, menu->slot, prompt);
    } else if (result != -2) result = 0;
    return result;
}

/* Enters pak menu mode 1 on the selected channel: shows the pending message (g_pakPlayerMessagePending) with the channel's
   prompt, else probes the Controller Pak; with no pak data it saves the player's profile (flags, four words
   and eight name bytes) with its checksum and opens the note list through Snapshot_MarkSaveNotes, otherwise it
   shows the g_pakDialogDamagedPak, g_pakDialogIdRepair_SnapshotCheckeuropeansaveavailability or g_pakChannelNotReadyDialog_SnapshotCheckstatusprompt prompt. */
void Snapshot_BeginProfileSave(Shared_PakMenu *menu) {
    Player *owner = menu->player;
    Player *player;
    PakStatusProfile *profile;
    s32 channel;
    char *prompt;
    s32 i;

    g_pakSaveMenuActiveDe = 1;
    g_pakNoteSelectProbesNote = 1;
    g_pakProfileLoadActive = 0;
    g_pakProfileLoadMode_de = 1;
    g_pakNoteTitleSelector = 0;
    g_pakMenuPromptAccepted = 0;
    g_pakUseScannedChannel = 0;
    channel = menu->slot->controllerPort;
    player = owner;
    prompt = pakPrompt_snapshotCheckstatusprompt(&channel);
    if (g_pakPlayerMessagePending) {
        g_pakMenuPromptAccepted = 1;
        Menu_OpenDialog((char *)&((GameplayCamera *)menu->player->camera)->messageList, prompt, player, player->weaponAnimation, 0);
        return;
    }
    if (g_pakUseScannedChannel) {
        Note_ProbeStatus(g_introSelectedItem);
    } else {
        Note_ProbeStatus(menu->slot->controllerPort);
    }
    if (!Note_GetStatus(channel)) {
        profile = (PakStatusProfile *)player->profile;
        g_controllerPakPreviewProfileFlags = profile->flags;
        g_pakControllerRecord.values[0] = profile->words[0];
        g_pakProfileSavedWords[0] = profile->words[1];
        g_pakProfileSavedWords[1] = profile->words[2];
        g_pakProfileSavedWords[2] = profile->words[3];
        g_controllerPakPreviewProfilePadAfterFlags = 0;
        g_controllerPakPreviewProfilePadMiddle = 0;
        g_controllerPakPreviewProfilePadBeforeName = 0;
        for (i = 0; i < 8; i++) {
            g_controllerPakPreviewProfileName[i] = profile->name[i];
        }
        g_pakControllerRecord.checksum = Note_Crc32(&g_pakControllerRecord, 20, 4);
        Snapshot_MarkSaveNotes(menu);
        return;
    }
    g_pakMenuPromptAccepted = 1;
    if (Note_IsChannelReady(channel)) {
        Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, g_pakDialogDamagedPak, player, player->weaponAnimation, prompt);
    } else if (Note_NeedsIdRepair(channel)) {
        Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, g_pakDialogIdRepair_SnapshotCheckeuropeansaveavailability, player, player->weaponAnimation, g_playerMenuDialogRomResource);
    } else {
        Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, g_pakChannelNotReadyDialog_SnapshotCheckstatusprompt, player, player->weaponAnimation, prompt);
    }
}
#undef PAK_CODE
#undef PAK_COMPANY
#undef PAK_TITLE1
#undef PAK_TITLE2

/* Enters pak menu mode 1: sets the mode flags, clears the owner's 0x01000000 flag and, when a
   message is pending (g_pakPlayerMessagePending), shows the player's message at 0x554 through Menu_OpenDialog;
   otherwise probes the Controller Pak on the selected channel, falls back to Snapshot_MarkSaveNotes when
   Note_GetStatus reports none, and shows the g_pakChannelReadyMessage_SnapshotEvaluatesavechannel, g_pakDialogIdRepair_SnapshotEvaluatesavechannel or g_pakChannelNotReadyDialog_SnapshotEvaluatesavechannel prompt according to
   Note_IsChannelReady_SnapshotEvaluatesavechannel and Note_NeedsIdRepair. */
void Snapshot_BeginProfileLoad(Shared_PakMenu *menu) {
    s32 ch;

    g_pakSaveMenuActiveDe = 0;
    g_pakNoteSelectProbesNote = 0;
    g_pakProfileLoadActive = 1;
    g_pakProfileLoadMode_de = 1;
    g_pakNoteTitleSelector = 1;
    g_pakMenuPromptAccepted = 0;
    g_pakUseScannedChannel = 0;
    menu->items[20].flags &= ~0x01000000;
    ch = menu->slot->controllerPort;
    if (g_pakPlayerMessagePending != 0) {
        g_pakMenuPromptAccepted = 1;
        Menu_OpenDialog(MESSAGE_LIST_OF(menu->player->camera), g_pakStatusPromptAlternate, menu->player, menu->slot, 0);
        return;
    }
    Note_ProbeStatus(ch);
    if (Note_GetStatus(ch) == 0) {
        Snapshot_MarkSaveNotes(menu);
        return;
    }
    g_pakMenuPromptAccepted = 1;
    if (Note_IsChannelReady(ch) != 0) {
        Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, g_pakChannelReadyMessage_SnapshotCheckstatusprompt, menu->player, menu->slot, g_pakStatusPromptAlternate);
    } else if (Note_NeedsIdRepair(ch) != 0) {
        Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, g_pakDialogIdRepair_SnapshotCheckeuropeansaveavailability, menu->player, menu->slot, g_pakProfileActionDialogResource);
    } else {
        Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, g_pakChannelNotReadyDialog_SnapshotCheckstatusprompt, menu->player, menu->slot, g_pakStatusPromptAlternate);
    }
}

/* Rates the Controller Pak on channel ch as a save target: when one of its 16 notes is named
   g_pakProfileGameNameFixed or g_pakSnapshotGameNameFixed it selects the pak with score 123 and returns 1; otherwise it reads the
   pak's free space and note count and, when the pak is readable but has no notes or lacks the
   space the save image needs, records the pak as the best candidate if that need beats the
   current score and returns 0; a readable pak with room returns 1 and a read error returns 0. */
static inline s32 Pak_HasNamedNote_snapshotCheckeuropeansaveavailability(char *name, s32 channel) {
    u8 text[16];
    char *note;
    s32 index;
    for (index = 0; index < 16; index++) {
        Note_GetNoteGameName(channel, index, &note);
        Note_DecodeNoteText(note, text, 16);
        if (XPlus_CompareStrings(text, name) == 0) {
            return 1;
        }
    }
    return 0;
}

s32 Snapshot_EvaluateSaveChannel(void *menu, s32 ch, s32 *bestCh, s32 *bestScore) {
    s32 freeSpace;
    s32 noteCount;
    s32 found0;
    s32 found1;
    s32 result;
    s32 need;
    char *wanted;

#if defined(VERSION_EU) || defined(VERSION_EU_X)
    wanted = g_pakProfileGameNames[g_languageIndex];
#else
    wanted = g_pakProfileGameNameFixed;
#endif
    found0 = Pak_HasNamedNote_snapshotCheckeuropeansaveavailability(wanted, ch);
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    wanted = g_pakSnapshotGameNames[g_languageIndex];
#else
    wanted = g_pakSnapshotGameNameFixed;
#endif
    found1 = Pak_HasNamedNote_snapshotCheckeuropeansaveavailability(wanted, ch);
    if (found0 || found1) {
        *bestCh = ch;
        *bestScore = 123;
        return 1;
    }
    result = Note_GetFreePages(g_introSelectedItem, &freeSpace);
    if (result == 0) {
        result = Note_CountFreeNotes(g_introSelectedItem, &noteCount);
        if (result == 0) {
            need = Note_BytesToPakPages(g_worldSnapshotNoteBytes + 1552);
            if (noteCount == 0 || freeSpace < need) {
                if (*bestScore < need) {
                    *bestScore = need;
                    *bestCh = ch;
                }
                return 0;
            }
        }
    }
    return result == 0;
}

#if defined(VERSION_EU)
#define Snapshot_CheckControllerPak Snapshot_CheckEuropeanSaveAvailability
#endif
#if defined(VERSION_EU_X)
#define Snapshot_CheckControllerPak Snapshot_CheckLocalizedSaveAvailability
#endif
/* Selects a usable Controller Pak, checks its notes and free space, and opens the appropriate prompt. */



/* Per-version dialog scripts opened by Snapshot_CheckControllerPak. */
#if defined(VERSION_DE)
#define PAK_DIALOG_NO_CONTROLLER g_pakSnapshotNoControllerPromptDe
#define PAK_DIALOG_NO_PAK g_pakSnapshotNoPakPromptDe
#define PAK_DIALOG_LOW_SPACE g_pakSnapshotLowSpacePromptDe
#define PAK_DIALOG_FULL g_pakSnapshotCapacityPromptDe
#elif defined(VERSION_US)
#define PAK_DIALOG_NO_CONTROLLER g_pakSnapshotNoControllerPromptUs
#define PAK_DIALOG_NO_PAK g_pakSnapshotNoPakPromptUs
#define PAK_DIALOG_LOW_SPACE g_pakSnapshotLowSpacePromptUs
#define PAK_DIALOG_FULL g_pakSnapshotCapacityPromptUsRevision
#elif defined(VERSION_EU)
#define PAK_DIALOG_NO_CONTROLLER g_pakSnapshotNoControllerPromptEu
#define PAK_DIALOG_NO_PAK g_pakSnapshotNoPakPromptEu
#define PAK_DIALOG_LOW_SPACE g_pakSnapshotLowSpacePromptEu
#define PAK_DIALOG_FULL g_pakSnapshotCapacityPromptEu
#elif defined(VERSION_EU_X)
#define PAK_DIALOG_NO_CONTROLLER g_pakSnapshotNoControllerPromptEuX
#define PAK_DIALOG_NO_PAK g_pakSnapshotNoPakPromptEuX
#define PAK_DIALOG_LOW_SPACE g_pakSnapshotLowSpacePromptEuX
#define PAK_DIALOG_FULL g_pakSnapshotCapacityPromptEu
#else
#define PAK_DIALOG_NO_CONTROLLER g_pakSnapshotNoControllerPromptUsRevision
#define PAK_DIALOG_NO_PAK g_pakSnapshotNoPakPromptUsRevision
#define PAK_DIALOG_LOW_SPACE g_pakSnapshotLowSpacePromptUsRevision
#define PAK_DIALOG_FULL g_pakSnapshotCapacityPromptEuX
#endif
/* The game's two Controller Pak note names (PAL: per language). */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#define PAK_NOTE_NAME_1 g_pakProfileGameNames[g_languageIndex]
#define PAK_NOTE_NAME_2 g_pakSnapshotGameNames[g_languageIndex]
#else
#define PAK_NOTE_NAME_1 g_pakProfileGameNameFixed
#define PAK_NOTE_NAME_2 g_pakSnapshotGameNameFixed
#endif
/* Timer_FindNextAvailableChannel's scan: from the channel after currentChannel (or 0), the first channel whose probe is not -2; -1 if none. */
static inline s32 Pak_ScanNextChannel_snapshotCheckeuropeansaveavailability(s32 currentChannel) {
    s32 channel = 0;
    s32 attempts;
    if (currentChannel != -1) {
        channel = currentChannel + 1;
        if (channel >= 4) {
            channel = 0;
        }
    }
    attempts = 0;
    do {
        Note_ProbeStatus(channel);
        if (Note_GetStatus(channel) != -2) {
            break;
        }
        channel++;
        if (channel >= 4) {
            channel = 0;
        }
        attempts++;
    } while (attempts < 4);
    if (attempts == 4) {
        channel = -1;
    }
    return channel;
}

/* Ends the availability check: refreshes the save notes unless a prompt was already accepted, then clears the scan flags. */


void Snapshot_CheckControllerPak(Shared_PakMenu *menu) {
    s32 firstChannel;
    s32 freeChannel;
    s32 freeBytes;
    s32 freeNotes;
    s32 error;
    s32 retries;
    s32 status;
    s32 hasNote1;
    s32 hasNote2;
    u32 minBytes;
    u32 maxBytes;

    g_pakSaveMenuActiveDe = 0;
    g_pakNoteSelectProbesNote = 1;
    g_pakProfileLoadActive = 0;
    g_pakProfileLoadMode_de = 0;
    g_pakNoteTitleSelector = 0;
    g_pakMenuPromptAccepted = 0;
    g_pakUseScannedChannel = 1;
    if (Control_AnyControllerConnected() == 0) {
        g_pakMenuPromptAccepted = 1;
        g_pakUsable = 0;
        Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, &PAK_DIALOG_NO_CONTROLLER, (s32)menu->player, (s32) menu->slot, 0);
        g_pakStartButtonLatched = 1;
        g_pakScanActive = 0;
        return;
    }
    if (g_introSelectedItem == -1) {
        g_introSelectedItem = Pak_ScanNextChannel_snapshotCheckeuropeansaveavailability(-1);
        if (g_introSelectedItem == -1) {
            g_pakMenuPromptAccepted = 1;
            g_pakUsable = 0;
            Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, &PAK_DIALOG_NO_PAK, (s32)menu->player, (s32) menu->slot, 0);
            g_pakScanActive = 0;
            g_pakStartButtonLatched = 1;
            return;
        }
    }
    error = Note_NeedsIdRepair(g_introSelectedItem);
    if (error == 0) {
        SetN64_CommitSessionInputs((intptr_t) &g_gameSession);
        if ((menu->slot->inputFlags & 0x1000) && (g_pakStartButtonLatched == 0)) {
            g_pakRequestLatched = 1;
            g_pakStartButtonLatched = 1;
        }
        g_pakStartButtonLatched = 1;
        if ((g_pakProbeRequested != 0) || (g_pakRequestLatched != 0)) {
            Note_ProbeStatus(g_introSelectedItem);
            if (Note_GetStatus(g_introSelectedItem) == -2) {
                g_pakMenuPromptAccepted = 1;
                g_pakUsable = 0;
                Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, &PAK_DIALOG_NO_PAK, (s32)menu->player, (s32) menu->slot, 0);
                g_pakScanActive = 0;
                g_pakStartButtonLatched = 1;
                return;
            }
            goto finish_availability;
        }
        status = 0;
        retries = 0;
        freeChannel = -1;
        firstChannel = g_introSelectedItem;
        do {
            if (g_introSelectedItem != -1) {
                status = Snapshot_EvaluateSaveChannel(menu, g_introSelectedItem, &firstChannel, &freeChannel);
                if (status != 0) {
                    break;
                }
            }
            g_introSelectedItem = Pak_ScanNextChannel_snapshotCheckeuropeansaveavailability(g_introSelectedItem);
        } while (++retries < 4);
        if (status == 0) {
            g_introSelectedItem = firstChannel;
            Note_ProbeStatus(firstChannel);
            if (Note_GetStatus(g_introSelectedItem) == -2) {
                g_pakMenuPromptAccepted = 1;
                g_pakUsable = 0;
                Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, &PAK_DIALOG_NO_PAK, (s32)menu->player, (s32) menu->slot, 0);
                g_pakScanActive = 0;
                g_pakStartButtonLatched = 1;
                return;
            }
        }
        hasNote1 = Pak_HasNamedNote_snapshotCheckeuropeansaveavailability(PAK_NOTE_NAME_1, g_introSelectedItem);
        hasNote2 = Pak_HasNamedNote_snapshotCheckeuropeansaveavailability(PAK_NOTE_NAME_2, g_introSelectedItem);
        if ((hasNote1 == 0) && (hasNote2 == 0)) {
            error = Note_GetFreePages(g_introSelectedItem, &freeBytes);
            if (error == 0) {
                error = Note_CountFreeNotes(g_introSelectedItem, &freeNotes);
                if (error == 0) {
                    maxBytes = Note_BytesToPakPages(g_worldSnapshotNoteBytes + sizeof(SaveSnapshot));
                    minBytes = Note_BytesToPakPages(24U);
                    if (freeNotes != 0) {
                        if (freeBytes >= (s32)minBytes && freeBytes < (s32)maxBytes) {
                            g_pakMenuPromptAccepted = 1;
                            g_pakRequestLatched = 1;
                            Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, &PAK_DIALOG_LOW_SPACE, (s32)menu->player, (s32) menu->slot, (intptr_t) &g_pakDialogPromptScannedChannel);
                        } else if (freeBytes < (s32)minBytes) {
                            g_pakMenuPromptAccepted = 1;
                            g_pakRequestLatched = 1;
                            Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, &PAK_DIALOG_FULL, (s32)menu->player, (s32) menu->slot, (intptr_t) &g_pakDialogPromptScannedChannel);
                        }
                    } else {
                        g_pakMenuPromptAccepted = 1;
                        g_pakRequestLatched = 1;
                        Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, &PAK_DIALOG_FULL, (s32)menu->player, (s32) menu->slot, (intptr_t) &g_pakDialogPromptScannedChannel);
                    }
                }
            }
        } else {
            goto finish_availability;
        }
    }
    if (error != 0) {
        g_pakMenuPromptAccepted = 1;
        g_pakRequestLatched = 1;
        Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, &g_pakDialogIdRepair_SnapshotCheckeuropeansaveavailability, (s32)menu->player, (s32) menu->slot, (intptr_t) &g_pakDialogPromptScannedChannel);
    }
    finish_availability:

    if (g_pakMenuPromptAccepted == 0) {
        Snapshot_MarkSaveNotes(menu);
    }
    g_pakScanActive = 0;
    g_pakStartButtonLatched = 1;

}

/* The channel the pak menu works on: the scanned channel g_introSelectedItem while g_pakUseScannedChannel is set, else the slot's. */
static __inline__ void pakGetChannel_snapshotCheckeuropeansaveavailability(Shared_PakMenu *menu, s32 *channel) {
    if (g_pakUseScannedChannel != 0) {
        *channel = g_introSelectedItem;
    } else {
        *channel = menu->owner->controllerPort;
    }
}
/* Timer_SetSaveTrailerValue's body: store the snapshot checksum after the g_worldSnapshotNoteBytes bytes of note data. */
static __inline__ void pakSetChecksum_snapshotCheckeuropeansaveavailability(s32 offset, s32 value) {
    ((struct PlayerPakTimerView *)(g_worldSnapshotNoteBytes + offset))->trailerValue = value;
}
/* Opens the pak menu for a snapshot save: unless a message is pending (g_pakPlayerMessagePending), probes the channel's
   Controller Pak; a ready pak gets the save snapshot with its checksum and the note list (Snapshot_MarkSaveNotes),
   otherwise the damaged-pak (g_pakDialogDamagedPak) or g_pakDialogIdRepair_SnapshotCheckeuropeansaveavailability prompt opens. Twin of Snapshot_BeginProfileSave. */
void Snapshot_BeginSnapshotSave(Shared_PakMenu *menu) {
    Player *owner = menu->player;
    Player *player;
    s32 channel;

    g_pakSaveMenuActiveDe = 1;
    g_pakNoteSelectProbesNote = 1;
    g_pakProfileLoadActive = 0;
    g_pakProfileLoadMode_de = 0;
    g_pakNoteTitleSelector = 0;
    g_pakMenuPromptAccepted = 0;
    g_pakUseScannedChannel = 0;
    pakGetChannel_snapshotCheckeuropeansaveavailability(menu, &channel);
    player = owner;
    if (g_pakPlayerMessagePending) {
        g_pakMenuPromptAccepted = 1;
        return;
    }
    if (g_pakUseScannedChannel) {
        Note_ProbeStatus(g_introSelectedItem);
    } else {
        Note_ProbeStatus(menu->slot->controllerPort);
    }
    if (!Note_GetStatus(channel)) {
        Snapshot_CreateSaveSnapshot(player);
        pakSetChecksum_snapshotCheckeuropeansaveavailability((s32)g_pakSaveSnapshot, Note_Crc32(g_pakSaveSnapshot, g_worldSnapshotNoteBytes + 1548, 11));
        Snapshot_MarkSaveNotes(menu);
        return;
    }
    g_pakMenuPromptAccepted = 1;
    if (Note_IsChannelReady(channel)) {
        Menu_OpenDialog((char *)&((GameplayCamera *)player->camera)->messageList, g_pakDialogDamagedPak, (s32)player, (s32)player->weaponAnimation, 1);
    } else if (Note_NeedsIdRepair(channel)) {
        Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, &g_pakDialogIdRepair_SnapshotCheckeuropeansaveavailability, (s32)player, (s32)player->weaponAnimation, (s32)g_pakAlternateReadyDialogResource);
    }
}
#undef Snapshot_CheckControllerPak
#undef PAK_DIALOG_NO_CONTROLLER
#undef PAK_DIALOG_NO_PAK
#undef PAK_DIALOG_LOW_SPACE
#undef PAK_DIALOG_FULL
#undef PAK_NOTE_NAME_1
#undef PAK_NOTE_NAME_2

/* Enters pak menu mode 2: sets the mode flags, shows the g_controllerPakNotReadyDialogResource prompt when a message is pending (g_pakPlayerMessagePending), and otherwise clears the owner's 0x01000000 flag, probes the Controller Pak on the selected channel, falls back to Snapshot_MarkSaveNotes when Note_GetStatus reports none, and shows the g_pakChannelReadyMessage_SnapshotCheckstatusprompt, g_pakDialogIdRepair_SnapshotCheckeuropeansaveavailability or g_pakChannelNotReadyDialog_SnapshotCheckstatusprompt prompt according to Note_IsChannelReady_SnapshotEvaluatesavechannel and Note_NeedsIdRepair. */
void Snapshot_BeginBlockLoad(Shared_PakMenu *menu)
{
  Shared_PakMenu *activeMenu;
  int statusValue;
  char *channelUnavailableDialog;
  s32 ch;
  statusValue = 1;
  g_pakNoteTitleSelector = 2;
  g_pakSaveMenuActiveDe = 0;
  g_pakNoteSelectProbesNote = 0;
  g_pakProfileLoadActive = statusValue;
  g_pakProfileLoadMode_de = 0;
  g_pakMenuPromptAccepted = 0;
  g_pakUseScannedChannel = 0;
  ch = menu->slot->controllerPort;
  if (g_pakPlayerMessagePending != 0)
  {
    g_pakMenuPromptAccepted = 1;
    Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, g_controllerPakNotReadyDialogResource, menu->player, menu->slot, 0);
    return;
  }
  menu->items[20].flags &= ~0x01000000;
  Note_ProbeStatus(menu->slot->controllerPort);
  statusValue = 0;
  if (Note_GetStatus(ch) == statusValue)
  {
    Snapshot_MarkSaveNotes(menu);
    return;
  }
  g_pakMenuPromptAccepted = 1;
  if (Note_IsChannelReady(ch) != statusValue)
  {
    channelUnavailableDialog = g_pakChannelReadyMessage_SnapshotCheckstatusprompt;
    Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, channelUnavailableDialog, menu->player, menu->slot, 1);
  }
  else
  {
    activeMenu = menu;
    if (Note_NeedsIdRepair(ch) != 0)
    {
      Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, g_pakDialogIdRepair_SnapshotCheckeuropeansaveavailability, activeMenu->player, menu->slot, g_controllerPakReadyDialogResource);
    }
    else
    {
      Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, g_pakChannelNotReadyDialog_SnapshotCheckstatusprompt, activeMenu->player, activeMenu->slot, g_controllerPakNotReadyDialogResource);
    }
  }
}


/* Save the small controller-pak record when capacity allows, release the
 * pending resources, and show the channel-specific success/error dialog. */
static inline Player *pakRecordChannel_snapshotSavecontrollerrecord(Shared_PakMenu *menu, s32 *channel) {
    if (g_pakUseScannedChannel != 0) {
        *channel = g_introSelectedItem;
        return 0;
    }
    *channel = menu->owner->controllerPort;
    return menu->player;
}

static inline char *pakRecordChannelLabel_snapshotSavecontrollerrecord(s32 channel) {
    switch (channel) {
    case 0:
    default: return g_pakControllerPortPrompts[0];
    case 1: return g_pakControllerPortPrompts[1];
    case 2: return g_pakControllerPortPrompts[2];
    case 3: return g_pakControllerPortPrompts[3];
    }
}

s32 Snapshot_SaveControllerRecord(s32 owner, struct Shared_PakMenu *menu, s32 unusedEvent)
{
    Player *player, *selectedPlayer;
    char extension[8];
    s32 channel, freeBytes, slots, required, status = 0;
    s32 insufficient = 1;
    s32 attempted = 0;
    selectedPlayer = pakRecordChannel_snapshotSavecontrollerrecord(menu, &channel);
    player = selectedPlayer;
    if (g_pakSaveMenuActiveDe != 0) {
        required = Note_BytesToPakPages(24);
        status = Note_GetFreePages(channel, &freeBytes);
        if (status == 0) {
            if (required <= freeBytes) {
                status = Note_CountFreeNotes(channel, &slots);
                if (status == 0 && slots != 0) {
                    insufficient = 0;
                    status = Note_FindFreeNoteExtension(channel, extension);
                    if (status == 0) {
                        attempted = 1;
                        status = Note_SaveNote(channel, 24, &g_pakControllerRecord,
                                              RW_PAK_RECORD_TITLE, extension, RW_PAK_GAME_CODE);
                    }
                }
            }
            if (insufficient != 0) {
                Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, rw_pak_no_space_dialog(), player,
                                (PakMenuSlot *)player->weaponAnimation, menu->dialogData);
                return 0;
            }
        }
    }
    if (g_pakSnapshotResourceHandle != 0 || g_pakLoadedNoteResourceHandle != 0) Cache_DrainAndCompactResources(0);
    if (g_pakSnapshotResourceHandle != 0) Cache_ReleaseResource(0, g_pakSnapshotResourceHandle);
    if (g_pakLoadedNoteResourceHandle != 0) Cache_ReleaseResource(0, g_pakLoadedNoteResourceHandle);
    g_pakSnapshotResourceHandle = 0;
    g_pakLoadedNoteResourceHandle = 0;
    g_pakSaveSnapshot = 0;
    g_controllerPakSnapshotPayload = 0;
    if (!attempted) return 1;
    if (status == 0) {
        Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, rw_pak_save_success_dialog(), player,
                        (PakMenuSlot *)player->weaponAnimation, pakRecordChannelLabel_snapshotSavecontrollerrecord(channel));
    } else {
        Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, rw_pak_save_error_dialog(), player,
                        (PakMenuSlot *)player->weaponAnimation, pakRecordChannelLabel_snapshotSavecontrollerrecord(channel));
    }
    return 1;
}

/* The capacity prompt is per release. */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
static inline char *pakSnapshotCapacityPrompt_snapshotSavecontrollerrecord(void) { return (char *)&g_pakSnapshotCapacityPromptEu; }
#else
#if defined(VERSION_US_REV1)
static inline char *pakSnapshotCapacityPrompt_snapshotSavecontrollerrecord(void) { return g_pakSnapshotCapacityPromptEuX; }
#elif defined(VERSION_US)
static inline char *pakSnapshotCapacityPrompt_snapshotSavecontrollerrecord(void) { return (char *)&g_pakSnapshotCapacityPromptUsRevision; }
#else
static inline char *pakSnapshotCapacityPrompt_snapshotSavecontrollerrecord(void) { return g_pakSnapshotCapacityPromptDe; }
#endif
#endif
/* Save the snapshot only when both page and note capacity are available;
 * retain pending resources while showing the insufficient-capacity prompt. */
s32 Snapshot_SaveSnapshotAndClose(void *owner, Shared_PakMenu *menu) {
    Player *player, *selectedPlayer;
    char extension[8];
    s32 channel, freePages, freeNotes;
    s32 snapshotBytes, required, status;
    s32 showPrompt = 1;
    selectedPlayer = pakRecordChannel_snapshotSavecontrollerrecord(menu, &channel);
    player = selectedPlayer;
    snapshotBytes = g_worldSnapshotNoteBytes + sizeof(SaveSnapshot);
    if (g_pakSaveMenuActiveDe != 0) {
        required = Note_BytesToPakPages(snapshotBytes);
        status = Note_GetFreePages(channel, &freePages);
        if (status == 0) {
            if (required <= freePages) {
                if (Note_CountFreeNotes(channel, &freeNotes) == 0 && freeNotes != 0) {
                    showPrompt = 0;
                    if (Note_FindFreeNoteExtension(channel, extension) == 0) {
                        Note_SaveNote(channel, snapshotBytes, g_pakSaveSnapshot,
                                     RW_PAK_SNAPSHOT_TITLE, extension, RW_PAK_GAME_CODE);
                    }
                }
            }
            if (showPrompt != 0) {
                Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, pakSnapshotCapacityPrompt_snapshotSavecontrollerrecord(), player,
                                (PakMenuSlot *)player->weaponAnimation, menu->dialogData);
                return 0;
            }
        }
    }
    if (g_pakSnapshotResourceHandle != 0 || g_pakLoadedNoteResourceHandle != 0) Cache_DrainAndCompactResources(0);
    if (g_pakSnapshotResourceHandle != 0) Cache_ReleaseResource(0, g_pakSnapshotResourceHandle);
    if (g_pakLoadedNoteResourceHandle != 0) Cache_ReleaseResource(0, g_pakLoadedNoteResourceHandle);
    g_pakSnapshotResourceHandle = 0;
    g_pakLoadedNoteResourceHandle = 0;
    g_pakSaveSnapshot = 0;
    g_controllerPakSnapshotPayload = 0;
    return 1;
}

static __inline__ s32 pakNoteHasGameId_snapshotSelectnote(u8 *company, u8 *code) { if ((XPlus_StringLength(code) == 4) && (XPlus_StringLength(company) == 2) && (XPlus_CompareStrings(code, rw_pak_game_code(&g_playerViewRenderContext.game)) == 0) && (XPlus_CompareStrings(company, rw_pak_company(&g_playerViewRenderContext.game)) == 0)) return 1; return 0; }
#define PAK_SNAPSHOT_CHECKSUM_SEED 11
static __inline__ s32 pakBlockHasSize_snapshotSelectnote(ControllerPakPayload *data, s32 expected) { return data->header.length == expected; }
/* Reports whether the payload's checksum word (stored after its data) and note byte count match this save. */
static __inline__ s32 pakBlockIsConsistent_snapshotSelectnote(ControllerPakPayload *payload) {
    s32 dataLength = payload->header.length - 4;
    s32 *storedChecksum = (s32 *)&payload->bytes[dataLength];
    return Note_Crc32(payload->bytes, dataLength, PAK_SNAPSHOT_CHECKSUM_SEED) == *storedChecksum &&
           g_worldSnapshotNoteBytes == payload->header.noteBytes;
}
/* Ends a note selection: opens the load-error dialog when the read failed (returns 1), otherwise returns 0. */


/* Load a Controller Pak note, validate its profile or save-block
 * checksum, and open the corresponding selection or error dialog. */
s32 Snapshot_SelectNote(s32 *selection, Shared_PakMenu *menu) {
    u8 extension[8];
    u8 company[8];
    u8 code[8];
    u8 name[16];
    s32 exists;
    s32 pages;
    s32 length;
    s32 noteIndex;
    s32 expectedSize;
    s32 status;
    s32 copying;
    s32 current;
    s32 allocationSize;
    u8 *text;
    s32 readError;
    s32 blockState;
    s32 profileMatches;
    s32 channel;
    s32 gameNote;
    s32 i;
    struct CacheResourceNode *handle;
    struct CacheResourceNode *handle2;
    ControllerPakPayload *payload;
    ControllerPakPayload *payload2;

    readError = 0;
    noteIndex = *selection - 3;
    expectedSize = g_worldSnapshotNoteBytes + 1552;
    if (g_pakUseScannedChannel != 0) {
        channel = g_introSelectedItem;
    } else {
        channel = menu->slot->controllerPort;
    }
    if (Snapshot_CheckStatusPrompt(menu, channel, 0) != 0) {
        g_pakMenuPromptAccepted = 1;
        return 1;
    }
    if (g_pakNoteSelectProbesNote != 0) {
        status = Note_ReadNoteInfo(channel, noteIndex, &exists, name, extension, &pages, company, code);
        if ((status == 0) && (exists == 0)) {
            menu->state = 20;
            Snapshot_MarkSaveNotes(menu);
            return 0;
        }
        gameNote = pakNoteHasGameId_snapshotSelectnote(company,code);
        if (gameNote != 0) {
            Shared_Game *settings = &g_playerViewRenderContext.game;
            profileMatches = XPlus_CompareStrings(name, rw_pak_profile_name(settings)) == 0;
            blockState = XPlus_CompareStrings(name, rw_pak_block_name(settings)) == 0;
        } else {
            profileMatches = 0;
            blockState = 0;
        }
        if ((status == 0) && (exists != 0)) {
            if (profileMatches != 0) {
                if (Note_ReadNoteData(channel, noteIndex, (intptr_t)&g_pakControllerRecord, 24) != 0 ||
                    Note_Crc32(&g_pakControllerRecord, 20, 4) != g_pakControllerRecord.checksum) {
                    profileMatches = 0;
                    readError = 1;
                } else {
                    *rw_pak_loaded_profile() = g_pakControllerRecord;
                    g_controllerPakOverwriteNoteIndex = noteIndex;
                    Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, rw_pak_selected_profile_dialog(), (s32)menu->player, (s32)menu->slot, (s32)menu->dialogData);
                    return 1;
                }
            }
            if ((blockState != 0) && (readError == 0)) {
                blockState = pages;
                if (g_pakLoadedNoteResourceHandle != 0) {
                    Cache_DrainAndCompactResources(0);
                    Cache_ReleaseResource(0, g_pakLoadedNoteResourceHandle);
                }
                if (blockState != 0) blockState <<= 8;
                else {
                    blockState = g_worldSnapshotNoteBytes + 1552;
                }
                handle = Cache_AllocateResource(0, blockState, 51U, g_pakSingleSaveBlockName);
                payload = (ControllerPakPayload *)handle->data;
                g_pakLoadedNoteResourceHandle = handle;
                g_controllerPakSnapshotPayload = payload;
                XPlus_FillMemory(payload, 0, (u32) blockState);
                if (Note_ReadNoteData(channel, noteIndex, (s32)g_controllerPakSnapshotPayload, pages << 8)==0 &&
                    pakBlockHasSize_snapshotSelectnote(g_controllerPakSnapshotPayload,expectedSize) &&
                    pakBlockIsConsistent_snapshotSelectnote(g_controllerPakSnapshotPayload)) {
                    g_controllerPakOverwriteNoteIndex=noteIndex;
                    Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, rw_pak_selected_block_dialog(), (s32)menu->player, (s32)menu->slot, (s32)menu->dialogData);
                    return 1;
                }
                blockState=0;
                readError=1;
            }
            if (profileMatches == 0) {
                if (blockState == 0) {
                    Shared_Game *settings = &g_playerViewRenderContext.game;
                    current = 0;
                    text = rw_pak_note_text(settings);
                    g_controllerPakOverwriteNoteIndex = noteIndex;
                    if (Note_ContainsInvalidNameByte(name, 16) != 0) {
                        XPlus_CopyString(name, (u8 *)rw_pak_invalid_name(settings));
                    }
                    copying = 1;
                    i = 0;
                    do {
                        if (copying != 0) {
                            current = (name)[i];
                        }
                        if (current == 0) {
                            copying = 0;
                            current = 32;
                        }
                        *text = current;
                        i += 1;
                        text += 1;
                    } while (i < 16);
                    copying = 1;
                    text += 1;
                    i = 0;
                    do {
                        if (copying != 0) {
                            current = (extension)[i];
                        }
                        if (current == 0) {
                            copying = 0;
                            current = 32;
                        }
                        *text = current;
                        i += 1;
                        text += 1;
                    } while (i < 4);
                    Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, rw_pak_other_note_dialog(), (s32)menu->player, (s32)menu->slot, (s32)menu->dialogData);
                        return 1;
                }
            }
            goto finish_select_note;
        }
        goto finish_select_note;

    }
    if (g_pakProfileLoadActive != 0) {
        if ((g_pakProfileLoadMode_de != 0) && (readError == 0)) {
            if (((status=Note_ReadNoteInfo(channel, noteIndex, &exists, name, extension, &pages, company, code)) == 0) && (exists != 0)) {
                Shared_Game *settings = &g_playerViewRenderContext.game;
                if (XPlus_CompareStrings(name,rw_pak_profile_name(settings)) == 0) {
                if (Note_ReadNoteData(channel, noteIndex, (intptr_t)&g_pakControllerRecord, 24)!=0) {
                    readError=1;
                    goto finish_select_note;
                }
                if (Note_Crc32(&g_pakControllerRecord,20,4)!=g_pakControllerRecord.checksum) {
                    readError=1;
                    goto finish_select_note;
                }
                    *rw_pak_loaded_profile() =g_pakControllerRecord;
                    Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, rw_pak_loaded_profile_dialog(), (s32)menu->player, (s32)menu->slot, 0);
                    return 1;
                }
            }
            goto finish_select_note;
        }
        if ((g_pakProfileLoadActive != 0) && (g_pakProfileLoadMode_de == 0)) {
            if (readError != 0) goto finish_select_note;
            {
                if (((status=Note_ReadNoteInfo(channel, noteIndex, &exists, name, extension, &pages, company, code)) == 0) && (exists != 0) && (XPlus_CompareStrings(name, rw_pak_block_name(&g_playerViewRenderContext.game)) == 0)) {
                    allocationSize = pages;
                    if (g_pakLoadedNoteResourceHandle != 0) {
                        Cache_DrainAndCompactResources(0);
                        Cache_ReleaseResource(0, g_pakLoadedNoteResourceHandle);
                    }
                    if (allocationSize != 0) allocationSize <<= 8;
                    else {
                        allocationSize = g_worldSnapshotNoteBytes + 1552;
                    }
                    handle2 = Cache_AllocateResource(0, allocationSize, 51U, g_pakSingleSaveBlockName);
                    payload2 = (ControllerPakPayload *)handle2->data;
                    g_pakLoadedNoteResourceHandle = handle2;
                    g_controllerPakSnapshotPayload = payload2;
                    XPlus_FillMemory(payload2, 0, (u32) allocationSize);
                    if (Note_ReadNoteData(channel, noteIndex, (s32)g_controllerPakSnapshotPayload, pages << 8) == 0) {
                        length = g_controllerPakSnapshotPayload->header.length;
                        if (length == expectedSize && pakBlockIsConsistent_snapshotSelectnote(g_controllerPakSnapshotPayload)) {
                            Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, rw_pak_loaded_block_dialog(), (s32)menu->player, (s32)menu->slot, 0);
                        return 1;
                        }
                    }
                    readError = 1;
                    if ((g_pakSnapshotResourceHandle != 0) || (g_pakLoadedNoteResourceHandle != 0)) {
                        Cache_DrainAndCompactResources(0);
                    }
                    if (g_pakSnapshotResourceHandle != 0) {
                        Cache_ReleaseResource(0, g_pakSnapshotResourceHandle);
                    }
                    if (g_pakLoadedNoteResourceHandle != 0) {
                        Cache_ReleaseResource(0, g_pakLoadedNoteResourceHandle);
                    }
                    g_pakSnapshotResourceHandle = 0;
                    g_pakLoadedNoteResourceHandle = 0;
                    g_pakSaveSnapshot = 0;
                    g_controllerPakSnapshotPayload = 0;
                    goto finish_select_note;
                }
                goto finish_select_note;
            }
            readError = 1;
            goto finish_select_note;
        }
        goto finish_select_note;
    }
    goto finish_select_note;
finish_select_note: {

    char *messageExtra;
    struct Dialog *dialog;

    if (readError == 0) {
        return 0;
    }
    if (g_pakProfileLoadMode_de != 0) messageExtra = g_pakProfileActionDialogResource;
    else messageExtra = g_controllerPakReadyDialogResource;
    dialog = rw_pak_load_error_dialog();
    g_controllerPakSelectedNoteIndex = noteIndex;
    Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, dialog, (s32)menu->player, (s32)menu->slot, (s32)messageExtra);
    return 1;

}
}
#undef PAK_SNAPSHOT_CHECKSUM_SEED

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#define ENTRY_TEXT(e) ((e)->text[g_languageIndex])
#define PAK_HEADER_376C g_pakSpaceLabelScannedLocalized_eu
#else
#define ENTRY_TEXT(e) (*(e)->text)
#define PAK_HEADER_376C (&g_pakSpaceLabelScannedText)
#endif

/* Native resident constant storage; absolute access symbols retain their addresses. */
static inline int spaceRequired_snapshotHandlemenuaction(int size) {size += 1552; return Note_BytesToPakPages(size);}

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#define PAK_OVERWRITE_NOTE_DIALOG g_pakOverwriteNoteDialogResource_eu
#else
#define PAK_OVERWRITE_NOTE_DIALOG g_pakOverwriteNoteDialogResource
#endif

static inline void pickChannel_snapshotHandlemenuaction(Shared_PakMenu *menu, s32 *ch)
{
    if (g_pakUseScannedChannel != 0) {
        *ch = g_introSelectedItem;
    } else {
        *ch = menu->owner->controllerPort;
    }
}

static inline s32 findNote_snapshotHandlemenuaction(s32 ch, s32 *found)
{
    char name[16];
    s32 state;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    char *game = g_pakSnapshotGameNames[g_languageIndex];
#else
    char *game = g_pakSnapshotGameNameFixed;
#endif
    s32 i;

    g_controllerPakOverwriteNoteIndex = -1;
    for (i = 0; i < 16; i++) {
        Note_GetNoteGameName(ch, i, &state);
        Note_DecodeNoteText(state, name, 16);
        if (XPlus_CompareStrings(name, game) == 0) {
            if (found != 0) {
                *found = i;
            }
            return 1;
        }
    }
    return 0;
}

s32 Snapshot_UpdateNoteLabel(PakNoteTextEntry *entry, PakNotesMenu *menu) {
    u8 name[16];
    u8 ext[8];
    char companyCode[8];
    char gameCode[8];
    s32 exists;
    s32 size;
    s32 ch;
    s32 result;
    s32 more;
    s32 i;
    u8 *dst;
    u8 c;
    s32 index;
    char **placeholder;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    Shared_Game *game;
#endif

    c = ' ';
    index = entry->id - 3;
    if (g_pakMenuPromptAccepted != 0) {
        return 0;
    }
    if (g_pakUseScannedChannel != 0) {
        ch = g_introSelectedItem;
    } else {
        ch = menu->owner->controllerPort;
    }
    result = Note_ReadNoteInfo(ch, index, &exists, name, ext, &size, companyCode, gameCode);
    if (exists != 0 && result == 0) {
        if (Note_ContainsInvalidNameByte(name, 16) != 0) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
            XPlus_CopyString(name, g_pakDefaultNoteNamesLocalized[g_languageIndex]);
#else
            XPlus_CopyString(name, g_pakDefaultNoteNameFixed);
#endif
        }
    } else {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        game = &g_gameSettings;
        XPlus_CopyString(name, g_pakEmptyNoteNamesLocalized_eu[game->language]);
        XPlus_CopyString(ext, g_pakEmptyNoteNamesLocalized_eu[game->language]);
#else
        placeholder = &g_pakEmptyNoteNameFixed;
        XPlus_CopyString(name, *placeholder);
        XPlus_CopyString(ext, *placeholder);
#endif
        size = 0;
    }
    more = 1;
    dst = ENTRY_TEXT(entry);
    dst += 3;
    for (i = 0; i < 16; i++) {
        if (more) {
            c = name[i];
        }
        if (c == 0) {
            more = 0;
            c = ' ';
        }
        *dst++ = c;
    }
    more = 1;
    dst++;
    for (i = 0; i < 4; i++) {
        if (more) {
            c = ext[i];
        }
        if (c == 0) {
            more = 0;
            c = ' ';
        }
        *dst++ = c;
    }
    *dst += 2;
    Defs_FormatIntegerValue(dst, g_pakPaddedCountFormat, size);
    return 0;
}

s32 Snapshot_UpdateSpaceLabel(PakNoteTextEntry *entry, PakStatusPakSaveMenu *menu) {
    Digits digits;
    s32 freeSpace;
    s32 ch;
    s32 need;
    s32 result;
    u8 *text;
    u8 **header;
    char *format;
    Digits *buffer;

    if (g_pakUseScannedChannel != 0) {
        ch = g_introSelectedItem;
    } else {
        ch = menu->slot->controllerPort;
    }
    digits = k_pakDigitsInitial;
    buffer = &digits;
    if (g_pakSaveMenuActiveDe != 0) {
        entry->text = &g_pakSpaceLabelText;
        if (Note_GetFreePages(ch, &freeSpace) == 0) {
            if (g_pakProfileLoadMode_de) need=Note_BytesToPakPages(24); else need=spaceRequired_snapshotHandlemenuaction(g_worldSnapshotNoteBytes);
            text = ENTRY_TEXT(entry);
            Defs_FormatIntegerValue(digits.c, g_pakPaddedCountFormat, freeSpace);
            text += 14;
            *text++ = digits.c[0];
            *text++ = digits.c[1];
            *text = digits.c[2];
            Defs_FormatIntegerValue(digits.c, g_pakPaddedCountFormat, need);
            text += 15;
            *text++ = digits.c[0];
            *text = digits.c[1];
            text[1] = digits.c[2];
        }
    } else if (g_pakUseScannedChannel != 0 || g_pakProfileLoadActive != 0) {
        if (g_pakUseScannedChannel != 0) {
            header = PAK_HEADER_376C;
        } else {
            header = &g_pakSpaceLabelText;
        }
        entry->text = header;
        result = Note_GetFreePages(ch, &freeSpace);
        need = Note_BytesToPakPages(g_worldSnapshotNoteBytes + 1552);
        text = ENTRY_TEXT(entry);
        if (result == 0) {
            text += 14;
            format = g_pakPaddedCountFormat;
            Defs_FormatIntegerValue(buffer->c, format, freeSpace);
            *text++ = digits.c[0];
            *text++ = digits.c[1];
            *text = digits.c[2];
            Defs_FormatIntegerValue(buffer->c, format, need);
            text += 15;
            *text++ = digits.c[0];
            *text = digits.c[1];
            text[1] = digits.c[2];
        }
    } else {
        entry->text = &g_unlockedLevelResultLabel;
    }
    return 0;
}

s32 Snapshot_HandleMenuAction(s32 entry, Shared_PakMenu *menu, s32 unusedEvent)
{
    s32 ch = 0;
    s32 use;
    s32 next;
    s32 tries;
    s32 hasNote;
    s32 c;

    if (g_pakSaveMenuActiveDe != 0) {
        pickChannel_snapshotHandlemenuaction(menu, &ch);
    }
    if (g_pakUseScannedChannel != 0) {
        use = g_introSelectedItem;
    } else {
        use = ch;
    }
    if (Snapshot_CheckStatusPrompt(menu, use, 0) != 0) {
        g_pakMenuPromptAccepted = 1;
        return 1;
    }
    if (g_pakProfileLoadMode_de != 0) {
        if (g_pakSaveMenuActiveDe != 0) {
            Snapshot_SaveControllerRecord(entry, menu, unusedEvent);
            return 1;
        }
    } else if (g_pakSaveMenuActiveDe != 0) {
        hasNote = findNote_snapshotHandlemenuaction(use, &g_controllerPakOverwriteNoteIndex);
        if (hasNote != 0 && g_controllerPakOverwriteNoteIndex >= 0 && g_controllerPakOverwriteNoteIndex < 16) {
            Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, PAK_OVERWRITE_NOTE_DIALOG, menu->player, menu->owner, g_pakAlternateReadyDialogResource);
            return 1;
        }
        Snapshot_SaveSnapshotAndClose(entry, menu);
        return 1;
    }
    if (g_pakUseScannedChannel != 0) {
        next = 0;
        if (g_introSelectedItem != -1) {
            next = g_introSelectedItem + 1;
            if (next >= 4) {
                next = 0;
            }
        }
        for (tries = 0; tries < 4; tries++) {
            Note_ProbeStatus(next);
            if (Note_GetStatus(next) != -2) {
                break;
            }
            next++;
            if (next >= 4) {
                next = 0;
            }
        }
        if (tries == 4) {
            next = -1;
        }
        g_introSelectedItem = next;
        if (next == -1) {
            g_pakRecheckRequested = g_pakMenuPromptAccepted = 1;
            return 1;
        }
        if (g_pakUseScannedChannel != 0) {
            c = g_introSelectedItem;
        } else {
            c = menu->owner->controllerPort;
        }
        ch = c;
        if (Snapshot_CheckStatusPrompt(menu, c, 0) != 0) {
            g_pakMenuPromptAccepted = 1;
            return 1;
        }
        Snapshot_MarkSaveNotes(menu);
    }
    return 0;
}
#undef ENTRY_TEXT
#undef PAK_HEADER_376C
#undef PAK_OVERWRITE_NOTE_DIALOG

/* Releases temporary profile buffers and opens the controller-pak prompt for the selected player and channel, labelling the port prompt by channel. */
static inline void getChannel_snapshotClosenotebrowser(PakNoteBrowserContext *menu, s32 *channel) {
    if (g_pakUseScannedChannel != 0) {
        *channel = g_introSelectedItem;
    } else {
        *channel = menu->slot->controllerPort;
    }
}

s32 Snapshot_CloseNoteBrowser(void *entry, PakNoteBrowserContext *menu) {
    s32 channel;
    char *label;
    s8 port;
    SharedPlayer *target;
    SharedPlayer *player;

    if (g_pakSnapshotResourceHandle != 0 || g_pakLoadedNoteResourceHandle != 0) {
        Cache_DrainAndCompactResources(0);
    }
    if (g_pakSnapshotResourceHandle != 0) {
        Cache_ReleaseResource(0, g_pakSnapshotResourceHandle);
    }
    if (g_pakLoadedNoteResourceHandle != 0) {
        Cache_ReleaseResource(0, g_pakLoadedNoteResourceHandle);
    }
    g_pakSnapshotResourceHandle = 0;
    g_pakLoadedNoteResourceHandle = 0;
    g_pakSaveSnapshot = 0;
    g_controllerPakSnapshotPayload = 0;
    g_pakCancelStateWord = 0;
    getChannel_snapshotClosenotebrowser(menu, &channel);
    if (g_pakUseScannedChannel != 0) {
        g_pakRecheckRequested = 0;
        g_pakRequestLatched = 0;
        g_pakUsable = 1;
        g_pakProbeRequested = 0;
        Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, g_pakDialogPromptScannedChannel, 0, menu->slot, 0);
        return 1;
    }
    if (g_pakProfileLoadMode_de != 0) {
        if (g_pakProfileLoadActive != 0) {
            g_pakMenuPromptAccepted = 1;
            target = Playerai_FindPlayerByController(&g_playerViewRenderContext, menu->slot);
            Menu_OpenDialog(MESSAGE_LIST_OF(target->views5DC.view5DC_6.storage), g_playerMenuDialogTable, target, target->views5E8.view698_38.title, channel);
            return 1;
        }
        if (g_pakSaveMenuActiveDe != 0) {
            g_pakMenuPromptAccepted = 1;
            port = menu->slot->controllerPort;
            player = menu->player;
            channel = port;
            target = player;
            switch (channel) {
            default:
            case 0:
                label = g_pakControllerPortPrompts[0];
                break;
            case 1:
                label = g_pakControllerPortPrompts[1];
                break;
            case 2:
                label = g_pakControllerPortPrompts[2];
                break;
            case 3:
                label = g_pakControllerPortPrompts[3];
                break;
            }
            Menu_OpenDialog(MESSAGE_LIST_OF(target->views5DC.view5DC_6.storage), label, target, target->views5E8.view698_38.title, channel);
            return 1;
        }
    } else {
        target = Playerai_FindPlayerByController(&g_playerViewRenderContext, menu->slot);
        if (g_pakProfileLoadActive != 0) {
            g_pakMenuPromptAccepted = 1;
            Menu_OpenDialog(&((Shared_MenuData *)&g_playerViewRenderContext)->dialogOwner, g_controllerPakNotReadyDialogResource, target, target->views5E8.view698_38.title, channel);
            return 1;
        }
        if (g_pakSaveMenuActiveDe != 0) {
            g_pakMenuPromptAccepted = 1;
            return 1;
        }
    }
    return 0;
}

/* The ROM stores the clock's seconds/minutes/hours through three separate objects (no shared base
   register, each store ordered after the block load), not through g_gameSettings.counters. */
s32 Snapshot_RestoreSaveBlock(void *menuOwner, PakPromptContext *menu) {
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
        owner = Playerai_FindPlayerByController(&g_playerViewRenderContext, menu->slot);
        world = &g_world;
        kept = g_frontendSavedVideoModeIndex;
        *(Copy70 *)&owner->state = g_controllerPakSnapshotPayload->save.player;
        *(Copy584 *)&g_gameSettings = g_controllerPakSnapshotPayload->save.world;
        g_gameSettings.counters.m_GameTimeFifteenth = g_controllerPakSnapshotPayload->save.view[0];
        g_controllerPakPreviewSeconds[0] = g_controllerPakSnapshotPayload->save.view[1];
        g_controllerPakPreviewMinutes[0] = g_controllerPakSnapshotPayload->save.view[2];
        g_controllerPakPreviewHours[0] = g_controllerPakSnapshotPayload->save.view[3];
        g_persistedOptionUnlockFlags = g_menuOptionAvailabilityFlags;
        g_frontendSavedVideoModeIndex = kept;
        src = g_controllerPakSnapshotPayload->save.name;
        dst = g_worldSnapshotNoteData;
        for (i = 0; i < world->noteCount; i++) {
            *dst++ = *src++;
        }
        /* The pre-fold s32 view stores at +0/+4 and addresses the dialog at 362 * 4. */
        ((s32 *)&g_gameStateBlock)[0] = 0;
        ((s32 *)&g_gameStateBlock)[1] = 0;
        Menu_OpenDialog(((char *)&g_gameStateBlock + 0x5A8), g_pakRestoreBlockPromptText, owner, owner->weaponAnimation, 0);
    } else if (Note_DeleteNote(channel, g_controllerPakOverwriteNoteIndex) == 0) {
        Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, g_pakNoteDeleteSucceededDialogResource, menu->player, menu->slot, menu->prompt);
    } else {
        Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, g_pakNoteDeleteFailedDialogResource, menu->player, menu->slot, menu->prompt);
    }
    return 1;
}

#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* Writes the 11-character rank title for the score g_pakProfileRankScore into the end of the item's text:
   the title comes from the band the score falls in (below 50, 150, 300, 500, 800, 1300, 2000,
   3000, 4500, 6500 and 9999 and above), and the text position is the text length from
   Menu_CountLineChars minus 11; returns 0. */

s32 Snapshot_UpdateScoreTitle(PakNoteTextEntry *item) {
    char *title;
    u8 *dest;
    s32 i;
    s32 score;

    title = 0;
    score = g_pakProfileRankScore;
    if (g_pakProfileRankScore < 50) {
        title = g_pakRankScoreTitles[0];
    } else if (score >= 50 && score < 150) {
        title = g_pakRankScoreTitles[1];
    } else if (score >= 150 && score < 300) {
        title = g_pakRankScoreTitles[2];
    } else if (score >= 300 && score < 500) {
        title = g_pakRankScoreTitles[3];
    } else if (score >= 500 && score < 800) {
        title = g_pakRankScoreTitles[4];
    } else if (score >= 800 && score < 1300) {
        title = g_pakRankScoreTitles[5];
    } else if (score >= 1300 && score < 2000) {
        title = g_pakRankScoreTitles[6];
    } else if (score >= 2000 && score < 3000) {
        title = g_pakRankScoreTitles[7];
    } else if (score >= 3000 && score < 4500) {
        title = g_pakRankScoreTitles[8];
    } else if (score >= 4500 && score < 6500) {
        title = g_pakRankScoreTitles[9];
    } else if (score >= 6500 && score < 9999) {
        title = g_pakRankScoreTitles[10];
    } else if (score >= 9999) {
        title = g_pakRankScoreTitles[11];
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

#if defined(VERSION_DE)
typedef struct { char pad0[0x14]; char **text; } PakThresholdLabel;
/* Copies the 12-byte rank label chosen by the value g_pakProfileRankScore (banded 0, 50, 150, 300, 500, 800, 1300, 2000, 3000, 4500, 6500, 9999) into the label's text after its fixed prefix; returns zero. */
s32 Snapshot_UpdateThresholdLabel(PakThresholdLabel *label) {
    u32 v = g_pakLoadedProfile.values[2];
    char *src = 0;
    char *dst;
    s32 i;
    if (v < 50) src = g_pakRankThresholdTexts[0];
    else if (v >= 50 && v < 150) src = g_pakRankThresholdTexts[1];
    else if (v >= 150 && v < 300) src = g_pakRankThresholdTexts[2];
    else if (v >= 300 && v < 500) src = g_pakRankThresholdTexts[3];
    else if (v >= 500 && v < 800) src = g_pakRankThresholdTexts[4];
    else if (v >= 800 && v < 1300) src = g_pakRankThresholdTexts[5];
    else if (v >= 1300 && v < 2000) src = g_pakRankThresholdTexts[6];
    else if (v >= 2000 && v < 3000) src = g_pakRankThresholdTexts[7];
    else if (v >= 3000 && v < 4500) src = g_pakRankThresholdTexts[8];
    else if (v >= 4500 && v < 6500) src = g_pakRankThresholdTexts[9];
    else if (v >= 6500 && v < 9999) src = g_pakRankThresholdTexts[10];
    else if ((s32)v >= 9999) src = g_pakRankThresholdTexts[11];
    dst = *label->text;
    dst += 8;
    if (src != 0) {
        i = 0;
        do { *dst++ = *src++; i++; } while (i < 12);
    }
    return 0;
}
#endif
