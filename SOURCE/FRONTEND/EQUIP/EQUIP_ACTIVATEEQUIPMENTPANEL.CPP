#include "FRONTEND/NODE_FINDWIDGETBYRESOURCEID.H"
#include "include_asm.h"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "FRONTEND/ENTRYRECAT4D4.H"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "FRONTEND/MENU_IMAGE.H"
#include "FRONTEND/EQUIP_ACTIVATEEQUIPMENTPANEL.H"
#include "FRONTEND/WIDGET_FINDWIDGETATPOINT.H"
#include "COMMON/PLAYERPROFILES.H"
#include "COMMON/SHARED_GAMESLOT.H"
#define g_gameSettingsView (*(HudStatusShared_Settings *)&g_gameSettings)

/* Moves player p's column cursor on the screen g_equipmentAndResultsScreen: fades the shown item of the current
   column (g_equipmentSecondaryWidgetIds[p][column]) to alpha 0x23, calls Widget_SetWidgetFlag08_EquipActivateequipmentpanel(0) on the item g_equipmentPrimaryWidgetIds[p][column]
   unless the column is 5, then steps the column back for direction 1 (0 wraps to 5, and in mode 1
   at 0x4D4 anything above 2 becomes 2) or forward otherwise (5 wraps to 0, and in mode 1 anything
   past 2 becomes 5), and redraws through Frontend_SelectEquipmentColumn. */











extern struct StateFlags g_equipmentPrimaryWidgetIds[][19];

extern void Widget_SetWidgetFlag08(void *object, int enabled);
extern FourPlayerResultsScreen *g_equipmentAndResultsScreen;


typedef struct EquipEntry {
    s32 item;
    s32 resource;
    s32 kind;
    s32 *label;
} EquipEntry;
extern EquipEntry g_loadoutWeaponItems[];



extern s32 Player_HasProfileUnlockFlag(u8 *profileBytes, s32 unlockIndex);

/* Enters player p's loadout panel on the screen g_equipmentAndResultsScreen: marks the entry open, hides the panel
   item g_equipmentPanelWidgetIds[p][0], then by the entry's mode at 0x4D4 either hides column item
   g_equipmentOptionWidgetIds[p][5] and fades label g_equipmentSecondaryWidgetIds[p][5] to alpha 0x23 (mode 0), or for each of the
   3 (mode 1) or 6 (mode 2 and any other) columns hides g_equipmentOptionWidgetIds[p][c], fades g_equipmentSecondaryWidgetIds[p][c]
   to 0x23 and redraws the column through Equip_ShowEquipChoice with the entry's value; mode 1 then also
   hides column 5's item, fades its label and hides the entry's item. Finally it hides the five
   g_equipmentPrimaryWidgetIds[p] items at alpha 0x37 and shows the selected column's label at alpha 0x96 through
   Widget_SetWidgetFlag40_EquipActivateequipmentpanel. */











void Equip_MoveEquipmentColumn(s32 player, s32 direction) {
    MenuWidget *item;
    s32 column;

    column = g_equipmentAndResultsScreen->panels[player].selection;
    item = Node_FindWidgetByResourceId(g_equipmentAndResultsScreen->window, g_equipmentSecondaryWidgetIds[player][column].value);
    Widget_SetWidgetFlag40(item, 0);
    item->alpha = 35;
    if (column != 5) {
        Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_equipmentAndResultsScreen->window, g_equipmentPrimaryWidgetIds[player][column].value), 0);
    }
    if (direction == 1) {
        if (column == 0) {
            column = 5;
        } else {
            column--;
            if (g_equipmentAndResultsScreen->panels[player].mode == 1 && column >= 3) {
                column = 2;
            }
        }
    } else {
        if (column == 5) {
            column = 0;
        } else {
            column++;
            if (g_equipmentAndResultsScreen->panels[player].mode == 1 && column >= 3) {
                column = 5;
            }
        }
    }
    Frontend_SelectEquipmentColumn(player, column);
}

/* Step an equipment choice, rejecting duplicates and the locked item 15. */
void Equip_CycleEquipmentChoice(s32 player, s32 step) {
    s32 count;
    s32 low;
    s32 high;
    s32 category;
    s32 value;
    s32 valid;
    s32 i;

    if (g_equipmentAndResultsScreen->panels[player].mode == 2) {
        count = 0;
        low = 0;
        high = 0;
        category = g_equipmentAndResultsScreen->panels[player].selection;
        switch (category) {
        case 0:
        case 1:
            count = 4;
            low = 0;
            high = 1;
            break;
        case 2:
        case 3:
            count = 8;
            low = 2;
            high = 3;
            break;
        case 4:
            count = 3;
            low = 4;
            high = 4;
            break;
        case 5:
            return;
        }
        value = g_equipmentAndResultsScreen->panels[player].values[category];
        value += step;
        do {
            if (value >= count) {
                value = 0;
            }
            if (value < 0) {
                value = count - 1;
            }
            valid = 1;
            for (i = low; i < high + 1; i++) {
                if (valid != 1) {
                    break;
                }
                if (g_equipmentAndResultsScreen->panels[player].values[i] == value) {
                    value += step;
                    valid = 0;
                }
            }
            if (valid == 1 && (category == 2 || category == 3) &&
                g_loadoutWeaponItems[value].kind == 15 &&
                !(g_gameSettingsView.flags & 0x10000000) &&
                !Player_HasProfileUnlockFlag((intptr_t)&g_localPlayerProfiles[player], 15)) {
                value += step;
                valid = 0;
            }
        } while (!valid);
        Equip_ShowEquipChoice(player, category, value);
        g_equipmentAndResultsScreen->panels[player].values[category] = value;
    }
}

