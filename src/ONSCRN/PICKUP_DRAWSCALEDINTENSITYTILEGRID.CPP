#include "COMMON/FONT_STYLE_AND_GLYPH_OPERATIONS.H"
#include "COMMON/ENTRYRECATE.H"
#include "TYPES.H"
#include "MENU/PICKUP_DRAWSCALEDINTENSITYTILEGRID.H"

/* Draws a grid of 4-bit image tiles: the header holds the column and row counts, each tile holds
   its width, height and packed nibble data, and every tile goes to OnScreen_DrawIntensityTexture at the running
   position, advancing x by the tile width and y by the last tile height per row. */

extern void OnScreen_DrawIntensityTexture(s32 *data, s32 x, s16 y, s32 w, s32 h);

void Pickup_DrawIntensityTileGrid(u16 *grid, s16 x0, s32 y) {
    s32 *tile;
    s32 rows;
    s32 cols;
    s32 x;
    s32 w;
    s32 h;

    tile = (s32 *)(grid + 4);
    h = 0;
    rows = grid[1];
    while (--rows != -1) {
        x = x0;
        cols = grid[0];
        while (--cols != -1) {
            w = tile[0];
            h = tile[1];
            OnScreen_DrawIntensityTexture(tile + 2, x, y, w, h);
            x += w;
            tile = (s32 *)((char *)tile + ((u32)(w * h) >> 1));
            tile += 2;
        }
        y += h;
    }
}

/* Draws a grid of 4-bit image tiles scaled by sx and sy: the header holds the column and row
   counts, each tile holds its width, height and packed nibble data, and every tile goes to
   OnScreen_DrawScaledIntensityTexture at the running float position, advancing x by the scaled tile width and y by the
   scaled last tile height per row. Scaled counterpart of Pickup_DrawIntensityTileGrid. */

extern void OnScreen_DrawScaledIntensityTexture(u32 *data, f32 x, f32 y, u32 w, u32 h, f32 sx, f32 sy);

void Pickup_DrawScaledIntensityTileGrid(u16 *grid, f32 x0, f32 y, f32 sx, f32 sy) {
    u32 *tile;
    f32 rows;
    f32 cols;
    f32 x;
    u32 w;
    u32 h;

    tile = (u32 *)(grid + 4);
    h = 0;
    rows = grid[1];
    while (rows-- != 0.0f) {
        x = x0;
        cols = grid[0];
        while (cols-- != 0.0f) {
            w = tile[0];
            h = tile[1];
            OnScreen_DrawScaledIntensityTexture(tile + 2, x, y, w, h, sx, sy);
            x += w * sx;
            tile = (u32 *)((char *)tile + ((w * h) >> 1));
            tile += 2;
        }
        y += h * sy;
    }
}

/* Builds a 256-entry byte lookup table: every entry becomes 0xFF, then each of the count
   (key, value) byte pairs stores value at table[key]. */
void Pickup_BuildByteLookup(int unused, unsigned char *pairs, int count, unsigned char *table) {
    int i;
    unsigned char *p;
    unsigned char fill = 0xFF;

    i = 255;
    p = table + i;
    for (; i >= 0; i--) {
        *p-- = fill;
    }
    for (i = 0; i < count; i++) {
        table[pairs[0]] = pairs[1];
        pairs += 2;
    }
}



void Pickup_SetupPickupText(void) {
    char pad[256];
    (void)pad;
    OnScreen_SetupTextRendering();
    OnScreen_LoadTextTileModeOne();
    OnScreen_SetTextScale((0.699999988079071f), (0.699999988079071f));
    OnScreen_SetTextColors(0xFF, 0xFF, 0xFF, 200, 200, 200);
}
