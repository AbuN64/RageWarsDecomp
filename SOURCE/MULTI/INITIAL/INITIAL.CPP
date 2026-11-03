#include "include_asm.h"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/PLAYERRECAT64E.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "TYPES.H"
#include "MULTI/INITIAL.H"
#include "COMMON/AIPROFILE.H"
#include "SYSTEM/SOUND_CONTEXT_MUSIC_AND_VOICE_CONTROL.H"
#include "MENU/PAK/MENU_CREATEMENUFROMTEMPLATE.H"

struct MenuCreationOwnerView;
struct ParamsPakAllocateMenu;
struct Dialog;



/* Reads an object's sub-record kind byte and forwards it to two per-kind setup routines. */





extern void Control_EnableControllerPak(s32 kind);

extern void Note_ProbeStatus(s32 kind);

/* Marks the selected record's byte tag and clears the active menu state. */
extern void Control_EnableControllerPak(int);

extern s32 g_pakPlayerMessagePending;

extern struct List g_controllerPakEnabledDialogResource;

extern void Control_EnableControllerPak(int controllerPort);

/* Restarts a round for the player passed in dialog: clears the world timer flag g_pakPlayerMessagePending via
   Timer_ClearTimerFlag, then reallocates a fresh scoreboard entry via Menu_OpenDialog using dialog's fields
   at 0x1C and 0x20 against the g_controllerPakReadyDialogResource_PakClosepromptbykind list, and always reports success. Sibling of
   CMenuProfile_OpenTimedPlayerDialog, which also fires SoundElement_StopAudioExceptKey(-1) and uses the g_profileDialogFixedLabel list instead. */



extern unsigned char g_controllerPakReadyDialogResource[];

void Timer_ClearTimerFlag(void);

extern void Control_DisableControllerPak(s32 controllerPort);

#include "COMMON/GAME_SESSION.H"


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
s32 Initial_OpenMatchSetupMenu(void *unused0, void *menuOwner, void *menuContext) {
    Menu_AllocateMenu(menuContext, menuOwner, &g_matchSetupMenuResource);
    return 1;
}

void Initial_ProbeMenuControllerPak(struct Shared_PakMenu *menu)
{
    s32 kind = menu->owner->controllerPort;

    Control_EnableControllerPak(kind);
    Note_ProbeStatus(kind);
}

void Initial_EnableMenuControllerPak(void *menu) {
    ControllerPakDialogContext *item = menu;

    Control_EnableControllerPak(item->controller->controllerPort);
    g_pakPlayerMessagePending = 0;
}

struct List;


extern char g_matchEndingTeamWheelClose[];

/** Marks dialog's inner record's byte tag via Control_EnableControllerPak_CmenuprofileOpentimedplayerdialog, then hands the record and dialog's fields to Menu_OpenDialog; ignores unused0. */
s32 Initial_OpenDialogWithControllerPak(void *unused0, ControllerPakDialogContext *dialog) {
    Control_EnableControllerPak(dialog->controller->controllerPort);
    Menu_OpenDialog(g_matchEndingTeamWheelClose, &g_controllerPakEnabledDialogResource, dialog->player, (s32) dialog->controller, 0);
    return 1;
}

s32 Initial_OpenDialogAfterTimerReset(void *unused0, Arg1Struct *dialog) {
    Timer_ClearTimerFlag();
    Menu_OpenDialog(g_matchEndingTeamWheelClose, &g_controllerPakReadyDialogResource, dialog->player, dialog->controller, 0);
    return 1;
}

/** Clears the g_gameSession record and g_initialMatchStartPending, then re-registers the target through Control_DisableControllerPakDe. */
s32 Initial_RequestTransitionWithPakDisabled(void *unused0, ControllerPortOwnerView *dialog) {
    SetN64_SetTransitionTarget(&g_gameSession, 8);
    g_initialMatchStartPending = 0;
    Control_DisableControllerPak(dialog->controller->controllerPort);
    return 1;
}

#if defined(VERSION_US)
/* 800DD010: the 120.0f Initial_ResetPlayerGameOverTimer stores into g_gameSettings.counters.m_GameOverTimer. */
const float k_InitialGameOverTimer = 120.0f;
/* 12 stale bytes between the timer and the item alpha scales: no instruction reads them. */
const unsigned int k_initialStaleWordsBefore[3] = {
    0x04000000, 0x16524158, 0x5F50555F,
};
/* 800DD020: alpha multipliers of Multi_DrawPlayerItemAvailability (ITEM.CPP) */
const float g_playerItemAlphaScale[2] = { 255.0f, 255.0f };
const float g_playerItemDisabledAlphaScale = 255.0f;
/* 4 stale bytes after the alpha scales, read by nothing. */
const unsigned int k_initialStaleTagAfter[1] = {
    0x65717552,
};
#endif

