#include "Ai/cteamselect.h"
#include "Menu/Pak/Snapshot/snapshot_checkeuropeansaveavailability_symbols.h"
#include "Common/aiprofile.h"
#include "Common/gameplay_camera.h"
#include "include_asm.h"
#include "Common/player_message_menu.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
#include "Common/ballisticparams.h"
#include "Common/shared_optionsscreen.h"
#include "Common/pak_profile_load.h"
#include "Menu/pak_profile_prompt_views.h"
#include "Common/frontend_resource_load_state.h"
#include <platform_sdk.h>
#include "types.h"
#include "Menu/Pak/timer_cancelpendingoperation.h"
#include "Menu/Pak/menu_createmenufromtemplate.h"
#include "Snapshot/snapshot_checkstatusprompt.h"
#include "Menu/Pak/Timer/timer_cancelpendingoperation_symbols.h"
#include "Common/pak_preview_selection.h"
#include "Common/frontend_video_mode.h"
#include "Frontend/node_findwidgetbyresourceid.h"
#include "Common/playerprofiles.h"
#if ((defined(VERSION_EU)))
#include "Common/menu_model_preview.h"
#endif
#if ((defined(VERSION_EU)))
#include "Common/shared_worldfunc.h"
#endif
#include "Common/world.h"
#include "Resmgr/resmgr_string_memory.h"
#include "Common/note_state.h"
#include "Menu/Pak/snapshot_payload.h"
#include "Menu/Pak/save_snapshot.h"
#include "Menu/Pak/profile_save_blocks.h"
#include "Ui/X_files/x_plus.h"
#include "Common/cache_releaseresource.h"
#include "Common/resourcelockstate.h"
#include "Common/cache_allocateresource.h"
#include "Common/shared_gameslot.h"
#if ((defined(VERSION_EU) || defined(VERSION_EU_X)))
#include "Common/pak_save_text.h"
#endif
#include "Menu/pak_load.h"
#if ((defined(VERSION_EU) || defined(VERSION_EU_X)))
#include "Menu/Pak/Timer/timer_symbols.h"
#endif
#include "Menu/Pak/pak_applystagedplayerprofile.h"
#include "Menu/Pak/Timer/pak_restoresavedsession_symbols.h"
#include "Common/pak_menu.h"
#include "Menu/Pak/Timer/timer_checkmenupakchange_symbols.h"
#include "Common/Lone/g_pakdialogpromptscannedchannel.h"
#include "Common/Lone/g_languageindex.h"
#include "Menu/pak_preview_views.h"
#include "Common/pakqueuestate.h"
#include "Common/globals.h"
#include "Menu/Pak/timer_getprompttext.h"
#include "Engine/defs.h"
#include "Menu/Items/Scene/scene_updatependingobjects.h"
#include "Menu/menu_createmenufromparameters.h"
#include "Note/note_readnotedata.h"
#include "Note/pak_allocaterenderbuffers.h"
#include "Common/sessionhandlerrow.h"
#include "Engine/control.h"
#include "Menu/Pak/Timer/timer_getprompttext_symbols.h"
#include "Common/game_session.h"
#include "Common/textlayermetrics.h"
#include "Common/triple.h"
#if ((defined(VERSION_EU) || defined(VERSION_EU_X)))
#include "Menu/Pak/Timer/pak_updateownerchannellabel_symbols.h"
#endif
#include "Menu/built_menu.h"
#include "Menu/Pak/timer_updateoperationchoicelabel.h"
#include "Menu/Pak/Timer/timer_updateoperationchoicelabel_symbols.h"
#include "Common/pak_enter_player_options.h"
#include "Menu/Pak/timer.h"
#include "Snapshot/pak_timer_preview_value_format.h"
#include "Menu/Pak/Timer/timer_formatpreviewvalue_symbols.h"
#include "Common/Lone/g_controllerpakreadydialogresource.h"
#include "Common/name.h"
#include "Menu/identifier.h"
#include "Pickup/pickup.h"
#include "Menu/Pak/profile_preview_and_line_text.h"
#include "Snapshot/g_pakformatdottedtriple.h"
#include "Menu/Pak/Timer/timer_formatpreviewdottedtriple_symbols.h"
#include "Menu/menu_event_handlers.h"

