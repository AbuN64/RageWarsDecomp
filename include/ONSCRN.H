#ifndef ONSCRN_H
#define ONSCRN_H
#include "COMMON/OBJRECAT18V6.H"
extern void OnScreen_DrawBevelBox(s32 x0, s32 y0, s32 x1, s32 y1, s32 border, s32 invert, s32 red, s32 green, s32 blue, s32 alpha);
extern void OnScreen_DrawSpriteNumber(s32 value, f32 x, f32 y, f32 size, f32 scaleY, s32, s32 rightAlign, s32 minDigits);
extern void OnScreen_SetupTextRendering(void);
extern void OnScreen_LoadTextTileModeOne(void);
extern void OnScreen_LoadTextTileModeTwo(void);

struct OverlayScriptTableView {
    unsigned char padding_0[4];
    s32 *script;
    s32 state;
};
struct OverlayScriptPrimaryRangeView {
    unsigned char padding_0[60];
    s32 target;
    s32 owner;
    s32 initialPercent;
};
struct OverlayScriptSecondaryRangeView {
    unsigned char padding_0[132];
    s32 target;
    s32 owner;
    s32 initialPercent;
};
struct COverlay {
    s32 active;
    s32 *script;
    s32 state;
    s32 wait;
    f32 x;
    f32 y;
    f32 targetX;
    f32 targetY;
    f32 velX;
    f32 velY;
    f32 accelX;
    f32 accelY;
    f32 rate;
    u8 pad34[4];
    s32 handle; /* 0x38: resource handle initialized by the mover constructor */
};
struct OnScreenImageTableView {
    s16 count;
    u8 pad2[6];
    ImageTableEntry entries[1];
};

/* Packed intensity font pixels installed by the resource loader. */
extern u8 *g_onScreenFontTexture;
extern u8 *OnScreen_GetFontTexture(void);

typedef struct TextureTileBlock {
    u32 width;
    u32 height;
    u8 pixels[0]; /* Tile pixels follow the eight-byte width/height header. */
} TextureTileBlock;
typedef struct TextureTileGrid {
    u16 columns;
    u16 rows;
    u32 reserved;
    u8 blocks[1];
} TextureTileGrid;
#endif
