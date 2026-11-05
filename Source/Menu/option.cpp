#include "Common/cheatcode.h"
#include "Common/effectrender.h"
#include "Common/runtime_declarations.h"
#include "types.h"
#include "Common/shared_gameslot.h"
#include "Menu/Option/menu_setselectedlevellabel_symbols.h"
#include "include_asm.h"
#include "Common/rg.h"
#include "Menu/Option/menu_updateunlockedoptionlabel_symbols.h"

/* Toggles the bits optionMask names in the settings flag word g_gameSettings and returns 0. */
s32 Menu_ToggleGameOptionBits(s32 entry, s32 optionMask) {
    s32 *flags = (s32 *)&g_gameSettings.flags;

    *flags ^= optionMask;
    return 0;
}

s32 Menu_SetSelectedLevelLabel(SelectedLevelLabelItem *label) {
    switch (g_encodedSelectedLevelIndex) {
    default:
        label->value = &g_unlockedLevelResultLabel;
        break;
    case 0:
        label->value = &g_selectedLevelPortOfAdiaLabel;
        break;
    case 1:
        label->value = &g_selectedLevelRiverOfSoulsLabel;
        break;
    case 2:
        label->value = &g_selectedLevelDeathMarshesLabel;
        break;
    case 3:
        label->value = &g_selectedLevelLairOfTheBlindOnesLabel;
        break;
    case 4:
        label->value = &g_selectedLevelHiveOfTheMantidsLabel;
        break;
    case 5:
        label->value = &g_selectedLevelPrimagensLightshipLabel;
        break;
    case 6:
        label->value = &g_selectedLevelBlindBossLabel;
        break;
    case 7:
        label->value = &g_selectedLevelQueenBossLabel;
        break;
    case 8:
        label->value = &g_selectedLevelMotherBossLabel;
        break;
    case 9:
        label->value = &g_selectedLevelPrimagenBossLabel;
        break;
    case 10:
        label->value = &g_selectedLevelCreditsLabel;
        break;
    }
    return 0;
}

#if defined(VERSION_EU_X)
/* Picks the label of option row 2..9 from its on/off flag (the eu-x twin of Items_SelectOptionRowLabel, without the language table). */
typedef struct { s32 id; u8 pad4[0x10]; char **text; } OptionRowEux;
s32 Menu_UpdateOptionToggleLabel(OptionRowEux *row) {
    switch (row->id) {
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

s32 Menu_UpdateUnlockedOptionLabel(struct MenuOptionLabel *label, s32 optionMask, s32 *enabledText, s32 *disabledText) {
    if (g_menuOptionAvailabilityFlags & optionMask) label->flags |= 0x01000000;
    else label->flags &= 0xFEFFFFFF;
    if (g_gameSettings.flags & optionMask) label->text = enabledText;
    else label->text = disabledText;
    return 0;
}
