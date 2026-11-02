#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "COMMON/SCREEN.H"
#include "UI/TSMOS/SCREENS/SCENARIOSETUPSCREEN.H"
#include "ENGINE/CONTROL.H"
#include "COMMON/MENULISTSCREEN.H"
#include "TYPES.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include "COMMON/SHARED_MENUREPLY.H"
#include "COMMON/MENU_SCREEN_SETUP.H"
#include "FRONTEND/NODE_FINDWIDGETBYRESOURCEID.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/WORLD.H"
#include "COMMON/ACCESS_S8_10F.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/SELF.H"
#include <ultra64.h>
#include "COMMON/LEVEL_GOAL.H"
#include "SCENE/CACHE_FREEMEMORY.H"
#include "COMMON/PLAYERPROFILES.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "FRONTEND/RESULTS_SETUP_TEXT.H"
#include "COMMON/SETTINGSRECAT24.H"
#include "COMMON/RESULTSOPTIONSSCREEN.H"
#include "include_asm.h"

/* 80423280_50.CPP */
typedef struct ArenaCatalogueEntry {
    s32 key;
    s32 other;
    s32 reserved;
    s32 value;
} ArenaCatalogueEntry;

extern ArenaCatalogueEntry g_scenarioCatalogueWidgetPairs[];

/* Sets the alpha of every catalogue icon on the screen g_setupScreen: for categories 0 to 3 (tables
   g_cupCategoryTwoArenaControls, g_cupCategoryThreeArenaControls, g_cupCategoryOneArenaControls and g_cupCategoryZeroArenaControls) it walks the count ScenarioSetup_GetCategoryEntryCount gives for the
   category's list ScenarioSetup_CategoryToList and, for the first of the forty 16-byte icon records g_scenarioCatalogueWidgetPairs
   whose key matches the entry, sets the alpha of the item its key names (and of the item its second
   word names unless that is -1) and shows them through Widget_SetWidgetFlag08_EquipActivateequipmentpanel while the alpha is at least
   12. */

/* Refreshes the selection on the screen g_setupScreen: for category 0 to 3 at 0x434 it takes the item
   the selection at 0x438 names in the 4-byte table g_cupCategoryTwoArenaControls, g_cupCategoryThreeArenaControls, g_cupCategoryOneArenaControls or
   g_cupCategoryZeroArenaControls from the window into 0x43C, copies the selection's name into the text at 0x3F4 (the
   default label for selection 0, otherwise the resource name Scene_CopyLevelName reads from
   g_world_AchieveUpdateresultsscreen for the entry ScenarioSetup_ResolveArenaFromSelection finds in the category's list ScenarioSetup_CategoryToList), points the
   label at 0x3EC to that text and calls Cinema_ReleaseSequenceContext_FrontendHandletaboptionsshortcut. */

#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
#endif

extern void Scene_CopyLevelName(struct Shared_World *world, s32 type, void *levelName, s32 maximumBytes);

extern u8 *XPlus_UppercaseString(u8 *string);

extern u8 *XPlus_CopyString(u8 *destination, u8 *source);

/* 80423280_51.CPP */
/* Starts the next stage of the current cup g_scenarioCupProgress unless ScenarioSetup_IsCupComplete reports the cup over:
   draws random stage numbers below the cup's size (5, 7, 17 or 11 stages) until one not yet marked
   in the played set at g_scenarioCupPlayedBits turns up (giving up after 15000 draws), marks it, counts the stage in
   g_scenarioCupStageCount, maps it through the cup's stage table to an arena id, finds that id among the 40
   arena entries at g_scenarioCatalogueWidgetPairs and starts the cup with the entry's value through Random_SetSelectedStage.
   Returns 1 when a stage was started, else 0. */

extern s32 Defs_TestBit(void *bitArray, s32 index);

extern void Defs_SetBitValue(u8 *bitArray, s32 index, s32 found);

/* ScenarioSetup_ResolveArenaFromSelection_Scenariosetupscreen.CPP */
extern s32 g_scenarioArenaSelectionTable[];

extern s32 Model_SetPreviewModel(struct RecordFrontendSetPreviewModel *record, s32 count);

/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_scenarioCatalogueEventIds, an actor kind at g_scenarioCatalogueEventActorKinds and a handler at g_scenarioCatalogueEventHandlers: the first row whose event equals eventId and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

typedef s32 (*ScenarioCatalogueEventHandler)(void *, s32, s32, s32, s32);

extern ScenarioCatalogueEventHandler g_scenarioCatalogueEventHandlers;

extern MatchScoreScreenView *g_matchResultBadgeScreen;

extern s8 g_profileSlotIndices[], g_profileSlotEnabledFlags[];

extern void Frontend_InitMenuImage(s32 *, s32, s32, s32, s32);

extern void Frontend_StartMenuImageTransition(s32 *record);

extern void Frontend_AccumulatePlayerStatistics(void);

extern void Match_UpdateMatchCounters(s32 playerIndex, s32 counterIndex);

extern void Achieve_MarkLevelPlayed(s32);

extern void Widget_SetWidgetFlag100(void *, s32);

extern s32 Widget_ListHasFlag100(struct WidgetNode *node);

extern s32 Key_FindKeyIndex(s32);

extern char *Match_UpdateRankText(s32);

extern s32 XStdio_FormatBuffer(void *goal, s32 fmt0, ...);

extern void Frontend_ShowResultRankBadge(s32,s32,u16);

/* Shows the model preview of the screen g_matchResultBadgeScreen when its model id at 0x32C is set: shows the
   version-specific preview item of the screen window with alpha 0xAF and the preview image, then sets up the
   view at 0x20 of the screen through Frontend_InitModelPreviewTransform with mode 0, a uniform g_scenarioPreviewScale scale and the
   offset (0, g_scenarioPreviewOffsetY, g_resultBadgeDrawParameters), through Frontend_SetPreviewRotation with a zero vector, through
   Frontend_SetPreviewRotationSpeed with (0, g_scenarioPreviewPositionY, 0), and loads the model through Model_SetPreviewModel. */
typedef struct PreviewScreen {
    char pad0[0x20];
    char view[0xE0 - 0x20];
    void *window;
    char padE4[0x32C - 0xE4];
    s32 model;
} PreviewScreen;

#define PREVIEW_SCREEN ((PreviewScreen *)g_matchResultBadgeScreen)
extern f32 g_scenarioPreviewScale;

extern f32 g_scenarioPreviewOffsetY, g_resultBadgeDrawParameters;

void ScenarioSetup_ResetSelectionIndicators(void);
void ScenarioSetup_SetCatalogueAlpha(s32 alpha);
s32 ScenarioSetup_CategoryToList(s32 category);
int ScenarioSetup_GetCategoryEntryCount(int index);
s32 ScenarioSetup_ResolveArenaFromSelection(s32 gameMode, s32 arenaSelection);
void ScenarioSetup_ClearFlagBits(void);
void ScenarioSetup_SetCupCategory(s32 value);
void ScenarioSetup_SetCupStageCount(s32 value);
s32 ScenarioSetup_StartRandomCupStage(void);
s32 ScenarioSetup_IsCupComplete(void);
void ScenarioSetup_HideArenaCatalogueWidgets(void);
void ScenarioSetup_FillResultRows(void);
void ScenarioSetup_HideResultCatalogueWidgets(void);
void ScenarioSetup_InitResultModelPreview(void);
void ScenarioSetup_SortResultsPlayers(void);
static inline Shared_PlayerSettingsRecord *playerSettings(void);

/* SCENARIOSETUPSCREEN.CPP */
/* 80423280_11.CPP */
#if !defined(VERSION_DE)
/* Advances the menu transition state and updates its visual effects. */

/* The values ScenarioSetup_UpdateSetupTransition loads by address:
 * 0x800E1AF4 = 0.0033333334 (float, k_setupPulsePhaseScale in this cartridge's tables)
 * 0x800E1AF8 = 100.0 (float, k_setupPulseAlphaAmplitude in this cartridge's tables)
 * 0x800E1AFC = 150.0 (float, unnamed in this cartridge's tables)
 * 0x800E1B00 = 2147483600.0 (float, k_setupPulseFloatToIntLimit in this cartridge's tables)
 * 0x800E1B04 = 0.0033333334 (float, k_setupPulsePhaseScale_de in this cartridge's tables)
 * 0x800E1B08 = 100.0 (float, k_setupPulseAlphaAmplitude_de in this cartridge's tables)
 * 0x800E1B0C = 150.0 (float, unnamed in this cartridge's tables)
 * 0x800E1B10 = 2147483600.0 (float, k_setupPulseFloatToIntLimit_de in this cartridge's tables)
 */

