#include "Frontend/node_findwidgetbyresourceid.h"
#include "include_asm.h"
#include "Common/Lone/g_languageindex.h"
#include "Frontend/results_player_panels.h"
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
#include "Frontend/menu_image.h"
#include "Frontend/equip_activateequipmentpanel.h"
#include "Frontend/widget_findwidgetatpoint.h"
#include "Common/playerprofiles.h"
#include "Common/shared_gameslot.h"
#include "Common/selectionscreenstate.h"
#include "World/playerprofile.h"
#include "Achieve/modelpreviewscreen.h"
#include "Pakinterfacescreen/ovl1_j.h"
#include "Frontend/frontend_address_symbols.h"
#include "Frontend/equip_loadequipmentselections.h"
#include "Common/gameplay_settings.h"
#include "Common/menu_overlay.h"
#include "Common/label.h"
#include "Common/resident_event_handler.h"
#include "Common/screen.h"
#include "Common/player_join_requests.h"
#include "Smp_overlay/smp_overlay.h"
#include "Preview/frontend_drawmodelpreview.h"
#include "Frontend/frontend.h"

/* unit EQUIP_ACTIVATEEQUIPMENTPANEL.CPP */

/* Moves player p's column cursor on the screen g_equipmentAndResultsScreen: fades the shown item of the current
   column (g_equipmentSecondaryWidgetIds[p][column]) to alpha 0x23, calls Widget_SetWidgetFlag08_EquipActivateequipmentpanel(0) on the item g_equipmentPrimaryWidgetIds[p][column]
   unless the column is 5, then steps the column back for direction 1 (0 wraps to 5, and in mode 1
   at 0x4D4 anything above 2 becomes 2) or forward otherwise (5 wraps to 0, and in mode 1 anything
   past 2 becomes 5), and redraws through Frontend_SelectEquipmentColumn. */



typedef struct EquipEntry {
    s32 item;
    s32 resource;
    s32 kind;
    s32 *label;
} EquipEntry;

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
                g_loadoutWeaponItems[value].weapon == 15 &&
                !(g_gameSettings.flags & 0x10000000) &&
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
   table (mode 1: columns 0/1/2 -> g_loadoutBonusWeaponItems/g_loadoutWeaponItems/g_loadoutSpecialWeaponItems; otherwise 0-1, 2-3, 4), writes
   the choice's item into the column widget's kind-3 child, sets the badge and the panel label (per
   language on EU); column 5 or out of range clears the badge and hides the item. */
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
            table = g_loadoutBonusWeaponItems;
            break;
        case 1:
            table = g_loadoutWeaponItems;
            break;
        case 2:
            table = g_loadoutSpecialWeaponItems;
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
            table = g_loadoutBonusWeaponItems;
            break;
        case 2:
        case 3:
            table = g_loadoutWeaponItems;
            break;
        case 4:
            table = g_loadoutSpecialWeaponItems;
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

/* unit EQUIP.CPP */
/* Fills player p's column values on the screen g_equipmentAndResultsScreen from what the player owns: unless the
   entry's mode word (0x4D4) is 0, it scans the 4 rows of g_loadoutBonusWeaponItems for column 1, the 3 rows of
   g_loadoutSpecialWeaponItems for column 4 and the 8 rows of g_loadoutWeaponItems for column 5, and writes the index of each
   row whose item is marked owned in the weapons flags of the player's settings record into the
   entry's next value slot (0x4B8 plus four per slot), starting at slot 0, 4 and 2, or at 0, 2 and
   1 in mode 1. */


void Equip_LoadEquipmentSelections(s32 player) {
    struct LoadoutWeaponItem *source;
    Shared_PlayerSettingsRecord *record;
    s32 column;
    s32 count;
    s32 slot;
    s32 i;

    if (g_equipmentAndResultsScreen->panels[player].mode == 0) {
        return;
    }
    record = &g_playerSettings[player];
    for (column = 0; column < 8; column++) {
        if (g_equipmentAndResultsScreen->panels[player].mode == 1) {
            switch (column) {
            case 1:
                source = g_loadoutBonusWeaponItems;
                count = 4;
                slot = 0;
                break;
            case 4:
                source = g_loadoutSpecialWeaponItems;
                count = 3;
                slot = 2;
                break;
            case 5:
                source = g_loadoutWeaponItems;
                count = 8;
                slot = 1;
                break;
            default:
                continue;
            }
        } else {
            switch (column) {
            case 1:
                source = g_loadoutBonusWeaponItems;
                count = 4;
                slot = 0;
                break;
            case 4:
                source = g_loadoutSpecialWeaponItems;
                count = 3;
                slot = 4;
                break;
            case 5:
                source = g_loadoutWeaponItems;
                count = 8;
                slot = 2;
                break;
            default:
                continue;
            }
        }
        for (i = 0; i < count; i++) {
            if (record->weapons[source[i].weapon] == 1) {
                g_equipmentAndResultsScreen->panels[player].values[slot++] = i;
            }
        }
    }
}


