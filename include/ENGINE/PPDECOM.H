#ifndef ENGINE_PPDECOM_H
#define ENGINE_PPDECOM_H
#include "TYPES.H"
#include "COMMON/PACKEDMESHMATERIAL.H"

extern void PpDecom_SelectionSortRange(u32 lo, u32 hi, s32 width, s32 (*compare)(u32, u32), void (*swap)(u32, u32));

extern void CResource_UnpackRequest(s32 argument, s32 request);
#endif
