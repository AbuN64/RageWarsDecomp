#ifndef FRONTEND_FRONTEND_READSOURCEPIXELCOLOR_H
#define FRONTEND_FRONTEND_READSOURCEPIXELCOLOR_H
#include "COMMON/FORMAT.H"
extern void Frontend_WriteDestinationNibbleIndex(void);
extern void Frontend_ReadSourceWordPixel(void);
extern void Frontend_WriteDestinationHalfwordPixel(void);
extern void Frontend_WriteDestinationPixelIndex(s32 x, s32 y, s32 value);
extern u32 Frontend_ReadSourcePixelColor(s32 x, s32 y);
extern void Frontend_ReadSourceNibbleIndex(void);
extern void Frontend_ReadSourceByteIndex(void);
extern void Frontend_WriteDestinationPixelColor(s32 x, s32 y, u32 color);
extern void Frontend_ReadSourceThreeBytePixel(void);
extern void Frontend_UseHalfwordPixelOffset(void);
extern void Frontend_ReadSourceHalfwordPixel(void);
extern u32 Frontend_DecodePixelColor(u32 value, s32 format);
extern u32 Frontend_EncodePixelColor(u32 color, s32 format);
extern void Frontend_WriteDestinationThreeBytePixel(void);
extern void Frontend_WriteDestinationByteIndex(void);
extern void Frontend_WriteDestinationWordPixel(void);
extern void Frontend_UseWordPixelOffset(void);
extern void Frontend_UseThreeBytePixelOffset(void);
#endif
