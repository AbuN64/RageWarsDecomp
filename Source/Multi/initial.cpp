#include "Menu/Misc/cmenuprofile_opentimedplayerdialog.h"
#include "Multi/multi_address_symbols.h"
#include "Menu/built_menu.h"
#include "Common/session_state.h"
#include "include_asm.h"
#include "Common/runtime_declarations.h"
#include "Common/player_item_inventory.h"
#include "Common/vector4f.h"
#include "Common/shared_gameslot.h"
#include "types.h"
#include "Multi/initial.h"
#include "Common/aiprofile.h"
#include "System/sound_context_music_and_voice_control.h"
#include "Menu/Pak/menu_createmenufromtemplate.h"
#include "Common/Lone/g_controllerpakreadydialogresource.h"
#include "Menu/player_settings_text.h"
#include "Common/pakqueuestate.h"
#include "Common/snapshot_actor.h"

struct ParamsPakAllocateMenu;
struct Dialog;

void Timer_ClearTimerFlag(void);

#include "Common/game_session.h"

s32 Initial_ToggleMenuRowOption(s32 *optionValue) {
    Shared_Game *base;

    switch (optionValue[0]) {
        case 2:
            base = &g_gameSettings;
            base->multiplayerRuleBytes[5] ^= 1;
            break;
        case 3:
            base = &g_gameSettings;
            base->multiplayerRuleBytes[6] ^= 1;
            break;
        case 4:
            base = &g_gameSettings;
            base->multiplayerRuleBytes[7] ^= 1;
            break;
        case 5:
            base = &g_gameSettings;
            base->multiplayerRuleBytes[8] ^= 1;
            break;
        case 6:
            base = &g_gameSettings;
            base->multiplayerRuleBytes[9] ^= 1;
            break;
        case 7:
            base = &g_gameSettings;
            base->multiplayerRuleBytes[10] ^= 1;
            break;
        case 8:
            base = &g_gameSettings;
            base->multiplayerRuleBytes[11] ^= 1;
            break;
        case 9:
            base = &g_gameSettings;
            base->multiplayerRuleBytes[13] ^= 1;
            break;
    }
    return 0;
}

/** Forwards menuOwner through and menuContext as the first parameter, adding the g_matchSetupMenuResource_Initial record. */
s32 Initial_OpenMatchSetupMenu(void *owner, void *menuOwner, void *menuContext) {
    Menu_AllocateMenu(menuContext, menuOwner, &g_matchSetupMenuResource);
    return 1;
}

/* Reads an object's sub-record kind byte and forwards it to two per-kind setup routines. */
void Initial_ProbeMenuControllerPak(struct Shared_PakMenu *menu)
{
    s32 kind = menu->owner->controllerPort;

    Control_EnableControllerPak(kind);
    Note_ProbeStatus(kind);
}

/* Marks the selected record's byte tag and clears the active menu state. */
void Initial_EnableMenuControllerPak(void *menu) {
    ControllerPakDialogContext *item = menu;

    Control_EnableControllerPak(item->controller->controllerPort);
    g_pakPlayerMessagePending = 0;
}

struct List;

/** Marks dialog's inner record's byte tag via Control_EnableControllerPak_CmenuprofileOpentimedplayerdialog, then hands the record and dialog's fields to Menu_OpenDialog; ignores owner. */
s32 Initial_OpenDialogWithControllerPak(void *owner, ControllerPakDialogContext *dialog) {
    Control_EnableControllerPak(dialog->controller->controllerPort);
    Menu_OpenDialog(&g_matchEndingTeamWheelClose, &g_controllerPakEnabledDialogResource, dialog->player, (s32) dialog->controller, 0);
    return 1;
}

/* Restarts a round for the player passed in dialog: clears the world timer flag g_pakPlayerMessagePending via
   Timer_ClearTimerFlag, then reallocates a fresh scoreboard entry via Menu_OpenDialog using two of dialog's fields
   against the g_controllerPakReadyDialogResource_PakClosepromptbykind list, and always reports success. Sibling of
   CMenuProfile_OpenTimedPlayerDialog, which also fires SoundElement_StopAudioExceptKey(-1) and uses the g_profileDialogFixedLabel list instead. */
s32 Initial_OpenDialogAfterTimerReset(void *owner, Arg1Struct *dialog) {
    Timer_ClearTimerFlag();
    Menu_OpenDialog(&g_matchEndingTeamWheelClose, &g_controllerPakReadyDialogResource, dialog->player, dialog->controller, 0);
    return 1;
}

