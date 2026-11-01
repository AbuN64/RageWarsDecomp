#include "COMMON/NODERECAT2A8.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "FRONTEND/LAYOUT.H"
#include "COMMON/FORMAT.H"
#include "TYPES.H"

/* The same table as Frontend_GetImagePixelType reads, at the field 24 bytes into the 52-byte record. The
   debugger returned 1 on every one of 400 calls, so the observed records all carry a non-zero
   value here and the zero arm is untested by execution. */

/* Copies record i of the 52-byte table g_pixelFormatDescriptors into the destination. */



int Frontend_GetImagePaletteByteCount(int *value) {
    return value[4];
}

int Frontend_GetImagePixelByteCount(int *value) {
    return value[3];
}

/* Returns the word at offset 0x18 of a record. */
s32 Frontend_GetOwnedImagePixels(s32 *record) {
    return (s32)((OwnedImage *)record)->pixels;
}

/* Returns the word at offset 0x14 of a record. */
s32 Frontend_GetOwnedImagePalette(s32 *record) {
    return (s32)((OwnedImage *)record)->palette;
}

int Frontend_HasOwnedImagePalette(void *object) {
    AnimationResourceHandleView *record = object;
    return record->resourceHandle > 0;
}

s32 Frontend_HasImageFormatMaskComponent(u8 *record) {
    return g_frontendImageRecordFlags[*record][0] != 0;
}

/* Returns bit 1 of the flag byte at offset 1 of a record; Frontend_OwnsImagePixels returns bit 0. */
u8 Frontend_OwnsImagePalette(u8 *record) {
    return (record[1] >> 1) & 1;
}

/* Returns bit 0 of the flag byte at offset 1 of a record; Frontend_OwnsImagePalette returns bit 1. */
u8 Frontend_OwnsImagePixels(u8 *record) {
    return record[1] & 1;
}

void Frontend_ConfigureOwnedImage(struct Config *out, unsigned char type, short x, short y,
                  short a, short b, int enable1, int d, int e, int enable2,
                  int f, int g, short last) {
    out->type = type;
    out->x = x;
    out->y = y;
    out->flags = 0;
    out->last = last;
    out->a = a;
    out->b = b;
    out->g = e;
    out->d = d;
    out->f = g;
    out->e = f;
    if (enable1) {
        out->flags = 1;
    }
    if (enable2) {
        out->flags |= 2;
    }
}

void Frontend_GetPixelFormatDescriptor(s32 index, struct Format *out) {
    *out = g_pixelFormatDescriptors[index];
}
