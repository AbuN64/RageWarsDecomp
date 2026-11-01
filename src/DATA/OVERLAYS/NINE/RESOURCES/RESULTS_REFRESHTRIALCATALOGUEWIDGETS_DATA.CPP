#include "COMMON/FORMAT.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "DATA_OVERLAY_LAYOUTS.H"
#include "TYPES.H"

extern char CTrialCatalogue_CloseTrialOptionsScreen[];
extern char CTrialCatalogue_CloseTrialOptionsScreen_Address[];
extern char CTrialCatalogue_ConfirmTrialStage[];
extern char CTrialCatalogue_ExitTrialCatalogue[];
extern char CTrialCatalogue_HandleTrialOptionRelease[];
extern char CTrialCatalogue_SelectNeighborOne[];
extern char CTrialCatalogue_SelectNeighborThree[];
extern char CTrialCatalogue_SelectNeighborTwo[];
extern char CTrialCatalogue_SelectNeighborZero[];
extern char Frontend_ClearEuxLoadingHints[];
extern char Frontend_ClearLoadingHints[];
extern char Frontend_CloseMatchMenu[];
extern char Frontend_HandleMatchMenuMessage[];
extern char Match_ClearGermanLoadingHints[];
extern char Match_HandleMatchMessage[];
extern char Results_AnimateResultsOptionsScreen[];
extern char Results_CreateResultsOptionsScreen[];
extern char Results_RenderResultsOptionsPreview[];
extern char Results_ShowResultsPlayerModels[];
extern char g_CTrialCatalogue_CloseTrialOptionsScreenPackedAddress24[];
extern char g_CTrialCatalogue_ConfirmTrialStagePackedAddress24[];
extern char g_CTrialCatalogue_ExitTrialCataloguePackedAddress24[];
extern char g_CTrialCatalogue_HandleTrialOptionReleasePackedAddress24[];
extern char g_CTrialCatalogue_TrialOptionsEvent05HandlerPackedAddress24[];
extern char g_CTrialCatalogue_TrialOptionsEvent06HandlerPackedAddress24[];
extern char g_CTrialCatalogue_TrialOptionsEvent07HandlerPackedAddress24[];
extern char g_CTrialCatalogue_TrialOptionsEvent08HandlerPackedAddress24[];
extern char g_Frontend_ClearEuLoadingHintsPackedAddress24[];
extern char g_Frontend_CloseMatchMenuPackedAddress24[];
extern char g_Frontend_HandleMatchMenuMessagePackedAddress24[];
extern char g_Results_AnimateResultsOptionsScreenPackedAddress24[];
extern char g_Results_CreateResultsOptionsScreenPackedAddress24[];
extern char g_Results_RenderResultsOptionsPreviewPackedAddress24[];
extern char g_Results_ShowResultsPlayerModelsPackedAddress24[];

#include "include_asm.h"

/* 800E4658_2.CPP */
/* ROM-grounded data: rodata/writable/800E4680 */
#ifdef VERSION_DE
#if defined(VERSION_DE)
struct {
    s32 g_currentStagePreset;
    u8 alignmentFill4[12];
    void * g_trialCatalogueScreen;
} g_ResultsRefreshtrialcataloguewidgetsWords2 __attribute__((aligned(4))) = {
    0,
    { 0x0, 0x0, 0x1, 0xa4, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0 },
    0
};
typedef char g_ResultsRefreshtrialcataloguewidgetsWords2SizeCheck[(sizeof(g_ResultsRefreshtrialcataloguewidgetsWords2) == 20) ? 1 : -1];
#endif
#endif
#ifdef VERSION_EU
#if defined(VERSION_EU)
struct {
    s32 g_currentStagePreset;
    u8 alignmentFill4[12];
    void * g_trialCatalogueScreen;
} g_ResultsRefreshtrialcataloguewidgetsWords2 __attribute__((aligned(4))) = {
    0,
    { 0x34, 0x21, 0xff, 0xff, 0x4a, 0x11, 0x8c, 0x6c, 0x3, 0x21, 0x88, 0x24 },
    0
};
typedef char g_ResultsRefreshtrialcataloguewidgetsWords2SizeCheck[(sizeof(g_ResultsRefreshtrialcataloguewidgetsWords2) == 20) ? 1 : -1];
#endif
#endif
#ifdef VERSION_EU_X
#if defined(VERSION_EU_X)
struct {
    s32 g_currentStagePreset;
    u8 alignmentFill4[12];
    void * g_trialCatalogueScreen;
} g_ResultsRefreshtrialcataloguewidgetsWords2 __attribute__((aligned(4))) = {
    0,
    { 0x0, 0x0, 0x0, 0x0, 0x8f, 0xa7, 0x0, 0x28, 0x24, 0x2, 0x0, 0x33 },
    0
};
typedef char g_ResultsRefreshtrialcataloguewidgetsWords2SizeCheck[(sizeof(g_ResultsRefreshtrialcataloguewidgetsWords2) == 20) ? 1 : -1];
#endif
#endif
#ifdef VERSION_US
#if defined(VERSION_US)
char g_ResultsRefreshtrialcataloguewidgetsWords2[20] __attribute__((aligned(4))) = "\000\000\000\000RENADE_LAUNC\000\000\000\000";
#endif
#endif
#ifdef VERSION_US_REV1
#if defined(VERSION_US_REV1)
struct {
    s32 g_currentStagePreset;
    u8 alignmentFill4[12];
    void * g_trialCatalogueScreen;
} g_ResultsRefreshtrialcataloguewidgetsWords2 __attribute__((aligned(4))) = {
    0,
    { 0x0, 0x0, 0x0, 0x0, 0xb, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1e, 0x53 },
    0
};
typedef char g_ResultsRefreshtrialcataloguewidgetsWords2SizeCheck[(sizeof(g_ResultsRefreshtrialcataloguewidgetsWords2) == 20) ? 1 : -1];
#endif
#endif

