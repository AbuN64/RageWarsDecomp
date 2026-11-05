#ifndef MENU_IMAGE_AND_DISPLAY_COMMAND_VIEWS_H
#define MENU_IMAGE_AND_DISPLAY_COMMAND_VIEWS_H
#include "types.h"
#include "Common/runtime_declarations.h"
struct SwizzledImageView {
    char pad0[8];
    s16 width;
    s16 height;
    char padC[0xC];
    s32 *pixels;
};
struct Command {
    unsigned words[2];
};
union Vtx10 {
    Vtx_t v;
    Vtx_tn n;
    s64 force_structure_alignment;
};
#endif
