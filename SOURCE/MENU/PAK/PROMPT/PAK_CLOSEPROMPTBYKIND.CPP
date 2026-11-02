#include "COMMON/GAMEPLAY_CAMERA.H"
#include "include_asm.h"
#include "COMMON/LONE/g_controllerPakReadyDialogResource.H"
#include "COMMON/MENURECAT24.H"
#include "MENU/PAK_PROFILE_PROMPT_VIEWS.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/PAKQUEUESTATE.H"
#include "COMMON/WORLD.H"
#include "COMMON/RECORDRECAT1C.H"
#include "TYPES.H"
#include "MENU/PAK/PROMPT_OPERATIONS.H"
#include "MENU/PAK/MENU_CREATEMENUFROMTEMPLATE.H"

/* Confirms the selected pak menu entry: marks the menu busy and returns when Snapshot_CheckStatusPrompt takes
   over the selected channel; with a profile loaded (g_pakProfileLoaded) it creates the player through
   Playerai_FindPlayerByController_PakClosepromptbykind, copies the loaded profile (flags, four words and eight name bytes) into the
   player's profile, applies the loaded team through Player_StartPlayerAnimation_CmenuprofileUpdateplayeranimationchoice and shows the player's message
   through Menu_AllocateMenu; otherwise it deletes the chosen note through Note_DeleteNote and shows the
   g_pakNoteDeleteSucceededDialogResource or g_pakNoteDeleteFailedDialogResource result prompt. Returns 1. */









extern s32 g_pakUseScannedChannel;

extern s32 g_pakProfileLoaded;

extern u8 g_controllerPakPreviewProfileFlags;

extern struct { u16 value; } g_pakControllerRecord;

extern struct { u16 value; } g_pakProfileSavedWordOne;

extern struct { u16 value; } g_pakProfileSavedWordTwo;

extern struct { u16 value; } g_pakProfileSavedWordThree;

extern u8 g_controllerPakPreviewProfileName[];

extern s8 g_pakPreviewNoteType;

extern char g_playerViewRenderContext;

extern char g_characterPreviewMenuRomResource[];

extern char g_matchEndingTeamWheelClose[];

extern SharedPlayer *Playerai_FindPlayerByController(char *pool, PakMenuSlot *slot);

extern void Player_StartPlayerAnimation(struct Player *animatedPlayer, s32 animationState);

extern void *Menu_AllocateMenu(struct MenuCreationOwnerView *owner, struct ParamsPakAllocateMenu *params, struct Dialog *list);

extern s32 Note_DeleteNote(s32 ch, s32 index);

/* Closes the current pak menu prompt by its kind g_controllerPakPromptKind: kind 8 is refused (returns 0); kinds
   9 and 5 release the slot's controller through Control_ResetControllerPakDe and Control_SetProfileModeDe; kind 9 then either
   hands the channel back through Control_DisableControllerPakDe and reopens the player's menu 0x5EC (load menu
   without a pending save) or returns to the main menu g_gameSession; kind 5 hands the channel back and
   reopens menu g_worldSelectionValueThree; kind 6 in the pak manager sets g_pakRecheckRequested; kinds 4 and 3 recheck the pak
   and show g_controllerPakReadyDialogResource_PakClosepromptbykind or g_controllerPakNotReadyDialogResource, or g_pakAlternateReadyDialogResource, and any other kind shows the menu's pending prompt
   (clearing the placeholder 1) in the player's message box. Returns 1. */









extern s32 g_controllerPakPromptKind;

extern s32 g_pakPromptKindNinePending;

extern s32 g_pakRecheckRequested;


#include "COMMON/GAME_SESSION.H"

extern char g_playerMenuDialogRomResource[];


extern char g_pakAlternateReadyDialogResource[];

extern char g_controllerPakNotReadyDialogResource[];


extern void Control_SetProfileMode(PakMenuSlot *slot, s32 mode);

extern void Control_DisableControllerPak(s32 ch);

extern void Scene_SetSelection(char *, s32, s32);

struct GameSession;
extern void Match_ResetGameClockAndSelectSpawn(struct GameSession *);

extern void Note_ProbeStatus(s32 ch);

extern s32 Note_GetStatus(s32 ch);

extern s32 Control_TakePakChange(s32 ch);

extern s32 g_frontendResourceLoadStage;

