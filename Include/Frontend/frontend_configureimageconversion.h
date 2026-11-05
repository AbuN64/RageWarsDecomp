#ifndef FRONTEND_FRONTEND_CONFIGUREIMAGECONVERSION_H
#define FRONTEND_FRONTEND_CONFIGUREIMAGECONVERSION_H
#include "Frontend/layout.h"
extern s16 Frontend_GetOwnedImageRowCount(s16 *record);
extern s16 Frontend_GetOwnedImageHeight(s16 *record);
extern s32 Frontend_GetImageBitsPerPixel(u8 *record);
extern u8 Frontend_GetOwnedImageFormat(u8 *record);
extern s16 Frontend_GetOwnedImageStride(s16 *record);
extern s16 Frontend_GetOwnedImagePaletteCount(s16 *record);
extern u32 Frontend_ConvertPixelFormat(u32 value, s32 from, s32 to);
extern s16 Frontend_GetOwnedImageWidth(s16 *record);
extern s32 Frontend_CopyOwnedImage(struct OwnedImage*dst, struct OwnedImage*src);
void Frontend_ClearOwnedImage(int value);
struct OwnedImage;
void Frontend_ReleaseOwnedImageBuffers(struct OwnedImage *res);
extern s32 Frontend_GetImagePixelType(const void *imageRecord);
#endif
