#include "TYPES.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "COMMON/RESULTSOPTIONSSCREEN.H"
#include "COMMON/STATERECAT91.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "FRONTEND/RESULTSOPTIONSSCREEN.H"
#include "FRONTEND/ENTRYRECAT4D4.H"
#include "ACHIEVE/ACHIEVE.H"

extern s32 Defs_TestBit(void *, s32);
void Results_SelectSuggestedTrial(void) {
    CGameStatus *state;
    Shared_Game *config;
    Preset *preset;
    s32 value, choice, i;
    g_trialCatalogueScreen->selection = g_selectedLevelId;
    if (g_trialCatalogueScreen->selection >= 37) g_trialCatalogueScreen->selection = 0;
    if (Defs_TestBit(g_trialCatalogueScreen->owned, g_trialCatalogueScreen->selection) != 0) {
        state = &g_gameSettings.counters;
        if (state->humanWon != 0) {
            /* The counters alias Game+0x5D8 in every version. */
            { void *whole = (u8 *)state - ((char *)&((Shared_Game *)0)->counters - (char *)0); config = whole; }
            switch (config->controllerMode) {
            case 1:
                preset = Achieve_CopyPreset(g_trialCatalogueScreen->selection, 0, config->slots[g_trialCatalogueScreen->player].kind);
                break;
            case 2:
                preset = Achieve_CopyPreset(g_trialCatalogueScreen->selection, 1, 0);
                break;
            case 3:
                preset = Achieve_CopyPreset(g_trialCatalogueScreen->selection, 3, 0);
                break;
            case 4:
                preset = Achieve_CopyPreset(g_trialCatalogueScreen->selection, 2, 0);
                break;
            default:
                preset = Achieve_CopyPreset(g_trialCatalogueScreen->selection, 0, g_gameSettings.playerSettings[g_trialCatalogueScreen->player].character);
                break;
            }
            choice = 0;
            if ((value = preset->bytes[1]) > 0) {
                choice = value - 1;
            } else {
                for (i = 0; i < 3; i++) {
                    if ((value = (preset->bytes + i)[2]) > 0) {
                        choice = value - 1;
                        break;
                    }
                }
            }
            if (choice >= 37) choice = 0;
            g_trialCatalogueScreen->selection = choice;
        }
    }
}