/* Rebuilds the loadout of every active player whose entry on the screen g_equipmentAndResultsScreen is in mode 2:
   clears the 22 owned flags and equipped levels of the player's settings record, then for columns 0 and 1 (16-byte table g_loadoutBonusWeaponItems, level column + 1), 2 and 3
   (g_loadoutWeaponItems, level column + 3) and 4 (g_loadoutSpecialWeaponItems, level 4) marks the item of the row the entry's
   value for that column selects as owned at that level, and finally marks item 0 owned at level
   0. */
void Equip_ApplySelectedPlayerLoadouts(void) {
    Shared_PlayerSettingsRecord *record;
    struct LoadoutWeaponItem *source;
    struct LoadoutWeaponItem *row;
    s32 level;
    s32 item;
    s32 i;
    s32 column;

    for (i = 0; i < 4; i++) {
        record = &g_playerSettings[i];
        if (record->enabled != 1) {
            continue;
        }
        if (g_equipmentAndResultsScreen->panels[i].mode != 2) {
            continue;
        }
        for (column = 0; column < 22; column++) {
            record->weapons[column] = 0;
            record->loadoutLevels[column] = 0;
        }
        for (column = 0; column < 6; column++) {
            switch (column) {
            case 0:
            case 1:
                source = g_loadoutBonusWeaponItems;
                level = column + 1;
                break;
            case 4:
                source = g_loadoutSpecialWeaponItems;
                level = 4;
                break;
            case 2:
            case 3:
                source = g_loadoutWeaponItems;
                level = column + 3;
                break;
            default:
                continue;
            }
            item = source[g_equipmentAndResultsScreen->panels[i].values[column]].weapon;
            row = source + g_equipmentAndResultsScreen->panels[i].values[column];
            record->weapons[item] = 1;
            record->loadoutLevels[row->weapon] = level;
        }
        record->weapons[0] = 1;
        record->loadoutLevels[0] = 0;
    }
}

/* unit G_EQUIPMENTSELECTIONRETAINEDDATA.CPP */
#if defined(VERSION_US_REV1)
unsigned int g_GEquipmentselectionretaineddataWords[3] = {
    0x00000000, 0x00000010, 0x00000008,
};
#endif

#ifdef VERSION_EU
const unsigned int g_equipmentSelectionRetainedData[3] = {
    0x4B6A5B31, 0x4B005B72, 0x4A0A6744,
};
#endif
#ifdef VERSION_US
const unsigned int g_equipmentSelectionRetainedData[3] = {
    0x73520000, 0x00000000, 0x0F000A00,
};
#endif

/* unit FRONTEND_CONFIRMEQUIPMENTSELECTION.CPP */
s32 Frontend_ConfirmEquipmentSelection(void *element, void *eventId, s32 event) {
    u8 *settings;
    s32 player;
    s32 i;
    s32 delay;
    FourPlayerResultsScreen *screen;
    player = event & 0xFFFF;
    MarkMenuEventHandled();
    if (g_equipmentAndResultsScreen->panels[player].state != 1) return 0;
    if (g_equipmentAndResultsScreen->panels[player].selection != 5) return 0;
    {
        g_equipmentAndResultsScreen->panels[player].state = 2;
        SmpOverlay_SetSlotValue(g_equipmentAndResultsScreen->menu, player, 1);
        for (i = 0; i < 6; i++) {
            Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_equipmentAndResultsScreen->window, g_equipmentOptionWidgetIds[player][i].value), 1);
        }
        Key_FindKeyIndex(g_gameSettings.playerSettings[player].character);
        settings = (u8 *)&g_equipmentAndResultsScreen->panels[player].previewTransform;
        {
            void *panel = settings;
            settings = (u8 *)g_playerSettings;
            Preview_SetPreviewTransformUpdate(panel, 0);
        }
        if (Frontend_CountActiveEquipmentPanels() != 0) return 0;
        {
            Equip_ApplySelectedPlayerLoadouts();
            screen = g_equipmentAndResultsScreen;
            screen->state = 5;
            screen->timer = 4;
            switch (settings[(u8 *)&g_gameSettings.controllerMode -
                             (u8 *)g_gameSettings.playerSettings]) {
            case 0: delay = 20; break;
            case 3: delay = 10; break;
            case 2: delay = 15; break;
            default: return 0;
            }
            screen->next = delay;
        }
    }
    return 0;
}
