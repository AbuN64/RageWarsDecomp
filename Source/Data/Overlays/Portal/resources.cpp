#include "Data/Rsp/scenariosetup_hidearenacataloguewidgets_data.h"
#include "Data/rest_source_records.h"
#include "Common/format.h"
#include "Common/menulistscreen.h"
#include "Common/resident_event_handler.h"
#include "data_overlay_layouts.h"
#include "types.h"
#include "Frontend/frontend_dispatchplaymodeevent.h"
#include "Menu_choice/frontend_initplaymodemenu.h"
#include "Menu_choice/menu_choice.h"
#include "include_asm.h"
#include "Data/Scenario_setup/frontend_applymodechoice_data.h"
#include "Data/Overlays/Portal/resources_addresses.h"
#include "Frontend/ctrialcatalogue_showtrialoptionchildren.h"
#include "Frontend/frontend.h"
#include "Match/frontend_handlematchmenumessage.h"
#include "Match/match_split.h"
#include "Results/results_animateresultsoptionsscreen.h"
#include "Results/results_createresultsoptionsscreen.h"
#include "Results/results_renderresultsoptionspreview.h"
#include "Data/Ovltbl/ctrialcatalogue_closetrialoptionsscreen_address.h"
#include "Match_reason/match_reason.h"
#include "Results/frontend_activateresultsaction.h"
#include "Ui/Tsmos/Screens/scenariosetupscreen.h"
#include "Frontend/Results/frontend_activateresultsaction.h"
#include "Playercount/frontend_createcourseoptionsmenu.h"
#include "Playercount/frontend_createplayercountscreende.h"
#include "Playercount/frontend_updateplayercountscreen.h"
#include "Frontend/Pakprofile/frontend_createpakprofilescreende.h"
#include "Frontend/Pakprofile/frontend_dispatchpakprofileevent.h"
#include "Data/Ovltbl/items_copylocalizedplayernamesuffix.h"
#include "Frontend/Pakprofile/frontend_handlepakprofileinput.h"
#include "Frontend/Pakprofile/frontend_updatepakscreenpanels.h"
#include "Ui/Tsmos/Screens/Pakinterfacescreen/pakinterface_activateplayerpanelaction.h"
#include "Ui/Tsmos/Screens/Pakinterfacescreen/pakinterface_handlenextpanelselection.h"
#include "Ui/Tsmos/Screens/Pakinterfacescreen/pakinterface_movenamecursorforward.h"
#include "Data/Scenario_setup/frontend_dispatchpakprofileevent_data.h"
#include "Frontend/Resident/frontend_handlepage67choice.h"
#include "Frontend/Timed/frontend_activatepausemenuaction.h"
#include "Frontend/Resident/frontend_updatepage67exit.h"
#include "Frontend/Timed/frontend_consumeconfirmationevent.h"
#include "Frontend/Timed/frontend_resumematchoninput.h"
#include "pause.h"
#include "Frontend/Timed/frontend_createtimedmenu.h"
#include "Frontend/Resident/frontend_freepage67screen.h"
#include "Frontend/Timed/timed_destroypauseconfirmation.h"
#include "Frontend/Timed/timed_finishpauseconfirmationtransition.h"
#include "Frontend/Timed/timed_setconfirmationinputmode.h"
#include "Frontend/Timed/timed.h"
#include "Data/Scenario_setup/g_arenacompatibilitytable.h"
#include "Data/Scenario_setup/frontend_dispatchresidentactorevent_data.h"

/* FRONTEND_APPLYMODECHOICE_DATA.CPP */

#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
#if defined(VERSION_DE)
#include "Common/runtime_declarations.h"
struct {
    ResidentEventHandlerEntry eventHandlers0[7];
    void * links84[10];
} g_frontendApplyModeChoiceRecord __attribute__((aligned(4))) = {
    { { 3592, 3, RESIDENT_HANDLER_PACKED(Frontend_UpdatePlayModeMenu) }, { 3590, 3,
    RESIDENT_HANDLER_PACKED(Frontend_InitPlayModeMenu) }, { 3587, 3,
    RESIDENT_HANDLER_PACKED(Frontend_DestroyPlayModeMenu) }, { 2, 3,
    RESIDENT_HANDLER_PACKED(Frontend_ConsumePlayModeEvent) }, { 1, 3,
    RESIDENT_HANDLER_PACKED(Frontend_ApplyModeChoice) }, { 10, 3,
    RESIDENT_HANDLER_PACKED(Frontend_HandlePlayModeShortcut) }, { 0, 0, (ResidentEventHandler)0 } },
    { (void *)&g_playerSettingsMixedText, (void *)&g_playerSettingsTapText,
    (void *)(&g_playerSettingsSlotNumberFormat + 1), (void *)(&g_playerSettingsSlotNumberFormat + 4),
    (void *)(&g_playerSettingsSlotNumberFormat + 3), (void *)(&g_playerSettingsSlotNumberFormat + 2),
    (void *)(&g_playerSettingsSlotNumberFormat + 3), (void *)(&g_playerSettingsSlotNumberFormat + 2),
    (void *)(&g_playerSettingsSlotNumberFormat + 4), (void *)(&g_playerSettingsSlotNumberFormat + 1) }
};
typedef char g_frontendApplyModeChoiceRecordSizeCheck[(sizeof(g_frontendApplyModeChoiceRecord) == 124) ? 1 : -1];
#endif
#if defined(VERSION_EU)
unsigned int g_frontendApplyModeChoiceRecord[31] = {
    0x00000E08, 0x00000003, 0x0042495C, 0x00000E06, 0x00000003, 0x004241E0, 0x00000E03, 0x00000003,
    0x0042492C, 0x00000002, 0x00000003, 0x00424AC8, 0x00000001, 0x00000003, 0x004246E8, 0x0000000A,
    0x00000003, 0x00424A74, 0x00000000, 0x00000000, 0x00000000, 0x97150000, 0x4A19CE6C,
    (unsigned int)g_playerSettingsSlotNumberTranslations + 0x10,
    (unsigned int)g_playerSettingsSlotNumberTranslations + 0x40, (unsigned int)g_playerSettingsSlotNumberTranslations + 0x30,
    (unsigned int)g_playerSettingsSlotNumberTranslations + 0x20, (unsigned int)g_playerSettingsSlotNumberTranslations + 0x30,
    (unsigned int)g_playerSettingsSlotNumberTranslations + 0x20, (unsigned int)g_playerSettingsSlotNumberTranslations + 0x40,
    (unsigned int)g_playerSettingsSlotNumberTranslations + 0x10,
};
#endif
#if defined(VERSION_EU_X)
unsigned int g_frontendApplyModeChoiceRecord[31] = {
    0x00000E08, 0x00000003, 0x00424AAC, 0x00000E06, 0x00000003, 0x00424330, 0x00000E03, 0x00000003,
    0x00424A7C, 0x00000002, 0x00000003, 0x00424C18, 0x00000001, 0x00000003, 0x00424838, 0x0000000A,
    0x00000003, 0x00424BC4, 0x00000000, 0x00000000, 0x00000000, 0x00000E03, 0x00000020,
    (unsigned int)g_playerSettingsSlotNumberTranslations + 0xC,
    (unsigned int)g_playerSettingsSlotNumberTranslations + 0x30, (unsigned int)g_playerSettingsSlotNumberTranslations + 0x24,
    (unsigned int)g_playerSettingsSlotNumberTranslations + 0x18, (unsigned int)g_playerSettingsSlotNumberTranslations + 0x24,
    (unsigned int)g_playerSettingsSlotNumberTranslations + 0x18, (unsigned int)g_playerSettingsSlotNumberTranslations + 0x30,
    (unsigned int)g_playerSettingsSlotNumberTranslations + 0xC,
};
#endif
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)
#if defined(VERSION_US)
ResidentEventHandlerEntry g_frontendApplyModeChoiceEventHandlers[1] = {
    { 3592, 3, (ResidentEventHandler)(void *)&addrLow_Frontend_UpdatePlayModeMenu_FrontendApplymodechoiceData }
};
#endif
#if defined(VERSION_US_REV1)
ResidentEventHandlerEntry g_frontendApplyModeChoiceEventHandlers[1] = {
    { 3592, 3, (ResidentEventHandler)(void *)&addrLow_Frontend_UpdatePlayModeMenu_FrontendApplymodechoiceData }
};
#endif
#endif

#if defined(VERSION_US)
unsigned int g_frontendApplyModeChoiceEventHandlerRecords[28] = {
    0x00000E06, 0x00000003, 0x00423C20, 0x00000E03, 0x00000003, 0x0042436C, 0x00000002, 0x00000003,
    0x00424508, 0x00000001, 0x00000003, 0x00424128, 0x0000000A, 0x00000003, 0x004244B4, 0x00000000,
    0x00000000, 0x00000000, 0x00660000, 0x00040000, (unsigned int)&g_playerSettingsSlotNumberFormat + 0x4,
    (unsigned int)&g_playerSettingsSlotNumberFormat + 0x10, (unsigned int)&g_playerSettingsSlotNumberFormat + 0xC,
    (unsigned int)&g_playerSettingsSlotNumberFormat + 0x8,
    (unsigned int)&g_playerSettingsSlotNumberFormat + 0xC, (unsigned int)&g_playerSettingsSlotNumberFormat + 0x8,
    (unsigned int)&g_playerSettingsSlotNumberFormat + 0x10, (unsigned int)&g_playerSettingsSlotNumberFormat + 0x4,
};
#endif

/* RESULTS_REFRESHTRIALCATALOGUEWIDGETS_DATA.CPP */
#ifdef VERSION_DE
struct {
    s32 g_currentStagePreset;
    u8 retainedEventWords[12];
    void * g_trialCatalogueScreen;
} g_trialCatalogueStageScreenState __attribute__((aligned(4))) = {
    0,
    { 0x0, 0x0, 0x1, 0xa4, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0 },
    0
};
typedef char g_trialCatalogueStageScreenStateSizeCheck[
    (sizeof(g_trialCatalogueStageScreenState) == 20) ? 1 : -1];
#endif
#ifdef VERSION_EU
struct {
    s32 g_currentStagePreset;
    u8 retainedInstructionWords[12];
    void * g_trialCatalogueScreen;
} g_trialCatalogueStageScreenState __attribute__((aligned(4))) = {
    0,
    { 0x34, 0x21, 0xff, 0xff, 0x4a, 0x11, 0x8c, 0x6c, 0x3, 0x21, 0x88, 0x24 },
    0
};
typedef char g_trialCatalogueStageScreenStateSizeCheck[
    (sizeof(g_trialCatalogueStageScreenState) == 20) ? 1 : -1];
#endif
#ifdef VERSION_EU_X
struct {
    s32 g_currentStagePreset;
    u8 retainedInstructionWords[12];
    void * g_trialCatalogueScreen;
} g_trialCatalogueStageScreenState __attribute__((aligned(4))) = {
    0,
    { 0x0, 0x0, 0x0, 0x0, 0x8f, 0xa7, 0x0, 0x28, 0x24, 0x2, 0x0, 0x33 },
    0
};
typedef char g_trialCatalogueStageScreenStateSizeCheck[
    (sizeof(g_trialCatalogueStageScreenState) == 20) ? 1 : -1];
