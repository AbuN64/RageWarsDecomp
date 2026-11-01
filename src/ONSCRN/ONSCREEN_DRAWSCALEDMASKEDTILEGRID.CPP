#include "../../sdk/include/LIBC.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "include_asm.h"
#include "COMMON/FONT_STYLE_AND_GLYPH_OPERATIONS.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "ONSCRN.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "COMMON/FRUSTUM.H"
#include "COMMON/STATEPAIR.H"
#include "COMMON/OBJRECAT18V6.H"
#include "TYPES.H"
#include "RESMGR/TSMOS_UPDATEFRONTEND.H"
#include "SYSTEM/TEXTLOAD_RESETTEXTURECACHE.H"
#include "COMMON/LONE/SCREEN_IMAGE_RESOURCES_ENABLED.H"
#include "COMMON/GAME_SESSION.H"
#include "COMMON/SHAREDPLAYER.H"
#include <PR/gbi.h>
#include <ultra64.h>
#include "COMMON/MATH_HELPERS.H"
#include "COMMON/WORLD.H"
#include "COMMON/WORLDSORTENTRY.H"
#include "GFX/TEXT/ONSCREEN_DRAWSCALEDMASKEDTILEGRID.H"
#include "COMMON/DISPLAY.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/ENTRYRECATE.H"
#include "ONSCRN/ONSCREEN_DRAWSCALEDMASKEDTILEGRID.H"

/* 802A8A94_4.CPP */
s32 OnScreen_UpdateMoverScript(void *);

extern void OnScreen_DrawStatusBar(void *hud, int which);

void OnScreen_InitMover(void *moverStorage, s16 x, s16 y)
{
  COverlay *mover = moverStorage;
  mover->handle = -1;
  mover->active = 0;
  mover->state = 0;
  mover->x = (f32) x;
  mover->y = (f32) y;
}

s32 OnScreen_StartMoverScript(void *widget, s32 *script) {
    (((struct OverlayScriptTableView *) ((s8 *) widget))->script) = script;
    (((struct OverlayScriptTableView *) ((s8 *) widget))->state) = 2;
    return OnScreen_UpdateMoverScript(widget);
}

s32 OnScreen_StartFirstStatusBar(void *widget, s32 owner, s32 target) {
    (((struct OverlayScriptPrimaryRangeView *) ((s8 *) widget))->owner) = owner;
    (((struct OverlayScriptPrimaryRangeView *) ((s8 *) widget))->target) = target;
    (((struct OverlayScriptPrimaryRangeView *) ((s8 *) widget))->initialPercent) = 100;
    return OnScreen_StartMoverScript(widget, &g_firstStatusBarMoverScript);
}

void OnScreen_StartSecondStatusBar(struct OverlayScriptSecondaryRangeView *hud, s32 owner, s32 target) {
    hud->owner = owner;
    hud->target = target;
    hud->initialPercent = 100;
    OnScreen_StartMoverScript(&((Hud *)hud)->bars[1], &g_secondStatusBarMoverScript);
}

void OnScreen_SetFirstBarTarget(char *object, int value) {
    Hud *hud = (void *)object;
    hud->bars[0].target = value;
}

void OnScreen_SetSecondBarTarget(void *object, int value) {
    Hud *hud = (void *)object;
    hud->bars[1].target = value;
}

void OnScreen_DrawStatusBars(void *playerHud) {
    char pad[256];
    (void)pad;

    if (Tsmos_IsFrontendActive() == 1) {
        Tsmos_UpdateFrontend();
        Geometry_InvalidateMaterialKeys();
        TextLoad_ResetTextureCache();
    }
    OnScreen_SetupTextRendering();
    OnScreen_LoadTextTileModeOne();
    OnScreen_SetTextScale(g_hudStatusBarTextScale, g_hudStatusBarTextScale);
    OnScreen_SetTextColors(0xFF, 0xFF, 0xFF, 200, 200, 200);
    Onscrn_SetupSpriteMode(g_gameSettings.hudFade);
    if (((Hud *)playerHud)->bars[0].enabled != 0) {
        OnScreen_DrawStatusBar(playerHud, 1);
    }
    if (((Hud *)playerHud)->bars[1].enabled != 0) {
        OnScreen_DrawStatusBar(playerHud, 2);
    }
}