static __inline__ void pakShow_timerCancelpendingoperation(MenuPakBeginProfileLoad *menu) {
    s32 channel;
    if (g_pakUseScannedChannel) channel = g_introSelectedItem;
    else channel = menu->slot->controllerPort;
    if (Snapshot_CheckStatusPrompt(menu, channel, 1)) {
        g_pakMenuPromptAccepted = 1;
        Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, menu->prompt, (s32)menu->player, (s32)menu->slot, 0);
    } else {
        Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, menu->prompt, (s32)menu->player, (s32)menu->slot, 0);
    }
}

static __inline__ void *pakPrompt_timerCancelpendingoperation(s32 *channel) {
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

static __inline__ void *menuPrompt_timerCancelpendingoperation(MenuPakBeginProfileLoad *menu) {
    s32 channel;
    void *prompt;
        prompt = 0;
        if (g_pakSaveMenuActiveDe) {
            if (g_pakProfileLoadMode_de) {
                channel = menu->slot->controllerPort;
                prompt = pakPrompt_timerCancelpendingoperation(&channel);
            }
        } else if (g_pakProfileLoadActive) {
            prompt = g_controllerPakNotReadyDialogResource;
            if (g_pakProfileLoadMode_de) prompt = g_pakStatusPromptAlternate;
        }
    return prompt;
}

/* Finds the first available controller slot and caches its index. */


/* Dialog resources are opaque ROM addresses. The list-builder ABI carries
 * player, slot, and optional formatting data as three raw 32-bit words. */
s32 Timer_CancelPendingOperation(void *menuOwner, MenuPakBeginProfileLoad *menu) {
    s32 channel;
    void *prompt;
    void *owner;
    Player *player;
    PakMenuSlot *slot;
    switch (g_frontendResourceLoadStage) {
    case 4: pakShow_timerCancelpendingoperation(menu); return 1;
    case 3: pakShow_timerCancelpendingoperation(menu); return 1;
    case 0: pakShow_timerCancelpendingoperation(menu); return 1;
    case 1:
    case 2:
        g_pakMenuPromptAccepted = 1;
        g_pakCancelStateWord = 0;
        if (g_pakUseScannedChannel) {
            g_pakRecheckRequested = 1;
            return 1;
        }
        prompt = menuPrompt_timerCancelpendingoperation(menu);
        if (!prompt) prompt = menu->prompt;
        if (menu->player) owner = (char *)&((GameplayCamera *)menu->player->camera)->messageList;
        else owner = &g_playerViewRenderContext.dialogOwner;
        Menu_OpenDialog(owner, prompt, (s32)menu->player, (s32)menu->slot, 0);
        return 1;
    default: return 1;
    }
    Menu_OpenDialog(owner, prompt, (s32)player, (s32)slot, 0);
    return 1;
}

/* Picks the first controller channel whose pak is available, probing up to four channels from channel 0;
   stores -1 when none is, and does nothing when a channel is already selected. */
void Timer_SelectAvailableChannel(void) {
    s32 channel;
    s32 attempts;
    s32 unavailable;
    if (g_introSelectedItem == -1) {
        channel = 0;
        attempts = 0;
    unavailable = -2;
        do {
            Note_ProbeStatus(channel);
            if (Note_GetStatus(channel) != unavailable) {
                break;
            }
            channel += 1;
            if (channel >= 4) {
                channel = 0;
            }
            attempts += 1;
        } while (attempts < 4);
        if (attempts == 4) {
            channel = -1;
        }
        g_introSelectedItem = channel;
    }
}

/* Returns whether g_introSelectedItem holds anything other than -1. */
s32 Timer_HasSelectedChannel(void) {
    return g_introSelectedItem != -1;
}

void Timer_ClearTimerFlag(void) {
    g_pakPlayerMessagePending = 0;
}

#if defined(VERSION_US)
const unsigned int k_TimerCancelpendingoperationEncodedWords[1] = {
    0x00000000,
};
#endif

#if defined(VERSION_EU)
const unsigned int k_timerCancelPendingOperationPad[1] = {
    0x00000000,
};
#endif

#if defined(VERSION_DE) || defined(VERSION_US)
#if defined(VERSION_DE)
unsigned int k_InitialZeroWords[1] = {
    0x00000000,
};
#endif
#endif

#if !(defined(VERSION_DE) || defined(VERSION_EU))
/* Keep the original state dispatch and shared exit ordering. */
s32 Frontend_SelectPakActionLabel(struct PakActionLabelView *field) {
    u32 state = g_frontendResourceLoadStage;

    if (state >= 5) {
        goto state_other;
    }
    switch (state) {
        case 0: goto state_other;
        case 1: goto state_alternate;
        case 2: goto state_alternate;
        case 3: goto state_three;
        case 4: goto state_four;
    }
state_other:
    field->text = s_nodeDefaultFieldText;
    goto done;
state_three:
    field->text = s_nodeDefaultFieldText;
    goto done;
state_four:
    field->text = s_nodeDefaultFieldText;
    goto done;
state_alternate:
    field->text = s_nodeAlternateFieldText;
done:
    return 0;
}
#endif
#if defined(VERSION_EU_X)
unsigned int k_FrontendCreateprofileresetscreeneuropeanEncodedWords[1] = {
    0x0043D414,
};
#endif
#if defined(VERSION_EU)
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)

