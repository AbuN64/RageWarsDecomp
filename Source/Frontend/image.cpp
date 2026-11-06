#include "Data/rest_source_records.h"
#include "include_asm.h"
#include "Common/frontend_video_mode.h"
#include "Common/runtime_declarations.h"
#include "Frontend/layout.h"
#include "Common/format.h"
#include "types.h"
#include "Frontend/frontend_configureimageconversion.h"
#include "Scene/cache_freememory.h"
#include "Resmgr/resmgr_string_memory.h"
#include "Common/selectionscreenstate.h"
#include "Image/frontend_configureownedimage.h"
#include "Frontend/frontend_address_symbols.h"
#include "Frontend/frontend_readsourcepixelcolor.h"

/* unit SMP_CONTROLLER_EVENTS.CPP */
#if defined(VERSION_DE)
#elif defined(VERSION_EU)
#elif defined(VERSION_EU_X)
#elif defined(VERSION_US)
RestsmpControllerStateAndEventWordsLayout875 g_smpControllerStateAndEventWords = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    "uR\000\000",
    0x98000000,
    { 1, 0 },
    0x1E475241,
    "PHIC"
};
#elif defined(VERSION_US_REV1)
RestsmpControllerStateAndEventWordsLayout876 g_smpControllerStateAndEventWords = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 177, 196, 1, 194, 134, 126 }
};
#endif

/* unit FRONTEND_CONFIGUREIMAGECONVERSION.CPP */
s32 Frontend_FindPixelFormat(Format *format) {
    s32 i;
    for (i = 0; i < 36; i++) {
        if (g_pixelFormatDescriptors[i].flags == format->flags &&
            g_pixelFormatDescriptors[i].type == format->type &&
            g_pixelFormatDescriptors[i].mask[0] == format->mask[0] &&
            g_pixelFormatDescriptors[i].mask[1] == format->mask[1] &&
            g_pixelFormatDescriptors[i].mask[2] == format->mask[2] &&
            g_pixelFormatDescriptors[i].mask[3] == format->mask[3]) {
            return i;
        }
    }
    return 0;
}

/* Converts a packed pixel value from format `from` to format `to` of the format table g_pixelFormatDescriptors:
   decodes the value to 0xAARRGGBB with the source format's channel masks and signed shifts, splits
   it into channels and re-encodes them with the destination format's shifts and masks. */
static inline u32 Frontend_DecodeFormatColor(u32 value, Format *format) {
    u32 r;
    u32 g;
    u32 b;
    u32 a;

    if (format->shift[0] < 0) {
        r = (value & format->mask[0]) << -format->shift[0];
    } else {
        r = (value & format->mask[0]) >> format->shift[0];
    }
    if (format->shift[1] < 0) {
        g = (value & format->mask[1]) << -format->shift[1];
    } else {
        g = (value & format->mask[1]) >> format->shift[1];
    }
    if (format->shift[2] < 0) {
        b = (value & format->mask[2]) << -format->shift[2];
    } else {
        b = (value & format->mask[2]) >> format->shift[2];
    }
    if (format->shift[3] < 0) {
        a = (value & format->mask[3]) << -format->shift[3];
    } else {
        a = (value & format->mask[3]) >> format->shift[3];
    }
    return (a << 24) | (r << 16) | (g << 8) | b;
}

static inline u32 Frontend_EncodeFormatColor(u32 color, Format *format) {
    u32 r;
    u32 g;
    u32 b;
    u32 a;

    r = (color >> 16) & 0xFF;
    g = (color & 0xFF00) >> 8;
    b = color & 0xFF;
    a = color >> 24;
    if (format->shift[0] < 0) {
        r = (r >> -format->shift[0]) & format->mask[0];
    } else {
        r = (r << format->shift[0]) & format->mask[0];
    }
    if (format->shift[1] < 0) {
        g = (g >> -format->shift[1]) & format->mask[1];
    } else {
        g = (g << format->shift[1]) & format->mask[1];
    }
    if (format->shift[2] < 0) {
        b = (b >> -format->shift[2]) & format->mask[2];
    } else {
        b = (b << format->shift[2]) & format->mask[2];
    }
    if (format->shift[3] < 0) {
        a = (a >> -format->shift[3]) & format->mask[3];
    } else {
        a = (a << format->shift[3]) & format->mask[3];
    }
    return r | g | b | a;
}

