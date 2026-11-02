#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/WORLD.H"
#include "COMMON/RESULTSOPTIONSSCREEN.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "TYPES.H"
#include "FRONTEND/ENTRYRECAT4D4.H"
#include "FRONTEND/RESULTS_FILLPROFILEWEAPONROWS.H"
#include "FRONTEND/CTRIALCATALOGUE_SHOWTRIALOPTIONCHILDREN.H"
#include "FRONTEND/RESULTS.H"
extern ResultsOptionsScreen *g_trialCatalogueScreen;

/* Formats the name of entry g_trialCatalogueScreen's word at 0xA44 into a local 0x40-byte buffer through
   Scene_CopyLevelName from g_world_AchieveUpdateresultsscreen, passes the length XPlus_UppercaseString measures to XPlus_CopyString_ResultsFillprofileweaponrows for the
   text object at offset 0xA04, and points word 0x38 of the object at 0x998 to that text object. */






extern void Scene_CopyLevelName(struct Shared_World *world, s32 type, void *levelName, s32 maximumBytes);

extern u8 *XPlus_UppercaseString(u8 *string);

extern u8 *XPlus_CopyString(u8 *destination, u8 *source);

/* Returns the index of the entry among the 0x24 28-byte entries of g_trialCatalogueStages whose identifier
   matches, or zero when none does. */


extern struct ProfileWeaponRowEntry g_trialCatalogueStages[];

/* Returns one when the two arguments are equal or when any of the sixty-four 12-byte pairs of g_arenaCompatibilityTable holds exactly that ordered pair, zero otherwise.
   Adapted from Key_GetCharacterPreviewModel with the single-key slot scan changed to an ordered-pair lookup over 64 twelve-byte entries. */




/* Sets the byte at offset 0x10 of the two objects at offsets 0xA64 and 0xA60 of the structure g_trialCatalogueScreen
   points to to 0xFF, shows both through Widget_SetWidgetFlag08_EquipActivateequipmentpanel and clears the word at 0xA68. */







extern void Widget_SetWidgetFlag08(void *object, int enabled);

/* Reports every set entry of each ready slot to the handler, stopping after two slots. */







extern void Results_SetTrialWeaponRow(u32, s32, s32);

/* Rebuilds the item list for the player g_trialCatalogueScreen selects: clears it through CTrialCatalogue_ShowTrialOptionChildren, looks
   up that player's model in g_world_AchieveUpdateresultsscreen, and for each of the model's eight slot ids at 0x4C that is
   at least 0x4C3 adds the nonzero id less 0x4C3 as the next row through Results_SetTrialWeaponRow when
   Player_HasProfileUnlockFlag accepts it for the player's 400-byte record in g_localPlayerProfiles. */








extern char g_localPlayerProfiles[];

extern struct Model *Scene_FindActorDefinition(Shared_World *, s32, s32);

extern s32 Player_HasProfileUnlockFlag(u8 *profileBytes, s32 unlockIndex);

/* Rebuilds the weapon menu for the player g_trialCatalogueScreen selects: clears it through CTrialCatalogue_ShowTrialOptionChildren, then
   for each of the 0x16 weapon ids (excluding id 0) whose owned flag in g_gameSettings (offset 0x11C,
   player stride 0x96) is set, appends a row through Results_SetTrialWeaponRow. */







extern void Results_SetTrialWeaponRow(u32 row, s32 weaponId, s32 amount);

/* Enumerates the eight item identifiers of the record Scene_GetBlLevelData finds for a key and registers each nonzero identifier above 0x4C3 through Results_SetTrialWeaponRow, translated by 0x4C3 and numbered in order. */





extern RecordFrontendFillTrialPresetWeaponRows *Scene_GetBlLevelData(void *table, s32 key);

extern void Results_SetTrialWeaponRow(u32 slot, s32 item, s32 amount);