void Tsmos_ActivateControllerState(void);

void SmpFlicker_StartFlicker(struct FlickerStartView *object, s32 count);

void SmXlate_SwitchScreen(s32);

/* Resource ids of this screen are numbered per version (relative to us): eu-x 4. */
static inline s32 setupRes(s32 id) {
#if defined(VERSION_EU_X)
    return id + 4;
#else
    return id;
#endif
}

s32 ScenarioSetup_UpdateSetupTransition(void *root, s32 unusedEventId, s32 phaseStep) {
    ListScreenScreen *countdown;
    f32 pulseAlpha;
    s32 updatedPulsePhase;
    s32 catalogueAlpha;
    s32 transitionStateOrAlpha;
    s32 exitCountdown;
    s32 entryCountdown;
    s32 previousCountdown;
    s32 enabled;
    s32 clampedCountdown;
    ListScreenItem *closeLeft;
    ListScreenItem *closeRight;
    ListScreenItem *openLeft;
    ListScreenItem *openRight;
    void *flagWidget;
    ListScreenItem *pulseWidget;
    void *visibilityWidget;

    if (g_selectionMessageReply.ready == 1) {
        g_selectionMessageReply.ready = 0;
        if (g_selectionMessageReply.value != -1) {
            g_setupScreen->widget30C->alpha = 90;
            MarkMenuEventHandled();
            SmXlate_SwitchScreen(g_selectionMessageReply.value);
            return 0;
        }
        g_setupScreen->widget30C->alpha = 0xFF;
        g_setupScreen->screenState = 9;
        if (g_setupScreen->selection == 0) {
            Widget_SetWidgetFlag08(g_setupScreen->widget30B, 1);
            flagWidget = g_setupScreen->widget35D;
        } else {
            flagWidget = g_setupScreen->widget30D;
        }
        Widget_SetWidgetFlag08(flagWidget, 1);
        Widget_SetWidgetFlag08(g_setupScreen->label, 1);
        Widget_SetWidgetFlag08(g_setupScreen->widget310, 1);
        goto block_7;
    }
block_7:
    transitionStateOrAlpha = g_setupScreen->screenState;
    switch (transitionStateOrAlpha) {
    case 1:
        openLeft = g_setupScreen->left;
        openLeft->x = (u16) (openLeft->x + (u16)g_setupScreen->leftCount);
        openRight = g_setupScreen->right;
        openRight->x = (u16) (openRight->x - (u16)g_setupScreen->rightCount);
        exitCountdown = g_setupScreen->stateCountdown - 1;
        g_setupScreen->stateCountdown = exitCountdown;
        if (exitCountdown <= 0) {
            SoundElement_PlayFlatSound(3705);
            Widget_SetWidgetFlag08(g_setupScreen->widget301, 1);
            SmpFlicker_StartFlicker(g_setupScreen->text3E4, 4);
            g_setupScreen->screenState = 4;
            g_setupScreen->stateCountdown = 4;
        }
        break;
    case 2:
        closeLeft = g_setupScreen->left;
        closeLeft->x = (u16) (closeLeft->x - (u16)g_setupScreen->leftCount);
        closeRight = g_setupScreen->right;
        closeRight->x = (u16) (closeRight->x + (u16)g_setupScreen->rightCount);
        entryCountdown = g_setupScreen->stateCountdown - 1;
        g_setupScreen->stateCountdown = entryCountdown;
        if (entryCountdown <= 0) {
            g_setupScreen->screenState = 3;
            MarkMenuEventHandled();
            SmXlate_SwitchScreen(8);
            return 0;
        }
        break;
    case 3:
        if (g_setupScreen->controllerActivated == 0) {
            Tsmos_ActivateControllerState();
            enabled = 0;
            visibilityWidget = g_setupScreen->widget300;
            g_setupScreen->controllerActivated = 1;
            Widget_SetWidgetFlag08(visibilityWidget, enabled);
        }
        break;
    case 4:
        countdown = g_setupScreen;
        previousCountdown = countdown->countdown;
        clampedCountdown = previousCountdown - 1 < 0 ? 0 : previousCountdown - 1 > previousCountdown ? previousCountdown : previousCountdown - 1;
        countdown->countdown = clampedCountdown;

        if ((((ListScreenScreen *) g_setupScreen)->countdown <= 0) && (SmpFlicker_IsFlickerIdle(g_setupScreen->text3E4) != 0)) {
            SmpFlicker_RestoreFlickerValue(g_setupScreen->text3E4);
            ScenarioSetup_SetCatalogueAlpha(10);
            g_setupScreen->screenState = 9;
        }
        break;
    case 5:
        Widget_SetWidgetFlag08(g_setupScreen->widget300, 1);
        Widget_SetWidgetFlag08(g_setupScreen->widget301, 0);
        ScenarioSetup_ResetSelectionIndicators();
        ScenarioSetup_SetCatalogueAlpha(0);
        g_setupScreen->screenState = 2;
        g_setupScreen->stateCountdown = 4;
        Widget_SetWidgetFlag08(g_setupScreen->widget35D, 0);
        SoundElement_PlayFlatSound(3704);
        break;
    case 8:
        transitionStateOrAlpha = ((ListScreenItem *)Node_FindWidgetByResourceId(root, setupRes(790)))->alpha;
        catalogueAlpha = transitionStateOrAlpha >> 1;
        ScenarioSetup_SetCatalogueAlpha(catalogueAlpha);
        if (catalogueAlpha < 10) {
            g_setupScreen->screenState = 3;
            Random_SetMenuChoiceResult(11);
            return 0;
        }
        break;
    case 9:
        catalogueAlpha = ((ListScreenItem *)Node_FindWidgetByResourceId(root, setupRes(790)))->alpha;
        catalogueAlpha = (catalogueAlpha + 1) * 2;
        if (catalogueAlpha >= 66) {
            catalogueAlpha = 65;
            g_setupScreen->screenState = 3;
        }
        ScenarioSetup_SetCatalogueAlpha(catalogueAlpha);
        enabled = 1;
        if (g_setupScreen->selection == 0) {
            visibilityWidget = g_setupScreen->widget35D;
            Widget_SetWidgetFlag08(visibilityWidget, enabled);
        }
        break;
    default:
        break;
    }
    if (g_setupScreen->screenState == 3) {
            updatedPulsePhase = g_setupScreen->pulsePhase + phaseStep;
            g_setupScreen->pulsePhase = updatedPulsePhase;
            if (g_selectionMessageReply.value == -1) {
                if (g_setupScreen->selection == 0) {
                    pulseAlpha = (Math_Cosf((f32) updatedPulsePhase * 0.0033333334f) * 100.0f) + 150.0f;
                    pulseWidget = g_setupScreen->widget35D;
                    pulseWidget->alpha = (u8) (u32) pulseAlpha;
                } else {
                    pulseAlpha = (Math_Cosf((f32) updatedPulsePhase * 0.0033333334f) * 100.0f) + 150.0f;
                    pulseWidget = g_setupScreen->item;
                    pulseWidget->alpha = (u8) (u32) pulseAlpha;
                }
            }
        }
        return 0;
}
#endif