/** Clears the g_gameSession record and g_initialMatchStartPending, then re-registers the target through Control_DisableControllerPakDe. */
s32 Initial_RequestTransitionWithPakDisabled(void *owner, ControllerPortOwnerView *dialog) {
    SetN64_SetTransitionTarget(&g_gameSession, 8);
    g_initialMatchStartPending = 0;
    Control_DisableControllerPak(dialog->controller->controllerPort);
    return 1;
}

#if defined(VERSION_US)
/* The 120.0f Initial_ResetPlayerGameOverTimer stores into g_gameSettings.counters.m_GameOverTimer. */

/* 12 stale bytes between the timer and the item alpha scales: no instruction reads them. */

/* Alpha multipliers of Multi_DrawPlayerItemAvailability (ITEM.CPP) */


/* 4 stale bytes after the alpha scales, read by nothing. */

#endif

/* Starts a match from the menu: clears byte 0x1D and sets byte 0x1E of g_gameSettings, clears the active byte 0x78 of its eight 150-byte status records, then gives the menu at 0x20 the first of the four 0x224-byte controller profiles of g_controllerProfiles that Control_IsAButtonPressed_Character reports active, marking the settings g_playerPartnerNameFallback at 0x78 and recording its index in g_gameSettings.defaults.slot, before calling SoundElement_DisableMusicGainOverride, resetting g_gameSession through Match_StartMatchTransition_Initial and setting g_initialMatchStartPending. */

#include "Common/game_session.h"

/* Sets the option bytes at 0x1D and 0x1E of g_gameSettings to 1 and 4, clears the first byte of each
   of the eight 150-byte player records at 0x148, then calls Menu_AllocateMenu with the third argument,
   the second and the resource g_localPlayerSetupMenuResource, and returns one. */


struct ParamsPakAllocateMenu;
struct Dialog;

/* Calls Menu_AllocateMenu with the third argument, the second argument and the resource g_initialDialogBottomRowResource,
   and returns one. */

/* Calls Menu_AllocateMenu with the third argument, the second argument and the resource g_initialDialogTopRowResource,
   and returns one. */

/* Calls Menu_AllocateMenu with the third argument, the second argument and the resource g_initialDialogMiddleRowResource,
   and returns one. */

/* Restarts sound: calls SoundElement_StopAudioExceptKey with -1, records what SoundElement_GetMusicPlaybackEnabled returns in g_menuSavedAudioSelection,
   passes g_menuMusicPreviewSelection to SoundElement_SetMusicPlaybackEnabled, calls SoundElement_SetVoiceMixValue with 1, clears g_musicPreviewMenuActive, calls
   Control_ClearMenuControlFlag and then Menu_AllocateMenu with the third argument, the second and g_musicPreviewMenuResource_PakOpenmusicpreviewmenu.
   Returns one. */

/* Calls Menu_AllocateMenu with the third argument, the second argument and the resource g_initialOpenDialogMenuResource,
   and returns one. */

void Initial_SelectInitialController(void *owner, struct MenuBuildState *menu) {
    Shared_Game *globals;
    struct Part *settings;
    struct ControllerProfile *profile;
    s32 i;

    globals = &g_gameSettings;
    globals->local = 0;
    globals->mode1E = 1;
    for (i = 7; i >= 0; i--) {
        globals->playerSettings[i].enabled = 0;
    }
    i = 0;
    settings = &g_playerPartnerNameFallback;
    for (; i < 4; i++) {
        profile = &g_controllerProfiles[i];
        if (Control_IsAButtonPressed(profile) != 0) {
            settings->active = 1;
            g_gameSettings.defaults.slot = i;
            menu->input = (struct PakMenuInputStateView *)profile;
            break;
        }
    }
    SoundElement_DisableMusicGainOverride();
    Match_StartMatchTransition(&g_gameSession, -1);
    g_initialMatchStartPending = 1;
}

/** Clears or sets bit 24 of item's record's flags depending on how many of Control_CountConnectedControllers_FrontendUpdateplayercountscreen's four slots are active, and demotes item->availability from state 2 to 1 in the low-count case. */
s32 Initial_UpdateMultiplayerAvailability(void *owner, MultiplayerAvailabilityItem *item) {
    if (Control_CountConnectedControllers() < 2) {
        item->widget->flags &= 0xFEFFFFFF;
        if (item->availability == 2) {
            item->availability = 1;
        }
    } else {
        item->widget->flags |= 0x01000000;
    }
    return 0;
}

s32 Initial_OpenLocalPlayerSetup(void *first, void *second, void *third) {
    Shared_Game *options = &g_gameSettings;
    s32 i;

    options->local = 1;
    options->mode1E = 4;
    for (i = 0; i < 8; i++) {
        options->playerSettings[i].enabled = 0;
    }
    Menu_AllocateMenu(third, second, g_localPlayerSetupMenuResource);
    return 1;
}

