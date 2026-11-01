#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/PAK_MENU.H"
#include "RESMGR/resmgr_string_memory.H"
#include "COMMON/LONE/g_pakProfileActionDialogResource.H"
#include "COMMON/LONE/g_pakDialogIdRepair_SnapshotCheckeuropeansaveavailability.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RECORDRECAT1C.H"
#include "COMMON/MENURECAT24.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"

/* Enters pak menu mode 1: sets the mode flags, clears the owner's 0x01000000 flag and, when a
   message is pending (g_pakPlayerMessagePending), shows the player's message at 0x554 through Menu_OpenDialog;
   otherwise probes the Controller Pak on the selected channel, falls back to Snapshot_MarkSaveNotes when
   Note_GetStatus reports none, and shows the g_pakChannelReadyMessage_SnapshotEvaluatesavechannel, g_pakDialogIdRepair_SnapshotEvaluatesavechannel or g_pakChannelNotReadyDialog_SnapshotEvaluatesavechannel prompt according to
   Note_IsChannelReady_SnapshotEvaluatesavechannel and Note_NeedsIdRepair. */















extern s32 g_pakUseScannedChannel;
extern s32 g_pakPlayerMessagePending;
extern char g_matchEndingTeamWheelClose[];

extern void Note_ProbeStatus(s32 ch);
extern s32 Note_GetStatus(s32 ch);
extern s32 Note_IsChannelReady(s32 ch);
extern s32 Note_NeedsIdRepair(s32 ch);
extern void *Menu_OpenDialog(void *parent, struct Dialog *list, s32 player, s32 controller, s32 d);

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
        Menu_OpenDialog((char *)&((GameplayCamera *)menu->player->owner)->messageList, g_pakStatusPromptAlternate, menu->player, menu->slot, 0);
        return;
    }
    Note_ProbeStatus(ch);
    if (Note_GetStatus(ch) == 0) {
        Snapshot_MarkSaveNotes(menu);
        return;
    }
    g_pakMenuPromptAccepted = 1;
    if (Note_IsChannelReady(ch) != 0) {
        Menu_OpenDialog(g_matchEndingTeamWheelClose, g_pakChannelReadyMessage_SnapshotCheckstatusprompt, menu->player, menu->slot, g_pakStatusPromptAlternate);
    } else if (Note_NeedsIdRepair(ch) != 0) {
        Menu_OpenDialog(g_matchEndingTeamWheelClose, g_pakDialogIdRepair_SnapshotCheckeuropeansaveavailability, menu->player, menu->slot, g_pakProfileActionDialogResource);
    } else {
        Menu_OpenDialog(g_matchEndingTeamWheelClose, g_pakChannelNotReadyDialog_SnapshotCheckstatusprompt, menu->player, menu->slot, g_pakStatusPromptAlternate);
    }
}

/* Rates the Controller Pak on channel ch as a save target: when one of its 16 notes is named
   g_pakProfileGameNameFixed or g_pakSnapshotGameNameFixed it selects the pak with score 123 and returns 1; otherwise it reads the
   pak's free space and note count and, when the pak is readable but has no notes or lacks the
   space the save image needs, records the pak as the best candidate if that need beats the
   current score and returns 0; a readable pak with room returns 1 and a read error returns 0. */

#if defined(VERSION_EU) || defined(VERSION_EU_X)


extern char *g_pakProfileGameNames[];
extern char *g_pakSnapshotGameNames[];


#else




#endif


extern s32 g_worldSnapshotNoteBytes;

extern s32 Note_GetNoteGameName(s32 ch, s32 index, u8 **state);
extern void Note_DecodeNoteText(u8 *state, u8 *name, s32 size);
extern s32 Note_GetFreePages(s32 ch, s32 *freeSpace);
extern s32 Note_CountFreeNotes(s32 ch, s32 *noteCount);
extern u32 Note_BytesToPakPages(u32 size);

s32 Snapshot_EvaluateSaveChannel(void *unused, s32 ch, s32 *bestCh, s32 *bestScore) {
    u8 name[16];
    u8 *state0;
    u8 *state1;
    s32 freeSpace;
    s32 noteCount;
    s32 found0;
    s32 found1;
    s32 i;
    s32 result;
    s32 need;
    char *wanted;

#if defined(VERSION_EU) || defined(VERSION_EU_X)
    wanted = g_pakProfileGameNames[g_languageIndex];
#else
    wanted = g_pakProfileGameNameFixed;
#endif
    for (i = 0; i < 16; i++) {
        Note_GetNoteGameName(ch, i, &state0);
        Note_DecodeNoteText(state0, name, 16);
        if (XPlus_CompareStrings(name, wanted) == 0) {
            found0 = 1;
            goto search1;
        }
    }
    found0 = 0;
search1:
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    wanted = g_pakSnapshotGameNames[g_languageIndex];
#else
    wanted = g_pakSnapshotGameNameFixed;
#endif
    for (i = 0; i < 16; i++) {
        Note_GetNoteGameName(ch, i, &state1);
        Note_DecodeNoteText(state1, name, 16);
        if (XPlus_CompareStrings(name, wanted) == 0) {
            found1 = 1;
            goto check;
        }
    }
    found1 = 0;
check:
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