/* 80408AC4_2.CPP */
#if defined(VERSION_DE)
s32 ScenarioSetup_UpdateSetupTransitionDe(void *root, s32 unused, s32 delta) {
    MenuWidget *item;
    f32 alpha;
    s32 fade;
    s32 count, previous, level;
    SetupScreen *countdown;
    if (g_selectionMessageReply.ready == 1) {
        g_selectionMessageReply.ready = 0;
        if (g_selectionMessageReply.value != -1) {
            g_setupScreen->widget30C->alpha = 90;
            MarkMenuEventHandled();
            SmXlate_SwitchScreen(g_selectionMessageReply.value);
            return 0;
        }
        g_setupScreen->widget30C->alpha = 0xFF;
        g_setupScreen->screenState = 9;
        if (g_setupScreen->selection == 0) {
            Widget_SetWidgetFlag08(g_setupScreen->widget30B, 1);
            item = g_setupScreen->widget35D;
        } else item = g_setupScreen->widget30D;
        Widget_SetWidgetFlag08(item, 1);
        Widget_SetWidgetFlag08(g_setupScreen->label, 1);
        Widget_SetWidgetFlag08(g_setupScreen->widget310, 1);
    }
    switch (g_setupScreen->screenState) {
    case 1:
        g_setupScreen->left->x += (u16)g_setupScreen->leftCount;
        g_setupScreen->right->x -= (u16)g_setupScreen->rightCount;
        if (--g_setupScreen->stateCountdown <= 0) {
            SoundElement_PlayFlatSound(3705);
            Widget_SetWidgetFlag08(g_setupScreen->widget301, 1);
            SmpFlicker_StartFlicker(g_setupScreen->text3E4, 4);
            g_setupScreen->screenState = 4;
            g_setupScreen->stateCountdown = 4;
        }
        break;
    case 2:
        g_setupScreen->left->x -= (u16)g_setupScreen->leftCount;
        g_setupScreen->right->x += (u16)g_setupScreen->rightCount;
        if (--g_setupScreen->stateCountdown <= 0) {
            g_setupScreen->screenState = 3;
            MarkMenuEventHandled();
            SmXlate_SwitchScreen(8);
            return 0;
        }
        break;
    case 3:
        if (g_setupScreen->controllerActivated == 0) {
            Tsmos_ActivateControllerState();
            g_setupScreen->controllerActivated = 1;
            Widget_SetWidgetFlag08(g_setupScreen->widget300, 0);
        }
        break;
    case 4:
        countdown = g_setupScreen;
        previous = countdown->stateCountdown;
        count = previous - 1 < 0 ? 0 : previous - 1 > previous ? previous : previous - 1;
        countdown->stateCountdown = count;
        if (g_setupScreen->stateCountdown <= 0 && SmpFlicker_IsFlickerIdle(g_setupScreen->text3E4)) {
            SmpFlicker_RestoreFlickerValue(g_setupScreen->text3E4);
            ScenarioSetup_SetCatalogueAlpha(10);
            g_setupScreen->screenState = 9;
        }
        break;
    case 5:
        Widget_SetWidgetFlag08(g_setupScreen->widget300, 1);
        Widget_SetWidgetFlag08(g_setupScreen->widget301, 0);
        ScenarioSetup_ResetSelectionIndicators();
        ScenarioSetup_SetCatalogueAlpha(0);
        g_setupScreen->screenState = 2;
        g_setupScreen->stateCountdown = 4;
        Widget_SetWidgetFlag08(g_setupScreen->widget35D, 0);
        SoundElement_PlayFlatSound(3704);
        break;
    case 6: case 7: break;
    case 8:
        level = Node_FindWidgetByResourceId(root, 786)->alpha;
        fade = level >> 1;
        ScenarioSetup_SetCatalogueAlpha(fade);
        if (fade < 10) {
            g_setupScreen->screenState = 3;
            Random_SetMenuChoiceResult(11);
            return 0;
        }
        break;
    case 9:
        fade = Node_FindWidgetByResourceId(root, 786)->alpha;
        fade = (fade + 1) * 2;
        if (fade > 65) { fade = 65; g_setupScreen->screenState = 3; }
        ScenarioSetup_SetCatalogueAlpha(fade);
        if (g_setupScreen->selection == 0) Widget_SetWidgetFlag08(g_setupScreen->widget35D, 1);
        break;
    }
    if (g_setupScreen->screenState == 3) {
        g_setupScreen->pulsePhase += delta;
        if (g_selectionMessageReply.value == -1) {
            if (g_setupScreen->selection == 0) {
                alpha = Math_Cosf((f32)g_setupScreen->pulsePhase * 0.0033333334f) * 100.0f + 150.0f;
                item = g_setupScreen->widget35D;
                item->alpha = (u32)alpha;
            } else {
                alpha = Math_Cosf((f32)g_setupScreen->pulsePhase * 0.0033333334f) * 100.0f + 150.0f;
                item = g_setupScreen->item;
                item->alpha = (u32)alpha;
            }
        }
    }
    return 0;
}
#endif

/* Resets the selection screen: maps the menu mode at 0x434 to a category (0 to 2, 1 to 3, 2 to 1,
   otherwise 0), builds the category list through ScenarioSetup_ResolveArenaFromSelection, hides the forty controls of the
   table g_scenarioCatalogueWidgetPairs (and each entry's optional second control), refreshes the list, hides five fixed
   widgets and restores the selection, starting from the first entry when nothing was selected. */

static inline int map_category(int mode) {
    int category;

    switch (mode) {
        case 3:
            category = 0;
            break;
        case 2:
            category = 1;
            break;
        case 1:
            category = 3;
            break;
        case 0:
            category = 2;
            break;
        default:
            return 0;
    }
    return category;
}

void ScenarioSetup_SetCatalogueAlpha(s32 alpha) {
    MenuWidget *item;
    s32 *table;
    s32 visible;
    s32 category;
    s32 count;
    s32 list;
    s32 found;
    s32 i;
    s32 j;

    visible = alpha >= 12;
    for (category = 0; category < 4; category++) {
        switch (category) {
        case 3:
            table = g_cupCategoryZeroArenaControls;
            list = 3;
            break;
        case 2:
            table = g_cupCategoryOneArenaControls;
            list = 2;
            break;
        case 0:
            table = g_cupCategoryTwoArenaControls;
            list = 0;
            break;
        case 1:
            table = g_cupCategoryThreeArenaControls;
            list = 1;
            break;
        default:
            return;
        }
        do {
            count = ScenarioSetup_GetCategoryEntryCount(ScenarioSetup_CategoryToList(list));
            for (i = 0; i < count; i++) {
                found = 0;
                j = 0;
            scan:
                if (table[i] == g_scenarioCatalogueWidgetPairs[j].key) {
                    item = Node_FindWidgetByResourceId(g_setupScreen->window, (u16)g_scenarioCatalogueWidgetPairs[j].key);
                    Widget_SetWidgetFlag08(item, visible);
                    item->alpha = alpha;
                    if (g_scenarioCatalogueWidgetPairs[j].other != -1) {
                        item = Node_FindWidgetByResourceId(g_setupScreen->window, (u16)g_scenarioCatalogueWidgetPairs[j].other);
                        Widget_SetWidgetFlag08(item, visible);
                        item->alpha = alpha;
                    }
                    found = 1;
                }
                j++;
                if (j < 40 && found == 0) {
                    goto scan;
                }
            }
        } while (0);
    }
}

void ScenarioSetup_RefreshSelectedArenaLabel(void) {
    s32 *table;
    char buffer[64];
    switch (g_setupScreen->category) {
    case 3:
        table = g_cupCategoryZeroArenaControls;
        break;
    case 2:
        table = g_cupCategoryOneArenaControls;
        break;
    case 1:
        table = g_cupCategoryThreeArenaControls;
        break;
    case 0:
        table = g_cupCategoryTwoArenaControls;
        break;
    default:
        return;
    }
    g_setupScreen->item = Node_FindWidgetByResourceId(g_setupScreen->window, (u16)table[g_setupScreen->selection]);
    if (g_setupScreen->selection == 0) {
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        XPlus_CopyString(g_setupScreen->text, g_matchOptionLabelSlots[0]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        XPlus_CopyString(g_setupScreen->text, g_scenarioSetupLocalizedTitles[g_languageIndex]);
#endif
    } else {
        Scene_CopyLevelName(&g_world,
                      ScenarioSetup_ResolveArenaFromSelection(ScenarioSetup_CategoryToList(g_setupScreen->category), g_setupScreen->selection),
                      buffer, 63);
        XPlus_CopyString(g_setupScreen->text, XPlus_UppercaseString(buffer));
    }
    g_setupScreen->label->text = g_setupScreen->text;
    Cinema_ReleaseSequenceContext();
}

void ScenarioSetup_StartSelectedScenario(void) {
    int category;
    int list;
    int i;

    category = map_category(g_setupScreen->category);
    list = ScenarioSetup_ResolveArenaFromSelection(category, g_setupScreen->selection);
    for (i = 0; i < 40; i++) {
        Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_setupScreen->window, (u16)g_scenarioCatalogueWidgetPairs[i].key), 0);
        if (g_scenarioCatalogueWidgetPairs[i].other != -1) {
            Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_setupScreen->window, (unsigned short)g_scenarioCatalogueWidgetPairs[i].other), 0);
        }
    }
    Random_SetSelectedStage(category, list);
    Random_SetMenuChoiceResult(21);
    Widget_SetWidgetFlag08(((struct ScreenScenarioSetupRefreshSelectedArenaLabel *)g_setupScreen)->widgetC, 0);
    Widget_SetWidgetFlag08(((struct ScreenScenarioSetupRefreshSelectedArenaLabel *)g_setupScreen)->widgetE, 0);
    Widget_SetWidgetFlag08(((struct ScreenScenarioSetupRefreshSelectedArenaLabel *)g_setupScreen)->widgetD, 0);
    Widget_SetWidgetFlag08(g_setupScreen->label, 0);
    Widget_SetWidgetFlag08(((struct ScreenScenarioSetupRefreshSelectedArenaLabel *)g_setupScreen)->widgetB, 0);
    ScenarioSetup_ClearFlagBits();
    if (g_setupScreen->selection == 0) {
        ScenarioSetup_SetCupCategory(category);
        ScenarioSetup_SetCupStageCount(0);
        ScenarioSetup_StartRandomCupStage();
    } else {
        ScenarioSetup_SetCupCategory(-1);
        ScenarioSetup_SetCupStageCount(g_setupScreen->selection);
    }
}