void Equip_ActivateEquipmentPanel(s32 player) {
    MenuWidget *item;
    s32 i;

    g_equipmentAndResultsScreen->panels[player].state = 1;
    Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_equipmentAndResultsScreen->window, g_equipmentPanelWidgetIds[player][0].value), 0);
    switch (g_equipmentAndResultsScreen->panels[player].mode) {
    case 0:
        Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_equipmentAndResultsScreen->window, g_equipmentOptionWidgetIds[player][5].value), 0);
        item = Node_FindWidgetByResourceId(g_equipmentAndResultsScreen->window, g_equipmentSecondaryWidgetIds[player][5].value);
        Widget_SetWidgetFlag08(item, 1);
        item->alpha = 35;
        break;
    case 1:
        for (i = 0; i < 3; i++) {
            Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_equipmentAndResultsScreen->window, g_equipmentOptionWidgetIds[player][i].value), 0);
            item = Node_FindWidgetByResourceId(g_equipmentAndResultsScreen->window, g_equipmentSecondaryWidgetIds[player][i].value);
            Widget_SetWidgetFlag08(item, 1);
            item->alpha = 35;
            Equip_ShowEquipChoice(player, i, g_equipmentAndResultsScreen->panels[player].values[i]);
        }
        Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_equipmentAndResultsScreen->window, g_equipmentOptionWidgetIds[player][5].value), 0);
        item = Node_FindWidgetByResourceId(g_equipmentAndResultsScreen->window, g_equipmentSecondaryWidgetIds[player][5].value);
        Widget_SetWidgetFlag08(item, 1);
        item->alpha = 35;
        Widget_SetWidgetFlag08(g_equipmentAndResultsScreen->panels[player].item, 0);
        break;
    case 2:
    default:
        for (i = 0; i < 6; i++) {
            Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_equipmentAndResultsScreen->window, g_equipmentOptionWidgetIds[player][i].value), 0);
            item = Node_FindWidgetByResourceId(g_equipmentAndResultsScreen->window, g_equipmentSecondaryWidgetIds[player][i].value);
            Widget_SetWidgetFlag08(item, 1);
            item->alpha = 35;
            Equip_ShowEquipChoice(player, i, g_equipmentAndResultsScreen->panels[player].values[i]);
        }
        break;
    }
    for (i = 0; i < 5; i++) {
        item = Node_FindWidgetByResourceId(g_equipmentAndResultsScreen->window, g_equipmentPrimaryWidgetIds[player][i].value);
        Widget_SetWidgetFlag08(item, 0);
        item->alpha = 55;
    }
    item = Node_FindWidgetByResourceId(g_equipmentAndResultsScreen->window,
                         g_equipmentSecondaryWidgetIds[player][g_equipmentAndResultsScreen->panels[player].selection].value);
    Widget_SetWidgetFlag40(item, 1);
    item->alpha = 150;
}

/* Redraws player p's equipment row for the chosen column: shows the panel item, picks the column's
   table (mode 1: columns 0/1/2 -> g_loadoutColumnOneItems/g_loadoutWeaponItems/g_loadoutColumnFourItems; otherwise 0-1, 2-3, 4), writes
   the choice's item into the column widget's kind-3 child, sets the badge and the panel label (per
   language on EU); column 5 or out of range clears the badge and hides the item. */
extern int g_loadoutColumnOneItems[];
extern int g_loadoutColumnFourItems[];
extern s32 Model_SetPreviewModel(struct RecordFrontendSetPreviewModel *record, s32 count);
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#endif
void Equip_ShowEquipChoice(s32 player, s32 category, s32 choice)
{
    EquipEntry *table;
    MenuWidget *node;
    s32 found;

    if (g_equipmentAndResultsScreen->panels[player].mode == 0) {
        return;
    }
    Widget_SetWidgetFlag08(g_equipmentAndResultsScreen->panels[player].item, 1);
    if (g_equipmentAndResultsScreen->panels[player].mode == 1) {
        switch (category) {
        case 0:
            table = g_loadoutColumnOneItems;
            break;
        case 1:
            table = g_loadoutWeaponItems;
            break;
        case 2:
            table = g_loadoutColumnFourItems;
            break;
        default:
            Model_SetPreviewModel(g_equipmentAndResultsScreen->badges[player], 0);
            Widget_SetWidgetFlag08(g_equipmentAndResultsScreen->panels[player].item, 0);
            return;
        }
    } else {
        switch (category) {
        case 0:
        case 1:
            table = g_loadoutColumnOneItems;
            break;
        case 2:
        case 3:
            table = g_loadoutWeaponItems;
            break;
        case 4:
            table = g_loadoutColumnFourItems;
            break;
        case 5:
        default:
            Model_SetPreviewModel(g_equipmentAndResultsScreen->badges[player], 0);
            Widget_SetWidgetFlag08(g_equipmentAndResultsScreen->panels[player].item, 0);
            return;
        }
    }
    if (table) {
        node = Node_FindWidgetByResourceId(g_equipmentAndResultsScreen->window, g_equipmentSecondaryWidgetIds[player][category].value)->child;
        found = 0;
        do {
            if (node->kind == 3) {
                node->value = table[choice].item;
                found = 1;
            } else {
                node = node->sibling;
            }
        } while (!found);
        Model_SetPreviewModel(g_equipmentAndResultsScreen->badges[player], table[choice].resource);
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        g_equipmentAndResultsScreen->panels[player].item->word38 = table[choice].label[g_languageIndex];
#else
        g_equipmentAndResultsScreen->panels[player].item->word38 = *table[choice].label;
#endif
    }
}