/* Starts a match from the menu: clears byte 0x1D and sets byte 0x1E of g_gameSettings, clears the active byte 0x78 of its eight 150-byte status records, then gives the menu at 0x20 the first of the four 0x224-byte controller profiles of g_controllerProfiles that Control_IsAButtonPressed_Character reports active, marking the settings g_playerPartnerNameFallback at 0x78 and recording its index in g_gameSettings.defaults.slot, before calling SoundElement_DisableMusicGainOverride, resetting g_gameSession through Match_StartMatchTransition_Initial and setting g_initialMatchStartPending. */

extern struct PlayerOptions g_playerPartnerNameFallback;

extern struct ControllerProfile g_controllerProfiles[4];

#include "COMMON/GAME_SESSION.H"


extern unsigned int Control_IsAButtonPressed(struct ControllerProfile *profile);


extern void Match_StartMatchTransition(GameSession *, s32);

extern s32 Control_CountConnectedControllers(void);

/* Sets the option bytes at 0x1D and 0x1E of g_gameSettings to 1 and 4, clears the first byte of each
   of the eight 150-byte player records at 0x148, then calls Menu_AllocateMenu with the third argument,
   the second and the resource g_localPlayerSetupMenuResource, and returns one. */


struct MenuCreationOwnerView;
struct ParamsPakAllocateMenu;
struct Dialog;

/* Calls Menu_AllocateMenu with the third argument, the second argument and the resource g_initialDialogRowThreeResource,
   and returns one. */

/* Calls Menu_AllocateMenu with the third argument, the second argument and the resource g_initialDialogRowOneResource,
   and returns one. */

/* Calls Menu_AllocateMenu with the third argument, the second argument and the resource g_initialDialogRowTwoResource,
   and returns one. */

/* Restarts sound: calls SoundElement_StopAudioExceptKey with -1, records what SoundElement_GetMusicPlaybackEnabled returns in g_menuSavedAudioSelection,
   passes g_menuMusicPreviewSelection to SoundElement_SetMusicPlaybackEnabled, calls SoundElement_SetVoiceMixValue with 1, clears g_musicPreviewMenuActive, calls
   Control_ClearMenuControlFlag and then Menu_AllocateMenu with the third argument, the second and g_musicPreviewMenuResource_PakOpenmusicpreviewmenu.
   Returns one. */




extern void Control_ClearMenuControlFlag(void);

/* Calls Menu_AllocateMenu with the third argument, the second argument and the resource g_initialOpenDialogMenuResource,
   and returns one. */

void Initial_SelectInitialController(void *unused0, struct GamePlayerListView *menu) {
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
            menu->players = profile;
            break;
        }
    }
    SoundElement_DisableMusicGainOverride();
    Match_StartMatchTransition(&g_gameSession, -1);
    g_initialMatchStartPending = 1;
}

/** Clears or sets bit 24 of item's record's flags depending on how many of Control_CountConnectedControllers_FrontendUpdateplayercountscreen's four slots are active, and demotes item->availability from state 2 to 1 in the low-count case. */
s32 Initial_UpdateMultiplayerAvailability(void *unused0, MultiplayerAvailabilityItem *item) {
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

s32 Initial_OpenDialog450E9C(void *first, void *second, void *third) {
    Menu_AllocateMenu(third, second, g_initialDialogRowThreeResource);
    return 1;
}

s32 Initial_OpenDialog44F4A4(void *first, void *second, void *third) {
    Menu_AllocateMenu(third, second, g_initialDialogRowOneResource);
    return 1;
}

s32 Initial_OpenDialog44F798(void *first, void *second, void *third) {
    Menu_AllocateMenu(third, second, g_initialDialogRowTwoResource);
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

/* Returns one. Nothing in the cartridge image calls it or stores its address as a word. */
s32 Initial_ReturnSuccess(void) {
    return 1;
}

s32 Initial_RequestSessionTransition(void) {
    SetN64_SetTransitionTarget(&g_gameSession, 8);
    return 1;
}

s32 Initial_OpenDialog44FFEC(void *first, void *second, void *third) {
    Menu_AllocateMenu(third, second, g_initialOpenDialogMenuResource);
    return 1;
}

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "TYPES.H"

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
