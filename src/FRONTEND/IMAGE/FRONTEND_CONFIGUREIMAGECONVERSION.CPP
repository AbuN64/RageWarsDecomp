#include "include_asm.h"
#include "COMMON/NODERECAT2A8.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "FRONTEND/LAYOUT.H"
#include "COMMON/FORMAT.H"
#include "TYPES.H"
#include "FRONTEND/FRONTEND_CONFIGUREIMAGECONVERSION.H"
#include "SCENE/CACHE_FREEMEMORY.H"
#include "RESMGR/resmgr_string_memory.H"

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





static inline u32 decode(u32 value, Format *format) {
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

static inline u32 encode(u32 color, Format *format) {
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

extern void *g_destinationColorBuffer;
extern void *g_sourceColorBuffer;

/* Releases a resource object's buffers through Cache_FreeMemory (the one at 0x18 when flag 1 is set, the
   one at 0x14 when flag 2 is set and its size at 0x10 is positive) and clears its 32 bytes. */



/* Copies image src into dst: releases dst's owned pixel data (flag 1) and palette (flag 2, when it
   has entries), clears it and copies src's header, drops a palette pointer without entries, marks
   the copies owned, then allocates and copies the pixel data (size from Frontend_GetImagePixelByteCount) and, when
   src has a palette, the palette (size from Frontend_GetImagePaletteByteCount). Returns 1 when an allocation fails,
   leaving dst cleared, otherwise 0. */




extern int Frontend_GetImagePixelByteCount(int *value);

extern int Frontend_GetImagePaletteByteCount(int *value);

extern struct Record *Cache_AllocateMemory(s32 size);


/* The argument is a pointer into 0x8068xxxx whose first byte the debugger read as 0x14, and the
   stride is 52. g_frontendImageRecordFlags, which Frontend_HasImageFormatMaskComponent indexes with the same stride and the same
   argument, sits 24 bytes further on, so both are fields of one 52-byte record. */

/* Returns the word in the 52-byte record g_frontendImageRecordValues selected by the first byte of a record. */

u32 Frontend_ConvertPixelFormat(u32 value, s32 from, s32 to) {
    return encode(decode(value, &g_pixelFormatDescriptors[from]), &g_pixelFormatDescriptors[to]);
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
        else if(dst.bits==24) g_writeDestinationColor=g_Frontend_WriteDestinationThreeBytePixelAddress;
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
        else if(src.bits==24) g_readSourceColor=g_Frontend_ReadSourceThreeBytePixelAddress;
        else if(src.bits==32) g_readSourceColor=g_Frontend_ReadSourceWordPixelAddress;
        if(src.type==4) g_readSourceIndex=g_Frontend_ReadSourceNibbleIndexAddress;
        else if(src.type==8) g_readSourceIndex=g_Frontend_ReadSourceByteIndexAddress;
        else if(src.type==16) g_readSourceIndex=g_Frontend_UseHalfwordPixelOffsetAddress;
        else if(src.type==24) g_readSourceIndex=g_Frontend_UseThreeBytePixelOffsetAddress;
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

s32 Frontend_GetImagePixelType(u8 *record) {
    return g_frontendImageFormatTable[*record][0];
}

s32 Frontend_GetImageBitsPerPixel(u8 *record) {
    return g_frontendImageRecordValues[record[0] * 13];
}

/* Returns the halfword at offset 0x2 of a record. It is one of a run of accessors from
   Frontend_GetOwnedImageWidth to Frontend_GetOwnedImagePaletteCount that return the halfwords at offsets 2 to 0xA in turn. */
s16 Frontend_GetOwnedImageWidth(s16 *record) {
    return ((OwnedImage *)record)->width;
}

/* Returns the halfword at offset 0x4 of a record. It is one of a run of accessors from
   Frontend_GetOwnedImageWidth to Frontend_GetOwnedImagePaletteCount that return the halfwords at offsets 2 to 0xA in turn. */
s16 Frontend_GetOwnedImageHeight(s16 *record) {
    return ((OwnedImage *)record)->height;
}

/* Returns the halfword at offset 0x6 of a record. It is one of a run of accessors from
   Frontend_GetOwnedImageWidth to Frontend_GetOwnedImagePaletteCount that return the halfwords at offsets 2 to 0xA in turn. */
s16 Frontend_GetOwnedImageStride(s16 *record) {
    return ((OwnedImage *)record)->stride;
}

/* Returns the halfword at offset 0x8 of a record. It is one of a run of accessors from
   Frontend_GetOwnedImageWidth to Frontend_GetOwnedImagePaletteCount that return the halfwords at offsets 2 to 0xA in turn. */
s16 Frontend_GetOwnedImageRowCount(s16 *record) {
    return ((OwnedImage *)record)->rowCount;
}

/* Returns the halfword at offset 0xA of a record. It is one of a run of accessors from
   Frontend_GetOwnedImageWidth to Frontend_GetOwnedImagePaletteCount that return the halfwords at offsets 2 to 0xA in turn. */
s16 Frontend_GetOwnedImagePaletteCount(s16 *record) {
    return ((OwnedImage *)record)->paletteEntries;
}
