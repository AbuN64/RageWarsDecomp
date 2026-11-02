#include "COMMON/GAMEPLAY_SETTINGS.H"
#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "OVLGAME/MENU_CONTROLLER_SELECTION_VIEW.H"
#include "OVLGAME/SHAREDRECAT224.H"
#include "TYPES.H"
#include "COMMON/TRIPLE.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "MENU/PLAYERSETTINGS.H"
#include "MENU/MISC/CONFIRMING_SETMENUCONTROLLERPAKENABLED.H"

#if defined(VERSION_EU)
unsigned int g_confirmationDialogCallbackAddressWordsEu[1] = {
    0x00000000,
};
#endif

#if defined(VERSION_US_REV1)
/* Selects a field's text according to its type and option byte. */
#include "TYPES.H"

extern char *g_menuToggleRow2EnabledText;
extern char *g_menuToggleRow2DisabledText;
extern char *g_menuToggleRow3EnabledText;
extern char *g_menuToggleRow3DisabledText;
extern char *g_menuToggleRow4EnabledText;
extern char *g_menuToggleRow4DisabledText;
extern char *g_menuToggleRow5EnabledText;
extern char *g_menuToggleRow5DisabledText;
extern char *g_menuToggleRow6EnabledText;
extern char *g_menuToggleRow6DisabledText;
extern char *g_menuToggleRow7EnabledText;
extern char *g_menuToggleRow7DisabledText;
extern char *g_menuToggleRow8EnabledText;
extern char *g_menuToggleRow8DisabledText;
extern char *g_menuToggleRow9EnabledText;
extern char *g_menuToggleRow9DisabledText;
#include "MENU/OPTION_TEXT_TYPE.H"


s32 Confirming_SelectToggleRowText(ToggleRowTextView *row) {
    s32 optionType;

    optionType = row->toggleRow;
    switch (optionType) {
    case 2:
    default:
        if (g_gameSettings.menuToggles[0] != 0) {
            row->text = &g_menuToggleRow2EnabledText;
        } else {
            row->text = &g_menuToggleRow2DisabledText;
        }
        break;
    case 3:
        if (g_gameSettings.menuToggles[1] != 0) {
            row->text = &g_menuToggleRow3EnabledText;
        } else {
            row->text = &g_menuToggleRow3DisabledText;
        }
        break;
    case 4:
        if (g_gameSettings.menuToggles[2] != 0) {
            row->text = &g_menuToggleRow4EnabledText;
        } else {
            row->text = &g_menuToggleRow4DisabledText;
        }
        break;
    case 5:
        if (g_gameSettings.menuToggles[3] != 0) {
            row->text = &g_menuToggleRow5EnabledText;
        } else {
            row->text = &g_menuToggleRow5DisabledText;
        }
        break;
    case 6:
        if (g_gameSettings.menuToggles[4] != 0) {
            row->text = &g_menuToggleRow6EnabledText;
        } else {
            row->text = &g_menuToggleRow6DisabledText;
        }
        break;
    case 7:
        if (g_gameSettings.menuToggles[5] != 0) {
            row->text = &g_menuToggleRow7EnabledText;
        } else {
            row->text = &g_menuToggleRow7DisabledText;
        }
        break;
    case 8:
        if (g_gameSettings.menuToggles[6] != 0) {
            row->text = &g_menuToggleRow8EnabledText;
        } else {
            row->text = &g_menuToggleRow8DisabledText;
        }
        break;
    case 9:
        if (g_gameSettings.menuToggles[8] != 0) {
            row->text = &g_menuToggleRow9EnabledText;
        } else {
            row->text = &g_menuToggleRow9DisabledText;
        }
        break;
    }
    return 0;
}
#endif

/* note: Clears eight status bytes and selects the first available profile. */
void SoundElement_DisableMusicGainOverride(void);
unsigned int Control_IsAButtonPressed(struct ControllerProfile *profile);
extern s32 g_controllerProfiles;
extern struct PlayerOptions g_playerPartnerNameFallback;
extern struct ConfirmingControllerStatusView g_gameSettingsRecordActiveFlagBase[];










void Confirming_SelectConfirmingController(MenuControllerSelectionView *menuOwner) {
    ConfirmingControllerSettingsView *settings;
    s8 *status;
    s32 *profile;
    s32 i;

    i = 7;
    status = (s8 *)&g_gameSettingsRecordActiveFlagBase[0];
    for (; i >= 0; i--) {
        ((ConfirmingControllerStatusView *)status)->confirmed = 0;
        status -= sizeof(Shared_PlayerSettingsRecord);
    }
    i = 0;
    settings = (ConfirmingControllerSettingsView *)&g_playerPartnerNameFallback;
    for (; i < 4; i++) {
        profile = (s32 *)((char *)&g_controllerProfiles + i * sizeof(ControllerProfile));
        if (Control_IsAButtonPressed(profile) != 0) {
            settings->controllerSelected = 1;
            settings->controllerIndex = i;
            menuOwner->controllerProfile = profile;
            break;
        }
    }
    SoundElement_DisableMusicGainOverride();
}

/** Dispatches to Control_EnableControllerPak_CmenuprofileOpentimedplayerdialog or Control_DisableControllerPakDe with a byte read from menuStorage->widget->controllerPort, chosen by enabled. */

extern void Control_EnableControllerPak(s32 arg);
extern void Control_DisableControllerPak(s32 arg);






void Confirming_SetMenuControllerPakEnabled(void *menuStorage, s32 enabled) {
    s32 val;
    PlayerProfileMenuContext *menu = menuStorage;

    val = menu->widget->controllerPort;
    if (enabled != 0) {
        Control_EnableControllerPak(val);
    } else {
        Control_DisableControllerPak(val);
    }
}

#include "COMMON/SESSIONHANDLERROW.H"
extern f32 g_confirmationDialogDefaultTimeLimit;

void Confirming_InitMatchCounters(f32 duration, s32 mode, s32 option, s32 teams, s32 last) {
    s32 i;
    CGameStatus *state = &g_gameSettings.counters;
    CGameStatus *result;
    state->m_bFragTagOn = option;
    state->teams = teams;
    state->m_CTFPlayerWithFlag = 0;
    state->timeLimit = duration * g_confirmationDialogTimeScale;
    state->mask = 0xA00;
    state->mode = mode;
    state->elapsed = 0;
    state->m_bCTFOn = last;
    for (i = 0; i < 5; i++) {
        state->scores[i] = 0;
        state->counts[i] = 0;
    }
    result = &g_gameSettings.counters;
    result->round = 0;
    result->state = 0;
    if (result->timeLimit == 0.0f) {
        result->timeLimit = g_confirmationDialogDefaultTimeLimit;
    }
}
