#include "MENU/PAK_PROFILE_PROMPT_VIEWS.H"
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "include_asm.h"
#include "RESMGR/resmgr_string_memory.H"
#include "MENU/PAK/SAVE_SNAPSHOT.H"
#include "COMMON/PAK_MENU.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/RECORDRECAT1C.H"
#include "COMMON/MENURECAT24.H"
#include "TYPES.H"
#include <ultra64.h>

#if defined(VERSION_EU)
#define Snapshot_CheckControllerPak Snapshot_CheckEuropeanSaveAvailability
#endif
#if defined(VERSION_EU_X)
#define Snapshot_CheckControllerPak Snapshot_CheckLocalizedSaveAvailability
#endif
/* Selects a usable Controller Pak, checks its notes and free space, and opens the appropriate prompt. */
s32 Control_AnyControllerConnected(void);
void SetN64_CommitSessionInputs(void *);
void Note_ProbeStatus(s32);
s32 Note_GetStatus(s32);
s32 Note_CountFreeNotes(s32, s32 *);
int Note_GetFreePages(int, int *);
s32 Note_GetNoteGameName(s32, s32, char **);
s32 Note_NeedsIdRepair(s32);
void Note_DecodeNoteText(u8 *, u8 *, s32);
u32 Note_BytesToPakPages(u32);
s32 Snapshot_EvaluateSaveChannel(void *, s32, s32 *, s32 *);
void *Menu_OpenDialog(void *parent, struct Dialog *list, s32 player, s32 controller, s32 d);
extern s32 g_pakDialogPromptScannedChannel;
extern s32 g_pakDialogIdRepair_SnapshotCheckeuropeansaveavailability;
/* Per-version dialog scripts opened by Snapshot_CheckControllerPak. */
#if defined(VERSION_DE)
extern s32 g_pakSnapshotNoPakPromptDe, g_pakSnapshotNoControllerPromptDe, g_pakSnapshotCapacityPromptDe, g_pakSnapshotLowSpacePromptDe;
#define PAK_DIALOG_NO_CONTROLLER g_pakSnapshotNoControllerPromptDe
#define PAK_DIALOG_NO_PAK g_pakSnapshotNoPakPromptDe
#define PAK_DIALOG_LOW_SPACE g_pakSnapshotLowSpacePromptDe
#define PAK_DIALOG_FULL g_pakSnapshotCapacityPromptDe
#elif defined(VERSION_US)
extern s32 g_pakSnapshotNoPakPromptUs, g_pakSnapshotNoControllerPromptUs, g_pakSnapshotCapacityPromptUsRev1, g_pakSnapshotLowSpacePromptUs;
#define PAK_DIALOG_NO_CONTROLLER g_pakSnapshotNoControllerPromptUs
#define PAK_DIALOG_NO_PAK g_pakSnapshotNoPakPromptUs
#define PAK_DIALOG_LOW_SPACE g_pakSnapshotLowSpacePromptUs
#define PAK_DIALOG_FULL g_pakSnapshotCapacityPromptUsRev1
#elif defined(VERSION_EU)
extern s32 g_pakSnapshotNoPakPromptEu, g_pakSnapshotNoControllerPromptEu, g_pakSnapshotCapacityPromptEu, g_pakSnapshotLowSpacePromptEu;
#define PAK_DIALOG_NO_CONTROLLER g_pakSnapshotNoControllerPromptEu
#define PAK_DIALOG_NO_PAK g_pakSnapshotNoPakPromptEu
#define PAK_DIALOG_LOW_SPACE g_pakSnapshotLowSpacePromptEu
#define PAK_DIALOG_FULL g_pakSnapshotCapacityPromptEu
#elif defined(VERSION_EU_X)
extern s32 D_0044FE74_eu_x, D_0044FEBC_eu_x, g_pakSnapshotCapacityPromptEu, D_004502D0_eu_x;
#define PAK_DIALOG_NO_CONTROLLER D_0044FEBC_eu_x
#define PAK_DIALOG_NO_PAK D_0044FE74_eu_x
#define PAK_DIALOG_LOW_SPACE D_004502D0_eu_x
#define PAK_DIALOG_FULL g_pakSnapshotCapacityPromptEu
#else
#define PAK_DIALOG_NO_CONTROLLER g_pakSnapshotNoControllerPromptUsRev1
#define PAK_DIALOG_NO_PAK g_pakSnapshotNoPakPromptUsRev1
#define PAK_DIALOG_LOW_SPACE g_pakSnapshotLowSpacePromptUsRev1
#define PAK_DIALOG_FULL g_pakSnapshotCapacityPromptEuX
#endif
/* The game's two Controller Pak note names (PAL: per language). */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
extern char *g_pakProfileGameNames[];
extern char *g_pakSnapshotGameNames[];
#define PAK_NOTE_NAME_1 g_pakProfileGameNames[g_languageIndex]
#define PAK_NOTE_NAME_2 g_pakSnapshotGameNames[g_languageIndex]
#else
#define PAK_NOTE_NAME_1 g_pakProfileGameNameFixed
#define PAK_NOTE_NAME_2 g_pakSnapshotGameNameFixed
#endif
extern s32 g_worldSnapshotNoteBytes;
#include "COMMON/GAME_SESSION.H"
extern s32 g_matchEndingTeamWheelClose;
extern s32 g_pakUseScannedChannel;
/* Timer_FindNextAvailableChannel's scan: from the channel after currentChannel (or 0), the first channel whose probe is not -2; -1 if none. */
static inline s32 Pak_ScanNextChannel(s32 currentChannel) {
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
static inline s32 Pak_HasNamedNote(char *name, s32 channel) {
    u8 text[16];
    char *note;
    s32 index;
    for (index = 0; index < 16; index++) {
        Note_GetNoteGameName(channel, index, &note);
        Note_DecodeNoteText((u8 *)note, text, 16);
        if (XPlus_CompareStrings(text, name) == 0) {
            return 1;
        }
    }
    return 0;
}
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
        Menu_OpenDialog(&g_matchEndingTeamWheelClose, &PAK_DIALOG_NO_CONTROLLER, (s32)menu->player, (s32) menu->slot, 0);
        g_pakStartButtonLatched = 1;
        g_pakScanActive = 0;
        return;
    }
    if (g_introSelectedItem == -1) {
        g_introSelectedItem = Pak_ScanNextChannel(-1);
        if (g_introSelectedItem == -1) {
            g_pakMenuPromptAccepted = 1;
            g_pakUsable = 0;
            Menu_OpenDialog(&g_matchEndingTeamWheelClose, &PAK_DIALOG_NO_PAK, (s32)menu->player, (s32) menu->slot, 0);
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
                Menu_OpenDialog(&g_matchEndingTeamWheelClose, &PAK_DIALOG_NO_PAK, (s32)menu->player, (s32) menu->slot, 0);
                g_pakScanActive = 0;
                g_pakStartButtonLatched = 1;
                return;
            }
            goto finish;
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
            g_introSelectedItem = Pak_ScanNextChannel(g_introSelectedItem);
        } while (++retries < 4);
        if (status == 0) {
            g_introSelectedItem = firstChannel;
            Note_ProbeStatus(firstChannel);
            if (Note_GetStatus(g_introSelectedItem) == -2) {
                g_pakMenuPromptAccepted = 1;
                g_pakUsable = 0;
                Menu_OpenDialog(&g_matchEndingTeamWheelClose, &PAK_DIALOG_NO_PAK, (s32)menu->player, (s32) menu->slot, 0);
                g_pakScanActive = 0;
                g_pakStartButtonLatched = 1;
                return;
            }
        }
        hasNote1 = Pak_HasNamedNote(PAK_NOTE_NAME_1, g_introSelectedItem);
        hasNote2 = Pak_HasNamedNote(PAK_NOTE_NAME_2, g_introSelectedItem);
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
                            Menu_OpenDialog(&g_matchEndingTeamWheelClose, &PAK_DIALOG_LOW_SPACE, (s32)menu->player, (s32) menu->slot, (intptr_t) &g_pakDialogPromptScannedChannel);
                        } else if (freeBytes < (s32)minBytes) {
                            g_pakMenuPromptAccepted = 1;
                            g_pakRequestLatched = 1;
                            Menu_OpenDialog(&g_matchEndingTeamWheelClose, &PAK_DIALOG_FULL, (s32)menu->player, (s32) menu->slot, (intptr_t) &g_pakDialogPromptScannedChannel);
                        }
                    } else {
                        g_pakMenuPromptAccepted = 1;
                        g_pakRequestLatched = 1;
                        Menu_OpenDialog(&g_matchEndingTeamWheelClose, &PAK_DIALOG_FULL, (s32)menu->player, (s32) menu->slot, (intptr_t) &g_pakDialogPromptScannedChannel);
                    }
                }
            }
        } else {
            goto finish;
        }
    }
    if (error != 0) {
        g_pakMenuPromptAccepted = 1;
        g_pakRequestLatched = 1;
        Menu_OpenDialog(&g_matchEndingTeamWheelClose, &g_pakDialogIdRepair_SnapshotCheckeuropeansaveavailability, (s32)menu->player, (s32) menu->slot, (intptr_t) &g_pakDialogPromptScannedChannel);
    }