/* 800E4694.CPP */
#if defined(VERSION_DE) || defined(VERSION_EU_X)
#if defined(VERSION_DE)
#if defined(VERSION_DE)
struct {
    OverlayTrialStage trialStages[36];
    OverlayTrialWidgetGroup trialWidgets[64];
    ResidentEventHandlerEntry eventHandlers1776[13];
    ResidentEventHandlerEntry eventHandlers1932[13];
    u8 alignmentFill2088[4];
    ResidentEventHandlerEntry eventHandlers2092[4];
} D_src_85547de0 __attribute__((aligned(4))) = {
    { { 420, 2, 0, { 1, -1, 2, -1 } }, { 342, 2, 1, { -1, 2, -1, 0 } }, { 341, 2, 2, { 1, 3, 4, 0 } }, { 343, 2, 3, { -1, -1, 4, 2 } }, { 410, 3, 4, { 5, 29, 13, 2 } }, { 345, 2, 5, { -1, 13, 6, 4 } }, { 352, 1, 6, { -1, 14, 7, 5 } }, { 349, 0, 7, { -1, 9, 8, 6 } }, { 350, 3, 8, { -1, 9, -1, 7 } }, { 417, 3, 9, { 15, 27, -1, 14 } }, { 351, 3, 10, { 9, 28, 27, 11 } }, { 353, 2, 11, { 14, 28, 10, 12 } }, { 354, 2, 12, { 13, 28, 11, 4 } }, { 347, 3, 13, { 6, 11, 14, 4 } }, { 348, 2, 14, { 7, 10, 9, 13 } }, { 422, 1, 15, { -1, 9, 16, -1 } }, { 359, 0, 16, { -1, 17, 19, 15 } }, { 363, 2, 17, { 16, -1, 18, 15 } }, { 362, 2, 18, { 19, -1, 20, 17 } }, { 360, 2, 19, { -1, 18, 20, 16 } }, { 361, 3, 20, { -1, 22, 21, 19 } }, { 377, 1, 21, { 20, 22, -1, -1 } }, { 429, 3, 22, { 20, 23, -1, -1 } }, { 395, 0, 23, { 24, -1, 22, 26 } }, { 432, 2, 24, { 22, 23, -1, 25 } }, { 375, 3, 25, { -1, 23, 24, 27 } }, { 394, 1, 26, { 25, -1, 23, 27 } }, { 392, 2, 27, { 9, 31, 25, 10 } }, { 357, 3, 28, { 11, 31, 27, -1 } }, { 421, 1, 29, { 4, 30, 31, -1 } }, { 356, 3, 30, { 29, -1, 31, -1 } }, { 355, 3, 31, { 28, -1, 32, 30 } }, { 399, 3, 32, { -1, -1, 33, 31 } }, { 400, 0, 33, { -1, -1, 34, 32 } }, { 401, 1, 34, { -1, -1, 35, 33 } }, { 412, 3, 35, { -1, -1, -1, 34 } } },
    { { 420, 342, 366 }, { 420, 341, 358 }, { 342, 341, 364 }, { 341, 343, 344 }, { 341, 410, 371 }, { 343, 410, 409 }, { 410, 421, 411 }, { 410, 347, 378 }, { 410, 345, 413 }, { 345, 347, 365 }, { 345, 352, 382 }, { 352, 348, 368 }, { 352, 349, 383 }, { 349, 417, 415 }, { 349, 350, 381 }, { 350, 417, 414 }, { 417, 392, 419 }, { 417, 422, 418 }, { 351, 357, 436 }, { 351, 392, 393 }, { 351, 417, 416 }, { 353, 357, 405 }, { 353, 351, 387 }, { 353, 348, 389 }, { 354, 357, 437 }, { 354, 353, 386 }, { 354, 347, 385 }, { 347, 353, 384 }, { 347, 348, 379 }, { 347, 352, 369 }, { 348, 351, 388 }, { 348, 417, 380 }, { 348, 349, 367 }, { 422, 363, 423 }, { 422, 359, 376 }, { 359, 363, 372 }, { 359, 360, 373 }, { 363, 362, 424 }, { 363, 360, 425 }, { 362, 361, 390 }, { 360, 362, 391 }, { 360, 361, 374 }, { 361, 377, 427 }, { 361, 429, 426 }, { 377, 429, 428 }, { 429, 395, 430 }, { 429, 432, 431 }, { 395, 394, 398 }, { 395, 375, 396 }, { 432, 395, 433 }, { 432, 375, 434 }, { 375, 394, 397 }, { 375, 392, 370 }, { 394, 392, 435 }, { 392, 357, 439 }, { 392, 355, 440 }, { 357, 355, 406 }, { 421, 356, 408 }, { 421, 355, 438 }, { 356, 355, 407 }, { 355, 399, 404 }, { 399, 400, 402 }, { 400, 401, 403 }, { 401, 412, 346 } },
    { { 3591, 10, (ResidentEventHandler)(void *)((char *)&Results_ShowResultsPlayerModels - 0x80000000U) }, { 3592, 10, (ResidentEventHandler)(void *)((char *)&Results_AnimateResultsOptionsScreen - 0x80000000U) }, { 10, 10, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_HandleTrialOptionRelease - 0x80000000U) }, { 3594, 10, (ResidentEventHandler)(void *)((char *)&Results_RenderResultsOptionsPreview - 0x80000000U) }, { 3590, 10, (ResidentEventHandler)(void *)((char *)&Results_CreateResultsOptionsScreen - 0x80000000U) }, { 3587, 10, (ResidentEventHandler)(void *)&CTrialCatalogue_CloseTrialOptionsScreen_Address }, { 2, 10, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_ExitTrialCatalogue - 0x80000000U) }, { 1, 10, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_ConfirmTrialStage - 0x80000000U) }, { 5, 10, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_SelectNeighborTwo - 0x80000000U) }, { 6, 10, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_SelectNeighborThree - 0x80000000U) }, { 8, 10, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_SelectNeighborZero - 0x80000000U) }, { 7, 10, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_SelectNeighborOne - 0x80000000U) }, { 0, 0, (ResidentEventHandler)0 } },
    { { 3591, 15, (ResidentEventHandler)(void *)((char *)&Results_ShowResultsPlayerModels - 0x80000000U) }, { 3592, 15, (ResidentEventHandler)(void *)((char *)&Results_AnimateResultsOptionsScreen - 0x80000000U) }, { 10, 15, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_HandleTrialOptionRelease - 0x80000000U) }, { 3594, 15, (ResidentEventHandler)(void *)((char *)&Results_RenderResultsOptionsPreview - 0x80000000U) }, { 3590, 15, (ResidentEventHandler)(void *)((char *)&Results_CreateResultsOptionsScreen - 0x80000000U) }, { 3587, 15, (ResidentEventHandler)(void *)&CTrialCatalogue_CloseTrialOptionsScreen_Address }, { 2, 15, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_ExitTrialCatalogue - 0x80000000U) }, { 1, 15, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_ConfirmTrialStage - 0x80000000U) }, { 5, 15, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_SelectNeighborTwo - 0x80000000U) }, { 6, 15, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_SelectNeighborThree - 0x80000000U) }, { 8, 15, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_SelectNeighborZero - 0x80000000U) }, { 7, 15, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_SelectNeighborOne - 0x80000000U) }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x0, 0x0, 0x0, 0x2 },
    { { 3590, 14, (ResidentEventHandler)(void *)((char *)&Match_ClearGermanLoadingHints - 0x80000000U) }, { 2, 14, (ResidentEventHandler)(void *)((char *)&Frontend_CloseMatchMenu - 0x80000000U) }, { 1, 14, (ResidentEventHandler)(void *)((char *)&Match_HandleMatchMessage - 0x80000000U) }, { 0, 0, (ResidentEventHandler)0 } }
};
typedef char D_src_85547de0SizeCheck[(sizeof(D_src_85547de0) == 2140) ? 1 : -1];
#endif
#endif
#if defined(VERSION_EU_X)
#if defined(VERSION_EU_X)
struct {
    OverlayTrialStage trialStages[36];
    OverlayTrialWidgetGroup trialWidgets[64];
    ResidentEventHandlerEntry eventHandlers1776[13];
    ResidentEventHandlerEntry eventHandlers1932[13];
    u8 alignmentFill2088[4];
    ResidentEventHandlerEntry eventHandlers2092[4];
} D_src_85547de0 __attribute__((aligned(4))) = {
    { { 426, 2, 0, { 1, -1, 2, -1 } }, { 348, 2, 1, { -1, 2, -1, 0 } }, { 347, 2, 2, { 1, 3, 4, 0 } }, { 349, 2, 3, { -1, -1, 4, 2 } }, { 416, 3, 4, { 5, 29, 13, 2 } }, { 351, 2, 5, { -1, 13, 6, 4 } }, { 358, 1, 6, { -1, 14, 7, 5 } }, { 355, 0, 7, { -1, 9, 8, 6 } }, { 356, 3, 8, { -1, 9, -1, 7 } }, { 423, 3, 9, { 15, 27, -1, 14 } }, { 357, 3, 10, { 9, 28, 27, 11 } }, { 359, 2, 11, { 14, 28, 10, 12 } }, { 360, 2, 12, { 13, 28, 11, 4 } }, { 353, 3, 13, { 6, 11, 14, 4 } }, { 354, 2, 14, { 7, 10, 9, 13 } }, { 428, 1, 15, { -1, 9, 16, -1 } }, { 365, 0, 16, { -1, 17, 19, 15 } }, { 369, 2, 17, { 16, -1, 18, 15 } }, { 368, 2, 18, { 19, -1, 20, 17 } }, { 366, 2, 19, { -1, 18, 20, 16 } }, { 367, 3, 20, { -1, 22, 21, 19 } }, { 383, 1, 21, { 20, 22, -1, -1 } }, { 435, 3, 22, { 20, 23, -1, -1 } }, { 401, 0, 23, { 24, -1, 22, 26 } }, { 438, 2, 24, { 22, 23, -1, 25 } }, { 381, 3, 25, { -1, 23, 24, 27 } }, { 400, 1, 26, { 25, -1, 23, 27 } }, { 398, 2, 27, { 9, 31, 25, 10 } }, { 363, 3, 28, { 11, 31, 27, -1 } }, { 427, 1, 29, { 4, 30, 31, -1 } }, { 362, 3, 30, { 29, -1, 31, -1 } }, { 361, 3, 31, { 28, -1, 32, 30 } }, { 405, 3, 32, { -1, -1, 33, 31 } }, { 406, 0, 33, { -1, -1, 34, 32 } }, { 407, 1, 34, { -1, -1, 35, 33 } }, { 418, 3, 35, { -1, -1, -1, 34 } } },
    { { 426, 348, 372 }, { 426, 347, 364 }, { 348, 347, 370 }, { 347, 349, 350 }, { 347, 416, 377 }, { 349, 416, 415 }, { 416, 427, 417 }, { 416, 353, 384 }, { 416, 351, 419 }, { 351, 353, 371 }, { 351, 358, 388 }, { 358, 354, 374 }, { 358, 355, 389 }, { 355, 423, 421 }, { 355, 356, 387 }, { 356, 423, 420 }, { 423, 398, 425 }, { 423, 428, 424 }, { 357, 363, 442 }, { 357, 398, 399 }, { 357, 423, 422 }, { 359, 363, 411 }, { 359, 357, 393 }, { 359, 354, 395 }, { 360, 363, 443 }, { 360, 359, 392 }, { 360, 353, 391 }, { 353, 359, 390 }, { 353, 354, 385 }, { 353, 358, 375 }, { 354, 357, 394 }, { 354, 423, 386 }, { 354, 355, 373 }, { 428, 369, 429 }, { 428, 365, 382 }, { 365, 369, 378 }, { 365, 366, 379 }, { 369, 368, 430 }, { 369, 366, 431 }, { 368, 367, 396 }, { 366, 368, 397 }, { 366, 367, 380 }, { 367, 383, 433 }, { 367, 435, 432 }, { 383, 435, 434 }, { 435, 401, 436 }, { 435, 438, 437 }, { 401, 400, 404 }, { 401, 381, 402 }, { 438, 401, 439 }, { 438, 381, 440 }, { 381, 400, 403 }, { 381, 398, 376 }, { 400, 398, 441 }, { 398, 363, 445 }, { 398, 361, 446 }, { 363, 361, 412 }, { 427, 362, 414 }, { 427, 361, 444 }, { 362, 361, 413 }, { 361, 405, 410 }, { 405, 406, 408 }, { 406, 407, 409 }, { 407, 418, 352 } },
    { { 3591, 10, (ResidentEventHandler)(void *)((char *)&Results_ShowResultsPlayerModels - 0x80000000U) }, { 3592, 10, (ResidentEventHandler)(void *)((char *)&Results_AnimateResultsOptionsScreen - 0x80000000U) }, { 10, 10, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_HandleTrialOptionRelease - 0x80000000U) }, { 3594, 10, (ResidentEventHandler)(void *)((char *)&Results_RenderResultsOptionsPreview - 0x80000000U) }, { 3590, 10, (ResidentEventHandler)(void *)((char *)&Results_CreateResultsOptionsScreen - 0x80000000U) }, { 3587, 10, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_CloseTrialOptionsScreen - 0x80000000U) }, { 2, 10, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_ExitTrialCatalogue - 0x80000000U) }, { 1, 10, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_ConfirmTrialStage - 0x80000000U) }, { 5, 10, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_SelectNeighborTwo - 0x80000000U) }, { 6, 10, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_SelectNeighborThree - 0x80000000U) }, { 8, 10, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_SelectNeighborZero - 0x80000000U) }, { 7, 10, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_SelectNeighborOne - 0x80000000U) }, { 0, 0, (ResidentEventHandler)0 } },
    { { 3591, 15, (ResidentEventHandler)(void *)((char *)&Results_ShowResultsPlayerModels - 0x80000000U) }, { 3592, 15, (ResidentEventHandler)(void *)((char *)&Results_AnimateResultsOptionsScreen - 0x80000000U) }, { 10, 15, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_HandleTrialOptionRelease - 0x80000000U) }, { 3594, 15, (ResidentEventHandler)(void *)((char *)&Results_RenderResultsOptionsPreview - 0x80000000U) }, { 3590, 15, (ResidentEventHandler)(void *)((char *)&Results_CreateResultsOptionsScreen - 0x80000000U) }, { 3587, 15, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_CloseTrialOptionsScreen - 0x80000000U) }, { 2, 15, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_ExitTrialCatalogue - 0x80000000U) }, { 1, 15, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_ConfirmTrialStage - 0x80000000U) }, { 5, 15, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_SelectNeighborTwo - 0x80000000U) }, { 6, 15, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_SelectNeighborThree - 0x80000000U) }, { 8, 15, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_SelectNeighborZero - 0x80000000U) }, { 7, 15, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_SelectNeighborOne - 0x80000000U) }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x8f, 0xb4, 0x0, 0x20 },
    { { 3590, 14, (ResidentEventHandler)(void *)((char *)&Frontend_ClearEuxLoadingHints - 0x80000000U) }, { 2, 14, (ResidentEventHandler)(void *)((char *)&Frontend_CloseMatchMenu - 0x80000000U) }, { 1, 14, (ResidentEventHandler)(void *)((char *)&Frontend_HandleMatchMenuMessage - 0x80000000U) }, { 0, 0, (ResidentEventHandler)0 } }
};
typedef char D_src_85547de0SizeCheck[(sizeof(D_src_85547de0) == 2140) ? 1 : -1];
#endif
#endif
#endif

