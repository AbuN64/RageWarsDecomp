#include "include_asm.h"
#include "COMMON/SHAREDPLAYER.H"
#include "FRONTEND/ENTRYRECAT4D4.H"
#include "TYPES.H"
#include "FRONTEND/EQUIP_LOADEQUIPMENTSELECTIONS.H"

/* Fills player p's column values on the screen g_equipmentAndResultsScreen from what the player owns: unless the
   entry's mode word (0x4D4) is 0, it scans the 4 rows of g_loadoutColumnOneItems for column 1, the 3 rows of
   g_loadoutColumnFourItems for column 4 and the 8 rows of g_loadoutWeaponItems for column 5, and writes the index of each
   row whose item is marked owned at 0x4C of the player's 150-byte record in g_playerSettings_Achieve into the
   entry's next value slot (0x4B8 plus four per slot), starting at slot 0, 4 and 2, or at 0, 2 and
   1 in mode 1. */







extern struct ScreenFrontendLoadEquipmentSelections *g_equipmentAndResultsScreen;
extern u8 g_playerSettings[];
extern int g_loadoutColumnOneItems[];
extern int g_loadoutColumnFourItems[];
extern struct CacheResourceBlockView g_loadoutWeaponItems[];

void Equip_LoadEquipmentSelections(s32 player) {
    struct CacheResourceBlockView *source;
    u8 *record;
    s32 column;
    s32 count;
    s32 slot;
    s32 i;

    if (g_equipmentAndResultsScreen->entries[player].mode == 0) {
        return;
    }
    record = &g_playerSettings[player * 150];
    for (column = 0; column < 8; column++) {
        if (g_equipmentAndResultsScreen->entries[player].mode == 1) {
            switch (column) {
            case 1:
                source = g_loadoutColumnOneItems;
                count = 4;
                slot = 0;
                break;
            case 4:
                source = g_loadoutColumnFourItems;
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
                source = g_loadoutColumnOneItems;
                count = 4;
                slot = 0;
                break;
            case 4:
                source = g_loadoutColumnFourItems;
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
            if ((record + source[i].third)[76] == 1) {
                g_equipmentAndResultsScreen->entries[player].values[slot++] = i;
            }
        }
    }
}

#include "TYPES.H"

/* Rebuilds the loadout of every active player whose entry on the screen g_equipmentAndResultsScreen is in mode 2:
   clears the 22 owned bytes at 0x4C and level bytes at 0x62 of the player's 150-byte record in
   g_playerSettings_Achieve, then for columns 0 and 1 (16-byte table g_loadoutColumnOneItems, level column + 1), 2 and 3
   (g_loadoutWeaponItems, level column + 3) and 4 (g_loadoutColumnFourItems, level 4) marks the item of the row the entry's
   value for that column selects as owned at that level, and finally marks item 0 owned at level
   0. */

void Equip_ApplySelectedPlayerLoadouts(void) {
    u8 *record;
    struct CacheResourceBlockView *source;
    struct CacheResourceBlockView *row;
    s32 level;
    s32 item;
    s32 i;
    s32 column;

    for (i = 0; i < 4; i++) {
        record = &g_playerSettings[i * 150];
        if (record[120] != 1) {
            continue;
        }
        if (g_equipmentAndResultsScreen->entries[i].mode != 2) {
            continue;
        }
        for (column = 0; column < 22; column++) {
            (record + column)[76] = 0;
            (record + column)[98] = 0;
        }
        for (column = 0; column < 6; column++) {
            switch (column) {
            case 0:
            case 1:
                source = g_loadoutColumnOneItems;
                level = column + 1;
                break;
            case 4:
                source = g_loadoutColumnFourItems;
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
            item = source[g_equipmentAndResultsScreen->entries[i].values[column]].third;
            row = source + g_equipmentAndResultsScreen->entries[i].values[column];
            (record + item)[76] = 1;
            (record + row->third)[98] = level;
        }
        record[76] = 1;
        record[98] = 0;
    }
}

