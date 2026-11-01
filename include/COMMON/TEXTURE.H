#ifndef COMMON_TEXTURE_H
#define COMMON_TEXTURE_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
struct Texture;
typedef struct Texture Texture;

struct SwizzledImageView;
typedef struct SwizzledImageView SwizzledImageView;




extern void XMath_ShutdownMath(void);

struct SwizzledImageView;

struct Command;

extern int g_primitiveRenderFlagSelect30000;

struct Texture;
struct Texture {
    u8 format;
    char pad1[3];
    s16 width;
    s16 height;
    s16 stride;
    s16 rows;
    s32 size;
    s32 flags;
    void *palette;
    u32 data;
};


extern int g_combineTexturingEnabled;

extern float g_fullImageTextureCoordinate;










extern s32 g_combineBoundImageWidth;
extern s32 g_combineBoundImageHeight;
extern s32 g_combineImageRequiresChunks;
extern s32 g_combineImageChunkState;
extern s32 g_combineBoundImageMaskComponent;
extern s32 Frontend_HasImageFormatMaskComponent(u8 *);

extern const char g_printfLowercaseHexDigits[];
extern const u8 g_formatUppercaseHexDigits[];
extern const u8 g_formatPercentText[];
extern const u8 g_formatSpacePadding[];
extern const u8 g_formatZeroPadding[];

extern f64 g_formatNegativeThreshold;
extern f64 g_formatZeroPrecisionScale;
extern f64 g_formatRoundingNumerator;
extern f64 g_formatScientificFractionDecimalBase;
#endif
