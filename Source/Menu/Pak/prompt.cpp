#include "Common/gameplay_camera.h"
extern s32 g_pakProfileSavePending;
#include "include_asm.h"
#include "Common/Lone/g_controllerpakreadydialogresource.h"
#include "Common/player_message_menu.h"
#include "Menu/pak_profile_prompt_views.h"
#include "Common/sharedplayer.h"
#include "Common/pakqueuestate.h"
#include "Common/world.h"
#include "Common/pak_profile_load.h"
#include "types.h"
#include "Menu/Pak/prompt_operations.h"
#include "Menu/Pak/menu_createmenufromtemplate.h"
#include "Ai/Player/player_getammocapacity.h"
#include "Menu/Items/Scene/scene_updatependingobjects.h"
#include "Render/control_cycleactorsnapshotmode.h"
#include "Snapshot/snapshot_checkstatusprompt.h"
#include "Common/runtime_declarations.h"
#include "Menu/pak_load.h"
#include "Common/ballisticparams.h"
#include "Common/sessionhandlerrow.h"
#include "Ovlgame/player_startplayeranimation.h"
#include "Menu/note_readnoteinfo.h"
#include "Engine/control.h"
#include "Ovlgame/match.h"
#include "Common/pak_preview_selection.h"
#include "Common/frontend_resource_load_state.h"
#include "Menu/note_readnotedata.h"
#include "Menu/snapshot_savecontrollerrecord.h"
#include "Menu/Pak/Prompt/pak_closepromptbykind_symbols.h"
#include "Common/game_session.h"

/* Closes the current pak menu prompt by its kind g_controllerPakPromptKind: kind 8 is refused (returns 0); kinds
   9 and 5 release the slot's controller through Control_ResetControllerPakDe and Control_SetProfileModeDe; kind 9 then either
   hands the channel back through Control_DisableControllerPakDe and reopens the player's menu 0x5EC (load menu
   without a pending save) or returns to the main menu g_gameSession; kind 5 hands the channel back and
   reopens menu g_worldSelectionMenu; kind 6 in the pak manager sets g_pakRecheckRequested; kinds 4 and 3 recheck the pak
   and show g_controllerPakReadyDialogResource_PakClosepromptbykind or g_controllerPakNotReadyDialogResource, or g_pakAlternateReadyDialogResource, and any other kind shows the menu's pending prompt
   (clearing the placeholder 1) in the player's message box. Returns 1. */

/* Value of menu->prompt while the pak ready dialog is still awaiting its confirmation (a marker, not a text pointer). */
#define PAK_PROMPT_PENDING ((char *)1)

struct GameSession;