/** Return the floating parameter selected by the current global mode. */
f32 OnScreen_GetGlyphWidth(void) {
    {
        s32 sw_mode_value = g_creditsTextDrawingEnabled;
        if ((unsigned int)sw_mode_value > 6) {
            goto sw_mode_default;
        }
        switch (sw_mode_value) {
        case 0: goto sw_mode_0;
        case 1: goto sw_mode_1;
        case 2: goto sw_mode_2;
        case 3: goto sw_mode_3;
        case 4: goto sw_mode_4;
        case 5: goto sw_mode_4;
        case 6: goto sw_mode_2;
        }
    }
    do {
    sw_mode_0:
        return 24.0f;
    sw_mode_1:
        return 12.0f;
    sw_mode_2:
    sw_mode_6:
        return 8.0f;
    sw_mode_3:
        return 6.0f;
    sw_mode_4:
    sw_mode_5:
        return 16.0f;
    sw_mode_default:
        return 1.0f;

    } while (0);
}

void OnScreen_GetImageEntry(OnScreenImageTableView **handle, s32 index, void **out, u8 *tag) {
    OnScreenImageTableView *table;
    ImageTableEntry *entry;
    void *result;
    u8 entryTag;
    s32 remainder;

    *out = 0;
    if (handle != 0) {
        table = *handle;
        entry = &table->entries[0];
        remainder = index % table->count;
        remainder *= 8;
        remainder += (s32)entry;
        entry = (ImageTableEntry *)remainder;
        entryTag = entry->pad4[0];
        result = (u8 *)table + entry->offset;
        *tag = entryTag;
        *out = result;
    }
}

extern Gfx *g_displayListCursor;

extern s32 Scene_StartWorldEffect(void *world, s32 id, s32 flags, s32 extra);
extern void Cache_UnlockResource(s32 cacheContext, s32 resource);
extern s32 Geometry_SetModePreset(s32);
extern void Geometry_SetCombineMode(u32);

#if defined(VERSION_EU_X)
void OnScreen_GetImageDimensions(s32 resourceId, s32 frameIndex, s32 *widthOutput, s32 *heightOutput)
{
  void *imageEntry;
  s32 entryTag;
  void *imageData;
  s32 resourceHandle;
  if (g_screenImageResourcesEnabled != 0)
  {
    resourceHandle = Scene_StartWorldEffect(&g_world, resourceId, 0, 1);
    if (resourceHandle != 0)
    {
      OnScreen_GetImageEntry(resourceHandle, frameIndex, &imageEntry, &entryTag);
      imageData = imageEntry;
      *widthOutput = ((ImageSet *)imageEntry)->width;
      *heightOutput = ((ImageSet *)imageData)->height;
      Cache_UnlockResource(0, resourceHandle);
    }
  }
}
#endif

#if defined(VERSION_EU_X)
void OnScreen_SetupFillMode(void) {

    Gfx *gfx;

    gfx = g_displayListCursor++;
    gDPPipeSync(gfx);
    gfx = g_displayListCursor++;
    gDPSetCycleType(gfx, G_CYC_1CYCLE);
    Geometry_SetModePreset(21);
    Geometry_SetCombineMode(25);
}
#endif

#if defined(VERSION_EU_X)
void OnScreen_FillRectangle(s32 x0,s32 y0,s32 x1,s32 y1,u8 r,u8 g,u8 b,u8 a) {

 gDPPipeSync(g_displayListCursor++);
 gDPSetPrimColor(g_displayListCursor++, 255, 255, r, g, b, a);
 gDPFillRectangle(g_displayListCursor++, ((x0))>((0))?((x0)):((0)), ((y0))>((0))?((y0)):((0)), ((x1))>((0))?((x1)):((0)), ((y1))>((0))?((y1)):((0)));
}
#endif

#if defined(VERSION_EU_X)
extern s32 Scene_StartWorldEffect(void *,s32,s32,s32);
extern void Cache_UnlockResource(s32,s32);

void OnScreen_SetTextColors(int topRed, int topGreen, int topBlue, int alpha, int bottomGreen, int bottomBlue) {
    g_tutorialStatusBars.envR = topRed;
    g_tutorialStatusBars.envG = topGreen;
    g_tutorialStatusBars.envB = topBlue;
    g_tutorialStatusBars.primR = alpha;
    g_tutorialStatusBars.primG = bottomGreen;
    g_tutorialStatusBars.primB = bottomBlue;
}
#endif

#if defined(VERSION_EU_X)
void OnScreen_SetTextScale(float scaleX, float scaleY) {
    g_tutorialStatusBars.width = scaleX;
    g_tutorialStatusBars.height = scaleY;
}
#endif

