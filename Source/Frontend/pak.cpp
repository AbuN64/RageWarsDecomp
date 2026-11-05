#include "Common/aiprofile.h"
#include "Common/gameplay_camera.h"
#include "Common/pak_preview_selection.h"
#include "include_asm.h"
#include "Common/runtime_declarations.h"
#include "Common/player_message_menu.h"
#include "Common/frontend_video_mode.h"
#include "Common/sharedplayer.h"
#include "Common/frontend_resource_load_state.h"
#include "types.h"

/* unit PAK.CPP */
#include <platform_sdk.h>
#include "types.h"
#include "Frontend/pak.h"
#include "Menu/Pak/menu_createmenufromtemplate.h"
#include "Snapshot/snapshot_checkstatusprompt.h"
#include "Frontend/frontend_address_symbols.h"
#include "Menu/menu_event_handlers.h"

/* Confirms the pak menu's channel: picks the team/channel override or the record's own channel byte, marks g_pakMenuPromptAccepted, and if Snapshot_CheckStatusPrompt accepts it opens the pak prompt keyed by the player's storage buffer (or the default buffer if there is no player), otherwise opens the prompt on the default buffer. */
static inline s32 Pak_GetMenuChannel(struct Shared_PakMenu *record) {
    if (g_pakUseScannedChannel != 0) {
        return g_introSelectedItem;
    }
    return record->owner->controllerPort;
}

/* Starts the action's channel (g_introSelectedItem in demo mode, else the record's inner value) through Snapshot_CheckStatusPrompt; on success loads the record's actor resource into g_matchEndingTeamWheelClose and latches g_pakMenuPromptAccepted, otherwise loads the shared fallback text with the actor as extra argument. Returns 1. */
s32 Pak_OpenPakChannel(s32 entry, Shared_PakMenu *menu) {
    s32 channel;

    if (g_pakUseScannedChannel != 0) {
        channel = g_introSelectedItem;
    } else {
        channel = menu->owner->controllerPort;
    }
    if (Snapshot_CheckStatusPrompt(menu, channel, 1) != 0) {
        g_pakMenuPromptAccepted = 1;
        Menu_OpenDialog(&g_matchEndingTeamWheelClose, menu->dialogText, menu->player, menu->owner, 0);
        return 1;
    }
    Menu_OpenDialog(&g_matchEndingTeamWheelClose, &g_pakChannelFallbackDialogText, menu->player, menu->owner, menu->dialogText);
    return 1;
}

/* Starts the configured action using the actor resource or the shared fallback. */
s32 Pak_OpenPakStatusPrompt(void *menuContext, Shared_PakMenu *menu) {
    void *buffer;
    Player *player;
    s32 channel;
    if (g_pakUseScannedChannel != 0) {
        channel = g_introSelectedItem;
    } else {
        channel = menu->owner->controllerPort;
    }
    g_pakMenuPromptAccepted = 1;
    if (Snapshot_CheckStatusPrompt(menu, channel, 1) != 0) {
        player = menu->player;
        if (player != NULL) {
            buffer = (char *)&((GameplayCamera *)player->camera)->messageList;
        } else {
            buffer = &g_matchEndingTeamWheelClose;
        }
        Menu_OpenDialog(buffer, menu->dialogText, menu->player, menu->owner, 0);
        return 1;
    }
    Menu_OpenDialog(&g_matchEndingTeamWheelClose, menu->dialogText, menu->player, menu->owner, 0);
    return 1;
}

s32 Pak_CancelPakAction(s32 entry, PakCancelActionView *action) {
    void *dialogOwner;
    Player *actionOwner;
    g_pakPlayerMessagePending = 1;
    g_pakCancelStateWord = 0;
    if (g_pakUseScannedChannel != 0) {
        g_pakRecheckRequested = 1;
    } else {
        actionOwner = action->player;
        if (actionOwner != NULL) {
            dialogOwner = (char *)&((GameplayCamera *)actionOwner->camera)->messageList;
        } else {
            dialogOwner = &g_matchEndingTeamWheelClose;
        }
        Menu_OpenDialog(dialogOwner, (void *)action->dialogList, (void *)action->player, (void *)action->controller, 0);
    }
    return 1;
}

