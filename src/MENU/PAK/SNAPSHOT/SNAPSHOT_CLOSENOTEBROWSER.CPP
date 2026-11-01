#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "MENU/PAK/SAVE_SNAPSHOT.H"
#include "COMMON/LONE/g_pakDialogPromptScannedChannel.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/MENURECAT24.H"
#include "MENU/PAK_PROFILE_PROMPT_VIEWS.H"
#include "TYPES.H"
#include "MENU/PAK/SNAPSHOT_CLOSENOTEBROWSER.H"
extern void Cache_ReleaseResource(void *cache, void *resource);

/* Releases temporary profile buffers and opens the controller-pak prompt for the selected player and channel, labelling the port prompt by channel. */







extern char g_playerMenuDialogTable[];
extern char g_playerViewRenderContext[];
extern char g_matchEndingTeamWheelClose[];




extern s32 g_pakUseScannedChannel;



extern s32 g_controllerPakSnapshotPayload;

extern SharedPlayer *Playerai_FindPlayerByController(void *profiles, PakMenuSlot *slot);
extern void Cache_DrainAndCompactResources(s32 heap);
extern void *Menu_OpenDialog(void *parent, struct Dialog *list, s32 player, s32 controller, s32 d);

static inline void get_channel(PakNoteBrowserContext *menu, s32 *channel) {
    if (g_pakUseScannedChannel != 0) {
        *channel = g_introSelectedItem;
    } else {
        *channel = menu->slot->controllerPort;
    }
}

s32 Snapshot_CloseNoteBrowser(void *unused, PakNoteBrowserContext *menu) {
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
    get_channel(menu, &channel);
    if (g_pakUseScannedChannel != 0) {
        g_pakRecheckRequested = 0;
        g_pakRequestLatched = 0;
        g_pakUsable = 1;
        g_pakProbeRequested = 0;
        Menu_OpenDialog(g_matchEndingTeamWheelClose, g_pakDialogPromptScannedChannel, 0, (char *)menu->slot, 0);
        return 1;
    }
    if (g_pakProfileLoadMode_de != 0) {
        if (g_pakProfileLoadActive != 0) {
            g_pakMenuPromptAccepted = 1;
            target = Playerai_FindPlayerByController(g_playerViewRenderContext, menu->slot);
            Menu_OpenDialog((char *)&((GameplayCamera *)target->views5DC.view5DC_6.storage)->messageList, g_playerMenuDialogTable, target, target->views5E8.view698_38.title, channel);
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
                label = g_pakPortZeroPrompt_de;
                break;
            case 1:
                label = g_pakPortOnePrompt_de;
                break;
            case 2:
                label = g_pakPortTwoPrompt_de;
                break;
            case 3:
                label = g_pakPortThreePrompt_de;
                break;
            }
            Menu_OpenDialog((char *)&((GameplayCamera *)target->views5DC.view5DC_6.storage)->messageList, label, target, target->views5E8.view698_38.title, channel);
            return 1;
        }
    } else {
        target = Playerai_FindPlayerByController(g_playerViewRenderContext, menu->slot);
        if (g_pakProfileLoadActive != 0) {
            g_pakMenuPromptAccepted = 1;
            Menu_OpenDialog(&((Shared_MenuData *)g_playerViewRenderContext)->dialogOwner, g_controllerPakNotReadyDialogResource, target, target->views5E8.view698_38.title, channel);
            return 1;
        }
        if (g_pakSaveMenuActiveDe != 0) {
            g_pakMenuPromptAccepted = 1;
            return 1;
        }
    }
    return 0;
}
