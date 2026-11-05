#include "Common/aiprofile.h"
#include "Common/shared_gameslot.h"
#include "Common/effectrender.h"
#include "Common/runtime_declarations.h"
#include "types.h"
#include "Common/rg.h"
#include "Menu/Pak/menu_createmenufromtemplate.h"
#include "Engine/Audio/T2SoundElement.h"
#include "Ovlgame/player_startplayeranimation.h"
#include "Menu/menu_createmenufromtemplate.h"
#include "Menu/menu_createmenufromparameters.h"
#include "Menu/Items/Character/character_symbols.h"

#if defined(VERSION_DE)
typedef struct { char pad0[0x1C]; Player *rec; struct ControllerProfile *player; } CharacterPreviewMenuContext;

/* Steps the choice a field of the slot the record in menuContext points to: while the player passes Control_IsAButtonPressed_Character it plays the sound for the record's style and runs the resource g_characterPreviewMenuRomResource; otherwise Menu_StepValue moves the choice and the remapping tables g_characterPreviewLeftChoices (Control_IsLeftPressed) and g_characterPreviewRightChoices (Control_IsRightPressed or Control_IsAButtonPressed_Character) are applied before the display is refreshed; returns 1 or 0. */
s32 Items_HandleCharacterPreviewSelectionGerman(s32 widget, CharacterPreviewMenuContext *menuContext, s32 owner) {
    Player *rec = menuContext->rec;
    AiProfile *slot = rec->profile;
    if (Control_IsAButtonPressed(menuContext->player) != 0) {
        Player_StartPlayerAnimation(rec, slot->character);
        SoundElement_PlayFlatSound(g_characterPreviewStyleSounds[rec->state][0]);
        Menu_AllocateMenu(owner, menuContext, g_characterPreviewMenuRomResource);
        return 1;
    }
    slot->character = Menu_StepValue(menuContext, slot->character, 1, 0, 18, 1);
    if (Control_IsLeftPressed(menuContext->player) != 0) {
        slot->character = g_characterPreviewLeftChoices[slot->character][0];
    }
    if (Control_IsRightPressed(menuContext->player) != 0 || Control_IsAButtonPressed(menuContext->player) != 0) {
        slot->character = g_characterPreviewRightChoices[slot->character][0];
    }
    Player_StartPlayerAnimation(rec, slot->character);
    Menu_SelectPreviewModel(widget, 11, slot->character);
    return 0;
}
#endif
#if defined(VERSION_DE) || defined(VERSION_US)
#if defined(VERSION_DE)
s32 Items_SelectToggleRowTextGerman(TextBoundsText *textRow) {
    s32 toggleRow;

    toggleRow = textRow->value;
    switch (toggleRow) {
    case 2:
    default:
        if (g_gameSettings.menuToggles[0] != 0) {
            textRow->text = &g_menuToggleChargeDartRifleEnabledText;
        } else {
            textRow->text = &g_menuToggleChargeDartRifleDisabledText;
        }
        break;
    case 3:
        if (g_gameSettings.menuToggles[1] != 0) {
            textRow->text = &g_menuToggleFirestormEnabledText;
        } else {
            textRow->text = &g_menuToggleFirestormDisabledText;
        }
        break;
    case 4:
        if (g_gameSettings.menuToggles[2] != 0) {
            textRow->text = &g_menuToggleAssaultRifleEnabledText;
        } else {
            textRow->text = &g_menuToggleAssaultRifleDisabledText;
        }
        break;
    case 5:
        if (g_gameSettings.menuToggles[3] != 0) {
            textRow->text = &g_menuTogglePlasmaRifleEnabledText;
        } else {
            textRow->text = &g_menuTogglePlasmaRifleDisabledText;
        }
        break;
    case 6:
        if (g_gameSettings.menuToggles[4] != 0) {
            textRow->text = &g_menuToggleCerebralBoreEnabledText;
        } else {
            textRow->text = &g_menuToggleCerebralBoreDisabledText;
        }
        break;
    case 7:
        if (g_gameSettings.menuToggles[5] != 0) {
            textRow->text = &g_menuToggleGrenadeLauncherEnabledText;
        } else {
            textRow->text = &g_menuToggleGrenadeLauncherDisabledText;
        }
        break;
    case 8:
        if (g_gameSettings.menuToggles[6] != 0) {
            textRow->text = &g_menuToggleScorpionLauncherEnabledText;
        } else {
            textRow->text = &g_menuToggleScorpionLauncherDisabledText;
        }
        break;
    case 9:
        if (g_gameSettings.menuToggles[8] != 0) {
            textRow->text = &g_menuToggleTorpedoLauncherEnabledText;
        } else {
            textRow->text = &g_menuToggleTorpedoLauncherDisabledText;
        }
        break;
    }
    return 0;
}
#endif
#endif