s32 Timer_MatchesGameIdentity(char *code, char *name) {
    Shared_Game *settings;
    if (XPlus_StringLength(name) == 4 && XPlus_StringLength(code) == 2) {
        settings = &g_gameSettings;
        if (XPlus_CompareStrings(name, g_pakLegacySnapshotGameNames[settings->language]) == 0 &&
            XPlus_CompareStrings(code, g_pakCompanyCodes[settings->language]) == 0) {
            return 1;
        }
    }
    return 0;
}
#endif

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
/* Reports whether the two-character code code and the four-character name name are the pair g_pakCompanyCodeFixed and g_pakLegacySnapshotGameNameFixed, measuring them with XPlus_StringLength and comparing them with XPlus_CompareStrings; returns one on a match and zero otherwise. */
s32 Timer_MatchesGameIdentity(char *code, char *name) {
    if (XPlus_StringLength(name) == 4 && XPlus_StringLength(code) == 2 &&
        XPlus_CompareStrings(name, g_pakLegacySnapshotGameNameFixed) == 0 && XPlus_CompareStrings(code, g_pakCompanyCodeFixed) == 0) {
        return 1;
    }
    return 0;
}
#endif

/* Releases the two active resources and clears their associated state. */

/* Saves the settings the object in an owner holds into the block g_pakControllerRecord: the
   flag byte, the four halfwords, the three bytes that follow the flag (cleared) and the trailing eight-byte block. */
char *Timer_GetSaveBlockByteCount(s32 block) {
    if (block == 0) {
        return g_worldSnapshotNoteBytes + sizeof(SaveSnapshot);
    }
    return (char *) (block << 8);
}

void Timer_SetSaveTrailerValue(s32 offset, s32 value) {
    ((struct PlayerPakTimerView *) (g_worldSnapshotNoteBytes + offset))->trailerValue = value;
}

/* Returns the last word of a self-sized block: the first word holds the block's byte length and
   the result is the word just before that many bytes from the start. */
s32 Timer_GetSaveTrailerValue(s32 *block) {
    return ((s32 *) (block[0] + (s32) block))[-1];
}

void Timer_AllocateSaveBlock(void ***handle, void **data, s32 units) {
    void **block;
    void *first;

    if (*handle != 0) {
        Cache_DrainAndCompactResources(0);
        Cache_ReleaseResource(0, *handle);
    }
    if (units != 0) {
        units <<= 8;
    } else {
        units = (s32)(g_worldSnapshotNoteBytes + sizeof(SaveSnapshot));
    }
    block = Cache_AllocateResource(0, units, 51, g_pakSingleSaveBlockName);
    *handle = block;
    first = *block;
    *data = first;
    XPlus_FillMemory(first, 0, units);
}

void Timer_ReleaseSaveBlocks(void) {
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
}