#endif
#ifdef VERSION_US
char g_trialCatalogueStageScreenState[20] __attribute__((aligned(4))) = "\000\000\000\000RENADE_LAUNC\000\000\000\000";
#endif
#ifdef VERSION_US_REV1
struct {
    s32 g_currentStagePreset;
    u8 retainedRecordWords[12];
    void * g_trialCatalogueScreen;
} g_trialCatalogueStageScreenState __attribute__((aligned(4))) = {
    0,
    { 0x0, 0x0, 0x0, 0x0, 0xb, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1e, 0x53 },
    0
};
typedef char g_trialCatalogueStageScreenStateSizeCheck[
    (sizeof(g_trialCatalogueStageScreenState) == 20) ? 1 : -1];
#endif

#if defined(VERSION_DE) || defined(VERSION_EU_X)
#if defined(VERSION_DE)
struct {
    OverlayTrialStage trialStages[36];
    OverlayTrialWidgetGroup trialWidgets[64];
    ResidentEventHandlerEntry eventHandlers1776[13];
    ResidentEventHandlerEntry eventHandlers1932[13];
    u8 retainedRecordWord[4];
    ResidentEventHandlerEntry eventHandlers2092[4];
} g_resultsRefreshTrialCatalogueWidgetsRecord __attribute__((aligned(4))) = {
    { { 420, 2, 0, { 1, -1, 2, -1 } }, { 342, 2, 1, { -1, 2, -1, 0 } }, { 341, 2, 2, { 1, 3, 4, 0 } }, { 343, 2, 3,
    { -1, -1, 4, 2 } }, { 410, 3, 4, { 5, 29, 13, 2 } }, { 345, 2, 5, { -1, 13, 6, 4 } }, { 352, 1, 6, { -1, 14, 7,
    5 } }, { 349, 0, 7, { -1, 9, 8, 6 } }, { 350, 3, 8, { -1, 9, -1, 7 } }, { 417, 3, 9, { 15, 27, -1, 14 } }, { 351, 3,
    10, { 9, 28, 27, 11 } }, { 353, 2, 11, { 14, 28, 10, 12 } }, { 354, 2, 12, { 13, 28, 11, 4 } }, { 347, 3, 13, { 6,
    11, 14, 4 } }, { 348, 2, 14, { 7, 10, 9, 13 } }, { 422, 1, 15, { -1, 9, 16, -1 } }, { 359, 0, 16, { -1, 17, 19,
    15 } }, { 363, 2, 17, { 16, -1, 18, 15 } }, { 362, 2, 18, { 19, -1, 20, 17 } }, { 360, 2, 19, { -1, 18, 20, 16 } },
    { 361, 3, 20, { -1, 22, 21, 19 } }, { 377, 1, 21, { 20, 22, -1, -1 } }, { 429, 3, 22, { 20, 23, -1, -1 } }, { 395,
    0, 23, { 24, -1, 22, 26 } }, { 432, 2, 24, { 22, 23, -1, 25 } }, { 375, 3, 25, { -1, 23, 24, 27 } }, { 394, 1, 26,
    { 25, -1, 23, 27 } }, { 392, 2, 27, { 9, 31, 25, 10 } }, { 357, 3, 28, { 11, 31, 27, -1 } }, { 421, 1, 29, { 4, 30,
    31, -1 } }, { 356, 3, 30, { 29, -1, 31, -1 } }, { 355, 3, 31, { 28, -1, 32, 30 } }, { 399, 3, 32, { -1, -1, 33,
    31 } }, { 400, 0, 33, { -1, -1, 34, 32 } }, { 401, 1, 34, { -1, -1, 35, 33 } }, { 412, 3, 35, { -1, -1, -1,
    34 } } },
    { { 420, 342, 366 }, { 420, 341, 358 }, { 342, 341, 364 }, { 341, 343, 344 }, { 341, 410, 371 }, { 343, 410, 409 },
    { 410, 421, 411 }, { 410, 347, 378 }, { 410, 345, 413 }, { 345, 347, 365 }, { 345, 352, 382 }, { 352, 348, 368 },
    { 352, 349, 383 }, { 349, 417, 415 }, { 349, 350, 381 }, { 350, 417, 414 }, { 417, 392, 419 }, { 417, 422, 418 },
    { 351, 357, 436 }, { 351, 392, 393 }, { 351, 417, 416 }, { 353, 357, 405 }, { 353, 351, 387 }, { 353, 348, 389 },
    { 354, 357, 437 }, { 354, 353, 386 }, { 354, 347, 385 }, { 347, 353, 384 }, { 347, 348, 379 }, { 347, 352, 369 },
    { 348, 351, 388 }, { 348, 417, 380 }, { 348, 349, 367 }, { 422, 363, 423 }, { 422, 359, 376 }, { 359, 363, 372 },
    { 359, 360, 373 }, { 363, 362, 424 }, { 363, 360, 425 }, { 362, 361, 390 }, { 360, 362, 391 }, { 360, 361, 374 },
    { 361, 377, 427 }, { 361, 429, 426 }, { 377, 429, 428 }, { 429, 395, 430 }, { 429, 432, 431 }, { 395, 394, 398 },
    { 395, 375, 396 }, { 432, 395, 433 }, { 432, 375, 434 }, { 375, 394, 397 }, { 375, 392, 370 }, { 394, 392, 435 },
    { 392, 357, 439 }, { 392, 355, 440 }, { 357, 355, 406 }, { 421, 356, 408 }, { 421, 355, 438 }, { 356, 355, 407 },
    { 355, 399, 404 }, { 399, 400, 402 }, { 400, 401, 403 }, { 401, 412, 346 } },
    { { 3591, 10, RESIDENT_HANDLER_PACKED(Results_ShowResultsPlayerModels) }, { 3592, 10,
    RESIDENT_HANDLER_PACKED(Results_AnimateResultsOptionsScreen) }, { 10, 10,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_HandleTrialOptionRelease) }, { 3594, 10,
    RESIDENT_HANDLER_PACKED(Results_RenderResultsOptionsPreview) }, { 3590, 10,
    RESIDENT_HANDLER_PACKED(Results_CreateResultsOptionsScreen) }, { 3587, 10,
    (ResidentEventHandler)(void *)&CTrialCatalogue_CloseTrialOptionsScreen_Address }, { 2, 10,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_ExitTrialCatalogue) }, { 1, 10,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_ConfirmTrialStage) }, { 5, 10,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_SelectNeighborAbove) }, { 6, 10,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_SelectNeighborBelow) }, { 8, 10,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_SelectNeighborRight) }, { 7, 10,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_SelectNeighborLeft) }, { 0, 0, (ResidentEventHandler)0 } },
    { { 3591, 15, RESIDENT_HANDLER_PACKED(Results_ShowResultsPlayerModels) }, { 3592, 15,
    RESIDENT_HANDLER_PACKED(Results_AnimateResultsOptionsScreen) }, { 10, 15,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_HandleTrialOptionRelease) }, { 3594, 15,
    RESIDENT_HANDLER_PACKED(Results_RenderResultsOptionsPreview) }, { 3590, 15,
    RESIDENT_HANDLER_PACKED(Results_CreateResultsOptionsScreen) }, { 3587, 15,
    (ResidentEventHandler)(void *)&CTrialCatalogue_CloseTrialOptionsScreen_Address }, { 2, 15,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_ExitTrialCatalogue) }, { 1, 15,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_ConfirmTrialStage) }, { 5, 15,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_SelectNeighborAbove) }, { 6, 15,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_SelectNeighborBelow) }, { 8, 15,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_SelectNeighborRight) }, { 7, 15,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_SelectNeighborLeft) }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x0, 0x0, 0x0, 0x2 },
    { { 3590, 14, RESIDENT_HANDLER_PACKED(Match_ClearGermanLoadingHints) }, { 2, 14,
    RESIDENT_HANDLER_PACKED(Frontend_CloseMatchMenu) }, { 1, 14, RESIDENT_HANDLER_PACKED(Match_HandleMatchMessage) },
    { 0, 0, (ResidentEventHandler)0 } }
};
typedef char g_resultsRefreshTrialCatalogueWidgetsRecordSizeCheck[
    (sizeof(g_resultsRefreshTrialCatalogueWidgetsRecord) == 2140) ? 1 : -1];