/* Points a field's text at g_pakStatusPrimaryLabel when the option g_pakProfileLoadActive is set and at g_pakStatusSecondaryLabel otherwise, and returns
   zero: the label an option menu shows for that option. */
s32 Pak_SelectPakLoadHeading(struct PakActionLabelView *field) {
    if (g_pakProfileLoadActive != 0) {
        field->text = g_pakStatusPrimaryLabel;
    } else {
        field->text = g_pakStatusSecondaryLabel;
    }
    return 0;
}

/* Latches g_frontendPakPromptAccepted to one when the record's team value is not -1 and both Control_PeekPakChange_Pak and Snapshot_CheckStatusPrompt accept it, then returns g_frontendPakPromptAccepted. */
s32 Pak_CheckPakActionChange(struct Shared_PakMenu *record) {
    if (g_frontendPakPromptAccepted == 0) {
        if (Pak_GetMenuChannel(record) != -1) {
            if (Control_PeekPakChange(Pak_GetMenuChannel(record)) != 0) {
                if (Snapshot_CheckStatusPrompt(record, Pak_GetMenuChannel(record), 0) != 0) {
                    g_frontendPakPromptAccepted = 1;
                }
            }
        }
    }
    return g_frontendPakPromptAccepted;
}

/* Stores 0 in g_frontendResourceLoadStage and 0 in g_frontendPakPromptAccepted. */
void Pak_SelectPakOperationZero(void) {
    g_frontendResourceLoadStage = 0;
    g_frontendPakPromptAccepted = 0;
}

/* Stores 1 in g_frontendResourceLoadStage and 0 in g_frontendPakPromptAccepted. */
void Pak_SelectPakOperationOne(void) {
    g_frontendResourceLoadStage = 1;
    g_frontendPakPromptAccepted = 0;
}

/* Stores 2 in g_frontendResourceLoadStage and 0 in g_frontendPakPromptAccepted. */
void Pak_SelectPakOperationTwo(void) {
    g_frontendResourceLoadStage = 2;
    g_frontendPakPromptAccepted = 0;
}

/* Stores 3 in g_frontendResourceLoadStage and 0 in g_frontendPakPromptAccepted. */
void Pak_SelectPakOperationThree(void) {
    g_frontendResourceLoadStage = 3;
    g_frontendPakPromptAccepted = 0;
}

/* Stores 4 in g_frontendResourceLoadStage and 0 in g_frontendPakPromptAccepted. */
void Pak_SelectPakOperationFour(void) {
    g_frontendResourceLoadStage = 4;
    g_frontendPakPromptAccepted = 0;
}

/* Points a field's text at the label for the state word g_frontendResourceLoadStage: one of four strings
   for states 0 to 4, and g_pakOperationStateLabels[0][0][0] for any other state. Returns zero. */
s32 Pak_SelectPakOperationTextOne(struct PakActionLabelView *field) {
    u32 state = g_frontendResourceLoadStage;

    switch (state) {
        default:
        case 0:
            field->text = g_pakOperationStateLabels[0][0][0];
            break;
        case 1:
            field->text = g_pakOperationStateLabels[1][0][0];
            break;
        case 2:
            field->text = g_pakOperationStateLabels[2][0][0];
            break;
        case 3:
            field->text = g_pakOperationStateLabels[3][0][0];
            break;
        case 4:
            field->text = g_pakOperationStateLabels[4][0][0];
            break;
    }
    return 0;
}

/* unit FRONTEND_SELECTPAKOPERATIONTEXTTWO.CPP */
/* Points a field's text at the label for the state word g_frontendResourceLoadStage: one of 4 strings for states 0 to 4, and g_pakOperationStateLabels[0][1][0] for any other state. Returns zero. */
s32 Frontend_SelectPakOperationTextTwo(struct PakActionLabelView *field) {
    u32 state = g_frontendResourceLoadStage;

    switch (state) {
        default:
        case 0:
            field->text = g_pakOperationStateLabels[0][1][0];
            break;
        case 1:
            field->text = g_pakOperationStateLabels[1][1][0];
            break;
        case 2:
            field->text = g_pakOperationStateLabels[2][1][0];
            break;
        case 3:
            field->text = g_pakOperationStateLabels[3][1][0];
            break;
        case 4:
            field->text = g_pakOperationStateLabels[4][1][0];
            break;
    }
    return 0;
}

