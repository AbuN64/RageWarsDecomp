#include "COMMON/GAMEPLAY_TRANSITION.H"
extern void Cache_ReleaseResource(s32, void *);
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "../../../../sdk/include/LIBC.H"
#include "include_asm.h"
#include "RESMGR/resmgr_string_memory.H"
#include "COMMON/LONE/g_pakDialogPromptScannedChannel.H"
#include "COMMON/LONE/g_pakDialogIdRepair_SnapshotCheckeuropeansaveavailability.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/PAK_MENU.H"
#include "COMMON/WORLD.H"
#include "MENU/PAK/SAVE_SNAPSHOT.H"
/* g_worldSnapshotNoteBytes is g_world_AchieveUpdateresultsscreen.noteCount (world + 0x44). The tail reads it as that member, which keeps cse from
 * folding its loads across the snapshot header stores; the two head reads stay plain scalar loads (MIXED). */
extern s32 g_worldSnapshotNoteBytes;
extern void *g_pakSnapshotResourceHandle;
extern const char g_pakSingleSaveBlockName[];
#include "COMMON/SHARED_GAMESLOT.H"
#include "MENU/PAK/MENU_CREATEMENUFROMTEMPLATE.H"
#include "NOTE/NOTE_READNOTEINFO.H"
#include "SNAPSHOT/SNAPSHOT_CHECKSTATUSPROMPT.H"
#include "UI/X_FILES/X_PLUS.H"
extern f32 g_matchRoundCounters[];
extern u8 g_worldSnapshotNoteData[];
extern void Cache_DrainAndCompactResources(s32);
extern void **Cache_AllocateResource(s32, s32, s32, char *);
extern void *XPlus_FillMemory(void *destination, int fillValue, u32 byteCount);

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
    g_pakSaveSnapshot->player = *(Copy70 *)(&((Shared_ActorView *)player)->state);
    g_pakSaveSnapshot->world = *(Copy584 *)&g_gameSettings;
    snapshot = g_pakSaveSnapshot;
    snapshot->view[0] = g_matchRoundCounters[0];
    snapshot->view[1] = g_matchRoundCounters[1];
    snapshot->view[2] = g_matchRoundCounters[2];
    snapshot->view[3] = g_matchRoundCounters[3];
    snapshot->size = snapshotSize;
    snapshot->dataSize = g_world.noteCount;
    Libc_CopyBytes(snapshot->name, g_worldSnapshotNoteData, g_world.noteCount);
}

#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern char *g_pakLegacySnapshotGameNames[];
extern char *g_pakCompanyCodes[];
extern char *g_pakProfileGameNames[];
extern char *g_pakSnapshotGameNames[];
#define PAK_CODE g_pakLegacySnapshotGameNames[g_languageIndex]
#define PAK_COMPANY g_pakCompanyCodes[g_languageIndex]
#define PAK_TITLE1 g_pakProfileGameNames[getSettings()->language]
#define PAK_TITLE2 g_pakSnapshotGameNames[getSettings()->language]
#else
#define PAK_CODE g_pakLegacySnapshotGameNameFixed
#define PAK_COMPANY g_pakCompanyCodeFixed
#define PAK_TITLE1 g_pakProfileGameNameFixed
#define PAK_TITLE2 g_pakSnapshotGameNameFixed
#endif
extern s32 g_introSelectedItem, g_pakNoteTitleSelector;
extern char *g_pakProfileGameNameFixed;
extern *g_pakSnapshotGameNameFixed;
extern unsigned char * g_pakCompanyCodeFixed;

extern s32 g_pakUseScannedChannel;

extern char *g_pakLegacySnapshotGameNameFixed;




/* Inlined into each title lookup: the loop pass merges the two address loads into one hoisted register,
 * which then outranks the loop-hoisted length constants 4 and 2 (a local pointer loses that race). */
