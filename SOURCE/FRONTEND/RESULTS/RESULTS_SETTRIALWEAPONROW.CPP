#include "include_asm.h"
#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
#include "FRONTEND/RESULTSOPTIONSSCREEN.H"
#include "COMMON/RESULTSOPTIONSSCREEN.H"
#include "FRONTEND/RESULTS_GETWEAPONICONVALUE.H"

/* Finds a menu item identifier in three selection tables, falling back to the first item of the second table. */
extern int g_loadoutWeaponItems[];

extern int g_loadoutColumnOneItems[];

extern int g_loadoutColumnFourItems[];

void Results_SetTrialWeaponRow(u32 row, s32 weaponId, s32 amount) {
    s32 id;
    MenuWidget *element;
    MenuWidget *field;
    s32 value;

    switch (row) {
    case 0:
        id = 479 + ID_SHIFT;
        if (amount == 0) {
            id = 329 + OPTION_SHIFT;
        }
        break;
    case 1:
        id = 480 + ID_SHIFT;
        if (amount == 0) {
            id = 332 + OPTION_SHIFT;
        }
        break;
    case 2:
        id = 481 + ID_SHIFT;
        if (amount == 0) {
            id = 333 + OPTION_SHIFT;
        }
        break;
    case 3:
        id = 482 + ID_SHIFT;
        if (amount == 0) {
            id = 334 + OPTION_SHIFT;
        }
        break;
    case 4:
        id = 483 + ID_SHIFT;
        if (amount == 0) {
            id = 335 + OPTION_SHIFT;
        }
        break;
    default:
        id = 329 + OPTION_SHIFT;
        break;
    }
    /* the hub's Item view shares the MenuWidget prefix; this unit reads alpha and value through it */
    element = (MenuWidget *) Node_FindWidgetByResourceId(g_trialCatalogueScreen->root, id);
    Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(element, 331 + OPTION_SHIFT), 0);
    value = Results_GetWeaponIconValue(weaponId);
    field = (MenuWidget *) Node_FindWidgetByResourceId(element, 330 + OPTION_SHIFT);
    field->alpha = 100;
    field->value = value;
}

int Results_GetWeaponIconValue(int id) {
 int i;
 for(i=0;i<8;i++) if(g_loadoutWeaponIds[i*4]==id) return g_loadoutWeaponItems[i*4];
 for(i=0;i<4;i++) if(g_trialBonusWeaponIds[i*4]==id) return g_loadoutColumnOneItems[i*4];
 for(i=0;i<3;i++) if(g_trialSpecialWeaponIds[i*4]==id) return g_loadoutColumnFourItems[i*4];
 return g_loadoutColumnOneItems[0];
}
