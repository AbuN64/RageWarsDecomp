#include "COMMON/GAMEPLAY_SETTINGS.H"
#include "COMMON/WORLD.H"
#include "include_asm.h"
#include "COMMON/RESULTSOPTIONSSCREEN.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/ARGB_COLOR.H"
#include "FRONTEND/RESULTSOPTIONSSCREEN.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
#include "COMMON/LOADOUT.H"
#include "COMMON/OWNERRECAT8V2.H"
#include "COMMON/GROUP.H"
#include "COMMON/OBJECT_INSTANCE_TRANSFORM_AND_RENDER_VIEWS.H"
#include "COMMON/MANAGER.H"
#include "COMMON/CARTRIDGEREADWORKER.H"
#include "COMMON/OBJRECAT4V6.H"
#include "COMMON/SOUNDVOICEPOOL.H"
#include "COMMON/LIGHTDATA.H"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "COMMON/MTX.H"
#include "COMMON/PARTICLE_ATTACHMENT_AND_OWNER_VIEWS.H"
#include "COMMON/COLORENTRY.H"
#include "COMMON/WORLDSORTENTRY.H"
#include "COMMON/RESULTS.H"
#include "COMMON/OBJRECAT26DD8.H"
#include "COMMON/INTEGERSTATE530.H"
#include "COMMON/OBJRECAT18V6.H"
#include "COMMON/ALBANK_S.H"
#include "COMMON/OBJRECAT18V1.H"
#include "COMMON/ALPARAM_S.H"
#include "COMMON/ALDELAY28.H"
#include "COMMON/OSPIHANDLE_S.H"
#include <ultra64.h>
#include "COMMON/OSVISCALE.H"
#include "COMMON/CTX.H"
#include "COMMON/AUDIO_LOADDECODEDSAMPLES.H"
#include "COMMON/CHEATCODE.H"
#include "COMMON/ENTRYRECAT0V3.H"
#include "COMMON/NODERECAT2A8.H"
#include "COMMON/SLOTRECATCV1.H"
#include "COMMON/TEXTURE.H"
#include "COMMON/LABEL.H"
#include "COMMON/REQUESTRECAT10.H"
#include "COMMON/CHARACTERSELECTIONROOT.H"
#include "COMMON/MENU_INITIALIZEOPTIONSSCENE.H"
#include "COMMON/STATERECAT91.H"
#include "COMMON/SETTINGSRECAT24.H"
#include "COMMON/OBJECTRECAT28.H"
#include "COMMON/PLAYERRECAT64E.H"
#include "COMMON/OBJB.H"
#include "TYPES.H"
#include "COMMON/MEASUREDRECAT0V1.H"
#include "COMMON/MEASURED.H"
#include "COMMON/MEASUREDRECAT14V4.H"
#include "COMMON/MEASUREDRECAT14V2.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/SCENE_FRAME_AND_EFFECT_UPDATES.H"
#include "FRONTEND/RESULTS_REFRESHTRIALCATALOGUEWIDGETS.H"
#include "FRONTEND/RESULTS_MARKLINKEDTRIALSAVAILABLE.H"
#include "ACHIEVE/ACHIEVE.H"
#include "FRONTEND/RESULTS.H"

/* Hides every model named by the sixty-four 12-byte entries of g_arenaCompatibilityTable: for each entry it looks
   up the first and second identifier in the current screen's context at 0x970 through Node_FindWidgetByResourceId
   and disables the object with Widget_SetWidgetFlag08_EquipActivateequipmentpanel, and does the same for the third identifier unless it
   is -1. The identifiers are passed as their low halfword, and the loop walks a manual byte offset
   so the table address is not hoisted. */
/* Read the optional resource as the low half of its word value on every host. */
void Results_HideTrialCatalogueWidgets(void) {
    s32 absentResource;
    s32 byteOffset;
    s32 index;
    index = 0;
    absentResource = -1;
    byteOffset = index;
loop:
    Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_trialCatalogueScreen->root, ((struct Pair *)((u8 *)g_arenaCompatibilityTable + (byteOffset)))->a & 0xFFFF), 0);
    Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_trialCatalogueScreen->root, ((struct Pair *)((u8 *)g_arenaCompatibilityTable + (byteOffset)))->b & 0xFFFF), 0);
    if (((struct Pair *)((u8 *)g_arenaCompatibilityTable + (byteOffset)))->c.id != absentResource) {
        Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_trialCatalogueScreen->root, (u16)*(u32 *)((u8 *)g_arenaCompatibilityTable + byteOffset + 8)), 0);
    }
    index += 1;
    byteOffset += 12;
    if (index < 64) {
        goto loop;
    }
}