#if !(defined(VERSION_DE) || defined(VERSION_EU_X))
/* ROM-grounded exact candidate, normalized from prior lane proof. */
#if defined(VERSION_EU)
struct {
    OverlayTrialStage trialStages[36];
} g_ResultsRefreshtrialcataloguewidgetsWords1 __attribute__((aligned(4))) = {
    { { 422, 2, 0, { 1, -1, 2, -1 } }, { 344, 2, 1, { -1, 2, -1, 0 } }, { 343, 2, 2, { 1, 3, 4, 0 } }, { 345, 2, 3, { -1, -1, 4, 2 } }, { 412, 3, 4, { 5, 29, 13, 2 } }, { 347, 2, 5, { -1, 13, 6, 4 } }, { 354, 1, 6, { -1, 14, 7, 5 } }, { 351, 0, 7, { -1, 9, 8, 6 } }, { 352, 3, 8, { -1, 9, -1, 7 } }, { 419, 3, 9, { 15, 27, -1, 14 } }, { 353, 3, 10, { 9, 28, 27, 11 } }, { 355, 2, 11, { 14, 28, 10, 12 } }, { 356, 2, 12, { 13, 28, 11, 4 } }, { 349, 3, 13, { 6, 11, 14, 4 } }, { 350, 2, 14, { 7, 10, 9, 13 } }, { 424, 1, 15, { -1, 9, 16, -1 } }, { 361, 0, 16, { -1, 17, 19, 15 } }, { 365, 2, 17, { 16, -1, 18, 15 } }, { 364, 2, 18, { 19, -1, 20, 17 } }, { 362, 2, 19, { -1, 18, 20, 16 } }, { 363, 3, 20, { -1, 22, 21, 19 } }, { 379, 1, 21, { 20, 22, -1, -1 } }, { 431, 3, 22, { 20, 23, -1, -1 } }, { 397, 0, 23, { 24, -1, 22, 26 } }, { 434, 2, 24, { 22, 23, -1, 25 } }, { 377, 3, 25, { -1, 23, 24, 27 } }, { 396, 1, 26, { 25, -1, 23, 27 } }, { 394, 2, 27, { 9, 31, 25, 10 } }, { 359, 3, 28, { 11, 31, 27, -1 } }, { 423, 1, 29, { 4, 30, 31, -1 } }, { 358, 3, 30, { 29, -1, 31, -1 } }, { 357, 3, 31, { 28, -1, 32, 30 } }, { 401, 3, 32, { -1, -1, 33, 31 } }, { 402, 0, 33, { -1, -1, 34, 32 } }, { 403, 1, 34, { -1, -1, 35, 33 } }, { 414, 3, 35, { -1, -1, -1, 34 } } }
};
typedef char g_ResultsRefreshtrialcataloguewidgetsWords1SizeCheck[(sizeof(g_ResultsRefreshtrialcataloguewidgetsWords1) == 1008) ? 1 : -1];
#endif
#if defined(VERSION_US)
struct {
    OverlayTrialStage trialStages[36];
} g_ResultsRefreshtrialcataloguewidgetsWords1 __attribute__((aligned(4))) = {
    { { 422, 2, 0, { 1, -1, 2, -1 } }, { 344, 2, 1, { -1, 2, -1, 0 } }, { 343, 2, 2, { 1, 3, 4, 0 } }, { 345, 2, 3, { -1, -1, 4, 2 } }, { 412, 3, 4, { 5, 29, 13, 2 } }, { 347, 2, 5, { -1, 13, 6, 4 } }, { 354, 1, 6, { -1, 14, 7, 5 } }, { 351, 0, 7, { -1, 9, 8, 6 } }, { 352, 3, 8, { -1, 9, -1, 7 } }, { 419, 3, 9, { 15, 27, -1, 14 } }, { 353, 3, 10, { 9, 28, 27, 11 } }, { 355, 2, 11, { 14, 28, 10, 12 } }, { 356, 2, 12, { 13, 28, 11, 4 } }, { 349, 3, 13, { 6, 11, 14, 4 } }, { 350, 2, 14, { 7, 10, 9, 13 } }, { 424, 1, 15, { -1, 9, 16, -1 } }, { 361, 0, 16, { -1, 17, 19, 15 } }, { 365, 2, 17, { 16, -1, 18, 15 } }, { 364, 2, 18, { 19, -1, 20, 17 } }, { 362, 2, 19, { -1, 18, 20, 16 } }, { 363, 3, 20, { -1, 22, 21, 19 } }, { 379, 1, 21, { 20, 22, -1, -1 } }, { 431, 3, 22, { 20, 23, -1, -1 } }, { 397, 0, 23, { 24, -1, 22, 26 } }, { 434, 2, 24, { 22, 23, -1, 25 } }, { 377, 3, 25, { -1, 23, 24, 27 } }, { 396, 1, 26, { 25, -1, 23, 27 } }, { 394, 2, 27, { 9, 31, 25, 10 } }, { 359, 3, 28, { 11, 31, 27, -1 } }, { 423, 1, 29, { 4, 30, 31, -1 } }, { 358, 3, 30, { 29, -1, 31, -1 } }, { 357, 3, 31, { 28, -1, 32, 30 } }, { 401, 3, 32, { -1, -1, 33, 31 } }, { 402, 0, 33, { -1, -1, 34, 32 } }, { 403, 1, 34, { -1, -1, 35, 33 } }, { 414, 3, 35, { -1, -1, -1, 34 } } }
};
typedef char g_ResultsRefreshtrialcataloguewidgetsWords1SizeCheck[(sizeof(g_ResultsRefreshtrialcataloguewidgetsWords1) == 1008) ? 1 : -1];
#endif
#if defined(VERSION_US_REV1)
struct {
    OverlayTrialStage trialStages[36];
} g_ResultsRefreshtrialcataloguewidgetsWords1 __attribute__((aligned(4))) = {
    { { 422, 2, 0, { 1, -1, 2, -1 } }, { 344, 2, 1, { -1, 2, -1, 0 } }, { 343, 2, 2, { 1, 3, 4, 0 } }, { 345, 2, 3, { -1, -1, 4, 2 } }, { 412, 3, 4, { 5, 29, 13, 2 } }, { 347, 2, 5, { -1, 13, 6, 4 } }, { 354, 1, 6, { -1, 14, 7, 5 } }, { 351, 0, 7, { -1, 9, 8, 6 } }, { 352, 3, 8, { -1, 9, -1, 7 } }, { 419, 3, 9, { 15, 27, -1, 14 } }, { 353, 3, 10, { 9, 28, 27, 11 } }, { 355, 2, 11, { 14, 28, 10, 12 } }, { 356, 2, 12, { 13, 28, 11, 4 } }, { 349, 3, 13, { 6, 11, 14, 4 } }, { 350, 2, 14, { 7, 10, 9, 13 } }, { 424, 1, 15, { -1, 9, 16, -1 } }, { 361, 0, 16, { -1, 17, 19, 15 } }, { 365, 2, 17, { 16, -1, 18, 15 } }, { 364, 2, 18, { 19, -1, 20, 17 } }, { 362, 2, 19, { -1, 18, 20, 16 } }, { 363, 3, 20, { -1, 22, 21, 19 } }, { 379, 1, 21, { 20, 22, -1, -1 } }, { 431, 3, 22, { 20, 23, -1, -1 } }, { 397, 0, 23, { 24, -1, 22, 26 } }, { 434, 2, 24, { 22, 23, -1, 25 } }, { 377, 3, 25, { -1, 23, 24, 27 } }, { 396, 1, 26, { 25, -1, 23, 27 } }, { 394, 2, 27, { 9, 31, 25, 10 } }, { 359, 3, 28, { 11, 31, 27, -1 } }, { 423, 1, 29, { 4, 30, 31, -1 } }, { 358, 3, 30, { 29, -1, 31, -1 } }, { 357, 3, 31, { 28, -1, 32, 30 } }, { 401, 3, 32, { -1, -1, 33, 31 } }, { 402, 0, 33, { -1, -1, 34, 32 } }, { 403, 1, 34, { -1, -1, 35, 33 } }, { 414, 3, 35, { -1, -1, -1, 34 } } }
};
typedef char g_ResultsRefreshtrialcataloguewidgetsWords1SizeCheck[(sizeof(g_ResultsRefreshtrialcataloguewidgetsWords1) == 1008) ? 1 : -1];
#endif
#endif