void Results_RefreshTrialSelectionLabel(void) {
    char buffer[64];

    Scene_CopyLevelName(&g_world, g_trialCatalogueScreen->selection, buffer, 63);
    XPlus_CopyString(g_trialCatalogueScreen->text, XPlus_UppercaseString(buffer));
    g_trialCatalogueScreen->owner->text = g_trialCatalogueScreen->text;
}

s32 Results_FindTrialValueIndex(s32 id) {
    s32 i;

    for (i = 0; i < 36; i++) {
        if (g_trialCatalogueStages[i].value == id) {
            return i;
        }
    }
    return 0;
}

s32 Results_IsUnlockLinked(s32 a, s32 b) {
    s32 i;

    if (a == b) {
        return 1;
    }
    for (i = 0; i < 64; i++) {
        if (g_arenaCompatibilityTable[i].a == a && g_arenaCompatibilityTable[i].b == b) {
            return 1;
        }
    }
    return 0;
}

void Results_ShowTrialPreviewBanner(void) {
    (g_trialCatalogueScreen->banner)->alpha = 0xFF;
    (g_trialCatalogueScreen->bannerShadow)->alpha = 0xFF;
    Widget_SetWidgetFlag08(g_trialCatalogueScreen->bannerShadow, 1);
    Widget_SetWidgetFlag08(g_trialCatalogueScreen->banner, 1);
    g_trialCatalogueScreen->blinking = 0;
}

void Results_FillTwoPlayerWeaponRows(void) {
    Shared_Game *st;
    s32 n;
    s32 k;
    s32 i;
    Shared_Game *base;
    s32 j;

    k = 0;
    st = &g_gameSettings;
    for (n = 0; n < 4; n++) {
        if (st->playerSettings[n].enabled == 1) {
            j = 0;
            for (i = 0; i < 22; i++) {
                if (((base = &g_gameSettings)->playerSettings[n].weapons[i] == 1) && (i != 0)) {
                    Results_SetTrialWeaponRow(j, i, k);
                    j++;
                }
            }
            k++;
            if (k >= 2) {
                return;
            }
        }
    }
}

void Results_FillProfileWeaponRows(void) {
    struct Model *model;
    s32 player;
    s32 id;
    s32 row;
    s32 i;

    CTrialCatalogue_ShowTrialOptionChildren();
    player = g_trialCatalogueScreen->player;
    model = Scene_FindActorDefinition(&g_world, 11, g_gameSettings.playerSettings[player].character);
    row = 0;
    for (i = 0; i < 8; i++) {
        id = model->slots[i];
        if (id >= 1219) {
            id -= 1219;
            if (Player_HasProfileUnlockFlag(&g_localPlayerProfiles[player * 400], id) == 1 && id != 0) {
                Results_SetTrialWeaponRow(row, id, 0);
                row++;
            }
        }
    }
}

void Results_FillSelectedPlayerWeaponRows(void) {
    s32 count;
    s32 weapon;
    s32 base;

    CTrialCatalogue_ShowTrialOptionChildren();
    count = 0;
    base = g_trialCatalogueScreen->player * 150;
    for (weapon = 0; weapon < 22; weapon++) {
        if (((ProfileWeaponOwnedView *)(weapon + base + (u8 *)&g_gameSettings))->owned == 1) {
            if (weapon != 0) {
                Results_SetTrialWeaponRow(count, weapon, 0);
                count += 1;
            }
        }
    }
}

void Results_FillTrialPresetWeaponRows(s32 key) {
    RecordFrontendFillTrialPresetWeaponRows *record;
    s32 count;
    s32 i;
    s32 item;

    CTrialCatalogue_ShowTrialOptionChildren();
    record = Scene_GetBlLevelData(&g_world, key);
    count = 0;
    for (i = 0; i < 8; i++) {
        item = record->items[i];
        if (item >= 1219) {
            item -= 1219;
            if (item != 0) {
                Results_SetTrialWeaponRow(count, item, 0);
                count++;
            }
        }
    }
}