extern struct ProfileWeaponRowEntry g_trialCatalogueStages[];
extern void Defs_SetBitValue(u8 *, s32, s32);
extern s32 Defs_TestBit(void *bitArray, s32 index);

void Results_RefreshTrialCatalogueWidgets(void) {
    u8 availableFlags[8];
    Preset *unlockedPreset;
    SlotSelectionWidget *widget;
    s32 entryIndex, unlockSlot, unlockIndex;
    s32 searchIndex;
    s32 unlockValue;
    s32 resourceKey;
    Shared_Game *playerSettings, *settings;
    u8 opacity;
    Results_HideTrialCatalogueWidgets();
    for (entryIndex = 0; entryIndex < 36; entryIndex++) {
        Defs_SetBitValue(availableFlags, entryIndex, 0);
    }
    Defs_SetBitValue(availableFlags, 0, 1);
    settings = &g_gameSettings;
    if (settings->controllerMode == 1) {
        playerSettings = settings;
        for (entryIndex = 0; entryIndex < 36; entryIndex++) {
            unlockedPreset = Achieve_CopyPreset(entryIndex, 0, *(s8 *)((char *)playerSettings + g_trialCatalogueScreen->player * sizeof(Shared_PlayerSettingsRecord) + ((char *)&((Shared_Game *)0)->playerSettings[0].character - (char *)0)));
            unlockValue = unlockedPreset->bytes[1];
            if (unlockValue > 0) Defs_SetBitValue(availableFlags, unlockValue - 1, 1);
            for (unlockSlot = 0; unlockSlot < 3; unlockSlot++) {
                unlockValue = *((u8 *)unlockedPreset + unlockSlot + 2);
                if (unlockValue > 0) Defs_SetBitValue(availableFlags, unlockValue - 1, 1);
            }
        }
    } else {
        for (entryIndex = 0; entryIndex < 36; entryIndex++) {
            Defs_SetBitValue(availableFlags, entryIndex, 1);
        }
    }
    for (entryIndex = 0; entryIndex < 64; entryIndex++) {
        resourceKey = g_arenaCompatibilityTable[entryIndex].a;
        for (searchIndex = 0; searchIndex < 36; searchIndex++) {
            if (g_trialCatalogueStages[searchIndex].value == resourceKey) { unlockIndex = searchIndex; goto found1; }
        }
        unlockIndex = 0;
found1:;
        if (Defs_TestBit((s32)availableFlags, unlockIndex) == 1) {
            widget = Node_FindWidgetByResourceId(g_trialCatalogueScreen->parent, (u16)g_arenaCompatibilityTable[entryIndex].a);
            Widget_SetWidgetFlag08(widget, 1);
            widget->alpha = 20;
            resourceKey = g_arenaCompatibilityTable[entryIndex].b;
            for (searchIndex = 0; searchIndex < 36; searchIndex++) {
                if (g_trialCatalogueStages[searchIndex].value == resourceKey) { unlockIndex = searchIndex; goto found2; }
            }
            unlockIndex = 0;
found2:;
            if (Defs_TestBit((s32)availableFlags, unlockIndex) == 1) {
                widget = Node_FindWidgetByResourceId(g_trialCatalogueScreen->parent, (u16)g_arenaCompatibilityTable[entryIndex].b);
                Widget_SetWidgetFlag08(widget, 1);
                widget->alpha = 20;
                if (g_arenaCompatibilityTable[entryIndex].c.id != -1) {
                    widget = Node_FindWidgetByResourceId(g_trialCatalogueScreen->parent, (u16)g_arenaCompatibilityTable[entryIndex].c.id);
                    Widget_SetWidgetFlag08(widget, 1);
                    widget->alpha = 20;
                }
            }
        }
    }
    for (entryIndex = 0; entryIndex < 36; entryIndex++) {
        if (Defs_TestBit((s32)g_trialCatalogueScreen->owned, entryIndex) == 1) ((void (*)(s32))Results_MarkLinkedTrialsAvailable)(entryIndex);
    }
    for (entryIndex = 0; entryIndex < 36; entryIndex++) {
        if (Defs_TestBit((s32)g_trialCatalogueScreen->pending, entryIndex) == 1) Defs_SetBitValue(g_trialCatalogueScreen->owned, entryIndex, 1);
    }
    for (entryIndex = 0; entryIndex < 64; entryIndex++) {
        opacity = 170;
        resourceKey = g_arenaCompatibilityTable[entryIndex].a;
        for (searchIndex = 0; searchIndex < 36; searchIndex++) {
            if (g_trialCatalogueStages[searchIndex].value == resourceKey) { unlockIndex = searchIndex; goto found3; }
        }
        unlockIndex = 0;
found3:;
        if (Defs_TestBit((s32)g_trialCatalogueScreen->owned, unlockIndex) == 1) {
            widget = Node_FindWidgetByResourceId(g_trialCatalogueScreen->parent, (u16)g_arenaCompatibilityTable[entryIndex].a);
            if (Defs_TestBit((s32)g_trialCatalogueScreen->pending, unlockIndex) == 1) { widget->alpha = 70; opacity = 70; }
            else widget->alpha = 170;
            resourceKey = g_arenaCompatibilityTable[entryIndex].b;
            for (searchIndex = 0; searchIndex < 36; searchIndex++) {
                if (g_trialCatalogueStages[searchIndex].value == resourceKey) { unlockIndex = searchIndex; goto found4; }
            }
            unlockIndex = 0;
found4:;
            if (Defs_TestBit((s32)g_trialCatalogueScreen->owned, unlockIndex) == 1) {
                widget = Node_FindWidgetByResourceId(g_trialCatalogueScreen->parent, (u16)g_arenaCompatibilityTable[entryIndex].b);
                if (Defs_TestBit((s32)g_trialCatalogueScreen->pending, unlockIndex) == 1) { widget->alpha = 70; opacity = 70; }
                else widget->alpha = 170;
                if (g_arenaCompatibilityTable[entryIndex].c.id != -1) {
                    widget = Node_FindWidgetByResourceId(g_trialCatalogueScreen->parent, (u16)g_arenaCompatibilityTable[entryIndex].c.id);
                    widget->alpha = opacity;
                }
            }
        }
    }
}

