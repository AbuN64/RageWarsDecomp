#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/RECORDRECATCV1.H"
#include "include_asm.h"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/MENURECAT24.H"
#include "COMMON/NODERECAT2A8.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include <ultra64.h>
#include "TYPES.H"
#include "FRONTEND/PAK.H"
#include "MENU/PAK/MENU_CREATEMENUFROMTEMPLATE.H"
#include "SNAPSHOT/SNAPSHOT_CHECKSTATUSPROMPT.H"

extern s32 g_pakUseScannedChannel;






/* Confirms the pak menu's channel: picks the team/channel override or the record's own channel byte, marks g_pakMenuPromptAccepted, and if Snapshot_CheckStatusPrompt accepts it opens the pak prompt keyed by the player's storage buffer (or the default buffer if there is no player), otherwise opens the prompt on the default buffer. */


/* Starts the configured action using the actor resource or the shared fallback. */


 /* extern */
extern s32 g_pakPlayerMessagePending;



/* Points a field's text at g_pakStatusPrimaryLabel when the option g_pakProfileLoadActive is set and at g_pakStatusSecondaryLabel otherwise, and returns
   zero: the label an option menu shows for that option. */





/* Latches g_frontendPakPromptAccepted to one when the record's team value is not -1 and both Control_PeekPakChange_Pak and Snapshot_CheckStatusPrompt accept it, then returns g_frontendPakPromptAccepted. Adapted from Timer_CheckMenuPakChange with the latch g_pakMenuPromptAccepted changed to g_frontendPakPromptAccepted. */









static inline s32 Pak_GetMenuChannel(struct Shared_PakMenu *record) {
    if (g_pakUseScannedChannel != 0) {
        return g_introSelectedItem;
    }
    return record->owner->controllerPort;
}

/* Stores 0 in g_frontendResourceLoadStage and 0 in g_frontendPakPromptAccepted. */


/* Stores 1 in g_frontendResourceLoadStage and 0 in g_frontendPakPromptAccepted. */


/* Stores 2 in g_frontendResourceLoadStage and 0 in g_frontendPakPromptAccepted. */


/* Stores 3 in g_frontendResourceLoadStage and 0 in g_frontendPakPromptAccepted. */


/* Stores 4 in g_frontendResourceLoadStage and 0 in g_frontendPakPromptAccepted. */


/* Points a field's text at the label for the state word g_frontendResourceLoadStage: one of four strings through the
   jump table k_pakOperationTextOneStateJumpTable for states 0 to 4, and g_pakStatusDefaultLabel for any other state. Returns zero. */










extern char g_matchEndingTeamWheelClose[];
extern s32 g_frontendResourceLoadStage;
/* Starts the action's channel (g_introSelectedItem in demo mode, else the record's inner value) through Snapshot_CheckStatusPrompt; on success loads the record's actor resource into g_matchEndingTeamWheelClose and latches g_pakMenuPromptAccepted, otherwise loads the shared fallback text with the actor as extra argument. Returns 1. */
s32 Pak_OpenPakChannel(s32 unused0, Shared_PakMenu *menu) {
    s32 channel;

    if (g_pakUseScannedChannel != 0) {
        channel = g_introSelectedItem;
    } else {
        channel = menu->owner->controllerPort;
    }
    if (Snapshot_CheckStatusPrompt(menu, channel, 1) != 0) {
        g_pakMenuPromptAccepted = 1;
        Menu_OpenDialog(g_matchEndingTeamWheelClose, menu->dialogText, menu->player, menu->owner, 0);
        return 1;
    }
    Menu_OpenDialog(g_matchEndingTeamWheelClose, &g_pakChannelFallbackDialogText, menu->player, menu->owner, menu->dialogText);
    return 1;
}

s32 Pak_OpenPakStatusPrompt(void *menuContext, Shared_PakMenu *menu) {
    void *buffer;
    ActorOwnerView *player;
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
            buffer = (char *)&((GameplayCamera *)player->owner)->messageList;
        } else {
            buffer = g_matchEndingTeamWheelClose;
        }
        Menu_OpenDialog(buffer, menu->dialogText, menu->player, menu->owner, 0);
        return 1;
    }
    Menu_OpenDialog(g_matchEndingTeamWheelClose, menu->dialogText, menu->player, menu->owner, 0);
    return 1;
}

s32 Pak_CancelPakAction(s32 unused0, PakCancelActionView *action) {
    void *dialogOwner;
    ActorOwnerView *actionOwner;
    g_pakPlayerMessagePending = 1;
    g_pakCancelStateWord = 0;
    if (g_pakUseScannedChannel != 0) {
        g_pakRecheckRequested = 1;
    } else {
        actionOwner = action->player;
        if (actionOwner != NULL) {
            dialogOwner = (char *)&((GameplayCamera *)actionOwner->owner)->messageList;
        } else {
            dialogOwner = g_matchEndingTeamWheelClose;
        }
        Menu_OpenDialog(dialogOwner, (void *)action->dialogList, (void *)action->player, (void *)action->controller, 0);
    }
    return 1;
}

s32 Pak_SelectPakLoadHeading(struct PakActionLabelView *field) {
    if (g_pakProfileLoadActive != 0) {
        field->text = g_pakStatusPrimaryLabel;
    } else {
        field->text = g_pakStatusSecondaryLabel;
    }
    return 0;
}

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

void Pak_SelectPakOperationZero(void) {
    g_frontendResourceLoadStage = 0;
    g_frontendPakPromptAccepted = 0;
}

void Pak_SelectPakOperationOne(void) {
    g_frontendResourceLoadStage = 1;
    g_frontendPakPromptAccepted = 0;
}

void Pak_SelectPakOperationTwo(void) {
    g_frontendResourceLoadStage = 2;
    g_frontendPakPromptAccepted = 0;
}

void Pak_SelectPakOperationThree(void) {
    g_frontendResourceLoadStage = 3;
    g_frontendPakPromptAccepted = 0;
}

void Pak_SelectPakOperationFour(void) {
    g_frontendResourceLoadStage = 4;
    g_frontendPakPromptAccepted = 0;
}

s32 Pak_SelectPakOperationTextOne(struct PakActionLabelView *field) {
    u32 state = g_frontendResourceLoadStage;

    if (state >= 5) {
        goto state_other;
    }
    switch (state) {
        case 0: goto state_other;
        case 1: goto state_1;
        case 2: goto state_2;
        case 3: goto state_3;
        case 4: goto state_4;
        }
state_other:
    field->text = g_pakStatusDefaultLabel;
    goto done;
state_1:
    field->text = g_pakOperationOneStateOneLabel;
    goto done;
state_2:
    field->text = g_pakOperationOneStateTwoLabel;
    goto done;
state_3:
    field->text = g_pakOperationOneStateThreeLabel;
    goto done;
state_4:
    field->text = g_pakOperationOneStateFourLabel;
done:
    return 0;
}
