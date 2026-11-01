#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/ANIMATION.H"
#include "TYPES.H"
#include "FRONTEND/FRONTEND_CONFIGUREIMAGECONVERSION.H"

/* Copies image src into dst when they differ, then fixes dst's pixel rows through Image_SwizzleImage when a paletted image has more than 0x800 bytes of pixels or a true-color image more than 0x1000; returns zero. */


extern int Frontend_GetImagePaletteByteCount(int *value);
extern int Frontend_GetImagePixelByteCount(int *value);
extern void Image_SwizzleImage(struct SwizzledImageView *image);

s32 Smp_CopyAndSwizzleImage(GameImage *dst, GameImage *src) {
    s32 palette;
    s32 size;
    s32 fix;

    if (dst != src) {
        Frontend_CopyOwnedImage(dst, src);
    }
    src = dst;
    palette = Frontend_GetImagePaletteByteCount(src);
    size = Frontend_GetImagePixelByteCount(src);
    fix = 0;
    if (palette > 0) {
        fix = size > 0x800;
    }
    if (palette == 0 && size > 0x1000) {
        fix = 1;
    }
    if (fix) {
        Image_SwizzleImage(src);
    }
    return 0;
}


void Smp_SetImageStateWord(int value) {
    g_imageSwizzleEnabled = value;
}
