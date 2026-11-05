#ifndef ONSCRN_H
#define ONSCRN_H
#include "Common/small_records.h"
#include "Common/hud_effects.h"
extern void OnScreen_DrawBevelBox(s32 x0, s32 y0, s32 x1, s32 y1, s32 border, s32 invert, s32 red, s32 green, s32 blue, s32 alpha);
extern void OnScreen_DrawSpriteNumber(s32 value, f32 x, f32 y, f32 size, f32 scaleY, s32, s32 rightAlign, s32 minDigits);
extern void OnScreen_SetupTextRendering(void);
extern void OnScreen_LoadTextTileModeOne(void);
extern void OnScreen_LoadTextTileModeTwo(void);





/* Loaded image resource: an eight-byte header followed by count eight-byte entries.
   Header bytes +2..+7 still require resource-format provenance. */
struct LoadedImageTable {
    s16 count;
    u8 pad2[6];
    ImageTableEntry entries[0];
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
struct Hud;
void OnScreen_DrawStatusBar(struct Hud *hud, s32 which);
struct COverlay;
void OnScreen_UpdateMoverScript(struct COverlay *m);
/* Resolved image payload and its one-byte resource tag; trailing bytes are ABI padding. */
typedef struct ResourceView {
    u8 *data;
    u8 type;
} ResourceView;

#endif