static inline s32 cup_stages(s32 cup) {
    switch (cup) {
    case 0:
        return 5;
    case 1:
        return 7;
    case 3:
        return 11;
    case 2:
        return 17;
    }
    return 0;
}

static inline s32 stage_arena(s32 cup, s32 stage) {
    s32 *table;
    s32 id;
    s32 value;
    s32 found;
    s32 i;

    value = 0;
    if (stage == 0) {
        stage = 1;
    }
    switch (cup) {
    case 0:
        table = g_cupCategoryZeroArenaControls;
        break;
    case 1:
        table = g_cupCategoryOneArenaControls;
        break;
    case 3:
        table = g_cupCategoryThreeArenaControls;
        break;
    case 2:
        table = g_cupCategoryTwoArenaControls;
        break;
    default:
        return 0;
    }
    id = table[stage];
    found = 0;
    i = 0;
    do {
        if (id == g_scenarioCatalogueWidgetPairs[i].key) {
            found = 1;
            value = g_scenarioCatalogueWidgetPairs[i].value;
        }
        i++;
    } while (i < 40 && !found);
    return value;
}

s32 ScenarioSetup_StartRandomCupStage(void) {
    s32 started;
    s32 found;
    s32 stage;
    s32 draws;
    s32 size;

    started = 0;
    if (ScenarioSetup_IsCupComplete() == 0) {
        started = 1;
        stage = 0;
        draws = 0;
        found = 0;
        size = cup_stages(g_scenarioCupProgress.index) - 1;
        while (!found) {
            stage = Graphu64_NextRandom() % size + 1;
            if (Defs_TestBit(g_scenarioCupProgress.played, stage) == 0) {
                found = 1;
                Defs_SetBitValue(g_scenarioCupProgress.played, stage, found);
            }
            draws++;
            if (draws >= 15001) {
                found = 1;
            }
        }
        g_scenarioCupProgress.stages++;
        Random_SetSelectedStage(g_scenarioCupProgress.index, stage_arena(g_scenarioCupProgress.index, stage));
    }
    return started;
}

/* Returns whether g_scenarioCupProgress holds anything other than -1; ScenarioSetup_SetCupCategory stores it. */

s32 ScenarioSetup_IsCupSelected(void) {
    return g_scenarioCupProgress.index != -1;
}

s32 ScenarioSetup_IsCupComplete(void) {
    s32 complete = 1;
    if (g_scenarioCupProgress.index >= 0) {
        complete = cup_stages(g_scenarioCupProgress.index);
        complete = (g_scenarioCupProgress.stages + 1) == complete;
    }
    return complete;
}

/* 80423280_52.CPP */

/* Stores its argument in g_scenarioCupStageCount. */

/* Refreshes the name label of screen g_setupScreen: with no entry at 0x438 it uses the default text
   g_matchOptionLabelSlots; otherwise it formats the entry's name from ScenarioSetup_ResolveArenaFromSelection on the list ScenarioSetup_CategoryToList
   returns for 0x434 into a 0x40-byte buffer through g_world_AchieveUpdateresultsscreen and takes the text XPlus_UppercaseString
   makes of it. Either text is copied into the screen's label at 0x3F4 through XPlus_CopyString_ResultsFillprofileweaponrows, and the
   widget at 0x3EC is pointed at that label. */

/* Calls ScenarioSetup_HideArenaCatalogueWidgets and then ScenarioSetup_SetCatalogueAlpha with 0. */

/* Hides each primary and optional secondary selection widget. */

 /* extern */

 /* extern */

/* Returns one; ScenarioSetup_OpenResultsScreen calls it. */
s32 ScenarioSetup_ReturnResultsGateTrue(void) {
    return 1;
}

/* Stores its argument in g_scenarioCupProgress. */

void ScenarioSetup_SetCupCategory(s32 value) {
    g_scenarioCupProgress.index = value;
}

void ScenarioSetup_SetCupStageCount(s32 value) {
    g_scenarioCupProgress.stages = value;
}

void ScenarioSetup_LoadSetupArenaLabel(void) {
    char buffer[64];

    if (g_setupScreen->selection == 0) {
        XPlus_CopyString(g_setupScreen->text,
#if defined(VERSION_EU) || defined(VERSION_EU_X)
g_matchOptionLabelSlots[g_gameSettings.language]
#else
g_matchOptionLabelSlots[0]
#endif
);
    } else {
        Scene_CopyLevelName(&g_world, ScenarioSetup_ResolveArenaFromSelection(ScenarioSetup_CategoryToList(g_setupScreen->category), g_setupScreen->selection),
                      buffer, 63);
        XPlus_CopyString(g_setupScreen->text, XPlus_UppercaseString(buffer));
    }
    g_setupScreen->label->text = g_setupScreen->text;
}

void ScenarioSetup_HideSetupCatalogue(void) {
    ScenarioSetup_HideArenaCatalogueWidgets();
    ScenarioSetup_SetCatalogueAlpha(0);
}

/* The catalogue stores word-valued widget identifiers; only the low 16 bits name a widget. */
void ScenarioSetup_HideArenaCatalogueWidgets(void) {
    s32 offset;
    s32 index;
    index = 0;
    do {
        offset = index * 16;
        Widget_SetWidgetFlag08((void *)Node_FindWidgetByResourceId((void*)g_setupScreen->window, (u16)*(s32 *)(&g_scenarioCatalogueFirstWidgetIds - 2 + offset)), 0);
        if (*(s32 *)(&g_scenarioCatalogueLinkedWidgetIds + offset) != -1) {
            Widget_SetWidgetFlag08((void *)Node_FindWidgetByResourceId((void*)g_setupScreen->window, (u16)*(s32 *)(&g_scenarioCatalogueSecondWidgetIds - 2 + offset)), 0);
        }
            index += 1;
    } while (index < 40);
}

/* Maps a selection index to its code: 0 gives 5, 1 gives 7, 2 gives 17, 3 gives 11 and anything else
   0. */
int ScenarioSetup_GetCategoryEntryCount(int index) {
    int r;

    switch (index) {
    case 0:
        return 5;
    case 1:
        return 7;
    case 3:
        return 11;
    case 2:
        return 17;
    default:
        r = 0;
        break;
    }
    return r;
}

s32 ScenarioSetup_ResolveArenaFromSelection(s32 gameMode, s32 arenaSelection) {
    s32 result = 0;
    s32 *table;
    s32 key;
    s32 found;
    s32 i;
    if (arenaSelection == 0) {
        arenaSelection = 1;
    }
    switch (gameMode) {
    case 0:
        table = g_cupCategoryZeroArenaControls;
        break;
    case 1:
        table = g_cupCategoryOneArenaControls;
        break;
    case 3:
        table = g_cupCategoryThreeArenaControls;
        break;
    case 2:
        table = g_cupCategoryTwoArenaControls;
        break;
    default:
        return 0;
    }
    key = table[arenaSelection];
    found = 0;
    i = 0;
    do {
        if (key == g_scenarioCatalogueWidgetPairs[i].key) {
            found = 1;
            result = g_scenarioArenaSelectionTable[i * 4];
        }
        i++;
    } while ((i < 40) && (found == 0));
    return result;
}

