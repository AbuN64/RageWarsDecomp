#ifndef COMMON_FORMAT_H
#define COMMON_FORMAT_H
#include "TYPES.H"
extern int g_destinationGreenShift;

extern int g_sourceBlueShift;

extern int g_destinationBlueShift;

extern int Frontend_HasOwnedImagePalette(void *object);

struct Format;
struct Format {
    s32 word0;
    s32 flags;
    s32 type;
    s32 bits;
    s32 word4;
    u32 mask[4];
    s32 shift[4];
};

struct Format;
extern struct Format g_pixelFormatDescriptors[];
extern void Frontend_GetPixelFormatDescriptor(s32 index, struct Format *out);


extern int g_sourceGreenShift;


extern int g_destinationPixelIndex;

extern s32 Frontend_GetOwnedImagePixels(s32 *record);






extern int g_sourceRedShift;




extern unsigned char g_destinationColorHighByte;


extern int g_sourceAlphaShift;

extern s32 Frontend_GetOwnedImagePalette(s32 *record);

struct Format;
typedef struct Format Format;

extern u8 Frontend_OwnsImagePixels(u8 *record);

extern int g_destinationAlphaShift;





extern unsigned char g_destinationColorLowByte;


struct Config;
struct Config {
    unsigned char type;
    unsigned char flags;
    short last;
    short x;
    short y;
    short a;
    short b;
    int d;
    int e;
    int f;
    int g;
};

extern u8 Frontend_OwnsImagePalette(u8 *record);


extern int g_destinationRedShift;
#endif
