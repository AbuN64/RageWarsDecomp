#include "include_asm.h"
#include "RESMGR/resmgr_string_memory.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/MENURECAT24.H"
#include "MENU/PAK_PROFILE_PROMPT_VIEWS.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/PAK_MENU.H"
#include "TYPES.H"
#include "MENU/PAK/SNAPSHOT_HANDLEMENUACTION.H"
#include "ENGINE/DEFS.H"

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "COMMON/SHARED_GAMESLOT.H"
extern char *g_pakDefaultNoteNamesLocalized[];
extern char *g_pakEmptyNoteNamesLocalized_eu[];
extern u8 *g_pakSpaceLabelScannedLocalized_eu[];
extern char *g_pakSnapshotGameNames[];
extern char g_pakOverwriteNoteDialogResource_eu[];
#define ENTRY_TEXT(e) ((e)->text[g_languageIndex])
#define PAK_HEADER_376C g_pakSpaceLabelScannedLocalized_eu
#else
#define ENTRY_TEXT(e) (*(e)->text)
#define PAK_HEADER_376C (&g_pakSpaceLabelScannedText)
#endif
extern s32 g_pakUseScannedChannel;

extern char *g_pakDefaultNoteNameFixed;

extern char *g_pakEmptyNoteNameFixed;

extern s32 Note_ReadNoteInfo(s32 ch, s32 index, s32 *exists, u8 *name, u8 *ext, s32 *size,
                         char *companyCode, char *gameCode);

extern s32 Note_ContainsInvalidNameByte(u8 *name, s32 size);

extern u8 *XPlus_CopyString(u8 *destination, u8 *source);

/* Native resident constant storage; absolute access symbols retain their addresses. */
#if defined(VERSION_US)

#elif defined(VERSION_US_REV1)

#elif defined(VERSION_DE)

#endif

extern s32 g_worldSnapshotNoteBytes;

extern Digits k_pakDigitsInitial;

extern u8 *g_pakSpaceLabelText;

extern u8 *g_pakSpaceLabelScannedText;

extern char *g_unlockedLevelResultLabel[];

extern s32 Note_GetFreePages(s32 ch, s32 *freeSpace);

extern u32 Note_BytesToPakPages(u32 size);

static inline int space_required(int size) {size += 1552; return Note_BytesToPakPages(size);}

extern char g_matchEndingTeamWheelClose[];
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#define PAK_OVERWRITE_NOTE_DIALOG g_pakOverwriteNoteDialogResource_eu
#else
#define PAK_OVERWRITE_NOTE_DIALOG g_pakOverwriteNoteDialogResource
#endif

extern char g_pakOverwriteNoteDialogResource[];

extern s32 Snapshot_CheckStatusPrompt(Shared_PakMenu *menu, s32 ch, s32 mode);

extern s32 Snapshot_SaveControllerRecord(s32 unused, Shared_PakMenu *menu, s32 unusedEvent);

extern void Snapshot_SaveSnapshotAndClose(s32 unusedEventSource, Shared_PakMenu *menu, s32 unusedEventPayload);

extern void Note_GetNoteGameName(s32 ch, s32 note, s32 *state);

extern void Note_DecodeNoteText(s32 state, char *name, s32 size);


extern void *Menu_OpenDialog(void *parent, struct Dialog *list, s32 player, s32 controller, s32 d);

extern void Note_ProbeStatus(s32 ch);

extern s32 Note_GetStatus(s32 ch);

static inline void pickChannel(Shared_PakMenu *menu, s32 *ch)
{
    if (g_pakUseScannedChannel != 0) {
        *ch = g_introSelectedItem;
    } else {
        *ch = menu->owner->controllerPort;
    }
}

static inline s32 findNote(s32 ch, s32 *found)
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
    Defs_FormatIntegerValue(dst, g_pakFormatInt3, size);
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
            if (g_pakProfileLoadMode_de) need=Note_BytesToPakPages(24); else need=space_required(g_worldSnapshotNoteBytes);
            text = ENTRY_TEXT(entry);
            Defs_FormatIntegerValue(digits.c, g_pakFormatInt3, freeSpace);
            text += 14;
            *text++ = digits.c[0];
            *text++ = digits.c[1];
            *text = digits.c[2];
            Defs_FormatIntegerValue(digits.c, g_pakFormatInt3, need);
            text += 15;
            *text++ = digits.c[0];
            *text = digits.c[1];
            text[1] = digits.c[2];
        }
    } else if (g_pakUseScannedChannel != 0) {
        header = PAK_HEADER_376C;
        goto fill;
    } else if (g_pakProfileLoadActive != 0) {
        header = &g_pakSpaceLabelText;
    fill:
        entry->text = header;
        result = Note_GetFreePages(ch, &freeSpace);
        need = Note_BytesToPakPages(g_worldSnapshotNoteBytes + 1552);
        text = ENTRY_TEXT(entry);
        if (result == 0) {
            text += 14;
            format = g_pakFormatInt3;
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

s32 Snapshot_HandleMenuAction(s32 unused, Shared_PakMenu *menu, s32 unusedEvent)
{
    s32 ch = 0;
    s32 use;
    s32 next;
    s32 tries;
    s32 hasNote;
    s32 c;

    if (g_pakSaveMenuActiveDe != 0) {
        pickChannel(menu, &ch);
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
            Snapshot_SaveControllerRecord(unused, menu, unusedEvent);
            return 1;
        }
    } else if (g_pakSaveMenuActiveDe != 0) {
        hasNote = findNote(use, &g_controllerPakOverwriteNoteIndex);
        if (hasNote != 0 && g_controllerPakOverwriteNoteIndex >= 0 && g_controllerPakOverwriteNoteIndex < 16) {
            Menu_OpenDialog(g_matchEndingTeamWheelClose, PAK_OVERWRITE_NOTE_DIALOG, menu->player, menu->owner, g_pakAlternateReadyDialogResource);
            return 1;
        }
        Snapshot_SaveSnapshotAndClose(unused, menu, unusedEvent);
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
