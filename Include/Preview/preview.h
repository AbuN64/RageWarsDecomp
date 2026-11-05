#ifndef PREVIEW_PREVIEW_H
#define PREVIEW_PREVIEW_H
#include "Common/menu_screen_setup.h"
#include "types.h"
#include "Common/menu_model_preview.h"
#include "Common/vector.h"
struct StateFrontendInitModelPreviewTransform;
extern void Preview_DrawMenuModelItem(struct MenuModelItem *item);
s32 Frontend_InitModelPreviewTransform(struct StateFrontendInitModelPreviewTransform *preview, s32 modelId, Triple first, Triple second);
#include "Common/virtual_pager.h"
#include "Common/sharedplayer.h"
#endif
