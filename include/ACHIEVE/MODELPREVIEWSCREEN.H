#ifndef ACHIEVE_MODELPREVIEWSCREEN_H
#define ACHIEVE_MODELPREVIEWSCREEN_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "COMMON/MENU_SCREEN_SETUP.H"



extern ModelPreviewScreen *g_resultsModelPreviewScreen;

extern s32 Model_SetPreviewModel(struct RecordFrontendSetPreviewModel *record, s32 count);


#if defined(VERSION_DE)
enum { RESULTS_MODEL_PREVIEW_IMAGE_WIDGET_ID = 638, PREVIEW_ID_SHIFT = 0 };
#elif defined(VERSION_EU_X)
enum { RESULTS_MODEL_PREVIEW_IMAGE_WIDGET_ID = 647, PREVIEW_ID_SHIFT = 9 };
#else
enum { RESULTS_MODEL_PREVIEW_IMAGE_WIDGET_ID = 642, PREVIEW_ID_SHIFT = 4 };
#endif
#endif