/* unit FRONTEND_SELECTPAKOPERATIONTEXTTHREE.CPP */
/* Points a field's text at the label for the state word g_frontendResourceLoadStage: one of 4 strings through a jump table
   for states 0 to 4, and g_pakOperationStateLabels[0][2][0] for any other state. Returns zero. */
s32 Frontend_SelectPakOperationTextThree(struct PakActionLabelView *field) {
    u32 state = g_frontendResourceLoadStage;

    switch (state) {
        default:
        case 0:
            field->text = g_pakOperationStateLabels[0][2][0];
            break;
        case 1:
            field->text = g_pakOperationStateLabels[1][2][0];
            break;
        case 2:
            field->text = g_pakOperationStateLabels[2][2][0];
            break;
        case 3:
            field->text = g_pakOperationStateLabels[3][2][0];
            break;
        case 4:
            field->text = g_pakOperationStateLabels[4][2][0];
            break;
    }
    return 0;
}

/* unit FRONTEND_SELECTPAKOPERATIONTEXTFOUR.CPP */
/* Points a field's text at the label for the state word g_frontendResourceLoadStage: one of 4 strings for states 0 to 4, and g_pakOperationStateLabels[0][3][0] for any other state. Returns zero. */
s32 Frontend_SelectPakOperationTextFour(struct PakActionLabelView *field) {
    u32 state = g_frontendResourceLoadStage;

    switch (state) {
        default:
        case 0:
            field->text = g_pakOperationStateLabels[0][3][0];
            break;
        case 1:
            field->text = g_pakOperationStateLabels[1][3][0];
            break;
        case 2:
            field->text = g_pakOperationStateLabels[2][3][0];
            break;
        case 3:
            field->text = g_pakOperationStateLabels[3][3][0];
            break;
        case 4:
            field->text = g_pakOperationStateLabels[4][3][0];
            break;
    }
    return 0;
}

/* unit FRONTEND_SELECTPAKOPERATIONTEXTFIVE.CPP */
/* Points a field's text at the label for the state word g_frontendResourceLoadStage: one of 4 strings for states 0 to 4, and g_pakOperationStateLabels[0][4][0] for any other state. Returns zero. */
s32 Frontend_SelectPakOperationTextFive(struct PakActionLabelView *field) {
    u32 state = g_frontendResourceLoadStage;

    switch (state) {
        default:
        case 0:
            field->text = g_pakOperationStateLabels[0][4][0];
            break;
        case 1:
            field->text = g_pakOperationStateLabels[1][4][0];
            break;
        case 2:
            field->text = g_pakOperationStateLabels[2][4][0];
            break;
        case 3:
            field->text = g_pakOperationStateLabels[3][4][0];
            break;
        case 4:
            field->text = g_pakOperationStateLabels[4][4][0];
            break;
    }
    return 0;
}

/* unit FRONTEND_SELECTPAKCONFIRMATIONLABEL.CPP */
/* Points a field's text at the label for the state word g_frontendResourceLoadStage: one of 3 strings for states 0 to 4, and g_pakConfirmationDefaultLabel for any other state. Returns zero. */
s32 Frontend_SelectPakConfirmationLabel(struct PakActionLabelView *field) {
    u32 state = g_frontendResourceLoadStage;

    switch (state) {
        case 3:
            field->text = g_pakConfirmationDefaultLabel;
            break;
        case 4:
            field->text = g_pakConfirmationDefaultLabel;
            break;
        case 1:
        case 2:
            field->text = g_pakConfirmationActiveLabel;
            break;
        default:
            field->text = g_pakConfirmationDefaultLabel;
            break;
    }
    return 0;
}