void Timer_CapturePlayerProfile(struct PlayerSavedProfileOwner *owner) {
    struct PakStatusProfile *settings = owner->settings;
    s32 i;

    g_pakControllerRecord.flag = settings->flags;
    g_pakControllerRecord.values[0] = settings->words[0];
    g_pakControllerRecord.values[1] = settings->words[1];
    g_pakControllerRecord.values[2] = settings->words[2];
    g_pakControllerRecord.values[3] = settings->words[3];
    g_pakControllerRecord.pad[0] = 0;
    g_pakControllerRecord.pad[1] = 0;
    g_pakControllerRecord.pad[2] = 0;
    for (i = 0; i < 8; i++) {
        g_pakControllerRecord.bytes[i] = settings->name[i];
    }
}

/* Copies the saved controller settings block g_pakControllerRecord into the profile settings of an owner:
   the four halfwords, the flag byte and the eight name bytes. */
void Pak_ApplyStagedPlayerProfile(struct PlayerSavedProfileOwner *owner) {
    struct PakStatusProfile *settings = owner->settings;
    s32 i;

    settings->flags = g_pakControllerRecord.flag;
    settings->words[0] = g_pakControllerRecord.values[0];
    settings->words[1] = g_pakControllerRecord.values[1];
    settings->words[2] = g_pakControllerRecord.values[2];
    settings->words[3] = g_pakControllerRecord.values[3];
    for (i = 0; i < 8; i++) {
        settings->name[i] = g_pakControllerRecord.bytes[i];
    }
}

void Pak_RestoreSavedSession(Player *player) {
    Shared_World *world = &g_world;
    s32 i;
    u8 *from, *to;
    u8 saved = g_frontendSavedVideoModeIndex[0];
    *(Copy70 *)&player->state = g_controllerPakSnapshotPayload->save.player;
    *(Copy584 *)&g_gameSettings = g_controllerPakSnapshotPayload->save.world;
    g_gameSettings.counters.m_GameTimeFifteenth = g_controllerPakSnapshotPayload->save.view[0];
    g_gameSettings.counters.m_GameTimeSeconds = g_controllerPakSnapshotPayload->save.view[1];
    g_gameSettings.counters.m_GameTimeMinutes = g_controllerPakSnapshotPayload->save.view[2];
    g_gameSettings.counters.m_GameTimeHours = g_controllerPakSnapshotPayload->save.view[3];
    g_persistedOptionUnlockFlags[0] = ((Copy584 *)&g_gameSettings)->words[1];
    g_gameSettings.resolution = saved;
    from = g_controllerPakSnapshotPayload->save.name;
    to = g_worldSnapshotNoteData;
    for (i = 0; i < world->noteCount; i++) *to++ = *from++;
}

/* Returns g_introSelectedItem when g_pakUseScannedChannel is set, otherwise the pak menu's channel from the record's owner object. */
s32 Pak_GetMenuChannel(struct Shared_PakMenu *record) {
    if (g_pakUseScannedChannel != 0) {
        return g_introSelectedItem;
    }
    return record->owner->controllerPort;
}

/* Latches g_pakMenuPromptAccepted to one when the record's team value (g_introSelectedItem when g_pakUseScannedChannel is set, otherwise the pak menu's channel from the record's owner object) is not -1 and both Control_PeekPakChange_Pak and Snapshot_CheckStatusPrompt accept it, then returns g_pakMenuPromptAccepted. */
static inline s32 Pak_GetMenuChannel_timerCheckmenupakchange(struct Shared_PakMenu *record) {
    if (g_pakUseScannedChannel != 0) {
        return g_introSelectedItem;
    }
    return record->owner->controllerPort;
}

s32 Timer_CheckMenuPakChange(struct Shared_PakMenu *record) {
    if (g_pakMenuPromptAccepted == 0) {
        if (Pak_GetMenuChannel_timerCheckmenupakchange(record) != -1) {
            if (Control_PeekPakChange(Pak_GetMenuChannel_timerCheckmenupakchange(record)) != 0) {
                if (Snapshot_CheckStatusPrompt(record, Pak_GetMenuChannel_timerCheckmenupakchange(record), 0) != 0) {
                    g_pakMenuPromptAccepted = 1;
                }
            }
        }
    }
    return g_pakMenuPromptAccepted;
}

