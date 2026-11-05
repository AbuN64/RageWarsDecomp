#include "Common/pakqueuestate.h"
#include "Common/gameplay_settings.h"
#include "include_asm.h"
#include "Common/shared_gameslot.h"
#include "Ovlgame/menu_controller_selection_view.h"
#include "Ovlgame/confirming_controller.h"
#include "types.h"
#include "Common/triple.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "Menu/playersettings.h"
#include "Menu/Misc/confirming_setmenucontrollerpakenabled.h"
#include "Common/rg.h"
#include "Menu/player_settings_text.h"

#if defined(VERSION_EU)
unsigned int g_confirmationDialogCallbackAddressWordsEu[1] = {
    0x00000000,
};
#endif

#if defined(VERSION_US_REV1)
/* Selects a field's text according to its type and option byte. */
#include "types.h"

#include "Menu/option_text_type.h"

s32 Confirming_SelectToggleRowText(ToggleRowTextView *row) {
    s32 optionType;

    optionType = row->toggleRow;
    switch (optionType) {
    case 2:
    default:
        if (g_gameSettings.menuToggles[0] != 0) {
            row->text = &g_menuToggleChargeDartRifleEnabledText;
        } else {
            row->text = &g_menuToggleChargeDartRifleDisabledText;
        }
        break;
    case 3:
        if (g_gameSettings.menuToggles[1] != 0) {
            row->text = &g_menuToggleFirestormEnabledText;
        } else {
            row->text = &g_menuToggleFirestormDisabledText;
        }
        break;
    case 4:
        if (g_gameSettings.menuToggles[2] != 0) {
            row->text = &g_menuToggleAssaultRifleEnabledText;
        } else {
            row->text = &g_menuToggleAssaultRifleDisabledText;
        }
        break;
    case 5:
        if (g_gameSettings.menuToggles[3] != 0) {
            row->text = &g_menuTogglePlasmaRifleEnabledText;
        } else {
            row->text = &g_menuTogglePlasmaRifleDisabledText;
        }
        break;
    case 6:
        if (g_gameSettings.menuToggles[4] != 0) {
            row->text = &g_menuToggleCerebralBoreEnabledText;
        } else {
            row->text = &g_menuToggleCerebralBoreDisabledText;
        }
        break;
    case 7:
        if (g_gameSettings.menuToggles[5] != 0) {
            row->text = &g_menuToggleGrenadeLauncherEnabledText;
        } else {
            row->text = &g_menuToggleGrenadeLauncherDisabledText;
        }
        break;
    case 8:
        if (g_gameSettings.menuToggles[6] != 0) {
            row->text = &g_menuToggleScorpionLauncherEnabledText;
        } else {
            row->text = &g_menuToggleScorpionLauncherDisabledText;
        }
        break;
    case 9:
        if (g_gameSettings.menuToggles[8] != 0) {
            row->text = &g_menuToggleTorpedoLauncherEnabledText;
        } else {
            row->text = &g_menuToggleTorpedoLauncherDisabledText;
        }
        break;
    }
    return 0;
}
#endif

/* note: Clears eight status bytes and selects the first available profile. */
void SoundElement_DisableMusicGainOverride(void);
unsigned int Control_IsAButtonPressed(struct ControllerProfile *profile);

void Confirming_SelectConfirmingController(struct MenuControllerSelectionView *menuOwner) {
    ConfirmingControllerSettingsView *settings;
    s8 *status;
    struct ControllerProfile *profile;
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
        profile = &g_controllerProfiles[i];
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

#include "Common/sessionhandlerrow.h"
#include "Control/control.h"
#include "Ovlgame/ovlgame_address_symbols.h"

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