/* Updates the selected player's appearance and creates its results-screen model. */
#include "TYPES.H"
#include "FRONTEND/FRONTEND_DRAWMODELPREVIEW.H"

typedef struct PreviewSettings { char pad[13]; u8 mode; char padE[0xC2]; struct EntryFrontendRefreshTrialCharacterPreview entries[4]; } PreviewSettings;
typedef struct PreviewRecord { char pad[4]; u8 kind; } PreviewRecord;
extern void Results_FillTrialPresetWeaponRows(s32,PreviewSettings *);
extern PreviewRecord *Scene_GetBlLevelData(void *,s32);

void Results_RefreshTrialCharacterPreview(void) {
    CVector3 scale;
    s32 record;
    s32 index;
    u8 kind;
    struct EntryFrontendRefreshTrialCharacterPreview *entry;
    PreviewSettings *settings = (PreviewSettings *)&g_gameSettings;
    if (settings->mode == 4) {
        record = (*(ResultsOptionsScreen **)&g_trialCatalogueScreen)->selection;
        entry = &((PreviewSettings *)&g_gameSettings)->entries[(*(ResultsOptionsScreen **)&g_trialCatalogueScreen)->player];
        Results_FillTrialPresetWeaponRows(record, settings);
        kind = Scene_GetBlLevelData(&g_world, record)->kind;
        entry->kind = kind;
        index = Key_FindKeyIndex((s8)kind);
        scale.x = g_characterPortraitRecords[index].scale[0];
        scale.y = g_characterPortraitRecords[index].scale[0];
        scale.z = g_characterPortraitRecords[index].scale[0];
        Preview_InitModelPreview((ModelPreview *)(*(ResultsOptionsScreen **)&g_trialCatalogueScreen)->panels, 9, entry->kind + 911, 75, 24000, scale,
                         g_characterPortraitRecords[index].position[0], g_characterPortraitRecords[index].distance[0],
                         g_characterPortraitRecords[index].light[0]);
    }
}