/* Latches g_pakMenuPromptAccepted to one when the record's team value is not -1 and both Control_PeekPakChange_Pak and Snapshot_CheckStatusPrompt accept it, then returns g_pakMenuPromptAccepted. */
static inline s32 Pak_GetMenuChannel_timerGetprompttext(struct Shared_PakMenu *record) {
    if (g_pakUseScannedChannel != 0) {
        return g_introSelectedItem;
    }
    return record->owner->controllerPort;
}

/* Latches g_pakRequestLatched and g_pakStartButtonLatched to one the first time bit 12 of a field of the
   object at 0x20 of a record is seen set, and returns g_pakRequestLatched. */

/* Finds the next available controller slot with wraparound. */

s32 Timer_CheckChangedMenuChannel(struct Shared_PakMenu *record) {
    if (g_pakMenuPromptAccepted == 0) {
        if (Pak_GetMenuChannel_timerGetprompttext(record) != -1) {
            if (Control_PeekPakChange(Pak_GetMenuChannel_timerGetprompttext(record)) != 0) {
                if (Snapshot_CheckStatusPrompt(record, Pak_GetMenuChannel_timerGetprompttext(record), 0) != 0) {
                    g_pakMenuPromptAccepted = 1;
                }
            }
        }
    }
    return g_pakMenuPromptAccepted;
}

s32 Timer_LatchControllerRequest(struct PakControllerRequestView *record) {
    if ((record->inner->buttons & 0x1000) && g_pakStartButtonLatched == 0) {
        g_pakRequestLatched = 1;
        g_pakStartButtonLatched = 1;
    }
    return g_pakRequestLatched;
}

s32 Timer_UpdateManagerStatus(void *menu) {
    if (g_pakRequestLatched == 0) {
        SetN64_CommitSessionInputs(&g_gameSession);
        Control_TrackControllerPakChanges();
        if (g_pakRequestLatched == 0) {
            if (g_pakUsable != 0) {
                g_pakRecheckRequested = 1;
            }
            g_pakScanActive = 0;
            g_pakMenuPromptAccepted = 1;
        }
    }
    if (g_pakMenuPromptAccepted == 0) {
        if ((g_introSelectedItem != -1) && (Control_PeekPakChange(g_introSelectedItem) != 0) && (Snapshot_CheckStatusPrompt(menu, g_introSelectedItem, 0) != 0)) {
            g_pakScanActive = 0;
            g_pakMenuPromptAccepted = 1;
        }
    }
    return g_pakMenuPromptAccepted;
}

s32 Timer_GetChannelAndResult(struct PakChannelResultView *record, s32 *out) {
    s32 value;
    s32 result;

    if (g_pakUseScannedChannel != 0) {
        value = g_introSelectedItem;
        result = 0;
    } else {
        value = record->inner->controllerPort;
        result = record->result;
    }
    *out = value;
    return result;
}

void Timer_ProbeMenuChannel(struct Shared_PakMenu *record) {
    s32 value;

    if (g_pakUseScannedChannel != 0) {
        value = g_introSelectedItem;
    } else {
        value = record->owner->controllerPort;
    }
    Note_ProbeStatus(value);
}

void Timer_ReturnToWorldMenu(void *owner, void *object) {
    Control_DisableControllerPak(object);
    Scene_SetSelection(&g_world, g_world.selectionValues[3], 2);
}

s32 Timer_FindNoteByGameName(void *callerContext, void *rightString, s32 index, s32 *noteIndexOut) {
    char game_name[16];
    s32 gameRef;
    s32 noteIndex;
    for(noteIndex=0;noteIndex<16;noteIndex++) {
        Note_GetNoteGameName(index,noteIndex,&gameRef);
        Note_DecodeNoteText(gameRef,&game_name,16);
        if(XPlus_CompareStrings(&game_name,rightString)==0) {
            if(noteIndexOut) *noteIndexOut=noteIndex;
            return 1;
        }
    }
    return 0;
}

char *Timer_GetPromptByKind(int promptOwner, int kind) {
    switch (kind) {
    case 0:
    default:
        return g_pakControllerPortPrompts[0];
    case 1:
        return g_pakControllerPortPrompts[1];
    case 2:
        return g_pakControllerPortPrompts[2];
    case 3:
        return g_pakControllerPortPrompts[3];
    }
}