#if defined(VERSION_US)
#if defined(VERSION_US)
struct {
    OverlayTrialWidgetGroup trialWidgets[64];
    ResidentEventHandlerEntry eventHandlers768[13];
    ResidentEventHandlerEntry eventHandlers924[13];
    u8 alignmentFill1080[4];
    ResidentEventHandlerEntry eventHandlers1084[4];
} g_resultsRefreshTrialCatalogueWidgetsWords_us __attribute__((aligned(4))) = {
    { { 422, 344, 368 }, { 422, 343, 360 }, { 344, 343, 366 }, { 343, 345, 346 }, { 343, 412, 373 }, { 345, 412, 411 }, { 412, 423, 413 }, { 412, 349, 380 }, { 412, 347, 415 }, { 347, 349, 367 }, { 347, 354, 384 }, { 354, 350, 370 }, { 354, 351, 385 }, { 351, 419, 417 }, { 351, 352, 383 }, { 352, 419, 416 }, { 419, 394, 421 }, { 419, 424, 420 }, { 353, 359, 438 }, { 353, 394, 395 }, { 353, 419, 418 }, { 355, 359, 407 }, { 355, 353, 389 }, { 355, 350, 391 }, { 356, 359, 439 }, { 356, 355, 388 }, { 356, 349, 387 }, { 349, 355, 386 }, { 349, 350, 381 }, { 349, 354, 371 }, { 350, 353, 390 }, { 350, 419, 382 }, { 350, 351, 369 }, { 424, 365, 425 }, { 424, 361, 378 }, { 361, 365, 374 }, { 361, 362, 375 }, { 365, 364, 426 }, { 365, 362, 427 }, { 364, 363, 392 }, { 362, 364, 393 }, { 362, 363, 376 }, { 363, 379, 429 }, { 363, 431, 428 }, { 379, 431, 430 }, { 431, 397, 432 }, { 431, 434, 433 }, { 397, 396, 400 }, { 397, 377, 398 }, { 434, 397, 435 }, { 434, 377, 436 }, { 377, 396, 399 }, { 377, 394, 372 }, { 396, 394, 437 }, { 394, 359, 441 }, { 394, 357, 442 }, { 359, 357, 408 }, { 423, 358, 410 }, { 423, 357, 440 }, { 358, 357, 409 }, { 357, 401, 406 }, { 401, 402, 404 }, { 402, 403, 405 }, { 403, 414, 348 } },
    { { 3591, 10, (ResidentEventHandler)(void *)((char *)&Results_ShowResultsPlayerModels - 0x80000000U) }, { 3592, 10, (ResidentEventHandler)(void *)((char *)&Results_AnimateResultsOptionsScreen - 0x80000000U) }, { 10, 10, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_HandleTrialOptionRelease - 0x80000000U) }, { 3594, 10, (ResidentEventHandler)(void *)((char *)&Results_RenderResultsOptionsPreview - 0x80000000U) }, { 3590, 10, (ResidentEventHandler)(void *)((char *)&Results_CreateResultsOptionsScreen - 0x80000000U) }, { 3587, 10, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_CloseTrialOptionsScreen - 0x80000000U) }, { 2, 10, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_ExitTrialCatalogue - 0x80000000U) }, { 1, 10, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_ConfirmTrialStage - 0x80000000U) }, { 5, 10, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_SelectNeighborTwo - 0x80000000U) }, { 6, 10, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_SelectNeighborThree - 0x80000000U) }, { 8, 10, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_SelectNeighborZero - 0x80000000U) }, { 7, 10, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_SelectNeighborOne - 0x80000000U) }, { 0, 0, (ResidentEventHandler)0 } },
    { { 3591, 15, (ResidentEventHandler)(void *)((char *)&Results_ShowResultsPlayerModels - 0x80000000U) }, { 3592, 15, (ResidentEventHandler)(void *)((char *)&Results_AnimateResultsOptionsScreen - 0x80000000U) }, { 10, 15, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_HandleTrialOptionRelease - 0x80000000U) }, { 3594, 15, (ResidentEventHandler)(void *)((char *)&Results_RenderResultsOptionsPreview - 0x80000000U) }, { 3590, 15, (ResidentEventHandler)(void *)((char *)&Results_CreateResultsOptionsScreen - 0x80000000U) }, { 3587, 15, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_CloseTrialOptionsScreen - 0x80000000U) }, { 2, 15, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_ExitTrialCatalogue - 0x80000000U) }, { 1, 15, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_ConfirmTrialStage - 0x80000000U) }, { 5, 15, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_SelectNeighborTwo - 0x80000000U) }, { 6, 15, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_SelectNeighborThree - 0x80000000U) }, { 8, 15, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_SelectNeighborZero - 0x80000000U) }, { 7, 15, (ResidentEventHandler)(void *)((char *)&CTrialCatalogue_SelectNeighborOne - 0x80000000U) }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x43, 0x45, 0x53, 0x43 },
    { { 3590, 14, (ResidentEventHandler)(void *)((char *)&Frontend_ClearLoadingHints - 0x80000000U) }, { 2, 14, (ResidentEventHandler)(void *)((char *)&Frontend_CloseMatchMenu - 0x80000000U) }, { 1, 14, (ResidentEventHandler)(void *)((char *)&Frontend_HandleMatchMenuMessage - 0x80000000U) }, { 0, 0, (ResidentEventHandler)0 } }
};
typedef char g_resultsRefreshTrialCatalogueWidgetsWords_usSizeCheck[(sizeof(g_resultsRefreshTrialCatalogueWidgetsWords_us) == 1132) ? 1 : -1];
#endif
#endif

