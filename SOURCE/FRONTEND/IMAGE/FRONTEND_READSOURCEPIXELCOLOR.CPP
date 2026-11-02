#include "COMMON/NODERECAT2A8.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/FORMAT.H"
#include "TYPES.H"
#include "FRONTEND/FRONTEND_READSOURCEPIXELCOLOR.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"

/* Reads the pixel at (x, y) of the current image g_conversionSourceImage as a 0xAARRGGBB colour: seeks to
   x + y * width through the format's seek hook g_readSourceIndex, fetches through g_readSourceColor and converts
   the value with the format's channel masks and shifts like Frontend_ReadSourceColorEntry. */











/* Sets the read position g_sourcePixelOffset to row y of column x, the row stride being the halfword at
   offset 8 of the structure g_conversionSourceImage points to, calls the reader g_readSourceIndex points to, and
   returns the value it left in g_sourcePixelIndex. */





/* Reads the pixel at index as a 0xAARRGGBB colour: stores the index for the current format's fetch
   hook g_readSourceColor, then extracts each channel of the fetched value with the format's channel mask
   and signed shift (a negative shift scales up) and packs alpha, red, green and blue, using 0xFF
   for alpha when the format has no alpha mask. */


/* Writes a 0xAARRGGBB colour to the pixel at (x, y) of the current target image g_conversionDestinationImage:
   converts the colour to the format's packed value like Frontend_WriteDestinationColorEntry, then stores it and the
   index x + y * width for the format's store hook g_writeDestinationColor and calls it. */











/* Stores a value in g_destinationPixelIndex, sets the write position g_destinationPixelOffset to row y of column x, the row
   stride being the halfword at offset 8 of the structure g_conversionDestinationImage points to, and calls the
   writer g_writeDestinationIndex points to. */






/* Encodes an 0xAARRGGBB color into a packed pixel value of entry `format` of the format table g_pixelFormatDescriptors, shifting each channel by its signed shift and masking it. */




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

/* Loads the byte at offset g_sourcePixelOffset of the buffer g_sourcePixelIndexBuffer points to into both g_sourcePixelIndex and
   g_sourceColorIndex. */
/* The pixel buffers the format hooks read from (g_sourceColorBuffer) and write to (g_destinationColorBuffer); each hook reads
   them as the 16-bit, 32-bit or packed 24-bit pixels of its format. */
extern void *g_sourceColorBuffer;
extern void *g_destinationColorBuffer;
extern u32 g_sourceEncodedColor; /* the fetched pixel */
extern u32 g_destinationEncodedColor; /* the pixel to store */
extern u8 g_destinationColorMiddleByte; /* the third byte of g_destinationEncodedColor */
extern void (*g_readSourceIndex)();

/* Stores the byte (u8)g_destinationPixelIndex at the offset g_destinationPixelOffset within the buffer g_destinationPixelIndexBuffer points to. */


u32 Frontend_ReadSourcePixelColor(s32 x, s32 y) {
    extern ConversionImageView *g_conversionSourceImage;
    u32 r;
    u32 g;
    u32 b;
    u32 a;

    g_sourcePixelOffset = x + y * g_conversionSourceImage->width;
    g_readSourceIndex(g_sourcePixelOffset);
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

s32 Frontend_ReadSourcePixelIndex(s32 x, s32 y) {
    extern struct ConversionImageView *g_conversionSourceImage;
    g_sourcePixelOffset = x + y * g_conversionSourceImage->width;
    g_readSourceIndex();
    return g_sourcePixelIndex;
}

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

void Frontend_WriteDestinationPixelColor(s32 x, s32 y, u32 color) {
    extern ConversionImageView *g_conversionDestinationImage;
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

void Frontend_WriteDestinationPixelIndex(s32 x, s32 y, s32 value) {
    extern struct ConversionImageView *g_conversionDestinationImage;
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
    return encode(color, &g_pixelFormatDescriptors[format]);
}

u32 Frontend_DecodePixelColor(u32 value, s32 format) {
    return decode(value, &g_pixelFormatDescriptors[format]);
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