static inline void Pak_GetPromptChannel_timerGetprompttext(struct Shared_PakMenu *menu, s32 *channel) {
    if (g_pakUseScannedChannel != 0) {
        *channel = g_introSelectedItem;
    } else {
        *channel = menu->owner->controllerPort;
    }
}

static inline char *Pak_GetChannelPrompt_timerGetprompttext(s32 channel) {
    char *prompt;
    switch (channel) {
    case 0:
    default:
        prompt = g_pakControllerPortPrompts[0];
        break;
    case 1:
        prompt = g_pakControllerPortPrompts[1];
        break;
    case 2:
        prompt = g_pakControllerPortPrompts[2];
        break;
    case 3:
        prompt = g_pakControllerPortPrompts[3];
        break;
    }
    return prompt;
}

char *Timer_GetPromptText(struct Shared_PakMenu *menu) {
    s32 channel;
    char *text;

    text = 0;
    if (g_pakSaveMenuActiveDe != 0) {
        if (g_pakProfileLoadMode_de == 0) {
            return text;
        }
        Pak_GetPromptChannel_timerGetprompttext(menu, &channel);
        text = Pak_GetChannelPrompt_timerGetprompttext(channel);
    } else if (g_pakProfileLoadActive != 0) {
        text = g_controllerPakNotReadyDialogResource;
        if (g_pakProfileLoadMode_de != 0) {
            text = g_pakStatusPromptAlternate;
        }
    } else if (g_pakUseScannedChannel != 0) {
        text = g_pakDialogPromptScannedChannel;
    }
    return text;
}

s32 Timer_FindNextAvailableChannel(s32 currentChannel) {
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

/* The EU builds compile a different original body for Timer_UpdateManagerChannelLabel; each version keeps its own. */
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
/* Shows g_pakSaveMenuProfileChannelLabels in a field when both g_pakProfileLoadMode_de and g_pakSaveMenuActiveDe are set, g_pakSaveMenuSnapshotChannelLabels when only g_pakSaveMenuActiveDe is, and otherwise, when g_pakUseScannedChannel is set, points the field at g_pakScannedChannelNumberLabels and formats g_introSelectedItem plus one into it with g_pakPromptTextDigitFormat one byte before the length Menu_CountLineChars reports, returning zero.
   */
s32 Timer_UpdateManagerChannelLabel(struct Field *field) {
    char *text;
    s32 value;

    if (g_pakProfileLoadMode_de != 0 && g_pakSaveMenuActiveDe != 0) {
        field->text = g_pakSaveMenuProfileChannelLabels;
    } else if (g_pakProfileLoadMode_de == 0 && g_pakSaveMenuActiveDe != 0) {
        field->text = g_pakSaveMenuSnapshotChannelLabels;
    } else if (g_pakUseScannedChannel != 0) {
        value = g_introSelectedItem;
        field->text = g_pakScannedChannelNumberLabels;
        text = g_pakScannedChannelNumberLabels[0];
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 1), g_pakChannelDigitFormat, value + 1);
    }
    return 0;
}

#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
/* Points an option field at its text: when g_pakSaveMenuActiveDe is set, g_pakSaveMenuProfileChannelLabels if g_pakProfileLoadMode_de is set and g_pakSaveMenuSnapshotChannelLabels if not; otherwise, when g_pakUseScannedChannel is set, the table g_pakScannedChannelNumberLabelsByLanguage, formatting its entry for the byte g_languageIndex_TimerGetprompttext with g_pakChannelNumberFormat and g_introSelectedItem plus one from one byte before the length Menu_CountLineChars reports; returns zero. */
s32 Timer_UpdateManagerChannelLabel(struct Field *field) {
    char **table;
    char *text;
    s32 value;

    if (g_pakProfileLoadMode_de != 0) {
        if (g_pakSaveMenuActiveDe != 0) {
            field->text = g_pakSaveMenuProfileChannelLabels;
            goto done;
        }
    } else if (g_pakSaveMenuActiveDe != 0) {
        field->text = g_pakSaveMenuSnapshotChannelLabels;
        goto done;
    }
    if (g_pakUseScannedChannel != 0) {
        do {
            table = g_pakScannedChannelNumberLabelsByLanguage;
        } while (0);
        field->text = table;
        value = g_introSelectedItem;
        text = table[g_languageIndex];
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 1), g_pakChannelNumberFormat, value + 1);
    }
