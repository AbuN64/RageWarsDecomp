#ifndef UI_TSMOS_SCREENS_SCENARIOSETUPSCREEN_H
#define UI_TSMOS_SCREENS_SCENARIOSETUPSCREEN_H
#include "types.h"
typedef struct ArenaCatalogueEntry {
    s32 key;
    s32 other;
    s32 reserved;
    s32 value;
} ArenaCatalogueEntry;
typedef s32 (*ScenarioCatalogueEventHandler)(void *, s32, s32, s32, s32);
#include "Menu/Extraoptions/menu_refreshextraoptionlocks_symbols.h"
#include "Common/runtime_declarations.h"
#include "Achieve/match_getresulttext.h"
#include "types.h"
#include "Common/Lone/g_languageindex.h"
#include "Common/effectrender.h"
struct ResourceBank;
extern struct ResourceBank g_scenarioResultRowWidgetIds[];

typedef struct { s32 selection; s32 trigger; } MenuTransitionSignal;

static inline s32 previewModelImage(void) {
#if defined(VERSION_EU)
return (s32)g_acquiredItemTextsEu[ACQUIRED_TEXT_COOPERATIVE_TALISMAN][g_languageIndex];
#elif defined(VERSION_EU_X)
return (s32)g_acquiredItemTextsEuX[ACQUIRED_TEXT_COOPERATIVE_TALISMAN][g_languageIndex];
#else
return (s32)g_acquiredItemTexts[ACQUIRED_TEXT_COOPERATIVE_TALISMAN];
#endif
}

/* PAL resources provide a string per selected language. */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern const char g_resultsNumberFormat[], g_resultsPercentFormat[];
static inline const char *resultsNumberFormat(void) { return g_resultsNumberFormat; }
static inline const char *resultsPercentFormat(void) { return g_resultsPercentFormat; }
static inline char *resultsRankText(s32 rank) { return g_resultsRankTexts[rank][g_languageIndex]; }
#else
extern const unsigned char g_resultRowIntFormat[];
extern const char g_resultRowPercentFormat[];
static inline const char *resultsNumberFormat(void) { return g_resultRowIntFormat; }
static inline const char *resultsPercentFormat(void) { return g_resultRowPercentFormat; }
static inline char *resultsRankText(s32 rank) { return g_resultsRankTexts[rank][0]; }
#endif

extern void ScenarioSetup_SetCatalogueAlpha(s32 alpha);
extern void ScenarioSetup_RefreshSelectedArenaLabel(void);
extern void ScenarioSetup_StartSelectedScenario(void);
extern s32 ScenarioSetup_IsCupSelected(void);
extern s32 ScenarioSetup_IsCupComplete(void);
extern s32 ScenarioSetup_ReturnResultsGateTrue(void);
extern void ScenarioSetup_SetCupStageCount(s32 value);
extern void ScenarioSetup_LoadSetupArenaLabel(void);
extern void ScenarioSetup_HideSetupCatalogue(void);
extern void ScenarioSetup_HideArenaCatalogueWidgets(void);
extern int ScenarioSetup_GetCategoryEntryCount(int index);
extern s32 ScenarioSetup_ResolveArenaFromSelection(s32, s32);
extern s32 ScenarioSetup_CategoryToList(s32 category);
extern s32 ScenarioSetup_ReturnSetupEventZero(void);
extern void ScenarioSetup_ClearFlagBits(void);
extern s32 ScenarioSetup_CloseSetupScreen(void);
extern s32 ScenarioSetup_ReturnSetupEventZeroAlt(void);
extern s32 ScenarioSetup_BeginSetupConfirmation(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 ScenarioSetup_SelectPreviousCatalogueItem(void *element, void *eventId, void *eventPayload, s32 event);
extern s32 ScenarioSetup_SelectNextSetupItem(void *element, void *eventId, void *eventPayload, s32 event);
extern s32 ScenarioSetup_SelectPreviousCatalogueCategory(void *element, void *eventId, void *eventPayload, s32 event);
extern s32 ScenarioSetup_SelectNextCatalogueCategory(void *element, void *eventId, void *eventPayload, s32 event);
extern s32 ScenarioSetup_EndSetupInput(void);
extern s32 ScenarioSetup_RefreshSetupScreen(void);
extern s32 ScenarioSetup_DispatchCatalogueEvent(void *, s32, s32, s32, s32);

extern void ScenarioSetup_FillResultRows(void);
extern void ScenarioSetup_SortResultsPlayers(void);
extern void ScenarioSetup_HideResultCatalogueWidgets(void);
extern void ScenarioSetup_InitResultModelPreview(void);
s32 ScenarioSetup_OpenResultsScreen(void *root);
/* Catalogue widget pairs, catalogue event handlers and the per-profile-slot tables the scenario setup screen reads. */
extern ArenaCatalogueEntry g_scenarioCatalogueWidgetPairs[];
extern ScenarioCatalogueEventHandler g_scenarioCatalogueEventHandlers;
#endif