s32 Initial_OpenDialogBottomRow(void *first, void *second, void *third) {
    Menu_AllocateMenu(third, second, g_initialDialogBottomRowResource);
    return 1;
}

s32 Initial_OpenDialogTopRow(void *first, void *second, void *third) {
    Menu_AllocateMenu(third, second, g_initialDialogTopRowResource);
    return 1;
}

s32 Initial_OpenDialogMiddleRow(void *first, void *second, void *third) {
    Menu_AllocateMenu(third, second, g_initialDialogMiddleRowResource);
    return 1;
}

s32 Initial_OpenTrackPreviewMenu(void *first, void *second, void *third) {
    SoundElement_StopAudioExceptKey(-1);
    g_menuSavedAudioSelection = SoundElement_GetMusicPlaybackEnabled();
    SoundElement_SetMusicPlaybackEnabled(g_menuMusicPreviewSelection);
    SoundElement_SetVoiceMixValue(1);
    g_musicPreviewMenuActive = 0;
    Control_ClearMenuControlFlag();
    Menu_AllocateMenu(third, second, g_musicPreviewMenuResource);
    return 1;
}

/* Placeholder that reports success by returning one. */
s32 Initial_ReturnSuccess(void) {
    return 1;
}

s32 Initial_RequestSessionTransition(void) {
    SetN64_SetTransitionTarget(&g_gameSession, 8);
    return 1;
}

s32 Initial_OpenInitialDialog(void *first, void *second, void *third) {
    Menu_AllocateMenu(third, second, g_initialOpenDialogMenuResource);
    return 1;
}

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "Common/runtime_declarations.h"
#include "Common/resident_event_handler.h"
#include "types.h"
#include "Control/control.h"
#include "Note/pak_probestatus.h"
#include "Ovlgame/match.h"
#include "Multi/multi_address_symbols.h"
#include "Frontend/frontend.h"
#include "Menu/Misc/cmenuprofile_opentimedplayerdialog.h"
#include "Menu/pak_load.h"
#include "Common/pak_preview_selection.h"

typedef struct FlagOwnerMultiResetPlayerGameOverTimer {
    char pad0[0x30];
    u32 flags;
} FlagOwnerMultiResetPlayerGameOverTimer;

typedef struct HolderMultiResetPlayerGameOverTimer {
    char pad0[0xC];
    FlagOwnerMultiResetPlayerGameOverTimer *owner;
} HolderMultiResetPlayerGameOverTimer;

void Initial_ResetPlayerGameOverTimer(HolderMultiResetPlayerGameOverTimer *holder) {
    g_gameSettings.counters.m_GameOverTimer = 120.0f;
    holder->owner->flags &= 0xFBFFFFFF;
}
#endif

#if defined(VERSION_DE)
extern unsigned int g_MultiEncodedWords[3];
#endif

#if !(defined(VERSION_US))

#endif

#if defined(VERSION_EU_X)
extern unsigned int k_itemFragment[1];
#endif

#if defined(VERSION_EU)
extern unsigned int k_itemFragment[1];
#endif

#if defined(VERSION_DE)
extern unsigned int k_itemFragment[1];
#endif

/* Retained data for this translation unit. */
#if defined(VERSION_US)
const float k_InitialGameOverTimer = 120.0f;
#endif
#if defined(VERSION_US)
const unsigned int k_initialStaleWordsBefore[3] = {
    0x04000000, 0x16524158, 0x5F50555F,
};
#endif
#if defined(VERSION_US)
const float g_playerItemAlphaScale[2] = { 255.0f, 255.0f };
#endif
#if defined(VERSION_US)
const float g_playerItemDisabledAlphaScale = 255.0f;
#endif
#if defined(VERSION_US)
const unsigned int k_initialStaleTagAfter[1] = {
    0x65717552,
};
#endif
#if !(defined(VERSION_US))
const float k_ItemEncodedWords[3] = {
    255.0f, 255.0f, 255.0f,
};
#endif
#if defined(VERSION_DE)
unsigned int g_MultiEncodedWords[3] = {
    0x437F0000, 0x437F0000, 0x00000001,
};
#endif
#if defined(VERSION_EU_X)
unsigned int k_itemFragment[1] = {
    0x00007530,
};
#endif
#if defined(VERSION_EU)
unsigned int k_itemFragment[1] = {
    0xE9F71877,
};
#endif
#if defined(VERSION_DE)
unsigned int k_itemFragment[1] = {
    0x73000000,
};
#endif
