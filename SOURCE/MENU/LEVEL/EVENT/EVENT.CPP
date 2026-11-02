#include "include_asm.h"


/* Maps an id from 1 to 33 to the address of its data block, returning 0 for any other id. */
#include "TYPES.H"
#include "MENU/EVENT.H"



void *Level_GetScreenEventTable(s32 id) {
    switch (id) {
    case 1:
        return g_Frontend_DispatchPauseMenuEventAddress;
    case 31:
        return g_Frontend_DispatchConfirmationEventAddress;
    case 32:
        return g_Frontend_DispatchResidentActorEventAddress;
    case 7:
        return g_Selection_DispatchCharacterSelectionEventAddress;
    case 8:
        return g_Frontend_DispatchEquipmentEventAddress;
    case 10:
        return g_CTrialCatalogue_DispatchCatalogueEventAddress;
    case 15:
        return g_CTrialCatalogue_DispatchOptionsEventAddress;
    case 3:
        return g_Frontend_DispatchPlayModeEventAddress;
    case 4:
        return g_Frontend_DispatchOptionsPageEventAddress;
    case 6:
        return g_Menu_DispatchSoundOptionsEventAddress;
    case 5:
        return g_Player_DispatchPlayerSettingsEventAddress;
    case 11:
        return g_Frontend_DispatchCompactOptionsEventAddress;
    case 12:
        return g_Player_DispatchAlternatePlayerSettingsEventAddress;
    case 13:
        return g_Menu_DispatchSoundSliderEventAddress;
    case 16:
        return g_Menu_DispatchSelectionMenuEventAddress;
    case 17:
        return g_Frontend_DispatchResultsEventAddress;
    case 18:
        return g_Achieve_DispatchResultsActorEventAddress;
    case 9:
        return g_Menu_DispatchScrollingChoiceEventAddress;
    case 30:
        return g_Menu_DispatchTitleButtonEventAddress;
    case 20:
        return g_ScenarioSetup_DispatchCatalogueEventAddress;
    case 21:
        return g_Frontend_DispatchMatchOptionsEventAddress;
    case 23:
        return g_Join_DispatchJoinOptionsEventAddress;
    case 14:
        return g_Frontend_DispatchMatchMenuEventAddress;
    case 19:
        return g_Frontend_DispatchPakProfileEventAddress;
    case 22:
        return g_Frontend_DispatchTabOptionsEventAddress;
    case 24:
        return g_Frontend_DispatchProfileResetEventAddress;
    case 25:
        return g_Menu_DispatchOptionsTransitionEventAddress;
    case 27:
        return g_Menu_DispatchSixChoiceEventAddress;
    case 26:
        return g_Frontend_DispatchPlayerCountEventAddress;
    case 29:
        return g_SmpOverlay_DispatchPakDialogEventAddress;
    case 28:
        return g_Menu_DispatchExtraOptionsEventAddress;
    case 33:
        return g_Frontend_DispatchNodePairMenuEventAddress;
    default:
        return 0;
    }
}