u32 Frontend_ConvertPixelFormat(u32 value, s32 from, s32 to) {
    return Frontend_EncodeFormatColor(Frontend_DecodeFormatColor(value, &g_pixelFormatDescriptors[from]), &g_pixelFormatDescriptors[to]);
}

void Frontend_ConfigureImageConversion(ImageDescriptor *destination, ImageDescriptor *source) {
    Format dst,src;
    g_writeDestinationIndex=0;
    g_readSourceIndex=0;
    g_writeDestinationColor=0;
    g_readSourceColor=0;
    g_destinationPixelIndexBuffer=0;
    g_sourcePixelIndexBuffer=0;
    g_destinationColorBuffer=0;
    g_sourceColorBuffer=0;
    g_destinationPixelOffset=0;
    g_sourcePixelOffset=0;
    g_destinationColorIndex=0;
    g_sourceColorIndex=0;
    g_conversionDestinationImage=0;
    g_conversionSourceImage=0;
    if(destination) {
        g_conversionDestinationImage=(void *)destination;
        dst=g_pixelFormatDescriptors[destination->format];
        g_destinationPixelFormat=dst;
        if(dst.flags) g_destinationColorBuffer=destination->pixels;
        else g_destinationColorBuffer=destination->palette;
        if(dst.flags) g_destinationPixelIndexBuffer=destination->palette;
        else g_destinationPixelIndexBuffer=0;
        if(dst.bits==16) g_writeDestinationColor=g_Frontend_WriteDestinationHalfwordPixelAddress;
        else if(dst.bits==24) g_writeDestinationColor=addrLow_Frontend_WriteDestinationThreeBytePixel;
        else if(dst.bits==32) g_writeDestinationColor=g_Frontend_WriteDestinationWordPixelAddress;
        if(dst.type==4) g_writeDestinationIndex=g_Frontend_WriteDestinationNibbleIndexAddress;
        else if(dst.type==8) g_writeDestinationIndex=g_Frontend_WriteDestinationByteIndexAddress;
        g_destinationRedMask=dst.mask[0];
        g_destinationGreenMask=dst.mask[1];
        g_destinationBlueMask=dst.mask[2];
        g_destinationAlphaMask=dst.mask[3];
        g_destinationRedShift=dst.shift[0];
        g_destinationGreenShift=dst.shift[1];
        g_destinationBlueShift=dst.shift[2];
        g_destinationAlphaShift=dst.shift[3];
    }
    if(source) {
        g_conversionSourceImage=(void *)source;
        src=g_pixelFormatDescriptors[source->format];
        g_sourcePixelFormat=src;
        if(src.flags) g_sourceColorBuffer=source->pixels;
        else g_sourceColorBuffer=source->palette;
        if(src.flags) g_sourcePixelIndexBuffer=source->palette;
        else g_sourcePixelIndexBuffer=0;
        if(src.bits==16) g_readSourceColor=g_Frontend_ReadSourceHalfwordPixelAddress;
        else if(src.bits==24) g_readSourceColor=addrLow_Frontend_ReadSourceThreeBytePixel;
        else if(src.bits==32) g_readSourceColor=g_Frontend_ReadSourceWordPixelAddress;
        if(src.type==4) g_readSourceIndex=g_Frontend_ReadSourceNibbleIndexAddress;
        else if(src.type==8) g_readSourceIndex=g_Frontend_ReadSourceByteIndexAddress;
        else if(src.type==16) g_readSourceIndex=g_Frontend_UseHalfwordPixelOffsetAddress;
        else if(src.type==24) g_readSourceIndex=addrLow_Frontend_UseThreeBytePixelOffset;
        else if(src.type==32) g_readSourceIndex=g_Frontend_UseWordPixelOffsetAddress;
        g_sourceRedMask=src.mask[0];
        g_sourceGreenMask=src.mask[1];
        g_sourceBlueMask=src.mask[2];
        g_sourceAlphaMask=src.mask[3];
        g_sourceRedShift=src.shift[0];
        g_sourceGreenShift=src.shift[1];
        g_sourceBlueShift=src.shift[2];
        g_sourceAlphaShift=src.shift[3];
    }
}

void Frontend_ClearOwnedImage(int value) {
    XPlus_FillBytes(value, 0, 32);
}

/* Releases a resource object's buffers through Cache_FreeMemory (the pixel buffer when the pixel-ownership flag is set, the
   palette buffer when the palette-ownership flag is set and the palette has entries) and clears the whole record. */
