#ifndef ENGINE_TENGINE_H
#define ENGINE_TENGINE_H
#include "types.h"
struct ResidentEntry;
extern s32 g_artsendTextureResourceCallback;
extern s32 g_artsendTextureFrameSelection;
extern s32 g_artsendActionMappingSelection;
extern s32 g_artsendTextureResetWordA;
extern s32 Tengine_QueryArtsendOverride(s32 overrideSelector);
extern struct ResidentEntry g_artsendSelectedTextureResource;
#endif