s32 Pak_ConfirmProfileOrDeleteNote(void *entry, MenuPakConfirmProfileOrDeleteNote *menu) {

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
        profile->words[0] = g_pakControllerRecord.values[0];
        profile->words[1] = g_pakProfileSavedWords[0];
        profile->words[2] = g_pakProfileSavedWords[1];
        profile->words[3] = g_pakProfileSavedWords[2];
        for (i = 0; i < 8; i++) {
            profile->name[i] = g_controllerPakPreviewProfileName[i];
        }
        Player_StartPlayerAnimation(player, g_pakPreviewNoteType);
        Menu_AllocateMenu(MESSAGE_LIST_OF(player->views5DC.view5DC_7.messages), menu, g_characterPreviewMenuRomResource);
        return 1;
    }
    if (Note_DeleteNote(ch, g_controllerPakOverwriteNoteIndex) == 0) {
        Menu_OpenDialog(&g_matchEndingTeamWheelClose, g_pakNoteDeleteSucceededDialogResource, menu->player, menu->slot, menu->prompt);
    } else {
        Menu_OpenDialog(&g_matchEndingTeamWheelClose, g_pakNoteDeleteFailedDialogResource, menu->player, menu->slot, menu->prompt);
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
        if (g_pakProfileLoadActive != 0 && g_pakProfileLoadMode_de == 0 && g_pakProfileSavePending == 0) {
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
        if ((status == 0 || connected != 0) && status != -2 && menu->prompt == PAK_PROMPT_PENDING) {
            Menu_OpenDialog(&g_matchEndingTeamWheelClose, g_controllerPakReadyDialogResource, menu->player, menu->slot, 0);
        } else {
            Menu_OpenDialog(&g_matchEndingTeamWheelClose, g_controllerPakNotReadyDialogResource, menu->player, menu->slot, 0);
        }
    } else if (g_controllerPakPromptKind == 3 && g_pakAlternatePromptEnabled != 0) {
        Note_ProbeStatus(ch);
        status = Note_GetStatus(ch);
        connected = Control_TakePakChange(ch);
        if ((status == 0 || connected != 0) && status != -2 && menu->prompt == PAK_PROMPT_PENDING) {
            Menu_OpenDialog(&g_matchEndingTeamWheelClose, g_pakAlternateReadyDialogResource, menu->player, menu->slot, 0);
        }
    } else {
        if (menu->prompt == PAK_PROMPT_PENDING) {
            menu->prompt = 0;
        }
        if (menu->prompt != 0) {
            Menu_OpenDialog(menu->prompt != g_playerMenuDialogRomResource && menu->player != 0 ?
                              menu->player->messages->text : &g_matchEndingTeamWheelClose,
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
                Menu_OpenDialog(&g_matchEndingTeamWheelClose, menu->prompt, menu->player, menu->slot, 0);
                break;
            }
            Note_ProbeStatus(ch);
            if (Note_DeleteNote(ch, g_controllerPakSelectedNoteIndex) == 0) {
                Menu_OpenDialog(&g_matchEndingTeamWheelClose, g_pakNoteDeleteSucceededDialogResource, menu->player, menu->slot, menu->prompt);
            } else {
                Menu_OpenDialog(&g_matchEndingTeamWheelClose, g_pakNoteDeleteFailedDialogResource, menu->player, menu->slot, menu->prompt);
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
                Menu_OpenDialog(&g_matchEndingTeamWheelClose, menu->prompt, menu->player, menu->slot, 0);
                break;
            }
            Note_ProbeStatus(ch);
            if (Note_DeleteNote(ch, g_controllerPakOverwriteNoteIndex) == 0) {
                Snapshot_SaveSnapshotAndClose(owner, (struct Shared_PakMenu *)menu);
                return 1;
            }
            Menu_OpenDialog(&g_matchEndingTeamWheelClose, g_pakNoteDeleteFailedDialogResource, menu->player, menu->slot, menu->prompt);
            break;
        case 0:
            if (g_pakUseScannedChannel != 0) {
                ch = g_introSelectedItem;
            } else {
                ch = menu->slot->controllerPort;
            }
            if (Snapshot_CheckStatusPrompt(menu, ch, 1) != 0) {
                g_pakMenuPromptAccepted = 1;
                Menu_OpenDialog(&g_matchEndingTeamWheelClose, menu->prompt, menu->player, menu->slot, 0);
                break;
            }
            Note_ProbeStatus(ch);
            if (Note_RepairIdIfNeeded(ch) == 0) {
                Menu_OpenDialog(&g_matchEndingTeamWheelClose, g_pakNoteIdRepairSucceededDialogResource, menu->player, menu->slot, menu->prompt);
            } else {
                Menu_OpenDialog(&g_matchEndingTeamWheelClose, g_pakNoteIdRepairFailedDialogResource, menu->player, menu->slot, menu->prompt);
            }
            break;
        case 1:
        case 2:
            if (g_pakUseScannedChannel != 0) {
                g_pakProbeRequested = 1;
            }
            Menu_OpenDialog(&g_matchEndingTeamWheelClose, menu->prompt, menu->player, menu->slot, 0);
            break;
    }
    return 1;
}
#undef PAK_PROMPT_PENDING

#if defined(VERSION_EU) || defined(VERSION_EU_X)
const char s_fourDigitDecimalFormat[5] =
    "%04d";
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
const char g_pakDigitDotFormat[5] =
    "%1d.";
#endif

#if defined(VERSION_EU_X)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_EU)
/* bytes live in the preceding array */
#endif