extern s32 g_controllerPakSelectedNoteIndex;

extern char g_pakNoteIdRepairSucceededDialogResource[];

extern char g_pakNoteIdRepairFailedDialogResource[];

extern s32 Note_RepairIdIfNeeded(s32 ch);

extern s32 Snapshot_SaveSnapshotAndClose(void *owner, PakPromptContext *menu, void *arg);

s32 Pak_ConfirmProfileOrDeleteNote(void *unused, MenuPakConfirmProfileOrDeleteNote *menu) {

    s32 ch;
    SharedPlayer *player;
    PakStatusProfile *profile;
    s32 i;

    if (g_pakUseScannedChannel != 0) {
        ch = g_introSelectedItem;
    } else {
        ch = menu->slot->controllerPort;
    }
    if (Snapshot_CheckStatusPrompt(menu, ch, 0) != 0) {
        g_pakMenuPromptAccepted = 1;
        return 1;
    }
    if (g_pakProfileLoaded != 0) {
        player = Playerai_FindPlayerByController(&g_playerViewRenderContext, menu->slot);
        menu->player = player;
        profile = player->views5D8.view5D8_6.profile;
        profile->flags = g_controllerPakPreviewProfileFlags;
        profile->words[0] = g_pakControllerRecord.value;
        profile->words[1] = g_pakProfileSavedWordOne.value;
        profile->words[2] = g_pakProfileSavedWordTwo.value;
        profile->words[3] = g_pakProfileSavedWordThree.value;
        for (i = 0; i < 8; i++) {
            profile->name[i] = g_controllerPakPreviewProfileName[i];
        }
        Player_StartPlayerAnimation(player, g_pakPreviewNoteType);
        Menu_AllocateMenu((char *)&((GameplayCamera *)player->views5DC.view5DC_7.messages)->messageList, menu, g_characterPreviewMenuRomResource);
        return 1;
    }
    if (Note_DeleteNote(ch, g_controllerPakOverwriteNoteIndex) == 0) {
        Menu_OpenDialog(g_matchEndingTeamWheelClose, g_pakNoteDeleteSucceededDialogResource, menu->player, menu->slot, menu->prompt);
    } else {
        Menu_OpenDialog(g_matchEndingTeamWheelClose, g_pakNoteDeleteFailedDialogResource, menu->player, menu->slot, menu->prompt);
    }
    return 1;
}

s32 Pak_ClosePromptByKind(void *owner, PakPromptContext *menu) {

    s32 ch;
    s32 status;
    s32 connected;

    if (g_controllerPakPromptKind == 8) {
        return 0;
    }
    if (g_controllerPakPromptKind == 9 || g_controllerPakPromptKind == 5) {
        Control_ResetControllerPak(menu->slot);
        Control_SetProfileMode(menu->slot, 1);
    }
    if (g_controllerPakPromptKind == 9) {
        if (g_pakProfileLoadActive != 0 && g_pakProfileLoadMode_de == 0 && g_pakPromptKindNinePending == 0) {
            if (g_pakUseScannedChannel != 0) {
                ch = g_introSelectedItem;
            } else {
                ch = menu->slot->controllerPort;
            }
            Control_DisableControllerPak(ch);
            Scene_SetSelection(&g_world, menu->player->menu, 2);
            return 1;
        }
        Match_ResetGameClockAndSelectSpawn(&g_gameSession);
        return 1;
    }
    if (g_pakUseScannedChannel != 0) {
        ch = g_introSelectedItem;
    } else {
        ch = menu->slot->controllerPort;
    }
    if (g_controllerPakPromptKind == 5) {
        Control_DisableControllerPak(ch);
        Scene_SetSelection(&g_world, g_world.selectionValues[3], 2);
    }
    if (g_pakUseScannedChannel != 0 && g_controllerPakPromptKind == 6) {
        g_pakRecheckRequested = 1;
    }
    if (g_controllerPakPromptKind == 4 && g_pakProfileLoadActive != 0 && g_pakProfileLoadMode_de == 0) {
        Note_ProbeStatus(ch);
        status = Note_GetStatus(ch);
        connected = Control_TakePakChange(ch);
        if ((status == 0 || connected != 0) && status != -2 && menu->prompt == (char *)1) {
            Menu_OpenDialog(g_matchEndingTeamWheelClose, g_controllerPakReadyDialogResource, menu->player, menu->slot, 0);
        } else {
            Menu_OpenDialog(g_matchEndingTeamWheelClose, g_controllerPakNotReadyDialogResource, menu->player, menu->slot, 0);
        }
    } else if (g_controllerPakPromptKind == 3 && g_pakAlternatePromptEnabled != 0) {
        Note_ProbeStatus(ch);
        status = Note_GetStatus(ch);
        connected = Control_TakePakChange(ch);
        if ((status == 0 || connected != 0) && status != -2 && menu->prompt == (char *)1) {
            Menu_OpenDialog(g_matchEndingTeamWheelClose, g_pakAlternateReadyDialogResource, menu->player, menu->slot, 0);
        }
    } else {
        if (menu->prompt == (char *)1) {
            menu->prompt = 0;
        }
        if (menu->prompt != 0) {
            Menu_OpenDialog(menu->prompt != g_playerMenuDialogRomResource && menu->player != 0 ?
                              menu->player->messages->text : g_matchEndingTeamWheelClose,
                          menu->prompt, menu->player, menu->slot, ch);
        }
    }
    return 1;
}