#endif
#if defined(VERSION_EU_X)
struct {
    OverlayTrialStage trialStages[36];
    OverlayTrialWidgetGroup trialWidgets[64];
    ResidentEventHandlerEntry eventHandlers1776[13];
    ResidentEventHandlerEntry eventHandlers1932[13];
    u8 retainedInstructionWord[4];
    ResidentEventHandlerEntry eventHandlers2092[4];
} g_resultsRefreshTrialCatalogueWidgetsRecord __attribute__((aligned(4))) = {
    { { 426, 2, 0, { 1, -1, 2, -1 } }, { 348, 2, 1, { -1, 2, -1, 0 } }, { 347, 2, 2, { 1, 3, 4, 0 } }, { 349, 2, 3,
    { -1, -1, 4, 2 } }, { 416, 3, 4, { 5, 29, 13, 2 } }, { 351, 2, 5, { -1, 13, 6, 4 } }, { 358, 1, 6, { -1, 14, 7,
    5 } }, { 355, 0, 7, { -1, 9, 8, 6 } }, { 356, 3, 8, { -1, 9, -1, 7 } }, { 423, 3, 9, { 15, 27, -1, 14 } }, { 357, 3,
    10, { 9, 28, 27, 11 } }, { 359, 2, 11, { 14, 28, 10, 12 } }, { 360, 2, 12, { 13, 28, 11, 4 } }, { 353, 3, 13, { 6,
    11, 14, 4 } }, { 354, 2, 14, { 7, 10, 9, 13 } }, { 428, 1, 15, { -1, 9, 16, -1 } }, { 365, 0, 16, { -1, 17, 19,
    15 } }, { 369, 2, 17, { 16, -1, 18, 15 } }, { 368, 2, 18, { 19, -1, 20, 17 } }, { 366, 2, 19, { -1, 18, 20, 16 } },
    { 367, 3, 20, { -1, 22, 21, 19 } }, { 383, 1, 21, { 20, 22, -1, -1 } }, { 435, 3, 22, { 20, 23, -1, -1 } }, { 401,
    0, 23, { 24, -1, 22, 26 } }, { 438, 2, 24, { 22, 23, -1, 25 } }, { 381, 3, 25, { -1, 23, 24, 27 } }, { 400, 1, 26,
    { 25, -1, 23, 27 } }, { 398, 2, 27, { 9, 31, 25, 10 } }, { 363, 3, 28, { 11, 31, 27, -1 } }, { 427, 1, 29, { 4, 30,
    31, -1 } }, { 362, 3, 30, { 29, -1, 31, -1 } }, { 361, 3, 31, { 28, -1, 32, 30 } }, { 405, 3, 32, { -1, -1, 33,
    31 } }, { 406, 0, 33, { -1, -1, 34, 32 } }, { 407, 1, 34, { -1, -1, 35, 33 } }, { 418, 3, 35, { -1, -1, -1,
    34 } } },
    { { 426, 348, 372 }, { 426, 347, 364 }, { 348, 347, 370 }, { 347, 349, 350 }, { 347, 416, 377 }, { 349, 416, 415 },
    { 416, 427, 417 }, { 416, 353, 384 }, { 416, 351, 419 }, { 351, 353, 371 }, { 351, 358, 388 }, { 358, 354, 374 },
    { 358, 355, 389 }, { 355, 423, 421 }, { 355, 356, 387 }, { 356, 423, 420 }, { 423, 398, 425 }, { 423, 428, 424 },
    { 357, 363, 442 }, { 357, 398, 399 }, { 357, 423, 422 }, { 359, 363, 411 }, { 359, 357, 393 }, { 359, 354, 395 },
    { 360, 363, 443 }, { 360, 359, 392 }, { 360, 353, 391 }, { 353, 359, 390 }, { 353, 354, 385 }, { 353, 358, 375 },
    { 354, 357, 394 }, { 354, 423, 386 }, { 354, 355, 373 }, { 428, 369, 429 }, { 428, 365, 382 }, { 365, 369, 378 },
    { 365, 366, 379 }, { 369, 368, 430 }, { 369, 366, 431 }, { 368, 367, 396 }, { 366, 368, 397 }, { 366, 367, 380 },
    { 367, 383, 433 }, { 367, 435, 432 }, { 383, 435, 434 }, { 435, 401, 436 }, { 435, 438, 437 }, { 401, 400, 404 },
    { 401, 381, 402 }, { 438, 401, 439 }, { 438, 381, 440 }, { 381, 400, 403 }, { 381, 398, 376 }, { 400, 398, 441 },
    { 398, 363, 445 }, { 398, 361, 446 }, { 363, 361, 412 }, { 427, 362, 414 }, { 427, 361, 444 }, { 362, 361, 413 },
    { 361, 405, 410 }, { 405, 406, 408 }, { 406, 407, 409 }, { 407, 418, 352 } },
    { { 3591, 10, RESIDENT_HANDLER_PACKED(Results_ShowResultsPlayerModels) }, { 3592, 10,
    RESIDENT_HANDLER_PACKED(Results_AnimateResultsOptionsScreen) }, { 10, 10,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_HandleTrialOptionRelease) }, { 3594, 10,
    RESIDENT_HANDLER_PACKED(Results_RenderResultsOptionsPreview) }, { 3590, 10,
    RESIDENT_HANDLER_PACKED(Results_CreateResultsOptionsScreen) }, { 3587, 10,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_CloseTrialOptionsScreen) }, { 2, 10,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_ExitTrialCatalogue) }, { 1, 10,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_ConfirmTrialStage) }, { 5, 10,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_SelectNeighborAbove) }, { 6, 10,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_SelectNeighborBelow) }, { 8, 10,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_SelectNeighborRight) }, { 7, 10,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_SelectNeighborLeft) }, { 0, 0, (ResidentEventHandler)0 } },
    { { 3591, 15, RESIDENT_HANDLER_PACKED(Results_ShowResultsPlayerModels) }, { 3592, 15,
    RESIDENT_HANDLER_PACKED(Results_AnimateResultsOptionsScreen) }, { 10, 15,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_HandleTrialOptionRelease) }, { 3594, 15,
    RESIDENT_HANDLER_PACKED(Results_RenderResultsOptionsPreview) }, { 3590, 15,
    RESIDENT_HANDLER_PACKED(Results_CreateResultsOptionsScreen) }, { 3587, 15,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_CloseTrialOptionsScreen) }, { 2, 15,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_ExitTrialCatalogue) }, { 1, 15,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_ConfirmTrialStage) }, { 5, 15,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_SelectNeighborAbove) }, { 6, 15,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_SelectNeighborBelow) }, { 8, 15,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_SelectNeighborRight) }, { 7, 15,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_SelectNeighborLeft) }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x8f, 0xb4, 0x0, 0x20 },
    { { 3590, 14, RESIDENT_HANDLER_PACKED(Frontend_ClearEuxLoadingHints) }, { 2, 14,
    RESIDENT_HANDLER_PACKED(Frontend_CloseMatchMenu) }, { 1, 14,
    RESIDENT_HANDLER_PACKED(Frontend_HandleMatchMenuMessage) }, { 0, 0, (ResidentEventHandler)0 } }
};
typedef char g_resultsRefreshTrialCatalogueWidgetsRecordSizeCheck[
    (sizeof(g_resultsRefreshTrialCatalogueWidgetsRecord) == 2140) ? 1 : -1];
#endif
#endif

#if !(defined(VERSION_DE) || defined(VERSION_EU_X))
#if defined(VERSION_EU)
struct {
    OverlayTrialStage trialStages[36];
} g_trialCatalogueStageGraph __attribute__((aligned(4))) = {
    { { 422, 2, 0, { 1, -1, 2, -1 } }, { 344, 2, 1, { -1, 2, -1, 0 } }, { 343, 2, 2, { 1, 3, 4, 0 } }, { 345, 2, 3,
    { -1, -1, 4, 2 } }, { 412, 3, 4, { 5, 29, 13, 2 } }, { 347, 2, 5, { -1, 13, 6, 4 } }, { 354, 1, 6, { -1, 14, 7,
    5 } }, { 351, 0, 7, { -1, 9, 8, 6 } }, { 352, 3, 8, { -1, 9, -1, 7 } }, { 419, 3, 9, { 15, 27, -1, 14 } }, { 353, 3,
    10, { 9, 28, 27, 11 } }, { 355, 2, 11, { 14, 28, 10, 12 } }, { 356, 2, 12, { 13, 28, 11, 4 } }, { 349, 3, 13, { 6,
    11, 14, 4 } }, { 350, 2, 14, { 7, 10, 9, 13 } }, { 424, 1, 15, { -1, 9, 16, -1 } }, { 361, 0, 16, { -1, 17, 19,
    15 } }, { 365, 2, 17, { 16, -1, 18, 15 } }, { 364, 2, 18, { 19, -1, 20, 17 } }, { 362, 2, 19, { -1, 18, 20, 16 } },
    { 363, 3, 20, { -1, 22, 21, 19 } }, { 379, 1, 21, { 20, 22, -1, -1 } }, { 431, 3, 22, { 20, 23, -1, -1 } }, { 397,
    0, 23, { 24, -1, 22, 26 } }, { 434, 2, 24, { 22, 23, -1, 25 } }, { 377, 3, 25, { -1, 23, 24, 27 } }, { 396, 1, 26,
    { 25, -1, 23, 27 } }, { 394, 2, 27, { 9, 31, 25, 10 } }, { 359, 3, 28, { 11, 31, 27, -1 } }, { 423, 1, 29, { 4, 30,
    31, -1 } }, { 358, 3, 30, { 29, -1, 31, -1 } }, { 357, 3, 31, { 28, -1, 32, 30 } }, { 401, 3, 32, { -1, -1, 33,
    31 } }, { 402, 0, 33, { -1, -1, 34, 32 } }, { 403, 1, 34, { -1, -1, 35, 33 } }, { 414, 3, 35, { -1, -1, -1, 34 } } }
};
typedef char g_trialCatalogueStageGraphSizeCheck[
    (sizeof(g_trialCatalogueStageGraph) == 1008) ? 1 : -1];
#endif
#if defined(VERSION_US)
struct {
    OverlayTrialStage trialStages[36];
} g_trialCatalogueStageGraph __attribute__((aligned(4))) = {
    { { 422, 2, 0, { 1, -1, 2, -1 } }, { 344, 2, 1, { -1, 2, -1, 0 } }, { 343, 2, 2, { 1, 3, 4, 0 } }, { 345, 2, 3,
    { -1, -1, 4, 2 } }, { 412, 3, 4, { 5, 29, 13, 2 } }, { 347, 2, 5, { -1, 13, 6, 4 } }, { 354, 1, 6, { -1, 14, 7,
    5 } }, { 351, 0, 7, { -1, 9, 8, 6 } }, { 352, 3, 8, { -1, 9, -1, 7 } }, { 419, 3, 9, { 15, 27, -1, 14 } }, { 353, 3,
    10, { 9, 28, 27, 11 } }, { 355, 2, 11, { 14, 28, 10, 12 } }, { 356, 2, 12, { 13, 28, 11, 4 } }, { 349, 3, 13, { 6,
    11, 14, 4 } }, { 350, 2, 14, { 7, 10, 9, 13 } }, { 424, 1, 15, { -1, 9, 16, -1 } }, { 361, 0, 16, { -1, 17, 19,
    15 } }, { 365, 2, 17, { 16, -1, 18, 15 } }, { 364, 2, 18, { 19, -1, 20, 17 } }, { 362, 2, 19, { -1, 18, 20, 16 } },
    { 363, 3, 20, { -1, 22, 21, 19 } }, { 379, 1, 21, { 20, 22, -1, -1 } }, { 431, 3, 22, { 20, 23, -1, -1 } }, { 397,
    0, 23, { 24, -1, 22, 26 } }, { 434, 2, 24, { 22, 23, -1, 25 } }, { 377, 3, 25, { -1, 23, 24, 27 } }, { 396, 1, 26,
    { 25, -1, 23, 27 } }, { 394, 2, 27, { 9, 31, 25, 10 } }, { 359, 3, 28, { 11, 31, 27, -1 } }, { 423, 1, 29, { 4, 30,
    31, -1 } }, { 358, 3, 30, { 29, -1, 31, -1 } }, { 357, 3, 31, { 28, -1, 32, 30 } }, { 401, 3, 32, { -1, -1, 33,
    31 } }, { 402, 0, 33, { -1, -1, 34, 32 } }, { 403, 1, 34, { -1, -1, 35, 33 } }, { 414, 3, 35, { -1, -1, -1, 34 } } }
};
typedef char g_trialCatalogueStageGraphSizeCheck[
    (sizeof(g_trialCatalogueStageGraph) == 1008) ? 1 : -1];