s32 ScenarioSetup_CategoryToList(s32 category) {
    s32 list;
    switch (category) {
    default:
        list = 0;
        break;
    case 2:
        list = 1;
        break;
    case 1:
        list = 3;
        break;
    case 0:
        list = 2;
        break;
    }
    return list;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 ScenarioSetup_ReturnSetupEventZero(void) {
    return 0;
}

void ScenarioSetup_ResetSelectionIndicators(void) {
    g_setupScreen->widget308->alpha = 0xFF;
    g_setupScreen->widget2FE->alpha = 0xFF;
    Widget_SetWidgetFlag08(g_setupScreen->widget2FE, 1);
    Widget_SetWidgetFlag08(g_setupScreen->widget308, 1);
    g_setupScreen->reservedWord3 = 0;
}

/* Clears the first 0x28 bits of the bit set g_scenarioCupPlayedBits (bit i set to 0 through Defs_SetBitValue). */
void ScenarioSetup_ClearFlagBits(void) {
    s32 i;

    for (i = 0; i < 40; i++) {
        Defs_SetBitValue(g_scenarioCupProgress.played, i, 0);
    }
}

/* Closes the setup screen g_setupScreen: releases it through Cache_FreeMemory, runs Tsmos_ActivateControllerState and
   Menu_ReleaseOptionsScene, then clears the pointer. Returns zero. */
s32 ScenarioSetup_CloseSetupScreen(void) {
    Cache_FreeMemory(g_setupScreen);
    Tsmos_ActivateControllerState();
    Menu_ReleaseOptionsScene();
    g_setupScreen = 0;
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 ScenarioSetup_ReturnSetupEventZeroAlt(void) {
    return 0;
}

/** Begin setup confirmation when the pending state and input event permit it. */
s32 ScenarioSetup_BeginSetupConfirmation(s32 a0, s32 a1, s32 a2, s32 a3)
{
    s32 v = g_setupScreen->screenState;

    if (v != 3) {
        return 0;
    }
    if (g_selectionMessageReply.value != -1) {
        return 0;
    }
    if ((u32)a2 >> 16 != v) {
        return 0;
    }
    if (a3 != 0) {
        return 0;
    }

    MarkMenuEventHandled();
    g_setupScreen->screenState = 8;
    ScenarioSetup_SetCatalogueAlpha(65);

    Widget_SetWidgetFlag08(g_setupScreen->widget30B, 0);
    Widget_SetWidgetFlag08(g_setupScreen->widget30D, 0);
    Widget_SetWidgetFlag08(g_setupScreen->widget35D, 0);
    Widget_SetWidgetFlag08(g_setupScreen->label, 0);
    Widget_SetWidgetFlag08(g_setupScreen->widget310, 0);

    g_setupScreen->widget30C->alpha = 90;
    SoundElement_PlayFlatSound(3708);

    return 0;
}

#define SCR4D4 ((struct ScreenScenarioSetupSelectPreviousCatalogueItem *)g_setupScreen)
s32 ScenarioSetup_SelectPreviousCatalogueItem(void *unused0, void *unused1, void *unused2, s32 event) {
    s32 changed;

    MarkMenuEventHandled();
    if (event != 1) {
        return 0;
    }
    changed = 0;
    if (SCR4D4->category != 0) {
        if (SCR4D4->selection > 0) {
            changed = 1;
            SCR4D4->selection = SCR4D4->selection - 1;
        }
    } else if (SCR4D4->selection >= 11) {
        s32 next = ScenarioSetup_GetCategoryEntryCount(ScenarioSetup_CategoryToList(0));
        if (SCR4D4->selection + 1 < next) {
            changed = 1;
            SCR4D4->selection = SCR4D4->selection + 1;
        }
    } else if (SCR4D4->selection > 0) {
        SCR4D4->selection = SCR4D4->selection - 1;
        changed = 1;
    }
    if (changed != 1) {
        return 0;
    }
    SoundElement_PlayFlatSound(3709);
    ScenarioSetup_ResetSelectionIndicators();
    SCR4D4->word45C = 0;
    SCR4D4->word464 = 0;
    SCR4D4->item->alpha = 65;
    ScenarioSetup_RefreshSelectedArenaLabel();
    if (SCR4D4->selection != 0) {
        return 0;
    }
    Widget_SetWidgetFlag08(SCR4D4->left, 1);
    Widget_SetWidgetFlag08(SCR4D4->marker, 1);
    SCR4D4->marker->x = SCR4D4->category * 34 + 124;
    Widget_SetWidgetFlag08(SCR4D4->right, 0);
    Model_SetPreviewModel(SCR4D4->view, SCR4D4->category + 3750);
    return 0;
}

#undef SCR4D4

/** Select the next setup item, reversing the displayed order on the second page. */
s32 ScenarioSetup_SelectNextSetupItem(void *unused0, void *unused1, void *unused2, s32 event) {
    SetupScreen *screen;
    s32 changed;
    s32 count;
    s32 next;
    s32 limit;

    MarkMenuEventHandled();
    if (event != 1) {
        return 0;
    }
    changed = 0;
    count = ScenarioSetup_GetCategoryEntryCount(ScenarioSetup_CategoryToList(g_setupScreen->category));
    screen = g_setupScreen;
    if (screen->category != 0) {
        next = screen->selection + 1;
        if (next < count) {
            changed = 1;
            screen->selection = next;
        }
    } else {
        if (screen->selection >= 11) {
            next = screen->selection - 1;
            limit = 10;
        } else {
            limit = ScenarioSetup_GetCategoryEntryCount(ScenarioSetup_CategoryToList(0));
            screen = g_setupScreen;
            next = screen->selection + 1;
            if (next == limit) {
                goto moved;
            }
            limit = 11;
        }
        if (next != limit) {
            changed = 1;
            screen->selection = next;
        }
    }
moved:
    if (changed != 1) {
        return 0;
    }
    SoundElement_PlayFlatSound(3709);
    ScenarioSetup_ResetSelectionIndicators();
    g_setupScreen->pulsePhase = 0;
    g_setupScreen->reservedWord1 = 0;
    g_setupScreen->item->alpha = 65;
    ScenarioSetup_RefreshSelectedArenaLabel();
    Widget_SetWidgetFlag08(g_setupScreen->widget30B, 0);
    Widget_SetWidgetFlag08(g_setupScreen->widget30D, 1);
    Widget_SetWidgetFlag08(g_setupScreen->widget35D, 0);
    return 0;
}

#define SCR78C ((struct ScreenScenarioSetupSelectPreviousCatalogueCategory *)g_setupScreen)
s32 ScenarioSetup_SelectPreviousCatalogueCategory(void *unused0, void *unused1, void *unused2, s32 event) {
    s32 changed;
    s32 count;
    s32 mirror;

    MarkMenuEventHandled();
    if (event != 1) {
        return 0;
    }
    changed = 0;
    if (SCR78C->category != 0) {
        changed = 1;
        SCR78C->category = SCR78C->category - 1;
    } else if ((u32)(SCR78C->selection - 5) < 6) {
        mirror = 21 - SCR78C->selection;
        if (mirror < ScenarioSetup_GetCategoryEntryCount(ScenarioSetup_CategoryToList(0))) {
            changed = 1;
            SCR78C->selection = mirror;
        }
    }
    if (changed != 1) {
        return 0;
    }
    SoundElement_PlayFlatSound(3709);
    ScenarioSetup_ResetSelectionIndicators();
    SCR78C->word45C = 0;
    SCR78C->word464 = 0;
    SCR78C->item->alpha = 65;
    count = ScenarioSetup_GetCategoryEntryCount(ScenarioSetup_CategoryToList(SCR78C->category));
    if (SCR78C->selection >= count) {
        SCR78C->selection = count - 1;
    }
    ScenarioSetup_RefreshSelectedArenaLabel();
    if (SCR78C->selection == 0) {
        Model_SetPreviewModel(SCR78C->view, SCR78C->category + 3750);
        Widget_SetWidgetFlag08(SCR78C->marker, 1);
        SCR78C->marker->x = SCR78C->category * 34 + 124;
    }
    return 0;
}

#undef SCR78C

#define SCR904 ((struct ScreenScenarioSetupSelectPreviousCatalogueCategory *)g_setupScreen)
s32 ScenarioSetup_SelectNextCatalogueCategory(void *unused0, void *unused1, void *unused2, s32 event) {
    s32 changed;
    s32 count;

    MarkMenuEventHandled();
    if (event != 1) {
        return 0;
    }
    changed = 0;
    if (SCR904->category != 3) {
        changed = SCR904->category == 0;
        if (changed) {
            changed = 1;
            if (SCR904->selection >= 11) {
                SCR904->selection = 21 - SCR904->selection;
            } else {
                SCR904->category = changed;
            }
        } else {
            changed = 1;
            SCR904->category = SCR904->category + changed;
        }
    }
    if (changed != 1) {
        return 0;
    }
    SoundElement_PlayFlatSound(3709);
    ScenarioSetup_ResetSelectionIndicators();
    SCR904->word45C = 0;
    SCR904->word464 = 0;
    SCR904->item->alpha = 65;
    count = ScenarioSetup_GetCategoryEntryCount(ScenarioSetup_CategoryToList(SCR904->category));
    if (SCR904->selection >= count) {
        SCR904->selection = count - 1;
    }
    ScenarioSetup_RefreshSelectedArenaLabel();
    if (SCR904->selection == 0) {
        Model_SetPreviewModel(SCR904->view, SCR904->category + 3750);
        Widget_SetWidgetFlag08(SCR904->marker, 1);
        SCR904->marker->x = SCR904->category * 34 + 124;
    }
    return 0;
}

#undef SCR904

s32 ScenarioSetup_EndSetupInput(void) {
    MarkMenuEventHandled();
    if (g_setupScreen->screenState == 3) {
        g_setupScreen->screenState = 5;
        g_setupScreen->stateCountdown = 4;
        return 0;
    }
    return 0;
}

/* Calls ScenarioSetup_StartSelectedScenario while the setup screen g_setupScreen is in mode 3, and returns zero. */
s32 ScenarioSetup_RefreshSetupScreen(void) {
    if (g_setupScreen->screenState == 3) {
        ScenarioSetup_StartSelectedScenario();
        return 0;
    }
    return 0;
}

s32 ScenarioSetup_DispatchCatalogueEvent(void *widget, s32 eventId, s32 eventData0, s32 eventData1, s32 eventData2) {
    ScenarioCatalogueEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuActorInputView *actor;

    if (g_scenarioCatalogueEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_scenarioCatalogueEventHandlers;
        index = 0;
        do {
            if (g_scenarioCatalogueEventIds[index].value == eventId) {
                actor = widget;
                actor_kind = actor->input;
                table_kind = g_scenarioCatalogueEventActorKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*entry)(widget, eventId, eventData0, eventData1, eventData2);
                }
            }
            entry += 3;
            index++;
        } while (*entry != 0);
    }
    return 0;
}

