#ifndef LIBGULTRA_RNC_UNPACKMETHOD1_H
#define LIBGULTRA_RNC_UNPACKMETHOD1_H
#include "TYPES.H"
/* RNC method 1 unpacker; src is the packed data after the 18-byte header. */
void Rnc_UnpackMethod1(const void *src, void *dst, s32 packedSize, s32 unpackedSize);
#endif