static __inline__ Shared_Game *getSettings(void) {
    return &g_gameSettings;
}

void Snapshot_MarkSaveNotes(Shared_PakMenu *menu) {
    s32 ch;
    s32 i;
    s32 other;
    s32 result;
    s32 match;
    char *title;
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
                    title = PAK_TITLE1;
                    break;
                case 2:
                    if (XPlus_StringLength(code) == 4 && XPlus_StringLength(company) == 2 &&
                        XPlus_CompareStrings(code, PAK_CODE) == 0 && XPlus_CompareStrings(company, PAK_COMPANY) == 0) {
                        match = 1;
                    } else {
                        match = 0;
                    }
                    title = PAK_TITLE2;
                    break;
                case 0:
                default:
                    other = 0;
                    goto done;
            }
            if (XPlus_CompareStrings(name, title) == 0 && match != 0) {
                other = 0;
            }
        }
    done:
        if (other) {
            menu->items[i + 3].flags &= ~0x1000000;
        } else {
            menu->items[i + 3].flags |= 0x1000000;
        }
    }
}

extern char g_pakPortZeroPrompt_de[], g_pakPortOnePrompt_de[], g_pakPortTwoPrompt_de[], g_pakPortThreePrompt_de[];
static __inline__ char *pakPrompt(s32 *channel) {
    char *result;
    switch (*channel) {
    case 0:
    default: result = g_pakPortZeroPrompt_de; break;
    case 1: result = g_pakPortOnePrompt_de; break;
    case 2: result = g_pakPortTwoPrompt_de; break;
    case 3: result = g_pakPortThreePrompt_de; break;
    }
    return result;
}
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RECORDRECAT1C.H"
#include "MENU/PAK_PROFILE_PROMPT_VIEWS.H"
extern s32 g_pakSaveMenuActiveDe, g_pakProfileLoadMode_de, g_pakUseScannedChannel, g_pakProfileLoadActive, g_pakMenuPromptAccepted, g_introSelectedItem;
extern char g_matchEndingTeamWheelClose[], g_controllerPakNotReadyDialogResource[], g_pakStatusPromptAlternate[];
extern char g_pakChangeBusyDialog[], g_pakChannelNotReadyDialog_SnapshotCheckstatusprompt[], g_pakChannelReadyMessage_SnapshotCheckstatusprompt[], g_pakDialogDamagedPak[], g_pakScannedChannelReadyMessage[];
extern void Note_ProbeStatus(s32);
extern s32 Note_GetStatus(s32), Note_IsChannelReady(s32), Note_NeedsIdRepair(s32), Control_TakePakChange(s32);

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
            sel = pakPrompt(&slot);
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
            Menu_OpenDialog(g_matchEndingTeamWheelClose, g_pakChangeBusyDialog, menu->player, menu->slot, prompt);
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
        Menu_OpenDialog(g_matchEndingTeamWheelClose, message, menu->player, menu->slot, prompt);
    } else if (!quiet) {
        g_pakMenuPromptAccepted = 1;
        if (Note_NeedsIdRepair(channel))
            Menu_OpenDialog(g_matchEndingTeamWheelClose, g_pakDialogIdRepair_SnapshotCheckeuropeansaveavailability, menu->player, menu->slot, prompt);
        else Menu_OpenDialog(g_matchEndingTeamWheelClose, g_pakChannelNotReadyDialog_SnapshotCheckstatusprompt, menu->player, menu->slot, prompt);
    } else if (result != -2) result = 0;
    return result;
}