s32 ScenarioSetup_OpenResultsScreen(void *root) {
    char buffer[64];
    MenuWidget *item;
    MatchScoreScreenView *screen;
    Shared_Game *game;
    Shared_Game *slot;
    Shared_PlayerSettingsRecord *config;
    s32 i, offset;

    g_matchResultBadgeScreen = (void *)Cache_AllocateMemory(816);
    g_matchResultBadgeScreen->window = root;
    Widget_SetWidgetFlag08(root, 0);
    Frontend_InitMenuImage(g_matchResultBadgeScreen->transition, 103, 0, 0, 0);
    Frontend_StartMenuImageTransition(g_matchResultBadgeScreen->transition);
    g_matchResultBadgeScreen->active = 1;
    Node_FindWidgetByResourceId(root, 564 + RESULTS_MENU_SHIFT)->alpha = 110;
    Node_FindWidgetByResourceId(root, 569 + RESULTS_MENU_SHIFT)->alpha = 20;
    Node_FindWidgetByResourceId(root, 566 + RESULTS_MENU_SHIFT)->alpha = 20;
    Frontend_AccumulatePlayerStatistics();
    screen = g_matchResultBadgeScreen;
    for (i = 0; i < 8; i++) {
        screen->icons[i][0] = -1;
        screen->icons[i][1] = -1;
    }
    g_matchResultBadgeScreen->selection = -1;
    ScenarioSetup_SortResultsPlayers();
    game = &g_gameSettings;
    switch (game->controllerMode) {
    case 0:
        Match_UpdateMatchCounters(g_matchResultBadgeScreen->data, g_selectedLevelId);
        Frontend_AwardResultAchievements();
        g_matchResultBadgeScreen->mode = 0;
        break;
    case 2:
        if (game->humanWon == 1) {
            g_matchResultBadgeScreen->mode = 0;
            Frontend_AwardResultMilestones();
            config = game->playerSettings;
            for (i = 0; i < 4; i++) {
                if (config[i].enabled == 1 && config[i].locked == 0) Achieve_MarkLevelPlayed(i);
            }
        } else g_matchResultBadgeScreen->mode = 1;
        break;
    }
    slot = &g_gameSettings;
    switch (slot->controllerMode) {
    case 0:
        ScenarioSetup_FillResultRows();
        break;
    case 2:
        screen = g_matchResultBadgeScreen;
        if (screen->mode == 1) {
            screen->first = 0;
            screen->count = 0;
            ScenarioSetup_HideResultCatalogueWidgets();
            item = Node_FindWidgetByResourceId(root, 614 + RESULTS_MENU_SHIFT);
            Widget_SetWidgetFlag08(item, 1);
            item->alpha = 115;
            item->text = resultsUnavailable(slot);
            Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(root, RESULTS_RIGHT_ITEM), 0);
        } else if (screen->selection != -1) {
            screen->first = 0;
            screen->count = 0;
            ScenarioSetup_HideResultCatalogueWidgets();
            Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(root, RESULTS_RIGHT_ITEM), 0);
            ScenarioSetup_InitResultModelPreview();
        } else {
            ScenarioSetup_FillResultRows();
        }
        break;
    }
    SmpButton_WrapButtonWidget(567 + RESULTS_MENU_SHIFT);
    SmpButton_WrapButtonWidget(568 + RESULTS_MENU_SHIFT);
    SmpButton_WrapButtonWidget(572 + RESULTS_MENU_SHIFT);
    Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(root, 568 + RESULTS_MENU_SHIFT), 1);
    i = 0;
    offset = 0;
    do {
        i++;
        if (g_profileSlotIndices[offset] >= 0 && g_profileSlotEnabledFlags[offset] == 0) {
            Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(root, 568 + RESULTS_MENU_SHIFT), 0);
            break;
        }
        offset += 400;
    } while (i < 4);
    if (Widget_ListHasFlag100(Node_FindWidgetByResourceId(root, 568 + RESULTS_MENU_SHIFT)) == 0 && ScenarioSetup_IsCupSelected() == 1 && ScenarioSetup_ReturnResultsGateTrue() == 0) {
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(root, 568 + RESULTS_MENU_SHIFT), 1);
    }
    item = Node_FindWidgetByResourceId(g_matchResultBadgeScreen->window, RESULTS_HEADING1);
    if (g_currentResultMode.kind == 0) item->text = resultsFirstHeading();
    else item->text = resultsSecondHeading();
    item = Node_FindWidgetByResourceId(g_matchResultBadgeScreen->window, RESULTS_HEADING2);
    switch (g_currentResultMode.kind) {
    case 3: item->text = resultsFirstHeading(); break;
    case 0: item->text = resultsFourthHeading(); break;
    case 1:
    default: item->text = resultsThirdHeading(); break;
    }
    item = Node_FindWidgetByResourceId(root, 565 + RESULTS_MENU_SHIFT);
    Scene_CopyLevelName(&g_world, g_selectedLevelId, buffer, 63);
    XPlus_CopyString(g_matchResultBadgeScreen->name, XPlus_UppercaseString(buffer));
    item->text = g_matchResultBadgeScreen->name;
    g_matchResultBadgeScreen->buttonAddress = (s32)Node_FindWidgetByResourceId(root, 573 + RESULTS_MENU_SHIFT);
    g_matchResultBadgeScreen->dirty = 1;
    g_frontendScreenStatus.status[7] = 1;
    g_matchResultBadgeScreen->phase = 0;
    Tsmos_DeactivateControllerState();
    return 0;
}