finish:
    if (g_pakMenuPromptAccepted == 0) {
        Snapshot_MarkSaveNotes(menu);
    }
    g_pakScanActive = 0;
    g_pakStartButtonLatched = 1;
}

#include "TYPES.H"
extern s32 g_pakUseScannedChannel, g_pakPlayerMessagePending;
extern s32 g_matchEndingTeamWheelClose, g_pakDialogIdRepair_SnapshotCheckeuropeansaveavailability, g_worldSnapshotNoteBytes;
extern char g_pakDialogDamagedPak[];
extern void Note_ProbeStatus(s32 ch);
extern s32 Note_GetStatus(s32 ch);
extern s32 Note_IsChannelReady(s32 ch);
extern s32 Note_NeedsIdRepair(s32 ch);
extern void Snapshot_CreateSaveSnapshot(ActorOwnerView *);
extern u32 Note_Crc32(u8 *data, u32 byteCount, u32 initialCrc);
void *Menu_OpenDialog(void *parent, struct Dialog *list, s32 player, s32 controller, s32 d);
/* The channel the pak menu works on: the scanned channel g_introSelectedItem while g_pakUseScannedChannel is set, else the slot's. */
static __inline__ void pakGetChannel(Shared_PakMenu *menu, s32 *channel) {
    if (g_pakUseScannedChannel != 0) {
        *channel = g_introSelectedItem;
    } else {
        *channel = menu->owner->controllerPort;
    }
}
/* Timer_SetSaveTrailerValue's body: store the snapshot checksum after the g_worldSnapshotNoteBytes bytes of note data. */
static __inline__ void pakSetChecksum(s32 offset, s32 value) {
    ((struct PlayerPakTimerView *)(g_worldSnapshotNoteBytes + offset))->trailerValue = value;
}
/* Opens the pak menu for a snapshot save: unless a message is pending (g_pakPlayerMessagePending), probes the channel's
   Controller Pak; a ready pak gets the save snapshot with its checksum and the note list (Snapshot_MarkSaveNotes),
   otherwise the damaged-pak (g_pakDialogDamagedPak) or g_pakDialogIdRepair_SnapshotCheckeuropeansaveavailability prompt opens. Twin of Snapshot_BeginProfileSave. */