done:
    return 0;
}

#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)

s32 Timer_UpdateOwnerChannelLabel(struct Field *field, Shared_PakMenu *pThis) {
    char *text;
    char **strings;
    s32 value;
    if (g_pakUseScannedChannel != 0) {
        field->text = g_unlockedLevelResultLabel;
    } else {
        value = pThis->owner->controllerPort;
        strings = g_pakOwnerChannelLabels;
        field->text = strings;
        text = strings[g_gameSettings.language];
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 1), g_pakChannelNumberFormat, value + 1);
    }
    return 0;
}
#endif

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
/* Uses the fixed option text while the mode flag is set. Otherwise formats
 * one more than the holder's signed option byte into the editable text,
 * one byte before the length returned by the item text helper. */
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
s32 Timer_UpdateOwnerChannelLabel(LayeredText *field, struct Shared_PakMenu *holder) {
    char *text;
    char **strings;
    s32 value;
    if (g_pakUseScannedChannel != 0) {
        field->text = g_unlockedLevelResultLabel;
    } else {
        value = holder->owner->controllerPort;
        strings = (char **)g_pakOwnerChannelLabelFixed;
        field->text = strings;
        text = *strings;
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 1),
                        g_pakChannelDigitFormat, value + 1);
    }
    return 0;
}

#endif
#endif

/* Selects a menu field's label table from the connection mode and the option index. */
s32 Timer_UpdateOperationChoiceLabel(struct Field *field, s16 *optionPtr) {
    s32 option;
    u32 rel;

    option = *optionPtr;
    rel = option - 3;
    if (g_pakProfileLoadActive != 0) {
        if (g_pakProfileLoadMode_de != 0) {
            field->text = g_pakProfileLoadProfileChoiceLabels;
        } else {
            field->text = g_pakProfileLoadSnapshotChoiceLabels;
        }
        goto done;
    }
    if (g_pakSaveMenuActiveDe != 0) {
        if (rel < 16) {
            field->text = g_pakSaveMenuNoteSlotChoiceLabels;
            return 0;
        }
        if (option == 21) {
            field->text = g_unlockedLevelResultLabel;
        } else if (g_pakProfileLoadMode_de != 0) {
            field->text = g_pakSaveMenuProfileChoiceLabels;
        } else {
            field->text = g_pakSaveMenuSnapshotChoiceLabels;
        }
        goto done;
    }
    if (g_pakUseScannedChannel != 0) {
        field->text = g_pakScannedChannelChoiceLabels;
    }
done:
    return 0;
}

s32 Timer_SetManagerHeading(struct MenuBuildEntry *record) {
    if (g_pakUseScannedChannel != 0) {
        record->resource = (s32)(g_pakScannedChannelManagerHeading);
    }
    return 0;
}

void Timer_EnableAlternatePrompt(void) {
    g_pakAlternateOptionEnabled = 1;
}

void Timer_DisableAlternatePrompt(void) {
    g_pakAlternateOptionEnabled = 0;
}

s32 Timer_UpdateAlternatePromptLabel(struct PakActionLabelView *field) {
    if (g_pakAlternateOptionEnabled != 0) {
        field->text = g_pakNoteLabelSlots;
    } else {
        field->text = g_pakAlternatePromptDefaultLabel;
    }
    return 0;
}

int Timer_UpdatePreviewDepthLabel(MenuBuildEntry *out) {
    switch (g_controllerPakSnapshotPayload->preview.depth) {
    case 8:
    default:
        out->resource = (s32)(&g_pakPreviewDifficultyEasyLabel);
        break;
    case 16:
        out->resource = (s32)(&g_pakPreviewDifficultyNormalLabel);
        break;
    case 32:
        out->resource = (s32)(&g_difficultyHardText);
        break;
    }
    return 0;
}