void Frontend_ReleaseOwnedImageBuffers(OwnedImage *res) {
    if (res->flags & 1) {
        Cache_FreeMemory(res->pixels);
    }
    if ((res->flags & 2) && res->paletteCount > 0) {
        Cache_FreeMemory(res->palette);
    }
    XPlus_FillBytes(res, 0, 32);
}

/** Report false. */
int Frontend_ReturnImageZero(void) {
    return 0;
}

/* Copies image src into dst: releases dst's owned pixel data (flag 1) and palette (flag 2, when it
   has entries), clears it and copies src's header, drops a palette pointer without entries, marks
   the copies owned, then allocates and copies the pixel data (size from Frontend_GetImagePixelByteCount) and, when
   src has a palette, the palette (size from Frontend_GetImagePaletteByteCount). Returns 1 when an allocation fails,
   leaving dst cleared, otherwise 0. */
s32 Frontend_CopyOwnedImage(OwnedImage *dst, OwnedImage *src) {
    s32 size;

    if (dst->flags & 1) {
        Cache_FreeMemory(dst->pixels);
    }
    if ((dst->flags & 2) && dst->paletteCount > 0) {
        Cache_FreeMemory(dst->palette);
    }
    XPlus_FillBytes(dst, 0, 32);
    *dst = *src;
    if (dst->paletteCount == 0) {
        dst->palette = 0;
    }
    dst->flags = 1;
    if (dst->palette != 0) {
        dst->flags = 3;
    }
    size = Frontend_GetImagePixelByteCount(src);
    if ((dst->pixels = Cache_AllocateMemory(size)) == 0) {
        return 1;
    }
    XPlus_CopyBytes(dst->pixels, src->pixels, size);
    if (src->paletteCount != 0) {
        size = Frontend_GetImagePaletteByteCount(src);
        if ((dst->palette = Cache_AllocateMemory(size)) == 0) {
            Cache_FreeMemory(dst->pixels);
            XPlus_FillBytes(dst, 0, 32);
            return 1;
        }
        XPlus_CopyBytes(dst->palette, src->palette, size);
    }
    return 0;
}

/* Returns the first byte of a record; Frontend_GetImagePixelType, which follows it, reads the same byte. */
u8 Frontend_GetOwnedImageFormat(u8 *record) {
    return record[0];
}

/* The argument is a pointer to an image record whose first byte selects an entry. The values and the flags
   (indexed the same way by Frontend_HasImageFormatMaskComponent) are fields of one 52-byte record. */
s32 Frontend_GetImagePixelType(const void *imageRecord) {
    const u8 *record = imageRecord;
    return g_frontendImageFormatTable[*record][0];
}

/* Returns the word in the 52-byte record g_frontendImageRecordValues selected by the first byte of a record. */
s32 Frontend_GetImageBitsPerPixel(u8 *record) {
    return g_frontendImageRecordValues[record[0] * 13];
}

/* Returns the width field of the record. */
s16 Frontend_GetOwnedImageWidth(s16 *record) {
    return ((OwnedImage *)record)->width;
}

/* Returns the height field of the record. */
s16 Frontend_GetOwnedImageHeight(s16 *record) {
    return ((OwnedImage *)record)->height;
}

/* Returns the stride field of the record. */
s16 Frontend_GetOwnedImageStride(s16 *record) {
    return ((OwnedImage *)record)->stride;
}

/* Returns the row count field of the record. */
s16 Frontend_GetOwnedImageRowCount(s16 *record) {
    return ((OwnedImage *)record)->rowCount;
}

/* Returns the palette entries field of the record. */
s16 Frontend_GetOwnedImagePaletteCount(s16 *record) {
    return ((OwnedImage *)record)->paletteEntries;
}

/* unit FRONTEND_CONFIGUREOWNEDIMAGE.CPP */
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

/* Returns the pixels field of the record. */
s32 Frontend_GetOwnedImagePixels(s32 *record) {
    return (s32)((OwnedImage *)record)->pixels;
}

/* Returns the palette field of the record. */
s32 Frontend_GetOwnedImagePalette(s32 *record) {
    return (s32)((OwnedImage *)record)->palette;
}

int Frontend_HasOwnedImagePalette(void *object) {
    OwnedImage *record = object;
    return record->paletteCount > 0;
}

s32 Frontend_HasImageFormatMaskComponent(u8 *record) {
    return g_frontendImageRecordFlags[*record][0] != 0;
}

