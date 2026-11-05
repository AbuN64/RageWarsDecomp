#include "Resmgr/resmgr_string_memory.h"
#include "Common/texture.h"
#include "Menu/image_and_display_command_views.h"
#include "types.h"
#include "Menu/Gfx/image.h"
#include "Frontend/frontend_configureimageconversion.h"
#include "Frontend/text_render.h"
#include "Common/sessionhandlerrow.h"

void Image_EmitMatrix(void *source) {
    void *allocation = ESmem_AllocateFrameHeapHigh(64);
    struct Command *command;

    guMtxF2L(source, allocation);
    command = g_displayListCursor++;
    command->words[0] = 0xDA380003;
    command->words[1] = (unsigned)allocation;
}

/* Rewrites an image's pixel rows in place when row fixing is enabled (g_imageSwizzleEnabled): the row length
   in 8-byte pixel groups comes from the image width and the bit depth reported by Frontend_GetImagePixelType
   (4, 8 or 16 bits), odd rows swap the two words of each group and even rows are copied to the
   write position through XPlus_CopyBytes when source and destination differ. */
void Image_SwizzleImage(SwizzledImageView *image) {
    s32 *src;
    s32 *dst;
    s32 groups;
    s32 row;
    s32 i;
    s32 first;
    s32 second;

    if (g_imageSwizzleEnabled == 0 || image->width == 0 || image->height == 0) {
        return;
    }
    switch (Frontend_GetImagePixelType(image)) {
        case 4:
            groups = image->width / 16;
            break;
        case 8:
            groups = image->width / 8;
            break;
        case 16:
            groups = image->width / 4;
            break;
        default:
            groups = 0;
            break;
    }
    src = image->pixels;
    dst = src;
    for (row = 0; row < image->height; row++) {
        if (row & 1) {
            for (i = 0; i < groups; i++) {
                first = *src++;
                second = *src++;
                *dst++ = second;
                *dst++ = first;
            }
        } else {
            if (src != dst) {
                XPlus_CopyBytes(dst, src, groups * 8);
            }
            dst += groups * 2;
            src += groups * 2;
        }
    }
}

struct OwnedImage;

/* The archive loader passes the image address through these forwarding calls. */
void Image_ResetImage(void *image) {
    Frontend_ClearOwnedImage((int)image);
}

void Image_ReleaseImage(struct OwnedImage *image) {
    Frontend_ReleaseOwnedImageBuffers(image);
}
