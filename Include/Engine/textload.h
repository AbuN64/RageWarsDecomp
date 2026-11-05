#ifndef ENGINE_TEXTLOAD_H
#define ENGINE_TEXTLOAD_H
#include <PR/gbi.h>
#include "Common/residentstate.h"

struct Request {
    s16 type;
};
typedef struct Request Request;


struct ResidentSlot;
extern void Scene_LocateTextureResource(struct SceneCounterPairView *world, s32 sectionIndex, s32 *resourceAddressOutput, s32 *sectionSizeOut);

extern int TextLoad_GetArtsendPrimaryButtonMask(void);

extern int TextLoad_GetArtsendSecondaryButtonMask(void);

extern void TextLoad_IncreaseArtsendSelectionValue(void);

extern void TextLoad_InitializeArtsendPreviewState(void);

extern void TextLoad_DecreaseArtsendSelectionValue(void);

extern void TextLoad_ReleaseArtsendTextureResource(void);

extern void TextLoad_CloseArtsendTexturePreview(void);

extern int TextLoad_IsArtsendTexturePreviewEnabled(void);

extern void TextLoad_ResetArtsendTextureState(void);

extern void Textload_SetResourceLocation(int *value, int first, int second);
extern void **Textload_RequestTextureVariationSync(s32 *resource, s32 variation);
extern int g_textureCacheResource;
extern s32 g_textureCacheFrame;
extern s32 g_textureCacheVariation;
extern s32 g_textureCacheWrapS;
extern s32 g_textureCacheWrapT;
extern unsigned int g_texturePaletteOverrideEnabled;
extern struct ResidentSlot g_artsendTextureViewerOverridesOff;
extern Gfx g_textureTileDefaultDisplayList[16], g_textureTileWrappedDisplayList[16];
extern Gfx g_textureTileAlternateDisplayList[19], g_textureTilePaletteDisplayList[19], g_textureTileFinishDisplayList[19];
extern Gfx g_textureFrameDefaultDisplayList[], g_textureFrameWrappedDisplayList[], g_textureFrameAlternateDisplayList[], g_textureFramePaletteDisplayList[];
extern Gfx g_textureFrameIntensityMipmapDisplayList[];
#endif
