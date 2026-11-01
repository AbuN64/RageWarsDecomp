#ifndef RENDER_MATERIAL_COLOR_AND_FOG_VIEWS_H
#define RENDER_MATERIAL_COLOR_AND_FOG_VIEWS_H
#include "TYPES.H"
struct Material {
    u8 pad[6];
    u8 flags;
};
struct Owner104 {
    char pad0[0x102];
    unsigned short flags;
};
struct SharedModelTintMaterial {
    s32 flags;
    u8 padding4[0xC];
    u8 color[4];
    u8 fog[4];
};
struct QueuedModelInstance {
    void *matrix;
    void *lights;
    void *vertices;
    s32 segmented;
};
/* The fill/tint override the material and menu drawers apply: g_menuModelFillEnabled is its mode (0 = off, 1..6 colour/fade
 * modes) and g_menuModelFillColor its colour, RGBA 0..255 plus the fade target alpha [4]. The ROM reaches the two through
 * separate addresses (a shared struct base breaks 18 exact fns), so they are two objects. */
extern s32 g_menuModelFillEnabled;
extern f32 g_menuModelFillColor[5];
#endif