s32 Pak_ConfirmPendingOperation(void *owner, PakPromptContext *menu, void *arg) {

    s32 ch;

    switch (g_frontendResourceLoadStage) {
        case 4:
            if (g_pakUseScannedChannel != 0) {
                ch = g_introSelectedItem;
            } else {
                ch = menu->slot->controllerPort;
            }
            if (Snapshot_CheckStatusPrompt(menu, ch, 1) != 0) {
                g_pakMenuPromptAccepted = 1;
                Menu_OpenDialog(g_matchEndingTeamWheelClose, menu->prompt, menu->player, menu->slot, 0);
                break;
            }
            Note_ProbeStatus(ch);
            if (Note_DeleteNote(ch, g_controllerPakSelectedNoteIndex) == 0) {
                Menu_OpenDialog(g_matchEndingTeamWheelClose, g_pakNoteDeleteSucceededDialogResource, menu->player, menu->slot, menu->prompt);
            } else {
                Menu_OpenDialog(g_matchEndingTeamWheelClose, g_pakNoteDeleteFailedDialogResource, menu->player, menu->slot, menu->prompt);
            }
            break;
        case 3:
            if (g_pakUseScannedChannel != 0) {
                ch = g_introSelectedItem;
            } else {
                ch = menu->slot->controllerPort;
            }
            if (Snapshot_CheckStatusPrompt(menu, ch, 1) != 0) {
                g_pakMenuPromptAccepted = 1;
                Menu_OpenDialog(g_matchEndingTeamWheelClose, menu->prompt, menu->player, menu->slot, 0);
                break;
            }
            Note_ProbeStatus(ch);
            if (Note_DeleteNote(ch, g_controllerPakOverwriteNoteIndex) == 0) {
                Snapshot_SaveSnapshotAndClose(owner, menu, arg);
                return 1;
            }
            Menu_OpenDialog(g_matchEndingTeamWheelClose, g_pakNoteDeleteFailedDialogResource, menu->player, menu->slot, menu->prompt);
            break;
        case 0:
            if (g_pakUseScannedChannel != 0) {
                ch = g_introSelectedItem;
            } else {
                ch = menu->slot->controllerPort;
            }
            if (Snapshot_CheckStatusPrompt(menu, ch, 1) != 0) {
                g_pakMenuPromptAccepted = 1;
                Menu_OpenDialog(g_matchEndingTeamWheelClose, menu->prompt, menu->player, menu->slot, 0);
                break;
            }
            Note_ProbeStatus(ch);
            if (Note_RepairIdIfNeeded(ch) == 0) {
                Menu_OpenDialog(g_matchEndingTeamWheelClose, g_pakNoteIdRepairSucceededDialogResource, menu->player, menu->slot, menu->prompt);
            } else {
                Menu_OpenDialog(g_matchEndingTeamWheelClose, g_pakNoteIdRepairFailedDialogResource, menu->player, menu->slot, menu->prompt);
            }
            break;
        case 1:
        case 2:
            if (g_pakUseScannedChannel != 0) {
                g_pakProbeRequested = 1;
            }
            Menu_OpenDialog(g_matchEndingTeamWheelClose, menu->prompt, menu->player, menu->slot, 0);
            break;
    }
    return 1;
}
