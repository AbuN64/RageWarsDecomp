#include "COMMON/RESULTSOPTIONSSCREEN.H"
#include "TYPES.H"
#include "FRONTEND/ENTRYRECAT4D4.H"
#include "FRONTEND/RESULTS_MARKLINKEDTRIALSAVAILABLE.H"
#include "ACHIEVE/ACHIEVE.H"
#include "COMMON/SHARED_GAMESLOT.H"
#define g_gameSettingsView (*(struct GameSettingsModeStatusView *)&g_gameSettings)

/* Grants unowned unlocks for the completed game using its mode and player kind; an unsigned local carries the globals address before the category value to preserve register scheduling, and the default kind calls the table selector directly. */









extern s8 g_activeProfileCharacterSelections[]; /* MIXED: this unit views g_gameSettings as GameSettingsModeStatusView */
extern struct ScreenFrontendMarkLinkedTrialsAvailable *g_trialCatalogueScreen;
extern s32 Defs_TestBit(void *bitArray, s32 index);
extern void Defs_SetBitValue(u8 *, s32, s32);

void Results_MarkLinkedTrialsAvailable(void *trialBits) {
    struct GameSettingsModeStatusView *globals;
    struct TableFrontendMarkLinkedTrialsAvailable *table;
    unsigned int category;
    s32 kind;
    s32 value;
    s32 i;

    category=(unsigned int)&g_gameSettingsView;
    globals=(struct GameSettingsModeStatusView *)category;
    switch (globals->mode) {
    case 1:
        kind = globals->status[g_trialCatalogueScreen->player].kind;
        category = 0;
        break;
    case 2:
        category = 1;
        kind = 0;
        break;
    case 3:
        category = 3;
        kind = 0;
        break;
    case 4:
        category = 2;
        kind = 0;
        break;
    default:
        kind = g_activeProfileCharacterSelections[g_trialCatalogueScreen->player * 150];
        table = Achieve_CopyPreset(trialBits,0,kind);
        goto selected;
        break;
    }
    table = Achieve_CopyPreset(trialBits, category, kind);
selected:
    if ((value = table->first) > 0) {

        if (Defs_TestBit(g_trialCatalogueScreen->owned, value-1) == 0) {
            Defs_SetBitValue(g_trialCatalogueScreen->unlocked, value-1, 1);
        }
    }
    for (i = 0; i < 3; i++) {
        if ((value = table->items[i]) > 0) {

            if (Defs_TestBit(g_trialCatalogueScreen->owned, value-1) == 0) {
                Defs_SetBitValue(g_trialCatalogueScreen->unlocked, value-1, 1);
            }
        }
    }
}
