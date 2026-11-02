#ifndef DATA_UI_RIBBON_BLEND_RESOURCE_DATA_H
#define DATA_UI_RIBBON_BLEND_RESOURCE_DATA_H
#include "TYPES.H"

/* Morph indexes Key with stride 20. Graphu64_ScaleVector reads XYZ;
 * the two remaining words are retained by the resource, not pointers. */
typedef struct RibbonBlendKeyData {
    f32 position[3];
    u32 retainedWords[2];
} RibbonBlendKeyData;

/* Five TSmos state aliases precede the ribbon resource header. The six
 * resource pointers select keys 0, 2, 4, 10, 16 and 18 at offset 32. */
typedef struct FrontendRibbonResourceData {
    s32 shutdown;
    s32 controller;
    s32 active;
    s32 modeOne;
    s32 timer;
    u32 retainedHeaderWord;
    u8 retainedHeaderBytes[8];
    RibbonBlendKeyData keys[20];
} FrontendRibbonResourceData;

typedef char RibbonBlendKeyDataSize[(sizeof(RibbonBlendKeyData) == 20) ? 1 : -1];
typedef char FrontendRibbonResourceDataSize[(sizeof(FrontendRibbonResourceData) == 432) ? 1 : -1];
#endif
