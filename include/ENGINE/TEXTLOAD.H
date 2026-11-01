#ifndef ENGINE_TEXTLOAD_H
#define ENGINE_TEXTLOAD_H
#include "COMMON/RESIDENTSTATE.H"

extern void Scene_LocateTextureResource(void *resource, s32 sectionIndex, s32 *sectionOut, s32 *sectionSizeOut);

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
#endif
