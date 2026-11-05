#ifndef ACHIEVE_MODELPREVIEWSCREEN_H
#define ACHIEVE_MODELPREVIEWSCREEN_H
#include "Frontend/frontend.h"
#include "Achieve/achieve_address_symbols.h"
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
#include "Common/selectionscreenstate.h"
#include "Common/menu_screen_setup.h"




extern s32 Model_SetPreviewModel(struct RecordFrontendSetPreviewModel *record, s32 count);


#if defined(VERSION_DE)
enum { RESULTS_MODEL_PREVIEW_IMAGE_WIDGET_ID = 638, PREVIEW_ID_SHIFT = 0 };
#elif defined(VERSION_EU_X)
enum { RESULTS_MODEL_PREVIEW_IMAGE_WIDGET_ID = 647, PREVIEW_ID_SHIFT = 9 };
#else
enum { RESULTS_MODEL_PREVIEW_IMAGE_WIDGET_ID = 642, PREVIEW_ID_SHIFT = 4 };
#endif
#endif