/* Returns whether the image owns its palette (bit 1 of the image's ownership flags); Frontend_OwnsImagePixels reports the pixel flag. */
u8 Frontend_OwnsImagePalette(u8 *record) {
    return (record[1] >> 1) & 1;
}

/* Returns whether the image owns its pixel data (bit 0 of the image's ownership flags); Frontend_OwnsImagePalette reports the palette flag. */
u8 Frontend_OwnsImagePixels(u8 *record) {
    return record[1] & 1;
}

void Frontend_ConfigureOwnedImage(struct Config *out, int type, short x, short y,
                  int a, int b, int enable1, int d, int e, int enable2,
                  int f, int g, int last) {
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

/* unit FRONTEND_READSOURCEPIXELCOLOR.CPP */
/* The pixel buffers the format hooks read from (g_sourceColorBuffer) and write to (g_destinationColorBuffer); each hook reads
   them as the 16-bit, 32-bit or packed 24-bit pixels of its format. */

/* Reads the pixel at (x, y) of the current image g_conversionSourceImage as a 0xAARRGGBB colour: seeks to
   x + y * width through the format's seek hook g_readSourceIndex, fetches through g_readSourceColor and converts
   the value with the format's channel masks and shifts like Frontend_ReadSourceColorEntry. */
u32 Frontend_ReadSourcePixelColor(s32 x, s32 y) {
    extern ImageDescriptor *g_conversionSourceImage;
    u32 r;
    u32 g;
    u32 b;
    u32 a;

    g_sourcePixelOffset = x + y * g_conversionSourceImage->width;
    g_readSourceIndex();
    g_readSourceColor();
    if (g_sourceRedShift < 0) {
        r = (g_sourceEncodedColor & g_sourceRedMask) << -g_sourceRedShift;
    } else {
        r = (g_sourceEncodedColor & g_sourceRedMask) >> g_sourceRedShift;
    }
    if (g_sourceGreenShift < 0) {
        g = (g_sourceEncodedColor & g_sourceGreenMask) << -g_sourceGreenShift;
    } else {
        g = (g_sourceEncodedColor & g_sourceGreenMask) >> g_sourceGreenShift;
    }
    if (g_sourceBlueShift < 0) {
        b = (g_sourceEncodedColor & g_sourceBlueMask) << -g_sourceBlueShift;
    } else {
        b = (g_sourceEncodedColor & g_sourceBlueMask) >> g_sourceBlueShift;
    }
    if (g_sourceAlphaShift < 0) {
        a = (g_sourceEncodedColor & g_sourceAlphaMask) << -g_sourceAlphaShift;
    } else {
        a = (g_sourceEncodedColor & g_sourceAlphaMask) >> g_sourceAlphaShift;
    }
    if (g_sourceAlphaMask == 0) {
        a = 0xFF;
    }
    return (a << 24) | (r << 16) | (g << 8) | b;
}

/* Sets the read position g_sourcePixelOffset to row y of column x, the row stride being the width of
   the image g_conversionSourceImage points to, calls the reader g_readSourceIndex points to, and
   returns the value it left in g_sourcePixelIndex. */
s32 Frontend_ReadSourcePixelIndex(s32 x, s32 y) {
    extern struct ImageDescriptor *g_conversionSourceImage;
    g_sourcePixelOffset = x + y * g_conversionSourceImage->width;
    g_readSourceIndex();
    return g_sourcePixelIndex;
}

/* Reads the pixel at index as a 0xAARRGGBB colour: stores the index for the current format's fetch
   hook g_readSourceColor, then extracts each channel of the fetched value with the format's channel mask
   and signed shift (a negative shift scales up) and packs alpha, red, green and blue, using 0xFF
   for alpha when the format has no alpha mask. */
u32 Frontend_ReadSourceColorEntry(s32 index) {
    u32 r;
    u32 g;
    u32 b;
    u32 a;

    g_sourceColorIndex = index;
    g_readSourceColor();
    if (g_sourceRedShift < 0) {
        r = (g_sourceEncodedColor & g_sourceRedMask) << -g_sourceRedShift;
    } else {
        r = (g_sourceEncodedColor & g_sourceRedMask) >> g_sourceRedShift;
    }
    if (g_sourceGreenShift < 0) {
        g = (g_sourceEncodedColor & g_sourceGreenMask) << -g_sourceGreenShift;
    } else {
        g = (g_sourceEncodedColor & g_sourceGreenMask) >> g_sourceGreenShift;
    }
    if (g_sourceBlueShift < 0) {
        b = (g_sourceEncodedColor & g_sourceBlueMask) << -g_sourceBlueShift;
    } else {
        b = (g_sourceEncodedColor & g_sourceBlueMask) >> g_sourceBlueShift;
    }
    if (g_sourceAlphaShift < 0) {
        a = (g_sourceEncodedColor & g_sourceAlphaMask) << -g_sourceAlphaShift;
    } else {
        a = (g_sourceEncodedColor & g_sourceAlphaMask) >> g_sourceAlphaShift;
    }
    if (g_sourceAlphaMask == 0) {
        a = 0xFF;
    }
    return (a << 24) | (r << 16) | (g << 8) | b;
}

/* Writes a 0xAARRGGBB colour to the pixel at (x, y) of the current target image g_conversionDestinationImage:
   converts the colour to the format's packed value like Frontend_WriteDestinationColorEntry, then stores it and the
   index x + y * width for the format's store hook g_writeDestinationColor and calls it. */
void Frontend_WriteDestinationPixelColor(s32 x, s32 y, u32 color) {
    extern ImageDescriptor *g_conversionDestinationImage;
    u32 r;
    u32 g;
    u32 b;
    u32 a;

    r = (color >> 16) & 0xFF;
    g = (color & 0xFF00) >> 8;
    b = color & 0xFF;
    a = color >> 24;
    if (g_destinationAlphaMask == 0) {
        a = 0xFF;
    }
    if (g_destinationRedShift < 0) {
        r = (r >> -g_destinationRedShift) & g_destinationRedMask;
    } else {
        r = (r << g_destinationRedShift) & g_destinationRedMask;
    }
    if (g_destinationGreenShift < 0) {
        g = (g >> -g_destinationGreenShift) & g_destinationGreenMask;
    } else {
        g = (g << g_destinationGreenShift) & g_destinationGreenMask;
    }
    if (g_destinationBlueShift < 0) {
        b = (b >> -g_destinationBlueShift) & g_destinationBlueMask;
    } else {
        b = (b << g_destinationBlueShift) & g_destinationBlueMask;
    }
    if (g_destinationAlphaShift < 0) {
        a = (a >> -g_destinationAlphaShift) & g_destinationAlphaMask;
    } else {
        a = (a << g_destinationAlphaShift) & g_destinationAlphaMask;
    }
    g_destinationEncodedColor = r | g | b | a;
    g_destinationColorIndex = x + y * g_conversionDestinationImage->width;
    g_writeDestinationColor();
}

/* Stores a value in g_destinationPixelIndex, sets the write position g_destinationPixelOffset to row y of column x, the row
   stride being the width of the image g_conversionDestinationImage points to, and calls the
   writer g_writeDestinationIndex points to. */
void Frontend_WriteDestinationPixelIndex(s32 x, s32 y, s32 value) {
    extern struct ImageDescriptor *g_conversionDestinationImage;
    g_destinationPixelIndex = value;
    g_destinationPixelOffset = x + y * g_conversionDestinationImage->width;
    g_writeDestinationIndex();
}

void Frontend_WriteDestinationColorEntry(s32 index, u32 color) {
    u32 r;
    u32 g;
    u32 b;
    u32 a;

    r = (color >> 16) & 0xFF;
    g = (color & 0xFF00) >> 8;
    b = color & 0xFF;
    a = color >> 24;
    if (g_destinationAlphaMask == 0) {
        a = 0xFF;
    }
    if (g_destinationRedShift < 0) {
        r = (r >> -g_destinationRedShift) & g_destinationRedMask;
    } else {
        r = (r << g_destinationRedShift) & g_destinationRedMask;
    }
    if (g_destinationGreenShift < 0) {
        g = (g >> -g_destinationGreenShift) & g_destinationGreenMask;
    } else {
        g = (g << g_destinationGreenShift) & g_destinationGreenMask;
    }
    if (g_destinationBlueShift < 0) {
        b = (b >> -g_destinationBlueShift) & g_destinationBlueMask;
    } else {
        b = (b << g_destinationBlueShift) & g_destinationBlueMask;
    }
    if (g_destinationAlphaShift < 0) {
        a = (a >> -g_destinationAlphaShift) & g_destinationAlphaMask;
    } else {
        a = (a << g_destinationAlphaShift) & g_destinationAlphaMask;
    }
    g_destinationColorIndex = index;
    g_destinationEncodedColor = r | g | b | a;
    g_writeDestinationColor();
}

u32 Frontend_EncodePixelColor(u32 color, s32 format) {
    return Frontend_EncodeFormatColor(color, &g_pixelFormatDescriptors[format]);
}

u32 Frontend_DecodePixelColor(u32 value, s32 format) {
    return Frontend_DecodeFormatColor(value, &g_pixelFormatDescriptors[format]);
}

void Frontend_ReadSourceHalfwordPixel(void) {
    g_sourceEncodedColor = ((u16 *)g_sourceColorBuffer)[g_sourceColorIndex];
}

void Frontend_ReadSourceWordPixel(void) {
    g_sourceEncodedColor = ((s32 *)g_sourceColorBuffer)[g_sourceColorIndex];
}

void Frontend_ReadSourceThreeBytePixel(void) {
    g_sourceEncodedColor = (((u8 *)g_sourceColorBuffer)[g_sourceColorIndex * 3] << 16) | (((u8 *)g_sourceColorBuffer)[g_sourceColorIndex * 3 + 1] << 8) |
                 ((u8 *)g_sourceColorBuffer)[g_sourceColorIndex * 3 + 2];
}

void Frontend_WriteDestinationHalfwordPixel(void) {
    ((u16 *)g_destinationColorBuffer)[g_destinationColorIndex] = (u16)g_destinationEncodedColor;
}

void Frontend_WriteDestinationWordPixel(void) {
    ((s32 *)g_destinationColorBuffer)[g_destinationColorIndex] = g_destinationEncodedColor;
}

void Frontend_WriteDestinationThreeBytePixel(void) {
    ((u8 *)g_destinationColorBuffer)[g_destinationColorIndex * 3] = g_destinationColorHighByte;
    ((u8 *)g_destinationColorBuffer)[g_destinationColorIndex * 3 + 1] = g_destinationColorMiddleByte;
    ((u8 *)g_destinationColorBuffer)[g_destinationColorIndex * 3 + 2] = g_destinationColorLowByte;
}

/* Loads the byte at offset g_sourcePixelOffset of the buffer g_sourcePixelIndexBuffer points to into both g_sourcePixelIndex and
   g_sourceColorIndex. */
void Frontend_ReadSourceByteIndex(void) {
    s32 value = g_sourcePixelIndexBuffer[g_sourcePixelOffset];

    g_sourcePixelIndex = value;
    g_sourceColorIndex = value;
}

void Frontend_ReadSourceNibbleIndex(void) {
    s32 index = g_sourcePixelOffset;
    s32 value;

    if (index & 1) {
        value = g_sourcePixelIndexBuffer[index >> 1] & 0xF;
    } else {
        value = g_sourcePixelIndexBuffer[index >> 1] >> 4;
    }
    g_sourcePixelIndex = value;
    g_sourceColorIndex = value;
}

void Frontend_UseHalfwordPixelOffset(void) {
    s32 value = g_sourcePixelOffset;

    g_sourcePixelIndex = value;
    g_sourceColorIndex = value;
}

void Frontend_UseThreeBytePixelOffset(void) {
    s32 value = g_sourcePixelOffset;

    g_sourcePixelIndex = value;
    g_sourceColorIndex = value;
}

void Frontend_UseWordPixelOffset(void) {
    s32 value = g_sourcePixelOffset;

    g_sourcePixelIndex = value;
    g_sourceColorIndex = value;
}

/* Stores the byte (u8)g_destinationPixelIndex at the offset g_destinationPixelOffset within the buffer g_destinationPixelIndexBuffer points to. */
void Frontend_WriteDestinationByteIndex(void) {
    g_destinationPixelIndexBuffer[g_destinationPixelOffset] = (u8)g_destinationPixelIndex;
}

void Frontend_WriteDestinationNibbleIndex(void) {
    s32 index = g_destinationPixelOffset;

    if (index & 1) {
        g_destinationPixelIndexBuffer[index >> 1] = (g_destinationPixelIndexBuffer[index >> 1] & 0xF0) | ((u8)g_destinationPixelIndex & 0xF);
    } else {
        g_destinationPixelIndexBuffer[index >> 1] = (g_destinationPixelIndexBuffer[index >> 1] & 0xF) | (((u8)g_destinationPixelIndex & 0xF) << 4);
    }
}