#if defined(VERSION_EU_X)
void OnScreen_DrawTextWithShadow(u8 *text, f32 x, f32 y, f32 scaleX, f32 scaleY, s32 drawShadow, s32 alpha, s32 textFlags) {
    if (drawShadow != 0) {
        OnScreen_DrawTextGlyphs(text, x, y, scaleX, scaleY, 1, alpha, textFlags);
    }
    OnScreen_DrawTextGlyphs(text, x, y, scaleX, scaleY, 0, alpha, textFlags);
}
#endif

#if !(defined(VERSION_EU_X))

/* Appends a pipe synchronisation and an other-mode setting to the display list g_displayListCursor_SimpleDrawcachedmodel points
   into, then calls Geometry_SetModePreset with 0x15 and Geometry_SetCombineMode_GeometryDrawcharactereffectparts with 0x19. */

/* Emits pipe sync, primitive color and a rectangle with nonnegative coordinates. */

extern void Text_DrawTileGrid(s32 handle, s32 index, s16 initialX, s16 initialY, f32 scaleX, f32 scaleY, s32 scaled);

void OnScreen_GetImageDimensions(s32 resourceId, s32 frameIndex, s32 *outWidth, s32 *outHeight)
{
  void *image;
  s32 imageTag;
  void *imageResource;
  s32 resourceHandle;
  if (g_screenImageResourcesEnabled != 0)
  {
    resourceHandle = Scene_StartWorldEffect(&g_world, resourceId, 0, 1);
    if (resourceHandle != 0)
    {
      OnScreen_GetImageEntry(resourceHandle, frameIndex, &image, &imageTag);
      imageResource = image;
      *outWidth = ((ImageSet *)image)->width;
      *outHeight = ((ImageSet *)imageResource)->height;
      Cache_UnlockResource(0, resourceHandle);
    }
  }
}

void OnScreen_SetupFillMode(void) {

    Gfx *gfx;

    gfx = g_displayListCursor++;
    gDPPipeSync(gfx);
    gfx = g_displayListCursor++;
    gDPSetCycleType(gfx, G_CYC_1CYCLE);
    Geometry_SetModePreset(21);
    Geometry_SetCombineMode(25);
}

void OnScreen_FillRectangle(s32 x0,s32 y0,s32 x1,s32 y1,u8 r,u8 g,u8 b,u8 a) {

 gDPPipeSync(g_displayListCursor++);
 gDPSetPrimColor(g_displayListCursor++, 255, 255, r, g, b, a);
 gDPFillRectangle(g_displayListCursor++, ((x0))>((0))?((x0)):((0)), ((y0))>((0))?((y0)):((0)), ((x1))>((0))?((x1)):((0)), ((y1))>((0))?((y1)):((0)));
}

/** Store six words into the global record. */
void OnScreen_SetTextColors(int environmentRed, int environmentGreen, int environmentBlue, int primitiveRed, int primitiveGreen, int primitiveBlue) {
    g_tutorialStatusBars.envR = environmentRed;
    g_tutorialStatusBars.envG = environmentGreen;
    g_tutorialStatusBars.envB = environmentBlue;
    g_tutorialStatusBars.primR = primitiveRed;
    g_tutorialStatusBars.primG = primitiveGreen;
    g_tutorialStatusBars.primB = primitiveBlue;
}

void OnScreen_SetTextScale(float horizontalScale, float verticalScale) {
    g_tutorialStatusBars.width = horizontalScale;
    g_tutorialStatusBars.height = verticalScale;
}

void OnScreen_DrawTextWithShadow(s32 text, f32 x, f32 y, f32 width, f32 height, s32 drawShadow, s32 alpha, s32 language) {
    if (drawShadow != 0) {
        OnScreen_DrawTextGlyphs(text, x, y, width, height, 1, alpha, language);
    }
    OnScreen_DrawTextGlyphs(text, x, y, width, height, 0, alpha, language);
}

#endif

