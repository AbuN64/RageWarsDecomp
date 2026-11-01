#ifndef MENU_GFX_IMAGE_H
#define MENU_GFX_IMAGE_H
extern void Image_EmitMatrix(void *source);
extern void Image_ResetImage(void *image);
struct OwnedImage;
extern void Image_ReleaseImage(struct OwnedImage *image);
#endif