#endif
#if defined(VERSION_US_REV1)
struct {
    OverlayTrialStage trialStages[36];
} g_trialCatalogueStageGraph __attribute__((aligned(4))) = {
    { { 422, 2, 0, { 1, -1, 2, -1 } }, { 344, 2, 1, { -1, 2, -1, 0 } }, { 343, 2, 2, { 1, 3, 4, 0 } }, { 345, 2, 3,
    { -1, -1, 4, 2 } }, { 412, 3, 4, { 5, 29, 13, 2 } }, { 347, 2, 5, { -1, 13, 6, 4 } }, { 354, 1, 6, { -1, 14, 7,
    5 } }, { 351, 0, 7, { -1, 9, 8, 6 } }, { 352, 3, 8, { -1, 9, -1, 7 } }, { 419, 3, 9, { 15, 27, -1, 14 } }, { 353, 3,
    10, { 9, 28, 27, 11 } }, { 355, 2, 11, { 14, 28, 10, 12 } }, { 356, 2, 12, { 13, 28, 11, 4 } }, { 349, 3, 13, { 6,
    11, 14, 4 } }, { 350, 2, 14, { 7, 10, 9, 13 } }, { 424, 1, 15, { -1, 9, 16, -1 } }, { 361, 0, 16, { -1, 17, 19,
    15 } }, { 365, 2, 17, { 16, -1, 18, 15 } }, { 364, 2, 18, { 19, -1, 20, 17 } }, { 362, 2, 19, { -1, 18, 20, 16 } },
    { 363, 3, 20, { -1, 22, 21, 19 } }, { 379, 1, 21, { 20, 22, -1, -1 } }, { 431, 3, 22, { 20, 23, -1, -1 } }, { 397,
    0, 23, { 24, -1, 22, 26 } }, { 434, 2, 24, { 22, 23, -1, 25 } }, { 377, 3, 25, { -1, 23, 24, 27 } }, { 396, 1, 26,
    { 25, -1, 23, 27 } }, { 394, 2, 27, { 9, 31, 25, 10 } }, { 359, 3, 28, { 11, 31, 27, -1 } }, { 423, 1, 29, { 4, 30,
    31, -1 } }, { 358, 3, 30, { 29, -1, 31, -1 } }, { 357, 3, 31, { 28, -1, 32, 30 } }, { 401, 3, 32, { -1, -1, 33,
    31 } }, { 402, 0, 33, { -1, -1, 34, 32 } }, { 403, 1, 34, { -1, -1, 35, 33 } }, { 414, 3, 35, { -1, -1, -1, 34 } } }
};
typedef char g_trialCatalogueStageGraphSizeCheck[
    (sizeof(g_trialCatalogueStageGraph) == 1008) ? 1 : -1];
#endif
#endif

#if defined(VERSION_US)
struct {
    OverlayTrialWidgetGroup trialWidgets[64];
    ResidentEventHandlerEntry eventHandlers768[13];
    ResidentEventHandlerEntry eventHandlers924[13];
    u8 retainedCescText[4];
    ResidentEventHandlerEntry eventHandlers1084[4];
} g_resultsRefreshTrialCatalogueWidgetsWords_us __attribute__((aligned(4))) = {
    { { 422, 344, 368 }, { 422, 343, 360 }, { 344, 343, 366 }, { 343, 345, 346 }, { 343, 412, 373 }, { 345, 412, 411 },
    { 412, 423, 413 }, { 412, 349, 380 }, { 412, 347, 415 }, { 347, 349, 367 }, { 347, 354, 384 }, { 354, 350, 370 },
    { 354, 351, 385 }, { 351, 419, 417 }, { 351, 352, 383 }, { 352, 419, 416 }, { 419, 394, 421 }, { 419, 424, 420 },
    { 353, 359, 438 }, { 353, 394, 395 }, { 353, 419, 418 }, { 355, 359, 407 }, { 355, 353, 389 }, { 355, 350, 391 },
    { 356, 359, 439 }, { 356, 355, 388 }, { 356, 349, 387 }, { 349, 355, 386 }, { 349, 350, 381 }, { 349, 354, 371 },
    { 350, 353, 390 }, { 350, 419, 382 }, { 350, 351, 369 }, { 424, 365, 425 }, { 424, 361, 378 }, { 361, 365, 374 },
    { 361, 362, 375 }, { 365, 364, 426 }, { 365, 362, 427 }, { 364, 363, 392 }, { 362, 364, 393 }, { 362, 363, 376 },
    { 363, 379, 429 }, { 363, 431, 428 }, { 379, 431, 430 }, { 431, 397, 432 }, { 431, 434, 433 }, { 397, 396, 400 },
    { 397, 377, 398 }, { 434, 397, 435 }, { 434, 377, 436 }, { 377, 396, 399 }, { 377, 394, 372 }, { 396, 394, 437 },
    { 394, 359, 441 }, { 394, 357, 442 }, { 359, 357, 408 }, { 423, 358, 410 }, { 423, 357, 440 }, { 358, 357, 409 },
    { 357, 401, 406 }, { 401, 402, 404 }, { 402, 403, 405 }, { 403, 414, 348 } },
    { { 3591, 10, RESIDENT_HANDLER_PACKED(Results_ShowResultsPlayerModels) }, { 3592, 10,
    RESIDENT_HANDLER_PACKED(Results_AnimateResultsOptionsScreen) }, { 10, 10,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_HandleTrialOptionRelease) }, { 3594, 10,
    RESIDENT_HANDLER_PACKED(Results_RenderResultsOptionsPreview) }, { 3590, 10,
    RESIDENT_HANDLER_PACKED(Results_CreateResultsOptionsScreen) }, { 3587, 10,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_CloseTrialOptionsScreen) }, { 2, 10,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_ExitTrialCatalogue) }, { 1, 10,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_ConfirmTrialStage) }, { 5, 10,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_SelectNeighborAbove) }, { 6, 10,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_SelectNeighborBelow) }, { 8, 10,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_SelectNeighborRight) }, { 7, 10,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_SelectNeighborLeft) }, { 0, 0, (ResidentEventHandler)0 } },
    { { 3591, 15, RESIDENT_HANDLER_PACKED(Results_ShowResultsPlayerModels) }, { 3592, 15,
    RESIDENT_HANDLER_PACKED(Results_AnimateResultsOptionsScreen) }, { 10, 15,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_HandleTrialOptionRelease) }, { 3594, 15,
    RESIDENT_HANDLER_PACKED(Results_RenderResultsOptionsPreview) }, { 3590, 15,
    RESIDENT_HANDLER_PACKED(Results_CreateResultsOptionsScreen) }, { 3587, 15,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_CloseTrialOptionsScreen) }, { 2, 15,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_ExitTrialCatalogue) }, { 1, 15,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_ConfirmTrialStage) }, { 5, 15,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_SelectNeighborAbove) }, { 6, 15,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_SelectNeighborBelow) }, { 8, 15,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_SelectNeighborRight) }, { 7, 15,
    RESIDENT_HANDLER_PACKED(CTrialCatalogue_SelectNeighborLeft) }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x43, 0x45, 0x53, 0x43 },
    { { 3590, 14, RESIDENT_HANDLER_PACKED(Frontend_ClearLoadingHints) }, { 2, 14,
    RESIDENT_HANDLER_PACKED(Frontend_CloseMatchMenu) }, { 1, 14,
    RESIDENT_HANDLER_PACKED(Frontend_HandleMatchMenuMessage) }, { 0, 0, (ResidentEventHandler)0 } }
};
typedef char g_resultsRefreshTrialCatalogueWidgetsWords_usSizeCheck[
    (sizeof(g_resultsRefreshTrialCatalogueWidgetsWords_us) == 1132) ? 1 : -1];
#endif