/* Fill the four visible player rows of the match results screen. */
void ScenarioSetup_FillResultRows(void) {
    s32 row, player, attempts, percent;
    SlotSelectionPlayerConfig *record;
    MenuWidget *widget, *pending;
    char *name;

    ScenarioSetup_HideResultCatalogueWidgets();
    for (row = 0; row < 4; row++) {
        if (row >= g_matchResultBadgeScreen->count) return;
        player = g_matchResultBadgeScreen->players[g_matchResultBadgeScreen->first + row];
        record = &g_playerSettings[player];

        widget = Node_FindWidgetByResourceId(g_matchResultBadgeScreen->window, g_scenarioResultRowWidgetIds[row].ids[0]);
        Widget_SetWidgetFlag08(widget, 1);
        widget->alpha = 150;
        pending = widget;
        pending->value = g_characterPortraitRecords[Key_FindKeyIndex(record->kind)].portrait;

        widget = Node_FindWidgetByResourceId(g_matchResultBadgeScreen->window, g_scenarioResultRowWidgetIds[row].ids[2]);
        Widget_SetWidgetFlag08(widget, 1);
        widget->alpha = 25;

        widget = Node_FindWidgetByResourceId(g_matchResultBadgeScreen->window, g_scenarioResultRowWidgetIds[row].ids[4]);
        widget->alpha = 175;
        Widget_SetWidgetFlag08(widget, 1);
        if (record->out == 0) {
            widget->text = g_localPlayerProfiles[player].name;
        } else {
            name = record->name;
            XPlus_CopyString(name, XPlus_UppercaseString(name));
            widget->text = name;
        }

        widget = Node_FindWidgetByResourceId(g_matchResultBadgeScreen->window, g_scenarioResultRowWidgetIds[row].ids[6]);
        widget->alpha = 115;
        Widget_SetWidgetFlag08(widget, 1);
        if (record->out == 0) widget->text = Match_UpdateRankText(player);
        else widget->text = resultsRankText(record->rank);

        widget = Node_FindWidgetByResourceId(g_matchResultBadgeScreen->window, g_scenarioResultRowWidgetIds[row].ids[8]);
        widget->alpha = 175;
        Widget_SetWidgetFlag08(widget, 1);
        XStdio_FormatBuffer(g_matchResultBadgeScreen->killText[row], resultsNumberFormat(), record->kills);
        widget->text = g_matchResultBadgeScreen->killText[row];

        widget = Node_FindWidgetByResourceId(g_matchResultBadgeScreen->window, g_scenarioResultRowWidgetIds[row].ids[10]);
        widget->alpha = 175;
        Widget_SetWidgetFlag08(widget, 1);
        XStdio_FormatBuffer(g_matchResultBadgeScreen->scoreText[row], resultsNumberFormat(), record->score + record->total);
        *&widget->text = g_matchResultBadgeScreen->scoreText[row];

        if (g_currentResultMode.kind == 0) {
            Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_matchResultBadgeScreen->window, g_scenarioResultRowWidgetIds[row].ids[12]), 0);
            Frontend_ShowResultRankBadge(player, row, RESULTS_RANK_GROUP);
        } else {
            widget = Node_FindWidgetByResourceId(g_matchResultBadgeScreen->window, g_scenarioResultRowWidgetIds[row].ids[12]);
            widget->alpha = 175;
            Widget_SetWidgetFlag08(widget, 1);
            attempts = g_playerCountedShots[player];
            percent = 0;
            if (attempts > 0) percent = g_playerHitCounts[player] * 100 / attempts;
            XStdio_FormatBuffer(g_matchResultBadgeScreen->ratioText[row], resultsPercentFormat(), percent);
            widget->text = g_matchResultBadgeScreen->ratioText[row];
        }

        if (g_currentResultMode.kind == 3) {
            Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_matchResultBadgeScreen->window, g_scenarioResultRowWidgetIds[row].ids[14]), 0);
            Frontend_ShowResultRankBadge(player, row, RESULTS_SECONDARY_GROUP);
        } else {
            widget = Node_FindWidgetByResourceId(g_matchResultBadgeScreen->window, g_scenarioResultRowWidgetIds[row].ids[14]);
            widget->alpha = 175;
            Widget_SetWidgetFlag08(widget, 1);
            pending = widget;
            switch (g_currentResultMode.kind) {
            case 0:
                XStdio_FormatBuffer(g_matchResultBadgeScreen->valueText[row], resultsNumberFormat(), record->other);
                break;
            case 1:
                XStdio_FormatBuffer(g_matchResultBadgeScreen->valueText[row], resultsNumberFormat(), record->selected);
                break;
            default:
                XStdio_FormatBuffer(g_matchResultBadgeScreen->valueText[row], resultsNumberFormat(), 0);
                break;
            }
            pending->text = g_matchResultBadgeScreen->valueText[row];
        }

        widget = Node_FindWidgetByResourceId(g_matchResultBadgeScreen->window, g_scenarioResultRowWidgetIds[row].ids[16]);
        Widget_SetWidgetFlag08(widget, 0);
        widget->alpha = 150;
        widget = Node_FindWidgetByResourceId(g_matchResultBadgeScreen->window, g_scenarioResultRowWidgetIds[row].ids[18]);
        Widget_SetWidgetFlag08(widget, 0);
        widget->alpha = 150;
        if (record->out == 0) {
            if (g_matchResultBadgeScreen->icons[player][0] != -1) {
                widget = Node_FindWidgetByResourceId(g_matchResultBadgeScreen->window, g_scenarioResultRowWidgetIds[row].ids[16]);
                Widget_SetWidgetFlag08(widget, 1);
                widget->value = g_resultAchievementBadgeImages[g_matchResultBadgeScreen->icons[player][0]];
            }
            if (g_matchResultBadgeScreen->icons[player][1] != -1) {
                widget = Node_FindWidgetByResourceId(g_matchResultBadgeScreen->window, g_scenarioResultRowWidgetIds[row].ids[18]);
                Widget_SetWidgetFlag08(widget, 1);
                widget->value = g_resultAchievementBadgeImages[g_matchResultBadgeScreen->icons[player][1]];
            }
        }
        pending = 0;
    }
}

/* The game settings record. */
static inline Shared_Game *resultsGame(void) { return &g_gameSettings; }

static inline LevelGoal *levelGoal(void) { return &g_currentResultMode; }

static inline CGameStatus *gameStatus(void) { return &resultsGame()->counters; }

static inline s32 resultsTeamTotal(s32 group) {
    if (levelGoal()->kind == 0) return gameStatus()->counts[group];
    return gameStatus()->scores[group];
}

static inline Shared_PlayerSettingsRecord *playerSettings(void) { return resultsGame()->playerSettings; }

/* Swap two sort entries through the caller's temp. */
#define RESULTS_SWAP(x, y) do { temp = x; x = y; y = temp; } while (0)
/* Swap the joined players at slots n and n + 1. */
#define RESULTS_SWAP_PLAYERS(n) do { RESULTS_SWAP(g_matchResultBadgeScreen->players[n], g_matchResultBadgeScreen->players[(n) + 1]); } while (0)
/* Order the joined players for the results screen: in team games (goal kinds 0 and 3) teams by
 * total, players by their team's total, then players within each team by the mode's score; otherwise
 * players by the mode's score. Ties fall back to the kill score. */
void ScenarioSetup_SortResultsPlayers(void) {
    s32 groups[5];
    s32 i, j, k, mode, temp, leftTotal, rightTotal, group, a, b, leftKills, rightKills, leftScore, rightScore, nextTotal;

    g_matchResultBadgeScreen->first = 0;
    g_matchResultBadgeScreen->count = 0;
    /* leftKills doubles as the empty-slot marker while the slots are cleared. */
    for (i = 0, leftKills = -1; i < 8; i++) {
        g_matchResultBadgeScreen->players[i] = leftKills;
        if (playerSettings()[i].enabled == 1) {
            g_matchResultBadgeScreen->players[g_matchResultBadgeScreen->count] = i;
            g_matchResultBadgeScreen->count++;
        }
    }
    mode = Frontend_GetMatchEndReason();
    if (mode == 0) {
        switch (g_currentResultMode.kind) {
        case 2: mode = 1; break;
        case 1: mode = 2; break;
        case 0: mode = 3; break;
        default: mode = 1; break;
        }
    }
    if (g_currentResultMode.kind == 3 || g_currentResultMode.kind == 0) {
        for (i = 4; i >= 0; i--) groups[i] = i;
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 4; j++) {
                a = groups[j];
                leftTotal = resultsTeamTotal(a);
                b = groups[j + 1];
                rightTotal = resultsTeamTotal(b);
                if (leftTotal < rightTotal) {
                    RESULTS_SWAP(groups[j], groups[j + 1]);
                }
            }
        }
        for (j = 0; j < g_matchResultBadgeScreen->count; j++) {
            for (k = 0; k < g_matchResultBadgeScreen->count - 1; k++) {
                a = g_matchResultBadgeScreen->players[k];
                leftTotal = resultsGame()->playerSettings[a].rank;
                if (leftTotal >= 5) leftTotal = -1;
                else leftTotal = resultsTeamTotal(leftTotal);
                b = g_matchResultBadgeScreen->players[k + 1];
                rightTotal = resultsGame()->playerSettings[b].rank;
                if (rightTotal >= 5) nextTotal = -1;
                else nextTotal = resultsTeamTotal(rightTotal);
                if (leftTotal < nextTotal) {
                    RESULTS_SWAP_PLAYERS(k);
                }
            }
        }
        for (i = 0; i < 5; i++) {
            group = groups[i];
            for (j = 0; j < g_matchResultBadgeScreen->count; j++) {
                for (k = 0; k < g_matchResultBadgeScreen->count - 1; k++) {
                    a = g_matchResultBadgeScreen->players[k];
                    b = g_matchResultBadgeScreen->players[k + 1];
                    leftKills = resultsGame()->playerSettings[a].score;
                    rightKills = resultsGame()->playerSettings[b].score;
                    if (resultsGame()->playerSettings[a].rank == group && resultsGame()->playerSettings[b].rank == group) {
                        switch (mode) {
                        case 1: leftScore = leftKills; rightScore = rightKills; break;
                        case 3: leftScore = resultsGame()->playerSettings[a].resultAlternate; rightScore = resultsGame()->playerSettings[b].resultAlternate; break;
                        default: leftScore = leftKills; rightScore = rightKills; break;
                        }
                        if (leftScore < rightScore || (leftScore == rightScore && leftKills < rightKills)) {
                            RESULTS_SWAP_PLAYERS(k);
                        }
                    }
                }
            }
        }
    } else {
        for (i = 0; i < g_matchResultBadgeScreen->count; i++) {
            for (j = 0; j < g_matchResultBadgeScreen->count - 1; j++) {
                a = g_matchResultBadgeScreen->players[j];
                b = g_matchResultBadgeScreen->players[j + 1];
                leftKills = resultsGame()->playerSettings[a].score;
                rightKills = resultsGame()->playerSettings[b].score;
                switch (mode) {
                case 3: leftScore = resultsGame()->playerSettings[a].resultAlternate; rightScore = resultsGame()->playerSettings[b].resultAlternate; break;
                case 2: leftScore = resultsGame()->playerSettings[a].resultScore; rightScore = resultsGame()->playerSettings[b].resultScore; break;
                case 1:
                default: leftScore = leftKills; rightScore = rightKills; break;
                }
                if (leftScore < rightScore || (leftScore == rightScore && leftKills < rightKills)) {
                    RESULTS_SWAP_PLAYERS(j);
                }
            }
        }
    }
}

