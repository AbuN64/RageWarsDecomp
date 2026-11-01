#ifndef FRONTEND_SCENARIO_CUP_CATALOGUE_H
#define FRONTEND_SCENARIO_CUP_CATALOGUE_H
#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
#include "ENGINE/CONTROL.H"
extern void ScenarioSetup_SetCupCategory(int);
extern void ScenarioSetup_SetCupStageCount(int);
extern void ScenarioSetup_LoadSetupArenaLabel(void);
extern void ScenarioSetup_HideArenaCatalogueWidgets(void);
extern void ScenarioSetup_HideSetupCatalogue(void);
extern s32 ScenarioSetup_ReturnResultsGateTrue(void);
#endif