#if defined(VERSION_EU)
struct {
    OverlayTrialWidgetGroup trialWidgets[64];
    ResidentEventHandlerEntry eventHandlers768[13];
    ResidentEventHandlerEntry eventHandlers924[13];
    u8 retainedInstructionWord[4];
    ResidentEventHandlerEntry eventHandlers1084[4];
} g_resultsRefreshTrialCatalogueWidgetsWords_eu __attribute__((aligned(4))) = {
    { { 422, 344, 368 }, { 422, 343, 360 }, { 344, 343, 366 }, { 343, 345, 346 }, { 343, 412, 373 }, { 345, 412, 411 },
    { 412, 423, 413 }, { 412, 349, 380 }, { 412, 347, 415 }, { 347, 349, 367 }, { 347, 354, 384 }, { 354, 350, 370 },
    { 354, 351, 385 }, { 351, 419, 417 }, { 351, 352, 383 }, { 352, 419, 416 }, { 419, 394, 421 }, { 419, 424, 420 },
    { 353, 359, 438 }, { 353, 394, 395 }, { 353, 419, 418 }, { 355, 359, 407 }, { 355, 353, 389 }, { 355, 350, 391 },
    { 356, 359, 439 }, { 356, 355, 388 }, { 356, 349, 387 }, { 349, 355, 386 }, { 349, 350, 381 }, { 349, 354, 371 },
    { 350, 353, 390 }, { 350, 419, 382 }, { 350, 351, 369 }, { 424, 365, 425 }, { 424, 361, 378 }, { 361, 365, 374 },
    { 361, 362, 375 }, { 365, 364, 426 }, { 365, 362, 427 }, { 364, 363, 392 }, { 362, 364, 393 }, { 362, 363, 376 },
    { 363, 379, 429 }, { 363, 431, 428 }, { 379, 431, 430 }, { 431, 397, 432 }, { 431, 434, 433 }, { 397, 396, 400 },
    { 397, 377, 398 }, { 434, 397, 435 }, { 434, 377, 436 }, { 377, 396, 399 }, { 377, 394, 372 }, { 396, 394, 437 },
    { 394, 359, 441 }, { 394, 357, 442 }, { 359, 357, 408 }, { 423, 358, 410 }, { 423, 357, 440 }, { 358, 357, 409 },
    { 357, 401, 406 }, { 401, 402, 404 }, { 402, 403, 405 }, { 403, 414, 348 } },
    { { 3591, 10, (ResidentEventHandler)(void *)&addrLow_Results_ShowResultsPlayerModels }, { 3592, 10,
    (ResidentEventHandler)(void *)&addrLow_Results_AnimateResultsOptionsScreen }, { 10, 10,
    (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_HandleTrialOptionRelease }, { 3594, 10,
    (ResidentEventHandler)(void *)&addrLow_Results_RenderResultsOptionsPreview }, { 3590, 10,
    (ResidentEventHandler)(void *)&addrLow_Results_CreateResultsOptionsScreen }, { 3587, 10,
    (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_CloseTrialOptionsScreen }, { 2, 10,
    (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_ExitTrialCatalogue }, { 1, 10,
    (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_ConfirmTrialStage }, { 5, 10,
    (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_TrialOptionsEvent05Handler }, { 6, 10,
    (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_TrialOptionsEvent06Handler }, { 8, 10,
    (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_TrialOptionsEvent08Handler }, { 7, 10,
    (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_TrialOptionsEvent07Handler }, { 0, 0,
    (ResidentEventHandler)0 } },
    { { 3591, 15, (ResidentEventHandler)(void *)&addrLow_Results_ShowResultsPlayerModels }, { 3592, 15,
    (ResidentEventHandler)(void *)&addrLow_Results_AnimateResultsOptionsScreen }, { 10, 15,
    (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_HandleTrialOptionRelease }, { 3594, 15,
    (ResidentEventHandler)(void *)&addrLow_Results_RenderResultsOptionsPreview }, { 3590, 15,
    (ResidentEventHandler)(void *)&addrLow_Results_CreateResultsOptionsScreen }, { 3587, 15,
    (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_CloseTrialOptionsScreen }, { 2, 15,
    (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_ExitTrialCatalogue }, { 1, 15,
    (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_ConfirmTrialStage }, { 5, 15,
    (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_TrialOptionsEvent05Handler }, { 6, 15,
    (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_TrialOptionsEvent06Handler }, { 8, 15,
    (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_TrialOptionsEvent08Handler }, { 7, 15,
    (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_TrialOptionsEvent07Handler }, { 0, 0,
    (ResidentEventHandler)0 } },
    { 0x21, 0xad, 0x0, 0x10 },
    { { 3590, 14, (ResidentEventHandler)(void *)&addrLow_Frontend_ClearEuLoadingHints }, { 2, 14,
    (ResidentEventHandler)(void *)&addrLow_Frontend_CloseMatchMenu }, { 1, 14,
    (ResidentEventHandler)(void *)&addrLow_Frontend_HandleMatchMenuMessage }, { 0, 0,
    (ResidentEventHandler)0 } }
};
typedef char g_resultsRefreshTrialCatalogueWidgetsWords_euSizeCheck[
    (sizeof(g_resultsRefreshTrialCatalogueWidgetsWords_eu) == 1132) ? 1 : -1];
#endif

/* SCENARIOSETUP_FILLRESULTROWS_DATA.CPP */

#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
#if defined(VERSION_DE)
ResidentEventHandlerEntry g_scenarioSetupFillResultRowsEventHandlers[9] = {
    { 3592, 17, RESIDENT_HANDLER_PACKED(Frontend_HandleResultsConfirmation) }, { 3590, 17,
    RESIDENT_HANDLER_PACKED(ScenarioSetup_OpenResultsScreen) }, { 3587, 17,
    RESIDENT_HANDLER_PACKED(Frontend_DestroyMatchResults) }, { 2, 17,
    RESIDENT_HANDLER_PACKED(Frontend_ConsumeResultsEvent) }, { 1, 17,
    RESIDENT_HANDLER_PACKED(Frontend_ActivateResultsAction) }, { 3594, 17,
    RESIDENT_HANDLER_PACKED(Frontend_UpdateMatchResultsTransition) }, { 5, 17,
    RESIDENT_HANDLER_PACKED(Frontend_ScrollResultsBackward) }, { 6, 17,
    RESIDENT_HANDLER_PACKED(Frontend_ScrollResultsForward) },
    { 0, 0, (ResidentEventHandler)0 }
};
#endif
#if defined(VERSION_EU)
ResidentEventHandlerEntry g_scenarioSetupFillResultRowsEventHandlers[9] = {
    { 3592, 17, (ResidentEventHandler)(void *)&addrLow_Frontend_HandleResultsConfirmation }, { 3590, 17,
    (ResidentEventHandler)(void *)&addrLow_ScenarioSetup_OpenResultsScreen }, { 3587, 17,
    (ResidentEventHandler)(void *)&addrLow_Frontend_DestroyMatchResults }, { 2, 17,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ConsumeResultsEvent }, { 1, 17,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ActivateResultsAction }, { 3594, 17,
    (ResidentEventHandler)(void *)&addrLow_Frontend_UpdateMatchResultsTransition }, { 5, 17,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ScrollResultsBackward }, { 6, 17,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ScrollResultsForward },
    { 0, 0, (ResidentEventHandler)0 }
};
#endif
#if defined(VERSION_EU_X)
ResidentEventHandlerEntry g_scenarioSetupFillResultRowsEventHandlers[9] = {
    { 3592, 17, RESIDENT_HANDLER_PACKED(Frontend_HandleResultsConfirmation) }, { 3590, 17,
    RESIDENT_HANDLER_PACKED(ScenarioSetup_OpenResultsScreen) }, { 3587, 17,
    RESIDENT_HANDLER_PACKED(Frontend_DestroyMatchResults) }, { 2, 17,
    RESIDENT_HANDLER_PACKED(Frontend_ConsumeResultsEvent) }, { 1, 17,
    RESIDENT_HANDLER_PACKED(Frontend_ActivateResultsAction) }, { 3594, 17,
    RESIDENT_HANDLER_PACKED(Frontend_UpdateMatchResultsTransition) }, { 5, 17,
    RESIDENT_HANDLER_PACKED(Frontend_ScrollResultsBackward) }, { 6, 17,
    RESIDENT_HANDLER_PACKED(Frontend_ScrollResultsForward) },
    { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)
#if defined(VERSION_US)
ResidentEventHandlerEntry g_scenarioSetupFillResultRowsEventHandlers[9] = {
    { 3592, 17, (ResidentEventHandler)(void *)&addrLow_Frontend_HandleResultsConfirmation2 }, { 3590, 17,
    (ResidentEventHandler)(void *)&addrLow_ScenarioSetup_OpenResultsScreen2 }, { 3587, 17,
    (ResidentEventHandler)(void *)&addrLow_Frontend_DestroyMatchResults2 }, { 2, 17,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ConsumeResultsEvent2 }, { 1, 17,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ActivateResultsAction2 }, { 3594, 17,
    (ResidentEventHandler)(void *)&addrLow_Frontend_UpdateMatchResultsTransition2 }, { 5, 17,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ScrollResultsBackward2 }, { 6, 17,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ScrollResultsForward2 },
    { 0, 0, (ResidentEventHandler)0 }
};
#endif
#if defined(VERSION_US_REV1)
ResidentEventHandlerEntry g_scenarioSetupFillResultRowsEventHandlers[9] = {
    { 3592, 17, (ResidentEventHandler)(void *)&addrLow_Frontend_HandleResultsConfirmation2 }, { 3590, 17,
    (ResidentEventHandler)(void *)&addrLow_ScenarioSetup_OpenResultsScreen2 }, { 3587, 17,
    (ResidentEventHandler)(void *)&addrLow_Frontend_DestroyMatchResults2 }, { 2, 17,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ConsumeResultsEvent2 }, { 1, 17,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ActivateResultsAction2 }, { 3594, 17,
    (ResidentEventHandler)(void *)&addrLow_Frontend_UpdateMatchResultsTransition2 }, { 5, 17,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ScrollResultsBackward2 }, { 6, 17,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ScrollResultsForward2 },
    { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif

/* FRONTEND_UPDATEPLAYERCOUNTSCREEN_DATA.CPP */

/* FRONTEND_DISPATCHPLAYERCOUNTEVENT_DATA.CPP */
#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
#if defined(VERSION_DE)
struct {
    ResidentEventHandlerEntry eventHandlers0[8];
    u8 retainedEventWords[12];
} g_frontendDispatchPlayerCountEventRecord __attribute__((aligned(4))) = {
    { { 3592, 26, RESIDENT_HANDLER_PACKED(Frontend_UpdatePlayerCountScreen) }, { 3590, 26,
    RESIDENT_HANDLER_PACKED(Frontend_CreatePlayerCountScreenDe) }, { 3587, 26,
    RESIDENT_HANDLER_PACKED(Frontend_DestroyPlayerCountScreen) }, { 2, 26,
    RESIDENT_HANDLER_PACKED(Frontend_CancelPlayerCount) }, { 1, 26,
    RESIDENT_HANDLER_PACKED(Frontend_ConfirmPlayerCount) }, { 8, 26,
    RESIDENT_HANDLER_PACKED(Frontend_IncreasePlayerCount) }, { 7, 26,
    RESIDENT_HANDLER_PACKED(Frontend_DecreasePlayerCount) }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xe, 0x7, 0x0, 0x0, 0x0, 0x13 }
};
typedef char g_frontendDispatchPlayerCountEventRecordSizeCheck[
    (sizeof(g_frontendDispatchPlayerCountEventRecord) == 108) ? 1 : -1];
#endif
#if defined(VERSION_EU)
struct {
    ResidentEventHandlerEntry handlers[8];
    u32 retainedRecordWords[3];
} g_frontendDispatchPlayerCountEventRecord __attribute__((aligned(4))) = {
    { { 3592, 26, (ResidentEventHandler)(void *)&addrLow_Frontend_UpdatePlayerCountScreen }, { 3590, 26,
    (ResidentEventHandler)(void *)&addrLow_Frontend_CreatePlayerCountScreenEu }, { 3587, 26,
    (ResidentEventHandler)(void *)&addrLow_Frontend_DestroyPlayerCountScreen }, { 2, 26,
    (ResidentEventHandler)(void *)&addrLow_Frontend_CancelPlayerCount }, { 1, 26,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ConfirmPlayerCount }, { 8, 26,
    (ResidentEventHandler)(void *)&addrLow_Frontend_IncreasePlayerCount }, { 7, 26,
    (ResidentEventHandler)(void *)&addrLow_Frontend_DecreasePlayerCount }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x020712D0, 0x00000250, 0x021712D0 }
};
#endif
#if defined(VERSION_EU_X)
ResidentEventHandlerEntry g_frontendDispatchPlayerCountEventRecord[9] = {
    { 3592, 26, RESIDENT_HANDLER_PACKED(Frontend_UpdatePlayerCountScreen) }, { 3590, 26,
    RESIDENT_HANDLER_PACKED(Frontend_CreatePlayerCountScreenEux) }, { 3587, 26,
    RESIDENT_HANDLER_PACKED(Frontend_DestroyPlayerCountScreen) }, { 2, 26,
    RESIDENT_HANDLER_PACKED(Frontend_CancelPlayerCount) }, { 1, 26,
    RESIDENT_HANDLER_PACKED(Frontend_ConfirmPlayerCount) }, { 8, 26,
    RESIDENT_HANDLER_PACKED(Frontend_IncreasePlayerCount) }, { 7, 26,
    RESIDENT_HANDLER_PACKED(Frontend_DecreasePlayerCount) }, { 0, 0, (ResidentEventHandler)0 },
    { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)
#if defined(VERSION_US)
ResidentEventHandlerEntry g_frontendDispatchPlayerCountEventHandlers[8] = {
    { 3592, 26, (ResidentEventHandler)(void *)&g_Frontend_UpdatePlayerCountScreenAddress }, { 3590, 26,
    (ResidentEventHandler)(void *)&addrLow_Frontend_CreatePlayerCountScreen }, { 3587, 26,
    (ResidentEventHandler)(void *)&addrLow_Frontend_DestroyPlayerCountScreen2 }, { 2, 26,
    (ResidentEventHandler)(void *)&addrLow_Frontend_CancelPlayerCount2 }, { 1, 26,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ConfirmPlayerCount2 }, { 8, 26,
    (ResidentEventHandler)(void *)&addrLow_Frontend_IncreasePlayerCount2 }, { 7, 26,
    (ResidentEventHandler)(void *)&addrLow_Frontend_DecreasePlayerCount2 }, { 0, 0, (ResidentEventHandler)0 }
};
#endif
#if defined(VERSION_US_REV1)
ResidentEventHandlerEntry g_frontendDispatchPlayerCountEventHandlers[8] = {
    { 3592, 26, (ResidentEventHandler)(void *)&g_Frontend_UpdatePlayerCountScreenAddress }, { 3590, 26,
    (ResidentEventHandler)(void *)&addrLow_Frontend_CreatePlayerCountScreen }, { 3587, 26,
    (ResidentEventHandler)(void *)&addrLow_Frontend_DestroyPlayerCountScreen2 }, { 2, 26,
    (ResidentEventHandler)(void *)&addrLow_Frontend_CancelPlayerCount2 }, { 1, 26,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ConfirmPlayerCount2 }, { 8, 26,
    (ResidentEventHandler)(void *)&addrLow_Frontend_IncreasePlayerCount2 }, { 7, 26,
    (ResidentEventHandler)(void *)&addrLow_Frontend_DecreasePlayerCount2 }, { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif

#if defined(VERSION_US)
char s_projectsDmPath_us[12] =
    "\\Projects\\DM";
#endif

/* FRONTEND_DISPATCHPAKPROFILEEVENT_DATA.CPP */


#if defined(VERSION_US) || defined(VERSION_US_REV1)
#if defined(VERSION_US)
ResidentEventHandlerEntry g_pakScreenUpdateEventHandlers[3] = {
    { 3591, 19, (ResidentEventHandler)(void *)&addrLow_Frontend_ReturnProfileEventZero2 }, { 3594, 19,
    (ResidentEventHandler)(void *)&addrLow_Frontend_UpdatePakScreenExit2 }, { 3592, 19,
    (ResidentEventHandler)(void *)&addrLow_Frontend_UpdatePakScreenPanels2 }
};
#endif
#if defined(VERSION_US_REV1)
ResidentEventHandlerEntry g_pakScreenUpdateEventHandlers[3] = {
    { 3591, 19, (ResidentEventHandler)(void *)&addrLow_Frontend_ReturnProfileEventZero2 }, { 3594, 19,
    (ResidentEventHandler)(void *)&addrLow_Frontend_UpdatePakScreenExit2 }, { 3592, 19,
    (ResidentEventHandler)(void *)&addrLow_Frontend_UpdatePakScreenPanels2 }
};
#endif
#endif

#if defined(VERSION_US)
ResidentEventHandlerEntry g_pakProfileScreenEventHandlers[11] = {
    { 3590, 19, RESIDENT_HANDLER_PACKED(Frontend_CreatePakProfileScreen) }, { 3587, 19,
    RESIDENT_HANDLER_PACKED(Frontend_DestroyPakProfileScreen) }, { 2, 19,
    RESIDENT_HANDLER_PACKED(PAKInterface_HandlePlayerPanelBack) }, { 1, 19,
    RESIDENT_HANDLER_PACKED(PAKInterface_ActivatePlayerPanelAction) }, { 10, 19,
    RESIDENT_HANDLER_PACKED(Frontend_HandlePakProfileInput) }, { 11, 19,
    RESIDENT_HANDLER_PACKED(Frontend_ResetNameRepeatOnEvent) }, { 5, 19,
    RESIDENT_HANDLER_PACKED(PAKInterface_HandlePakMenuConfirm) }, { 6, 19,
    RESIDENT_HANDLER_PACKED(PAKInterface_HandleNextPanelSelection) },
    { 8, 19, RESIDENT_HANDLER_PACKED(PAKInterface_MoveNameCursorForward) }, { 7, 19,
    RESIDENT_HANDLER_PACKED(PAKInterface_MoveNameCursorBackward) }, { 0, 0, (ResidentEventHandler)0 }
};
#endif

/* FRONTEND_DESTROYPAUSEMENU_DATA.CPP */

#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
#if defined(VERSION_DE)
struct {
    ResidentEventHandlerEntry eventHandlers0[9];
    ResidentEventHandlerEntry eventHandlers108[8];
    ResidentEventHandlerEntry eventHandlers204[8];
    u8 retainedEventWords[8];
} g_frontendDestroyPauseMenuRecord __attribute__((aligned(4))) = {
    { { 3591, 1, RESIDENT_HANDLER_PACKED(Frontend_SetPauseMenuInputMode) }, { 3592, 1,
    RESIDENT_HANDLER_PACKED(Frontend_ReturnPauseEventZeroAlt) }, { 3594, 1,
    RESIDENT_HANDLER_PACKED(Frontend_ReturnPauseEventZero) }, { 3590, 1,
    RESIDENT_HANDLER_PACKED(Frontend_CreatePauseMenu) }, { 3587, 1,
    (ResidentEventHandler)(void *)&Frontend_DestroyPauseMenu_Address }, { 1, 1,
    RESIDENT_HANDLER_PACKED(Frontend_ActivatePauseMenuAction) }, { 2, 1,
    RESIDENT_HANDLER_PACKED(Frontend_ConsumePauseMenuEvent) }, { 10, 1,
    RESIDENT_HANDLER_PACKED(Frontend_ResumeMatchOnInput) }, { 0, 0, (ResidentEventHandler)0 } },
    { { 3591, 31, RESIDENT_HANDLER_PACKED(Timed_SetConfirmationInputMode) }, { 3592, 31,
    RESIDENT_HANDLER_PACKED(Frontend_ReturnConfirmationEventZero) }, { 3594, 31,
    RESIDENT_HANDLER_PACKED(Timed_FinishPauseConfirmationTransition) }, { 3590, 31,
    RESIDENT_HANDLER_PACKED(Frontend_CreatePauseConfirmation) }, { 3587, 31,
    RESIDENT_HANDLER_PACKED(Timed_DestroyPauseConfirmation) }, { 1, 31,
    RESIDENT_HANDLER_PACKED(Timed_UpdateTimedScreen) }, { 2, 31,
    RESIDENT_HANDLER_PACKED(Frontend_ConsumeConfirmationEvent) }, { 0, 0, (ResidentEventHandler)0 } },
    { { 3591, 32, RESIDENT_HANDLER_PACKED(Frontend_ClearPage67ModeFlag) }, { 3592, 32,
    RESIDENT_HANDLER_PACKED(Frontend_IgnorePage67Event) }, { 3594, 32,
    RESIDENT_HANDLER_PACKED(Frontend_UpdatePage67Exit) }, { 3590, 32,
    RESIDENT_HANDLER_PACKED(Frontend_CreateTimedMenu) }, { 3587, 32,
    RESIDENT_HANDLER_PACKED(Frontend_FreePage67Screen) }, { 1, 32,
    RESIDENT_HANDLER_PACKED(Frontend_HandlePage67Choice) }, { 2, 32,
    RESIDENT_HANDLER_PACKED(Frontend_AcknowledgePage67Event) }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x0, 0x0, 0xe, 0x7, 0x0, 0x0, 0x0, 0x5 }
};
typedef char g_frontendDestroyPauseMenuRecordSizeCheck[(sizeof(g_frontendDestroyPauseMenuRecord) == 308) ? 1 : -1];
#endif
#if defined(VERSION_EU)
struct {
    ResidentEventHandlerEntry handlers[25];
    u32 retainedRecordWords[2];
} g_frontendDestroyPauseMenuRecord __attribute__((aligned(4))) = {
    { { 3591, 1, (ResidentEventHandler)(void *)&addrLow_Frontend_SetPauseMenuInputMode }, { 3592, 1,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ReturnPauseEventZeroAlt }, { 3594, 1,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ReturnPauseEventZero }, { 3590, 1,
    (ResidentEventHandler)(void *)&addrLow_Frontend_CreatePauseMenu }, { 3587, 1,
    (ResidentEventHandler)(void *)&addrLow_Frontend_DestroyPauseMenu }, { 1, 1,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ActivatePauseMenuAction }, { 2, 1,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ConsumePauseMenuEvent }, { 10, 1,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ResumeMatchOnInput }, { 0, 0, (ResidentEventHandler)0 },
    { 3591, 31, (ResidentEventHandler)(void *)&addrLow_Timed_SetConfirmationInputMode }, { 3592, 31,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ReturnConfirmationEventZero }, { 3594, 31,
    (ResidentEventHandler)(void *)&addrLow_Timed_FinishPauseConfirmationTransition }, { 3590, 31,
    (ResidentEventHandler)(void *)&addrLow_Frontend_CreatePauseConfirmation }, { 3587, 31,
    (ResidentEventHandler)(void *)&addrLow_Timed_DestroyPauseConfirmation }, { 1, 31,
    (ResidentEventHandler)(void *)&addrLow_Timed_UpdateTimedScreen }, { 2, 31,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ConsumeConfirmationEvent }, { 0, 0,
    (ResidentEventHandler)0 }, { 3591, 32,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ClearPage67ModeFlag }, { 3592, 32,
    (ResidentEventHandler)(void *)&addrLow_Frontend_IgnorePage67Event }, { 3594, 32,
    (ResidentEventHandler)(void *)&addrLow_Frontend_UpdatePage67Exit }, { 3590, 32,
    (ResidentEventHandler)(void *)&addrLow_Frontend_CreateTimedMenu }, { 3587, 32,
    (ResidentEventHandler)(void *)&addrLow_Frontend_FreePage67Screen }, { 1, 32,
    (ResidentEventHandler)(void *)&addrLow_Frontend_HandlePage67Choice }, { 2, 32,
    (ResidentEventHandler)(void *)&addrLow_Frontend_AcknowledgePage67Event }, { 0, 0,
    (ResidentEventHandler)0 } },
    { 0x00000000, 0x00800000 }
};
#endif
#if defined(VERSION_EU_X)
struct {
    ResidentEventHandlerEntry eventHandlers0[9];
    ResidentEventHandlerEntry eventHandlers108[8];
    ResidentEventHandlerEntry eventHandlers204[8];
    u8 retainedInstructionWords[8];
} g_frontendDestroyPauseMenuRecord __attribute__((aligned(4))) = {
    { { 3591, 1, RESIDENT_HANDLER_PACKED(Frontend_SetPauseMenuInputMode) }, { 3592, 1,
    RESIDENT_HANDLER_PACKED(Frontend_ReturnPauseEventZeroAlt) }, { 3594, 1,
    RESIDENT_HANDLER_PACKED(Frontend_ReturnPauseEventZero) }, { 3590, 1,
    RESIDENT_HANDLER_PACKED(Frontend_CreatePauseMenu) }, { 3587, 1,
    RESIDENT_HANDLER_PACKED(Frontend_DestroyPauseMenu) }, { 1, 1,
    RESIDENT_HANDLER_PACKED(Frontend_ActivatePauseMenuAction) }, { 2, 1,
    RESIDENT_HANDLER_PACKED(Frontend_ConsumePauseMenuEvent) }, { 10, 1,
    RESIDENT_HANDLER_PACKED(Frontend_ResumeMatchOnInput) }, { 0, 0, (ResidentEventHandler)0 } },
    { { 3591, 31, RESIDENT_HANDLER_PACKED(Timed_SetConfirmationInputMode) }, { 3592, 31,
    RESIDENT_HANDLER_PACKED(Frontend_ReturnConfirmationEventZero) }, { 3594, 31,
    RESIDENT_HANDLER_PACKED(Timed_FinishPauseConfirmationTransition) }, { 3590, 31,
    RESIDENT_HANDLER_PACKED(Frontend_CreatePauseConfirmation) }, { 3587, 31,
    RESIDENT_HANDLER_PACKED(Timed_DestroyPauseConfirmation) }, { 1, 31,
    RESIDENT_HANDLER_PACKED(Timed_UpdateTimedScreen) }, { 2, 31,
    RESIDENT_HANDLER_PACKED(Frontend_ConsumeConfirmationEvent) }, { 0, 0, (ResidentEventHandler)0 } },
    { { 3591, 32, RESIDENT_HANDLER_PACKED(Frontend_ClearPage67ModeFlag) }, { 3592, 32,
    RESIDENT_HANDLER_PACKED(Frontend_IgnorePage67Event) }, { 3594, 32,
    RESIDENT_HANDLER_PACKED(Frontend_UpdatePage67Exit) }, { 3590, 32,
    RESIDENT_HANDLER_PACKED(Frontend_CreateTimedMenu) }, { 3587, 32,
    RESIDENT_HANDLER_PACKED(Frontend_FreePage67Screen) }, { 1, 32,
    RESIDENT_HANDLER_PACKED(Frontend_HandlePage67Choice) }, { 2, 32,
    RESIDENT_HANDLER_PACKED(Frontend_AcknowledgePage67Event) }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x8f, 0xa7, 0x0, 0x28, 0x24, 0x2, 0x0, 0x33 }
};
typedef char g_frontendDestroyPauseMenuRecordSizeCheck[(sizeof(g_frontendDestroyPauseMenuRecord) == 308) ? 1 : -1];
#endif
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)
#if defined(VERSION_US)
ResidentEventHandlerEntry g_frontendDestroyPauseMenuEventHandlers[9] = {
    { 3591, 1, (ResidentEventHandler)(void *)&addrLow_Frontend_SetPauseMenuInputMode2 }, { 3592, 1,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ReturnPauseEventZeroAlt2 }, { 3594, 1,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ReturnPauseEventZero2 }, { 3590, 1,
    (ResidentEventHandler)(void *)&addrLow_Frontend_CreatePauseMenu2 }, { 3587, 1,
    (ResidentEventHandler)(void *)&addrLow_Frontend_DestroyPauseMenu2 }, { 1, 1,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ActivatePauseMenuAction2 }, { 2, 1,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ConsumePauseMenuEvent2 }, { 10, 1,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ResumeMatchOnInput2 },
    { 0, 0, (ResidentEventHandler)0 }
};
#endif
#if defined(VERSION_US_REV1)
ResidentEventHandlerEntry g_frontendDestroyPauseMenuEventHandlers[9] = {
    { 3591, 1, (ResidentEventHandler)(void *)&addrLow_Frontend_SetPauseMenuInputMode2 }, { 3592, 1,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ReturnPauseEventZeroAlt2 }, { 3594, 1,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ReturnPauseEventZero2 }, { 3590, 1,
    (ResidentEventHandler)(void *)&addrLow_Frontend_CreatePauseMenu2 }, { 3587, 1,
    (ResidentEventHandler)(void *)&addrLow_Frontend_DestroyPauseMenu2 }, { 1, 1,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ActivatePauseMenuAction2 }, { 2, 1,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ConsumePauseMenuEvent2 }, { 10, 1,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ResumeMatchOnInput2 },
    { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif

#if defined(VERSION_US)
struct {
    ResidentEventHandlerEntry eventHandlers0[8];
    ResidentEventHandlerEntry eventHandlers96[8];
    u8 retainedRecordWords[8];
} g_pauseMenuEventHandlerRecords __attribute__((aligned(4))) = {
    { { 3591, 31, RESIDENT_HANDLER_PACKED(Timed_SetConfirmationInputMode) }, { 3592, 31,
    RESIDENT_HANDLER_PACKED(Frontend_ReturnConfirmationEventZero) }, { 3594, 31,
    RESIDENT_HANDLER_PACKED(Timed_FinishPauseConfirmationTransition) }, { 3590, 31,
    RESIDENT_HANDLER_PACKED(Frontend_CreatePauseConfirmation) }, { 3587, 31,
    RESIDENT_HANDLER_PACKED(Timed_DestroyPauseConfirmation) }, { 1, 31,
    RESIDENT_HANDLER_PACKED(Timed_UpdateTimedScreen) }, { 2, 31,
    RESIDENT_HANDLER_PACKED(Frontend_ConsumeConfirmationEvent) }, { 0, 0, (ResidentEventHandler)0 } },
    { { 3591, 32, RESIDENT_HANDLER_PACKED(Frontend_ClearPage67ModeFlag) }, { 3592, 32,
    RESIDENT_HANDLER_PACKED(Frontend_IgnorePage67Event) }, { 3594, 32,
    RESIDENT_HANDLER_PACKED(Frontend_UpdatePage67Exit) }, { 3590, 32,
    RESIDENT_HANDLER_PACKED(Frontend_CreateTimedMenu) }, { 3587, 32,
    RESIDENT_HANDLER_PACKED(Frontend_FreePage67Screen) }, { 1, 32,
    RESIDENT_HANDLER_PACKED(Frontend_HandlePage67Choice) }, { 2, 32,
    RESIDENT_HANDLER_PACKED(Frontend_AcknowledgePage67Event) }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x2e, 0x48, 0x1c, 0xf4, 0x0, 0x20, 0x43, 0x3a }
};
typedef char g_pauseMenuEventHandlerRecordsSizeCheck[(sizeof(g_pauseMenuEventHandlerRecords) == 200) ? 1 : -1];
#endif

/* PLAYER_INITPLAYERSETTINGSSCREEN_DATA.CPP */

/* G_ARENACOMPATIBILITYTABLE.CPP */
#if defined(VERSION_US_REV1)
OverlayTrialWidgetGroup g_arenaCompatibilityTable[64] = {
    { 422, 344, 368 }, { 422, 343, 360 }, { 344, 343, 366 }, { 343, 345, 346 }, { 343, 412, 373 }, { 345, 412, 411 },
    { 412, 423, 413 }, { 412, 349, 380 },
    { 412, 347, 415 }, { 347, 349, 367 }, { 347, 354, 384 }, { 354, 350, 370 }, { 354, 351, 385 }, { 351, 419, 417 },
    { 351, 352, 383 }, { 352, 419, 416 },
    { 419, 394, 421 }, { 419, 424, 420 }, { 353, 359, 438 }, { 353, 394, 395 }, { 353, 419, 418 }, { 355, 359, 407 },
    { 355, 353, 389 }, { 355, 350, 391 },
    { 356, 359, 439 }, { 356, 355, 388 }, { 356, 349, 387 }, { 349, 355, 386 }, { 349, 350, 381 }, { 349, 354, 371 },
    { 350, 353, 390 }, { 350, 419, 382 },
    { 350, 351, 369 }, { 424, 365, 425 }, { 424, 361, 378 }, { 361, 365, 374 }, { 361, 362, 375 }, { 365, 364, 426 },
    { 365, 362, 427 }, { 364, 363, 392 },
    { 362, 364, 393 }, { 362, 363, 376 }, { 363, 379, 429 }, { 363, 431, 428 }, { 379, 431, 430 }, { 431, 397, 432 },
    { 431, 434, 433 }, { 397, 396, 400 },
    { 397, 377, 398 }, { 434, 397, 435 }, { 434, 377, 436 }, { 377, 396, 399 }, { 377, 394, 372 }, { 396, 394, 437 },
    { 394, 359, 441 }, { 394, 357, 442 },
    { 359, 357, 408 }, { 423, 358, 410 }, { 423, 357, 440 }, { 358, 357, 409 }, { 357, 401, 406 }, { 401, 402, 404 },
    { 402, 403, 405 }, { 403, 414, 348 }
};

ResidentEventHandlerEntry g_resultsOptionsEventHandlers[2][13] = {
{
    { 3591, 10, (ResidentEventHandler)(void *)&addrLow_Results_ShowResultsPlayerModels2 }, { 3592, 10,
    (ResidentEventHandler)(void *)&addrLow_Results_AnimateResultsOptionsScreen2 }, { 10, 10,
    (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_HandleTrialOptionRelease2 }, { 3594, 10,
    (ResidentEventHandler)(void *)&addrLow_Results_RenderResultsOptionsPreview2 }, { 3590, 10,
    (ResidentEventHandler)(void *)&addrLow_Results_CreateResultsOptionsScreen2 }, { 3587, 10,
    (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_CloseTrialOptionsScreen2 }, { 2, 10,
    (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_ExitTrialCatalogue2 }, { 1, 10,
    (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_ConfirmTrialStage2 },
    { 5, 10, (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_SelectNeighborAbove }, { 6, 10,
    (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_SelectNeighborBelow }, { 8, 10,
    (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_SelectNeighborRight }, { 7, 10,
    (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_SelectNeighborLeft }, { 0, 0,
    (ResidentEventHandler)0 }
},

{
    { 3591, 15, (ResidentEventHandler)(void *)&addrLow_Results_ShowResultsPlayerModels2 }, { 3592, 15,
    (ResidentEventHandler)(void *)&addrLow_Results_AnimateResultsOptionsScreen2 }, { 10, 15,
    (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_HandleTrialOptionRelease2 }, { 3594, 15,
    (ResidentEventHandler)(void *)&addrLow_Results_RenderResultsOptionsPreview2 }, { 3590, 15,
    (ResidentEventHandler)(void *)&addrLow_Results_CreateResultsOptionsScreen2 }, { 3587, 15,
    (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_CloseTrialOptionsScreen2 }, { 2, 15,
    (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_ExitTrialCatalogue2 }, { 1, 15,
    (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_ConfirmTrialStage2 },
    { 5, 15, (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_SelectNeighborAbove }, { 6, 15,
    (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_SelectNeighborBelow }, { 8, 15,
    (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_SelectNeighborRight }, { 7, 15,
    (ResidentEventHandler)(void *)&addrLow_CTrialCatalogue_SelectNeighborLeft }, { 0, 0,
    (ResidentEventHandler)0 }
}
};

struct {
    u8 retainedFloatWord[4];
    ResidentEventHandlerEntry eventHandlers4[4];
} g_GArenacompatibilitytablePointerWords __attribute__((aligned(4))) = {
    { 0x3f, 0x19, 0x99, 0x9a },
    { { 3590, 14, (ResidentEventHandler)(void *)&addrLow_Frontend_ClearLoadingHints2 }, { 2, 14,
    (ResidentEventHandler)(void *)&addrLow_Frontend_CloseMatchMenu2 }, { 1, 14,
    (ResidentEventHandler)(void *)&addrLow_Frontend_HandleMatchMenuMessage2 }, { 0, 0,
    (ResidentEventHandler)0 } }
};
typedef char g_GArenacompatibilitytablePointerWordsSizeCheck[
    (sizeof(g_GArenacompatibilitytablePointerWords) == 52) ? 1 : -1];
#endif

/* G_OVERLAYNINEEOSTAGBYTES.CPP */
#if defined(VERSION_US_REV1)
struct {
    u8 retainedEosTagWords[12];
} g_portalEosTagBytes __attribute__((aligned(4))) = {
    { 0x04, 0x2E, 0x65, 0x6F, 0x73, 0x00, 0x00, 0x00, 0x00, 0x94, 0x0F, 0x00 }
};
#endif

/* G_PAKPROFILEEVENTHANDLERS.CPP */
#if defined(VERSION_US_REV1)
ResidentEventHandlerEntry g_pakProfileCreateEventHandler[1] = {
    { 3590, 19, (ResidentEventHandler)(void *)&addrLow_Frontend_CreatePakProfileScreen }
};

ResidentEventHandlerEntry g_pakProfileEventHandlers[10] = {
    { 3587, 19, (ResidentEventHandler)(void *)&addrLow_Frontend_DestroyPakProfileScreen2 }, { 2, 19,
    (ResidentEventHandler)(void *)&addrLow_PAKInterface_HandlePlayerPanelBack2 }, { 1, 19,
    (ResidentEventHandler)(void *)&addrLow_PAKInterface_ActivatePlayerPanelAction2 }, { 10, 19,
    (ResidentEventHandler)(void *)&g_frontend_HandlePakProfileInputEntry }, { 11, 19,
    (ResidentEventHandler)(void *)&addrLow_Frontend_ResetNameRepeatOnEvent2 }, { 5, 19,
    (ResidentEventHandler)(void *)&addrLow_PAKInterface_HandlePakMenuConfirm2 }, { 6, 19,
    (ResidentEventHandler)(void *)&addrLow_PAKInterface_HandleNextPanelSelection2 }, { 8, 19,
    (ResidentEventHandler)(void *)&addrLow_PAKInterface_MoveNameCursorForward2 },
    { 7, 19, (ResidentEventHandler)(void *)&addrLow_PAKInterface_MoveNameCursorBackward2 }, { 0, 0,
    (ResidentEventHandler)0 }
};
#endif

/* FRONTEND_DISPATCHRESIDENTACTOREVENT_DATA.CPP */
#if defined(VERSION_US_REV1)
/* Pause confirmation event handlers, one row per resident actor id (31, 32). */
ResidentEventHandlerEntry g_pauseConfirmationHandlersByActor[2][8] = {
    {
        { 3591, 31, (ResidentEventHandler)(void *)&addrLow_Timed_SetConfirmationInputMode2 }, { 3592, 31,
        (ResidentEventHandler)(void *)&addrLow_Frontend_ReturnConfirmationEventZero2 }, { 3594, 31,
        (ResidentEventHandler)(void *)&addrLow_Timed_FinishPauseConfirmationTransition2 }, { 3590, 31,
        (ResidentEventHandler)(void *)&addrLow_Frontend_CreatePauseConfirmation2 }, { 3587, 31,
        (ResidentEventHandler)(void *)&addrLow_Timed_DestroyPauseConfirmation2 }, { 1, 31,
        (ResidentEventHandler)(void *)&addrLow_Timed_UpdateTimedScreen2 }, { 2, 31,
        (ResidentEventHandler)(void *)&addrLow_Frontend_ConsumeConfirmationEvent2 }, { 0, 0,
        (ResidentEventHandler)0 }
    },
    {
        { 3591, 32, (ResidentEventHandler)(void *)&addrLow_Timed_SetConfirmationInputMode3 }, { 3592, 32,
        (ResidentEventHandler)(void *)&addrLow_Frontend_ReturnConfirmationEventZero3 }, { 3594, 32,
        (ResidentEventHandler)(void *)&addrLow_Timed_FinishPauseConfirmationTransition3 }, { 3590, 32,
        (ResidentEventHandler)(void *)&addrLow_Frontend_CreatePauseConfirmation3 }, { 3587, 32,
        (ResidentEventHandler)(void *)&addrLow_Timed_DestroyPauseConfirmation3 }, { 1, 32,
        (ResidentEventHandler)(void *)&addrLow_Timed_UpdateTimedScreen3 }, { 2, 32,
        (ResidentEventHandler)(void *)&addrLow_Frontend_ConsumeConfirmationEvent3 }, { 0, 0,
        (ResidentEventHandler)0 }
    },
};

struct {
    u8 retainedEosTagWords[8];
} g_frontendDispatchResidentActorEventData __attribute__((aligned(4))) = {
    { 0x71, 0x75, 0x04, 0x2E, 0x65, 0x6F, 0x73, 0x00 }
};
#endif

#if defined(VERSION_US_REV1)
RestArenaCatalogueRecord g_catalogueArenaRecordWords[40] = {
    { 813, 815, 2, 0 },
    { 786, 816, 2, 1 },
    { 785, 860, 2, 2 },
    { 787, 835, 2, 3 },
    { 799, 801, 2, 4 },
    { 804, 788, 2, 5 },
    { 844, 841, 1, 6 },
    { 853, 858, 0, 7 },
    { 824, 827, 3, 8 },
    { 800, 817, 2, 9 },
    { 831, 829, 3, 10 },
    { 803, 859, 2, 11 },
    { 793, 798, 2, 12 },
    { 820, 834, 3, 13 },
    { 802, 805, 2, 14 },
    { 843, 846, 1, 15 },
    { 852, 855, 0, 16 },
    { 794, 796, 2, 17 },
    { 809, 806, 2, 18 },
    { 808, 811, 2, 19 },
    { 830, 832, 3, 20 },
    { 836, 839, 1, 21 },
    { 795, 797, 2, 22 },
    { 851, 854, 0, 23 },
    { 807, 810, 2, 24 },
    { 819, 822, 3, 25 },
    { 837, 840, 1, 26 },
    { 814, 812, 2, 27 },
    { 818, 821, 3, 28 },
    { 842, 845, 1, 29 },
    { 848, 833, 3, 30 },
    { 847, 849, 3, 31 },
    { 826, 823, 3, 32 },
    { 857, 856, 0, 33 },
    { 838, 850, 1, 34 },
    { 825, 828, 3, 35 },
    { 790, -1, 2, 0 },
    { 792, -1, 3, 0 },
    { 791, -1, 1, 0 },
    { 789, -1, 0, 0 },
};
#endif

#if defined(VERSION_US_REV1)
/* Consecutive cup rows contain 5, 7, 11 and 17 arena widget ids. */
s32 g_cupArenaControls[40] = {
    789, 853, 852, 851, 857,
    791, 838, 837, 836, 844, 843, 842,
    792, 820, 819, 818, 826, 825, 824, 831, 830, 848, 847,
    790, 787, 804, 803, 802, 809, 808, 807, 814, 813, 786, 785, 799, 800, 793, 794, 795,
};
#endif

#if defined(VERSION_US_REV1)
ScenarioSetupMenuEventHandlerWords g_scenarioSetupMenuEventHandlerWords = {
    3592,
    20,
    (unsigned int)&ScenarioSetup_UpdateSetupTransition,
    3591,
    20,
    (unsigned int)&ScenarioSetup_ReturnSetupEventZeroAlt,
    10,
    20,
    (unsigned int)&ScenarioSetup_BeginSetupConfirmation,
    3590,
    20,
    (unsigned int)&CScenarioSetup_OpenScenarioSetupScreen,
    3587,
    20,
    (unsigned int)&ScenarioSetup_CloseSetupScreen,
    3594,
    20,
    (unsigned int)g_frontend_DrawSetupResultPanelsEntry,
    2,
    20,
    (unsigned int)&ScenarioSetup_EndSetupInput,
    1,
    20,
    (unsigned int)&ScenarioSetup_RefreshSetupScreen,
    5,
    20,
    (unsigned int)&ScenarioSetup_SelectPreviousCatalogueItem,
    6,
    20,
    (unsigned int)&ScenarioSetup_SelectNextSetupItem,
    8,
    20,
    (unsigned int)&ScenarioSetup_SelectNextCatalogueCategory,
    7,
    20,
    (unsigned int)&ScenarioSetup_SelectPreviousCatalogueCategory,
    { 0x00000000, 0x00000000, 0x00000000 },
};
#endif

#if defined(VERSION_US_REV1)
s32 k_scenarioSetupCatalogueTextIds[40] = {
    574, 610, 577, 582, 586, 590,
    594, 598, 602, 603, 575, 611,
    579, 583, 587, 591, 595, 599,
    604, 605, 576, 612, 580, 584,
    588, 592, 596, 600, 606, 607,
    578, 613, 581, 585, 589, 593,
    597, 601, 608, 609,
};
#endif

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X)
/* The pak profile screen's resident event handlers (event, actor kind 19, handler), read by
   Frontend_DispatchPakProfileEvent; a zero handler ends the table. */
extern s32 Frontend_ReturnProfileEventZero();
extern s32 Frontend_UpdatePakScreenExit();
extern s32 Frontend_UpdatePakScreenPanels();
extern s32 Frontend_DestroyPakProfileScreen();
extern s32 PAKInterface_HandlePlayerPanelBack();
extern s32 PAKInterface_ActivatePlayerPanelAction();
extern s32 Frontend_HandlePakProfileInput();
extern int Frontend_ResetNameRepeatOnEvent();
extern s32 PAKInterface_HandlePakMenuConfirm();
extern s32 PAKInterface_HandleNextPanelSelection();
extern s32 PAKInterface_MoveNameCursorForward();
extern s32 PAKInterface_MoveNameCursorBackward();
ResidentEventHandlerEntry g_pakProfileEventHandlers[14] = {
    { 3591, 19, RESIDENT_HANDLER_PACKED(Frontend_ReturnProfileEventZero) },
    { 3594, 19, RESIDENT_HANDLER_PACKED(Frontend_UpdatePakScreenExit) },
    { 3592, 19, RESIDENT_HANDLER_PACKED(Frontend_UpdatePakScreenPanels) },
#if defined(VERSION_EU)
    { 3590, 19, RESIDENT_HANDLER_PACKED(Frontend_CreatePakProfileScreenEu) },
#elif defined(VERSION_EU_X)
    { 3590, 19, RESIDENT_HANDLER_PACKED(Frontend_CreatePakProfileScreenEux) },
#else
    { 3590, 19, RESIDENT_HANDLER_PACKED(Frontend_CreatePakProfileScreenDe) },
#endif
    { 3587, 19, RESIDENT_HANDLER_PACKED(Frontend_DestroyPakProfileScreen) },
    { 2, 19, RESIDENT_HANDLER_PACKED(PAKInterface_HandlePlayerPanelBack) },
    { 1, 19, RESIDENT_HANDLER_PACKED(PAKInterface_ActivatePlayerPanelAction) },
    { 10, 19, RESIDENT_HANDLER_PACKED(Frontend_HandlePakProfileInput) },
    { 11, 19, RESIDENT_HANDLER_PACKED(Frontend_ResetNameRepeatOnEvent) },
    { 5, 19, RESIDENT_HANDLER_PACKED(PAKInterface_HandlePakMenuConfirm) },
    { 6, 19, RESIDENT_HANDLER_PACKED(PAKInterface_HandleNextPanelSelection) },
    { 8, 19, RESIDENT_HANDLER_PACKED(PAKInterface_MoveNameCursorForward) },
    { 7, 19, RESIDENT_HANDLER_PACKED(PAKInterface_MoveNameCursorBackward) },
    { 0, 0, (ResidentEventHandler)0 },
};
#endif