extern void Text_DrawTileGrid(s32 handle, s32 index, s16 initialX, s16 initialY, f32 scaleX, f32 scaleY, s32 scaled);
s32 OnScreen_DrawSpriteResource(s32 resourceId, s32 index, s16 x, s16 y, f32 scaleX, f32 scaleY, s32 scaled) {

    s32 resourceHandle;

    if ((u32)(g_displayListCapacityUsRev1 - (((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) >> 3)) < 1000
        || g_screenImageResourcesEnabled == 0
        || (resourceHandle = Scene_StartWorldEffect(&g_world, resourceId, 0, 1), resourceHandle == 0)) {
        return 0;
    }
    Text_DrawTileGrid(resourceHandle, index, x, y, scaleX, scaleY, scaled);
    Cache_UnlockResource(0, resourceHandle);
    return 1;
}

extern u8 g_onScreenFontTextureStorage[144];

typedef struct ResourceView {
    u8 *data;
    u8 type;
} ResourceView;
void OnScreen_LoadFontTexture(void) {
    OnScreenImageTableView **handle;
    OnScreenImageTableView *table;
    ImageTableEntry *entry;
    ResourceView view;
    u8 entryTag;
    s32 remainder;
    void *result;
    void *base;
    g_onScreenFontTexture = 0;
    handle = Scene_StartWorldEffect(&g_world, 2, 0, 1);
    if (handle != 0) {
        table = *handle;
        view.data = 0;
        entry = &table->entries[0];
        remainder = 0 % table->count;
        entry += remainder;
        base = table;
        result = base + entry->offset;
        entryTag = entry->pad4[0];
        view.type = entryTag;
        view.data = result;
        if (view.data != 0) {
            view.data += 0x10;
        }
        Libc_CopyBytes(g_onScreenFontTextureStorage, view.data, 144);
        Cache_UnlockResource(0, handle);
        g_onScreenFontTexture = g_onScreenFontTextureStorage;
    }
}

/** Return the global word at g_onScreenFontTexture. */

u8 *OnScreen_GetFontTexture(void) {
    return g_onScreenFontTexture;
}

/* Draws a grid of 16-bit image tiles with a 4-bit mask: the header holds the column and row counts,
   each tile holds its width, height, two bytes per pixel and then half a byte per pixel of mask,
   and every tile goes to OnScreen_DrawTextureWithOpacity at the running position, advancing x by the tile width and
   y by the last tile height per row. Adapted from Pickup_DrawIntensityTileGrid with the mask pointer added. */

extern void OnScreen_DrawTextureWithOpacity(s32 *pixels, char *mask, s32 x, s16 y, s32 w, s32 h);

void OnScreen_DrawMaskedTileGrid(u16 *grid, s16 x0, s32 y) {
    s32 *tile;
    s32 rows;
    s32 cols;
    s32 x;
    s32 w;
    s32 h;
    u32 area;

    tile = (s32 *)(grid + 4);
    h = 0;
    rows = grid[1];
    while (--rows != -1) {
        x = x0;
        cols = grid[0];
        while (--cols != -1) {
            w = tile[0];
            h = tile[1];
            area = w * h;
            OnScreen_DrawTextureWithOpacity(tile + 2, (char *)tile + (area * 2 + 8), x, y, w, h);
            x += w;
            tile = (s32 *)((char *)tile + (area * 2 + (area >> 1)));
            tile += 2;
        }
        y += h;
    }
}

/* Draws a grid of 16-bit image tiles with a 4-bit mask scaled by sx and sy: the header holds the column
   and row counts, each tile holds its width, height, two bytes per pixel and then half a byte per pixel
   of mask, and every tile goes to OnScreen_DrawScaledMaskedImage at the running float position, advancing x by the
   scaled tile width and y by the scaled last tile height per row. Scaled counterpart of
   OnScreen_DrawMaskedTileGrid; the float counters count down with `rows-- != 0.0f` as in Pickup_DrawScaledIntensityTileGrid. */
extern void OnScreen_DrawScaledMaskedImage(void *pTexture, void *pOpacity, float XPos, float YPos, int TextureWidth, int TextureHeight, float ScaleX, float ScaleY);
void OnScreen_DrawScaledMaskedTileGrid(u16 *grid, f32 x0, f32 y, f32 sx, f32 sy) {
    u32 *tile;
    f32 rows;
    f32 cols;
    f32 x;
    u32 w;
    u32 h;
    u32 area;

    tile = (u32 *)(grid + 4);
    h = 0;
    rows = grid[1];
    while (rows-- != 0.0f) {
        x = x0;
        cols = grid[0];
        while (cols-- != 0.0f) {
            w = tile[0];
            h = tile[1];
            area = w * h;
            OnScreen_DrawScaledMaskedImage(tile + 2, (char *)tile + (area * 2 + 8), x, y, w, h, sx, sy);
            x += w * sx;
            tile = (u32 *)((char *)tile + (area * 2 + (area >> 1)));
            tile += 2;
        }
        y += h * sy;
    }
}