/* 80423280_55.CPP */

/** Load four banks of ten resources, then activate the two resources used by the set. */
void ScenarioSetup_HideResultCatalogueWidgets(void)
{
    s32 bank;
    s32 offset;
    void *resource;

    bank = 0;
    offset = 0;
    do {
        resource = Node_FindWidgetByResourceId(g_matchResultBadgeScreen->window, g_scenarioResultRowWidgetIds[bank].ids[0]);
        Widget_SetWidgetFlag08(resource, 0);
        resource = Node_FindWidgetByResourceId(g_matchResultBadgeScreen->window, g_scenarioResultRowWidgetIds[bank].ids[2]);
        Widget_SetWidgetFlag08(resource, 0);
        resource = Node_FindWidgetByResourceId(g_matchResultBadgeScreen->window, g_scenarioResultRowWidgetIds[bank].ids[4]);
        Widget_SetWidgetFlag08(resource, 0);
        resource = Node_FindWidgetByResourceId(g_matchResultBadgeScreen->window, g_scenarioResultRowWidgetIds[bank].ids[6]);
        Widget_SetWidgetFlag08(resource, 0);
        resource = Node_FindWidgetByResourceId(g_matchResultBadgeScreen->window, g_scenarioResultRowWidgetIds[bank].ids[8]);
        Widget_SetWidgetFlag08(resource, 0);
        resource = Node_FindWidgetByResourceId(g_matchResultBadgeScreen->window, g_scenarioResultRowWidgetIds[bank].ids[10]);
        Widget_SetWidgetFlag08(resource, 0);
        resource = Node_FindWidgetByResourceId(g_matchResultBadgeScreen->window, g_scenarioResultRowWidgetIds[bank].ids[12]);
        Widget_SetWidgetFlag08(resource, 0);
        resource = Node_FindWidgetByResourceId(g_matchResultBadgeScreen->window, g_scenarioResultRowWidgetIds[bank].ids[14]);
        Widget_SetWidgetFlag08(resource, 0);
        resource = Node_FindWidgetByResourceId(g_matchResultBadgeScreen->window, g_scenarioResultRowWidgetIds[bank].ids[16]);
        Widget_SetWidgetFlag08(resource, 0);
        resource = Node_FindWidgetByResourceId(g_matchResultBadgeScreen->window, g_scenarioResultRowWidgetIds[bank].ids[18]);
        Widget_SetWidgetFlag08(resource, 0);
        offset += 40;
        bank++;
    } while (bank < 4);

#if defined(VERSION_DE)
    Frontend_HideResultBadgeGroup(612);
    Frontend_HideResultBadgeGroup(617);
#elif defined(VERSION_EU_X)
    Frontend_HideResultBadgeGroup(621);
    Frontend_HideResultBadgeGroup(626);
#else
    Frontend_HideResultBadgeGroup(617);
    Frontend_HideResultBadgeGroup(622);
#endif
}

void ScenarioSetup_InitResultModelPreview(void) {
    struct MenuWidget *item;
    CVector3 scale;
    CVector3 offset;
    CVector3 angle;
    CVector3 position;
    if (PREVIEW_SCREEN->model != -1) {
#if defined(VERSION_DE)
        item = Node_FindWidgetByResourceId(PREVIEW_SCREEN->window, 611);
#elif defined(VERSION_EU_X)
        item = Node_FindWidgetByResourceId(PREVIEW_SCREEN->window, 620);
#else
        item = Node_FindWidgetByResourceId(PREVIEW_SCREEN->window, 616);
#endif
        Widget_SetWidgetFlag08(item, 1);
        item->alpha = 175;
        item->image = previewModelImage();
        scale.x = g_scenarioPreviewScale;
        scale.y = g_scenarioPreviewScale;
        scale.z = g_scenarioPreviewScale;
        angle.x = 0;
        angle.y = 0;
        angle.z = 0;
        position.x = 0;
        position.y = g_scenarioPreviewPositionY;
        position.z = 0;
        offset.x = 0;
        offset.y = g_scenarioPreviewOffsetY;
        offset.z = g_resultBadgeDrawParameters;
        ((void (*)(void *, s32, CVector3, CVector3))Frontend_InitModelPreviewTransform)(PREVIEW_SCREEN->view, 0, scale, offset);
        ((void (*)(void *, CVector3))Frontend_SetPreviewRotation)(PREVIEW_SCREEN->view, angle);
        ((void (*)(void *, CVector3))Frontend_SetPreviewRotationSpeed)(PREVIEW_SCREEN->view, position);
        Model_SetPreviewModel(PREVIEW_SCREEN->view, PREVIEW_SCREEN->model);
    }
}

/* SCENARIO_SETUP_ROW_AND_OFFSET_DATA.CPP */
/* 800E1B14.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800E1B14 */
unsigned int g_scenarioSetupLabelRecordUsRev1[3] = {
    0x00000000, 0xFFFFFFEC, 0x800D7394,
};
#endif

/* 800E8E60_2.CPP */
#if defined(VERSION_EU_X)
unsigned int k_ScenarioSetupRowAndOffsetEncodedWords[3] = {
    0xFFFFFFF8, 0xFFFFFFF8, 0xFFFFFFF8,
};
#endif

/* SCENARIOSETUPSCREEN.CPP */
#if defined(VERSION_US)
char s_ScenariosetupscreenRAXINTText[12] =
    "\000\000\000\000\023RAX_INT";
#endif

#if defined(VERSION_EU)
unsigned int k_ScenariosetupscreenEncodedWordsBlock1[3] = {
    0x00BA00C9, 0x00BB00C2, 0x00BC00BF,
};
#endif

#if defined(VERSION_DE)
unsigned int k_ScenariosetupscreenEncodedWords[3] = {
    0x25642525, 0x00000000, 0x3E99999A,
};
#endif

/* SCENARIOSETUP_FILLRESULTROWS_DATA.CPP */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
const unsigned char s_ScenarioSetup_FillResultRowsTextDePart2[3] = {
    0x25, 0x64, 0x00,
};
#endif

/* SCENARIOSETUPSCREEN_DATA.CPP */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
const char s_ScenarioSetup_FillResultRowsTextDe[5] =
    "%d%%";
#endif

/* G_RESULTROWINTFORMAT.CPP */
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_resultRowIntFormat_GResultrowintformat.c */
const unsigned char g_resultRowIntFormat[3] = {
    0x25, 0x64, 0x00,
};
#endif

/* G_RESULTROWPERCENTFORMAT.CPP */
/* 800E1B24.CPP */
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_resultRowPercentFormat_GResultrowpercentformat.c */
const char g_resultRowPercentFormat[5] =
    "%d%%";
#endif

/* 80406A88_13.CPP */

/* SCENARIOSETUP_INITRESULTMODELPREVIEW_DATA.CPP */
const float k_scenariosetupInitresultmodelpreviewDataFloatConstantWords[4] = {
    0.3f, 3.0f, -3e+01f, -1e+02f,
};