#include "COMMON/SHAREDPLAYER.H"
extern void Cache_ReleaseResource(s32, void *);
extern s32 g_pakSaveMenuActiveDe, g_pakNoteSelectProbesNote, g_pakProfileLoadActive, g_pakProfileLoadMode_de, g_pakNoteTitleSelector, g_pakMenuPromptAccepted, g_pakUseScannedChannel, g_pakPlayerMessagePending, g_introSelectedItem;
extern struct Saved g_pakControllerRecord;
extern struct { u8 value; } g_controllerPakPreviewProfileFlags;
extern u8 g_controllerPakPreviewProfileReservedByte1, g_controllerPakPreviewProfileReservedByte2, g_controllerPakPreviewProfileReservedByte3;
extern u8 g_controllerPakPreviewProfileName[];
extern struct { u16 value; } g_pakProfileSavedWordOne, g_pakProfileSavedWordTwo, g_pakProfileSavedWordThree;
extern char g_pakDialogDamagedPak[], g_playerMenuDialogRomResource[], g_pakChannelNotReadyDialog_SnapshotCheckstatusprompt[], g_matchEndingTeamWheelClose[];
extern void Note_ProbeStatus(s32 ch);
extern s32 Note_GetStatus(s32 ch);
extern s32 Note_IsChannelReady(s32 ch);
extern s32 Note_NeedsIdRepair(s32 ch);
extern u32 Note_Crc32(u8 *data, u32 byteCount, u32 initialCrc);


/* Enters pak menu mode 1 on the selected channel: shows the pending message (g_pakPlayerMessagePending) with the channel's
   prompt, else probes the Controller Pak; with no pak data it saves the player's profile (flags, four words
   and eight name bytes) with its checksum and opens the note list through Snapshot_MarkSaveNotes, otherwise it
   shows the g_pakDialogDamagedPak, g_pakDialogIdRepair_SnapshotCheckeuropeansaveavailability or g_pakChannelNotReadyDialog_SnapshotCheckstatusprompt prompt. */
void Snapshot_BeginProfileSave(Shared_PakMenu *menu) {
    ActorOwnerView *owner = menu->player;
    ActorOwnerView *player;
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
    prompt = pakPrompt(&channel);
    if (g_pakPlayerMessagePending) {
        g_pakMenuPromptAccepted = 1;
        Menu_OpenDialog((char *)&((GameplayCamera *)menu->player->owner)->messageList, prompt, player, player->controller, 0);
        return;
    }
    if (g_pakUseScannedChannel) {
        Note_ProbeStatus(g_introSelectedItem);
    } else {
        Note_ProbeStatus(menu->slot->controllerPort);
    }
    if (!Note_GetStatus(channel)) {
        profile = player->profile;
        g_controllerPakPreviewProfileFlags.value = profile->flags;
        g_pakControllerRecord.values[0] = profile->words[0];
        g_pakProfileSavedWordOne.value = profile->words[1];
        g_pakProfileSavedWordTwo.value = profile->words[2];
        g_pakProfileSavedWordThree.value = profile->words[3];
        g_controllerPakPreviewProfileReservedByte1 = 0;
        g_controllerPakPreviewProfileReservedByte2 = 0;
        g_controllerPakPreviewProfileReservedByte3 = 0;
        for (i = 0; i < 8; i++) {
            g_controllerPakPreviewProfileName[i] = profile->name[i];
        }
        g_pakControllerRecord.checksum = Note_Crc32(&g_pakControllerRecord, 20, 4);
        Snapshot_MarkSaveNotes(menu);
        return;
    }
    g_pakMenuPromptAccepted = 1;
    if (Note_IsChannelReady(channel)) {
        Menu_OpenDialog(g_matchEndingTeamWheelClose, g_pakDialogDamagedPak, player, player->controller, prompt);
    } else if (Note_NeedsIdRepair(channel)) {
        Menu_OpenDialog(g_matchEndingTeamWheelClose, g_pakDialogIdRepair_SnapshotCheckeuropeansaveavailability, player, player->controller, g_playerMenuDialogRomResource);
    } else {
        Menu_OpenDialog(g_matchEndingTeamWheelClose, g_pakChannelNotReadyDialog_SnapshotCheckstatusprompt, player, player->controller, prompt);
    }
}