s32 Timer_FormatPreviewPageCount(struct Field *field) {
    s32 value = g_controllerPakSnapshotPayload->preview.value >> 8;
    char *text =
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        field->text[g_languageIndex];
#else
        *field->text;
#endif

    Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 3), g_pakPaddedCountFormat, value);
    return 0;
}

/* Formats a field of the structure g_controllerPakSnapshotPayload points to into a field's text
   (the current menu language's text in the EU builds) with the format string, two bytes before
   the length Menu_CountLineChars reports, and returns zero. */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#define PREVIEW_VALUE_FORMAT g_pakTimerPreviewValueFormat
#else
#define PREVIEW_VALUE_FORMAT g_pakPreviewValueFormat
#endif

s32 Timer_FormatPreviewValue(struct Field *field) {
    s32 value = g_controllerPakSnapshotPayload->previewText.value;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    char *text = field->text[g_languageIndex];
#else
    char *text = *field->text;
#endif

    Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 2), PREVIEW_VALUE_FORMAT, value);
    return 0;
}
#undef PREVIEW_VALUE_FORMAT

/* Stores 1 in g_pakProfileLoaded and 0 in g_pakUseDefaultPreviewLabels. */
s32 Timer_DispatchPreviewHandle(void) {

#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)
Menu_ClassifyResourceRange
#else
Pickup_ClassifyMenuCode
#endif
(g_controllerPakSnapshotPayload->preview.handle);
    return 0;
}

/* Formats the three position floats of the pak preview g_controllerPakSnapshotPayload points to,
   truncated to integers, into a field's text with the format g_pakFormatDottedTriple_TimerFormatpreviewdottedtriple, into the last nine characters of the field text (the
   length Menu_CountLineChars reports). Returns zero. */
s32 Timer_FormatPreviewDottedTriple(struct Field *field) {
    s32 x = g_controllerPakSnapshotPayload->preview.x;
    s32 y = g_controllerPakSnapshotPayload->preview.y;
    s32 z = g_controllerPakSnapshotPayload->preview.z;
    char *text =

#if defined(VERSION_EU) || defined(VERSION_EU_X)
        field->text[g_languageIndex];
#else
        *field->text;
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
    Defs_FormatThreeIntegers(text + (Menu_CountLineChars(field) - 9), g_pakDottedTripleFormat, z, y, x);
#else
    Defs_FormatThreeIntegers(text + (Menu_CountLineChars(field) - 9), g_pakFormatDottedTriple, z, y, x);
#endif
    return 0;
}

s32 Timer_UpdateAlternateActionLabel(struct PakActionLabelView *field) {
    if (g_pakAlternateOptionEnabled != 0) {
        field->text = g_pakAlternateActionLabel;
    } else {
        field->text = g_pakActionLabel;
    }
    return 0;
}

s32 Timer_OpenSelectedPrompt(void *owner, struct PakSelectedPromptView *record) {
    do {
        if (g_pakAlternateOptionEnabled != 0) {
            Menu_OpenDialog(&g_matchEndingTeamWheelClose, g_controllerPakReadyDialogResource, record->first, record->second, 0);
        } else {
            Menu_OpenDialog(&g_matchEndingTeamWheelClose, record->resource, record->first, record->second, 0);
        }
    } while (0);
    return 1;
}

void Timer_EnableProfilePreview(void) {
    g_pakProfileLoaded = 1;
    g_pakUseDefaultPreviewLabels = 0;
}

void Timer_ClearProfilePreview(void) {
    g_pakProfileLoaded = 0;
    g_pakUseDefaultPreviewLabels = 0;
}

void Timer_DisablePreviewSelection(struct PakPreviewSelectionView *record) {
    record->target->first &= ~0x01800000;
    g_pakProfileLoaded = 0;
    g_pakUseDefaultPreviewLabels = 1;
    record->target->second &= ~0x01800000;
}

s32 Timer_UpdatePreviewKindLabel(struct PakActionLabelView *field) {
    if (g_pakProfileLoaded != 0) {
        field->text = g_pakPreviewKindLabelProfile;
    } else if (g_pakUseDefaultPreviewLabels != 0) {
        field->text = g_pakPreviewKindLabelDefault;
    } else {
        field->text = g_pakPreviewKindLabelSelected;
    }
    return 0;
}