#if defined(VERSION_EU)
#if defined(VERSION_EU)
struct {
    OverlayTrialWidgetGroup trialWidgets[64];
    ResidentEventHandlerEntry eventHandlers768[13];
    ResidentEventHandlerEntry eventHandlers924[13];
    u8 alignmentFill1080[4];
    ResidentEventHandlerEntry eventHandlers1084[4];
} g_resultsRefreshTrialCatalogueWidgetsWords_eu __attribute__((aligned(4))) = {
    { { 422, 344, 368 }, { 422, 343, 360 }, { 344, 343, 366 }, { 343, 345, 346 }, { 343, 412, 373 }, { 345, 412, 411 }, { 412, 423, 413 }, { 412, 349, 380 }, { 412, 347, 415 }, { 347, 349, 367 }, { 347, 354, 384 }, { 354, 350, 370 }, { 354, 351, 385 }, { 351, 419, 417 }, { 351, 352, 383 }, { 352, 419, 416 }, { 419, 394, 421 }, { 419, 424, 420 }, { 353, 359, 438 }, { 353, 394, 395 }, { 353, 419, 418 }, { 355, 359, 407 }, { 355, 353, 389 }, { 355, 350, 391 }, { 356, 359, 439 }, { 356, 355, 388 }, { 356, 349, 387 }, { 349, 355, 386 }, { 349, 350, 381 }, { 349, 354, 371 }, { 350, 353, 390 }, { 350, 419, 382 }, { 350, 351, 369 }, { 424, 365, 425 }, { 424, 361, 378 }, { 361, 365, 374 }, { 361, 362, 375 }, { 365, 364, 426 }, { 365, 362, 427 }, { 364, 363, 392 }, { 362, 364, 393 }, { 362, 363, 376 }, { 363, 379, 429 }, { 363, 431, 428 }, { 379, 431, 430 }, { 431, 397, 432 }, { 431, 434, 433 }, { 397, 396, 400 }, { 397, 377, 398 }, { 434, 397, 435 }, { 434, 377, 436 }, { 377, 396, 399 }, { 377, 394, 372 }, { 396, 394, 437 }, { 394, 359, 441 }, { 394, 357, 442 }, { 359, 357, 408 }, { 423, 358, 410 }, { 423, 357, 440 }, { 358, 357, 409 }, { 357, 401, 406 }, { 401, 402, 404 }, { 402, 403, 405 }, { 403, 414, 348 } },
    { { 3591, 10, (ResidentEventHandler)(void *)&g_Results_ShowResultsPlayerModelsPackedAddress24 }, { 3592, 10, (ResidentEventHandler)(void *)&g_Results_AnimateResultsOptionsScreenPackedAddress24 }, { 10, 10, (ResidentEventHandler)(void *)&g_CTrialCatalogue_HandleTrialOptionReleasePackedAddress24 }, { 3594, 10, (ResidentEventHandler)(void *)&g_Results_RenderResultsOptionsPreviewPackedAddress24 }, { 3590, 10, (ResidentEventHandler)(void *)&g_Results_CreateResultsOptionsScreenPackedAddress24 }, { 3587, 10, (ResidentEventHandler)(void *)&g_CTrialCatalogue_CloseTrialOptionsScreenPackedAddress24 }, { 2, 10, (ResidentEventHandler)(void *)&g_CTrialCatalogue_ExitTrialCataloguePackedAddress24 }, { 1, 10, (ResidentEventHandler)(void *)&g_CTrialCatalogue_ConfirmTrialStagePackedAddress24 }, { 5, 10, (ResidentEventHandler)(void *)&g_CTrialCatalogue_TrialOptionsEvent05HandlerPackedAddress24 }, { 6, 10, (ResidentEventHandler)(void *)&g_CTrialCatalogue_TrialOptionsEvent06HandlerPackedAddress24 }, { 8, 10, (ResidentEventHandler)(void *)&g_CTrialCatalogue_TrialOptionsEvent08HandlerPackedAddress24 }, { 7, 10, (ResidentEventHandler)(void *)&g_CTrialCatalogue_TrialOptionsEvent07HandlerPackedAddress24 }, { 0, 0, (ResidentEventHandler)0 } },
    { { 3591, 15, (ResidentEventHandler)(void *)&g_Results_ShowResultsPlayerModelsPackedAddress24 }, { 3592, 15, (ResidentEventHandler)(void *)&g_Results_AnimateResultsOptionsScreenPackedAddress24 }, { 10, 15, (ResidentEventHandler)(void *)&g_CTrialCatalogue_HandleTrialOptionReleasePackedAddress24 }, { 3594, 15, (ResidentEventHandler)(void *)&g_Results_RenderResultsOptionsPreviewPackedAddress24 }, { 3590, 15, (ResidentEventHandler)(void *)&g_Results_CreateResultsOptionsScreenPackedAddress24 }, { 3587, 15, (ResidentEventHandler)(void *)&g_CTrialCatalogue_CloseTrialOptionsScreenPackedAddress24 }, { 2, 15, (ResidentEventHandler)(void *)&g_CTrialCatalogue_ExitTrialCataloguePackedAddress24 }, { 1, 15, (ResidentEventHandler)(void *)&g_CTrialCatalogue_ConfirmTrialStagePackedAddress24 }, { 5, 15, (ResidentEventHandler)(void *)&g_CTrialCatalogue_TrialOptionsEvent05HandlerPackedAddress24 }, { 6, 15, (ResidentEventHandler)(void *)&g_CTrialCatalogue_TrialOptionsEvent06HandlerPackedAddress24 }, { 8, 15, (ResidentEventHandler)(void *)&g_CTrialCatalogue_TrialOptionsEvent08HandlerPackedAddress24 }, { 7, 15, (ResidentEventHandler)(void *)&g_CTrialCatalogue_TrialOptionsEvent07HandlerPackedAddress24 }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x21, 0xad, 0x0, 0x10 },
    { { 3590, 14, (ResidentEventHandler)(void *)&g_Frontend_ClearEuLoadingHintsPackedAddress24 }, { 2, 14, (ResidentEventHandler)(void *)&g_Frontend_CloseMatchMenuPackedAddress24 }, { 1, 14, (ResidentEventHandler)(void *)&g_Frontend_HandleMatchMenuMessagePackedAddress24 }, { 0, 0, (ResidentEventHandler)0 } }
};
typedef char g_resultsRefreshTrialCatalogueWidgetsWords_euSizeCheck[(sizeof(g_resultsRefreshTrialCatalogueWidgetsWords_eu) == 1132) ? 1 : -1];
#endif
#endif
