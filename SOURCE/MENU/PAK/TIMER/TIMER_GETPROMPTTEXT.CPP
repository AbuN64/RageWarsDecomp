#include "COMMON/RECORDRECATCV1.H"
#include "RESMGR/resmgr_string_memory.H"
#include "COMMON/LONE/g_pakDialogPromptScannedChannel.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "MENU/PAK_PREVIEW_VIEWS.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/WORLD.H"
#include "COMMON/PAKQUEUESTATE.H"
#include <ultra64.h>
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/GLOBALS.H"
#include "COMMON/MENURECAT24.H"
#include "MENU/PAK/TIMER_GETPROMPTTEXT.H"
#include "ENGINE/DEFS.H"
#include "MENU/ITEMS/SCENE/SCENE_UPDATEPENDINGOBJECTS.H"
#include "MENU/MENU_CREATEMENUFROMPARAMETERS.H"
#include "NOTE/NOTE_READNOTEDATA.H"
#include "NOTE/PAK_ALLOCATERENDERBUFFERS.H"
#include "SNAPSHOT/SNAPSHOT_CHECKSTATUSPROMPT.H"

/* Latches g_pakMenuPromptAccepted to one when the record's team value is not -1 and both Control_PeekPakChange_Pak and Snapshot_CheckStatusPrompt accept it, then returns g_pakMenuPromptAccepted. Adapted from Timer_CheckMenuPakChange with nothing changed (identical code). */






extern s32 g_pakUseScannedChannel;



static inline s32 Pak_GetMenuChannel(struct Shared_PakMenu *record) {
    if (g_pakUseScannedChannel != 0) {
        return g_introSelectedItem;
    }
    return record->owner->controllerPort;
}


/* Latches g_pakRequestLatched and g_pakStartButtonLatched to one the first time bit 12 of the word at offset 0xB0 of the
   object at 0x20 of a record is seen set, and returns g_pakRequestLatched. */








#include "COMMON/GAME_SESSION.H"

extern void SetN64_CommitSessionInputs(void *unused);


/* Calls Control_DisableControllerPakDe on its second argument, then Scene_SetSelection_MenuInitializeoptionsscene on g_world_AchieveUpdateresultsscreen with g_worldSelectionValueThree
   and 2. */


extern void Control_DisableControllerPak(int controllerPort);


/* Searches the sixteen controller-pak notes for the requested name and returns the matching index when requested. */



/* Returns the data table for a kind: kinds 1, 2 and 3 have their own, kind 0 and anything else use the
   first. */




/* Picks the pak menu prompt text: in pak mode, when a prompt is due, the text for the channel (g_introSelectedItem when g_pakUseScannedChannel is set, else the widget's channel) from four channel texts; otherwise one of two texts in the other mode, or a third text when g_pakUseScannedChannel alone is set, and 0 when none applies. */











/* Finds the next available controller slot with wraparound. */

 /* extern */

s32 Timer_CheckChangedMenuChannel(struct Shared_PakMenu *record) {
    if (g_pakMenuPromptAccepted == 0) {
        if (Pak_GetMenuChannel(record) != -1) {
            if (Control_PeekPakChange(Pak_GetMenuChannel(record)) != 0) {
                if (Snapshot_CheckStatusPrompt(record, Pak_GetMenuChannel(record), 0) != 0) {
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

void Timer_ReturnToWorldMenu(void *unused, void *object) {
    Control_DisableControllerPak(object);
    Scene_SetSelection(&g_world, g_world.selectionValues[3], 2);
}

s32 Timer_FindNoteByGameName(void *unused, void *rightString, s32 index, s32 *noteIndexOut) {
    char game_name[16];
    s32 game_ref;
    s32 note_index;
    for(note_index=0;note_index<16;note_index++) {
        Note_GetNoteGameName(index,note_index,&game_ref);
        Note_DecodeNoteText(game_ref,&game_name,16);
        if(XPlus_CompareStrings(&game_name,rightString)==0) {
            if(noteIndexOut) *noteIndexOut=note_index;
            return 1;
        }
    }
    return 0;
}

char *Timer_GetPromptByKind(int unused, int kind) {
    switch (kind) {
    case 0:
    default:
        return g_pakPortZeroPrompt_de;
    case 1:
        return g_pakPortOnePrompt_de;
    case 2:
        return g_pakPortTwoPrompt_de;
    case 3:
        return g_pakPortThreePrompt_de;
    }
}

static inline void Pak_GetPromptChannel(struct Shared_PakMenu *menu, s32 *channel) {
    if (g_pakUseScannedChannel != 0) {
        *channel = g_introSelectedItem;
    } else {
        *channel = menu->owner->controllerPort;
    }
}

static inline char *Pak_GetChannelPrompt(s32 channel) {
    char *prompt;
    switch (channel) {
    case 0:
    default:
        prompt = g_pakPortZeroPrompt_de;
        break;
    case 1:
        prompt = g_pakPortOnePrompt_de;
        break;
    case 2:
        prompt = g_pakPortTwoPrompt_de;
        break;
    case 3:
        prompt = g_pakPortThreePrompt_de;
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
        Pak_GetPromptChannel(menu, &channel);
        text = Pak_GetChannelPrompt(channel);
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

 /* extern */
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
/* Shows g_pakSaveMenuProfileChannelLabels in a field when both g_pakProfileLoadMode_de and g_pakSaveMenuActiveDe are set, g_pakSaveMenuSnapshotChannelLabels when only g_pakSaveMenuActiveDe is, and otherwise, when g_pakUseScannedChannel is set, points the field at g_pakScannedChannelNumberLabels and formats g_introSelectedItem plus one into it with g_pakFormatInt1_TimerGetprompttext one byte before the length Menu_CountLineChars reports, returning zero.
   Adapted from Items_FormatPackedGameOption with the three flag tests, the texts, the format, the offset and the incremented value changed. */




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
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 1), g_pakFormatInt1, value + 1);
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