void Snapshot_BeginSnapshotSave(Shared_PakMenu *menu) {
    ActorOwnerView *owner = menu->player;
    ActorOwnerView *player;
    s32 channel;

    g_pakSaveMenuActiveDe = 1;
    g_pakNoteSelectProbesNote = 1;
    g_pakProfileLoadActive = 0;
    g_pakProfileLoadMode_de = 0;
    g_pakNoteTitleSelector = 0;
    g_pakMenuPromptAccepted = 0;
    g_pakUseScannedChannel = 0;
    pakGetChannel(menu, &channel);
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
        pakSetChecksum((s32)g_pakSaveSnapshot, Note_Crc32(g_pakSaveSnapshot, g_worldSnapshotNoteBytes + 1548, 11));
        Snapshot_MarkSaveNotes(menu);
        return;
    }
    g_pakMenuPromptAccepted = 1;
    if (Note_IsChannelReady(channel)) {
        Menu_OpenDialog((char *)&((GameplayCamera *)player->owner)->messageList, g_pakDialogDamagedPak, (s32)player, (s32)player->controller, 1);
    } else if (Note_NeedsIdRepair(channel)) {
        Menu_OpenDialog(&g_matchEndingTeamWheelClose, &g_pakDialogIdRepair_SnapshotCheckeuropeansaveavailability, (s32)player, (s32)player->controller, (s32)g_pakAlternateReadyDialogResource);
    }
}
