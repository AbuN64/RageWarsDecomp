#ifndef UI_TSMOS_SCREENS_SCENARIOSETUPSCREEN_H
#define UI_TSMOS_SCREENS_SCENARIOSETUPSCREEN_H
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "TYPES.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/EFFECTRENDER.H"
extern ResourceBank g_scenarioResultRowWidgetIds[];

typedef struct { s32 selection; s32 trigger; } MenuTransitionSignal;

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#else
#endif
static inline s32 previewModelImage(void) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
return (s32)g_matchResult5052TextEu[g_languageIndex];
#else
return g_matchResult5052TextDe;
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
extern s32 ScenarioSetup_SelectPreviousCatalogueItem(void *unused0, void *unused1, void *unused2, s32 event);
extern s32 ScenarioSetup_SelectNextSetupItem(void *unused0, void *unused1, void *unused2, s32 event);
extern s32 ScenarioSetup_SelectPreviousCatalogueCategory(void *unused0, void *unused1, void *unused2, s32 event);
extern s32 ScenarioSetup_SelectNextCatalogueCategory(void *unused0, void *unused1, void *unused2, s32 event);
extern s32 ScenarioSetup_EndSetupInput(void);
extern s32 ScenarioSetup_RefreshSetupScreen(void);
extern s32 ScenarioSetup_DispatchCatalogueEvent(void *, s32, s32, s32, s32);
extern s32 ScenarioSetup_OpenResultsScreen(void *root);
extern void ScenarioSetup_FillResultRows(void);
extern void ScenarioSetup_SortResultsPlayers(void);
extern void ScenarioSetup_HideResultCatalogueWidgets(void);
extern void ScenarioSetup_InitResultModelPreview(void);
#endif
