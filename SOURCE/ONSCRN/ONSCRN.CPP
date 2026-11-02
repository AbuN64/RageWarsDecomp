#include "COMMON/OBJRECAT18V6.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/LONE/HUD_REFERENCE_VIEWPORT_HEIGHT.H"
#include "COMMON/FONT_STYLE_AND_GLYPH_OPERATIONS.H"
#include "TYPES.H"
#include "GFX/TEXT/ONSCREEN_DRAWSCALEDMASKEDTILEGRID.H"
#include "ONSCRN.H"
#include <PR/abi.h>
#include <PR/gbi.h>
#include <ultra64.h>
#include "COMMON/WORLD.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "SCENE/CACHE_ALLOCATERESOURCEAT.H"
#include "include_asm.h"

/* 802A6AC0_9.CPP */
extern void Onscrn_SetupSpriteMode(s32 color);

/* Draws one of the two gauges of the head-up panel, the first at hud->bars[0] and the second at
   hud->bars[1]: steps the gauge's scripted mover, walks its shown amount toward the gauge's target
   count by eight a frame up or four a frame down without passing it, fills the bar from x+80 to the
   right margin in the gauge's own colour at the options fade g_playerHudSpriteMode times 180/255, and draws the
   gauge's label at the bar's left edge. The first gauge also draws its two end caps, at the screen
   edges, unit width and one and a half times the panel scale. */

extern s32 SetN64_IsModeThirteen(void);

void OnScreen_UpdateMoverScript(COverlay *m);
extern void OnScreen_FillRectangle(s32 x0, s32 y0, s32 x1, s32 y1, s32 red, s32 green, s32 blue, u8 alpha);

void OnScreen_DrawStatusBar(Hud *hud, s32 which) {
    Bar *bar;
    f32 scale;
    f32 wide;
    f32 target;
    f32 shift;
    s32 red;
    s32 green;
    s32 blue;
    s32 offset;
    s32 x;
    s32 y;
    s32 left;
    s32 right;
    s32 inset;
    u8 *fade;
    s32 value;

    if (Cinema_IsSequenceInWindow() != 0) {
        return;
    }
    if (SetN64_IsModeThirteen() == 0) {
        return;
    }
    wide = Frontend_GetScreenMode() == 0 ? 0.75f : 1.0f;
    scale = g_gameplayCameraList.camera->viewHeight / (f32) g_hudReferenceViewportHeight;
    scale = scale * wide;
    switch (which) {
    case 1:
        bar = &hud->bars[0];
        target = (f32) hud->bars[0].target;
        red = 29;
        green = 83;
        blue = 226;
        offset = 31;
        break;
    case 2:
        bar = &hud->bars[1];
        target = (f32) hud->bars[1].target;
        red = 139;
        green = 185;
        blue = 70;
        offset = 48;
        break;
    default:
        return;
    }
    x = (s32) bar->x;
    y = (s32) (bar->y + (f32) offset * scale);
    OnScreen_SetupFillMode();
    OnScreen_UpdateMoverScript((COverlay *)bar);
    if (bar->state == 1) {
        value = bar->fill;
        if ((f32) value < target) {
            value += 8;
            bar->fill = value;
            if (target < (f32) value) {
                bar->fill = (s32) target;
            }
        } else if (target < (f32) value) {
            value -= 4;
            bar->fill = value;
            if ((f32) value < target) {
                bar->fill = (s32) target;
            }
        }
    }
    left = x + 80;
    inset = x - 112;
    right = inset + g_hudReferenceViewportWidth;
    fade = &g_gameSettings.hudFade;
    OnScreen_FillRectangle(left, (s32) ((f32) y + scale * 9.0f),
                  left + ((right - left) * bar->fill) / 100,
                  (s32) ((f32) y + scale * 15.0f), red, green, blue,
                  (u8) (*fade * 180 / 255));
    Onscrn_SetupSpriteMode(*fade);
    if (which == 1) {
        shift = scale * 27.0f;
        OnScreen_DrawSpriteResource(514, 0, (s16) (x + 70), (s16) (s32) (bar->y + shift), 1.0f, scale * 1.5f, which);
        OnScreen_DrawSpriteResource(515, 0, (s16) (g_hudReferenceViewportWidth + x - 109), (s16) (s32) (bar->y + shift), 1.0f, scale * 1.5f, which);
        OnScreen_SetupTextRendering();
        OnScreen_SetTextScale(0.4f, scale * 0.4f);
        OnScreen_SetTextColors(0xFF, 0xFF, 0xFF, 200, 200, 200);
        Onscrn_DrawText(hud->bars[0].label, left, y - 2, *fade, 0, 0, 1.0f, 1.0f);
    } else {
        OnScreen_SetupTextRendering();
        OnScreen_SetTextScale(0.4f, scale * 0.4f);
        OnScreen_SetTextColors(0xFF, 0xFF, 0xFF, 200, 200, 200);
        Onscrn_DrawText(hud->bars[1].label, left, y - 2, *fade, 0, 0, 1.0f, 1.0f);
    }
}

/* 802A8A94.CPP */
static inline void rectangle(s32 x0,s32 y0,s32 x1,s32 y1,s32 r,s32 g,s32 b,s32 a) {
    gDPPipeSync(g_displayListCursor++);
    gDPSetPrimColor(g_displayListCursor++,255,255,r,g,b,a);
    gDPFillRectangle(g_displayListCursor++, x0>0?x0:0,y0>0?y0:0,x1>0?x1:0,y1>0?y1:0);
}

/* Draws a signed integer of up to four digits with the font sprite set from Scene_StartWorldEffect: splits the magnitude into thousands, hundreds, tens and ones, draws a leading minus sign through OnScreen_DrawSpriteResource when negative, then draws at least minDigits digits through Text_DrawTileGrid, advancing 13 units per digit (0.7 of that for a one) scaled by the size, laid out right to left when rightAlign is set, and releases the sprite set. */

extern s32 Scene_StartWorldEffect(void *world, s32 effectId, s32 flags, s32 extra);

extern void Text_DrawTileGrid(s32 handle, s32 index, s16 initialX, s16 initialY, f32 scaleX, f32 scaleY, s32 scaled);

extern void Geometry_SetCombineMode(u32 mode);

extern s32 Geometry_SetModePreset(s32);

void OnScreen_UpdateMoverScript(COverlay *m) {
    s32 next;
    f32 dx;
    f32 dy;
    s32 bottom;
    s32 right;

    bottom = g_hudReferenceViewportHeight + 96;
    right = g_hudReferenceViewportWidth + 96;
    do {
        next = 0;
        switch (m->state) {
        case 0:
        case 1:
            break;
        case 2:
            if (m->script != 0) {
                switch (*m->script++) {
                case 6:
                    m->state = 0;
                    m->script = 0;
                    break;
                case 1:
                    next = 1;
                    m->x = *m->script++;
                    m->y = *m->script++;
                    break;
                case 2:
                    m->state = 3;
                    m->wait = *m->script++;
                    break;
                case 3:
                    m->active = 1;
                    m->state = 4;
                    m->targetX = *m->script++;
                    m->targetY = *m->script++;
                    m->rate = 1.0f / *m->script++;
                    break;
                case 4:
                    m->active = 1;
                    m->state = 5;
                    m->velY = 0.0f;
                    m->accelY = *m->script++ * (1.0f / 65536.0f);
                    break;
                case 5:
                    m->active = 1;
                    m->state = 6;
                    m->velX = 0.0f;
                    m->accelX = *m->script++ * (1.0f / 65536.0f);
                    break;
                default:
                    m->state = 1;
                    m->script = 0;
                    break;
                }
            } else {
                m->state = 1;
            }
            break;
        case 3:
            if (m->wait-- <= 0) {
                next = 1;
            }
            break;
        case 4:
            dx = (m->targetX - m->x) * m->rate;
            dy = (m->targetY - m->y) * m->rate;
            m->x += dx;
            m->y += dy;
            if ((dx < 0.0f ? -dx < 0.25f : dx < 0.25f) && (dy < 0.0f ? -dy < 0.25f : dy < 0.25f)) {
                m->x = m->targetX;
                m->y = m->targetY;
                next = 1;
            }
            break;
        case 5:
            m->y += m->velY;
            m->velY += m->accelY;
            if ((f32)bottom < m->y || m->y < -90.0f) {
                m->active = 0;
                next = 1;
            }
            break;
        case 6:
            m->x += m->velX;
            m->velX += m->accelX;
            if ((f32)right < m->x || m->x < -90.0f) {
                m->active = 0;
                next = 1;
            }
            break;
        }
        if (next) {
            m->state = 2;
        }
    } while (next);
}

void OnScreen_DrawBevelBox(s32 x0,s32 y0,s32 x1,s32 y1,s32 border,s32 invert,s32 red,s32 green,s32 blue,s32 alpha) {
    u8 r=red,g=green,b=blue,a=alpha;
    s32 lightR,lightG,lightB,darkR,darkG,darkB;
    lightR=invert ? r>>1 : r<<1;
    lightG=invert ? g>>1 : g<<1;
    lightB=invert ? b>>1 : b<<1;
    darkR=invert ? r<<1 : r>>1;
    darkG=invert ? g<<1 : g>>1;
    darkB=invert ? b<<1 : b>>1;
    rectangle(x0,y0,x1,y1,r,g,b,a);
    rectangle(x0,y0,x1,y0+border,lightR,lightG,lightB,a);
    rectangle(x1-border,y0,x1,y1,lightR,lightG,lightB,a);
    rectangle(x0,y1-border,x1,y1,darkR,darkG,darkB,a);
    rectangle(x0,y0,x0+border,y1,darkR,darkG,darkB,a);
}

void OnScreen_DrawSpriteNumber(s32 value, f32 x, f32 y, f32 size, f32 scaleY, s32 scaled, s32 rightAlign, s32 minDigits) {
    s32 sprites;
    s32 negative;
    s32 thousands;
    s32 hundreds;
    s32 tens;
    s32 ones;
    s32 rest;
    s32 last;
    s32 i;
    s32 place;
    s32 digit;
    f32 width;
    f32 scale;

    sprites = Scene_StartWorldEffect(&g_world, 4, 16, 1);
    if (sprites == 0) {
        return;
    }
    negative = 0;
    if (value < 0) {
        value = -value;
        negative = 1;
        if (value < 0) {
            goto release;
        }
    }
    thousands = value * 0.001f;
    rest = value - thousands * 1000;
    hundreds = rest * 0.01f;
    rest -= hundreds * 100;
    tens = rest * 0.1f;
    ones = rest - tens * 10;
    last = 3;
    if (thousands == 0) {
        last = 2;
        if (hundreds == 0) {
            last = tens != 0;
        }
    }
    if (last < minDigits - 1) {
        last = minDigits - 1;
    }
    if (negative) {
        OnScreen_DrawSpriteResource(4, 10, x, y, size, scaleY, scaled);
        x += size * 13.0f;
    }
    for (i = last; i >= 0; i--) {
        place = i;
        if (rightAlign) {
            place = last - i;
        }
        switch (place) {
        case 3:
            digit = thousands;
            break;
        case 2:
            digit = hundreds;
            break;
        case 1:
            digit = tens;
            break;
        case 0:
        default:
            digit = ones;
            break;
        }
        scale = 1.0f;
        if (digit == 1) {
            scale = 0.7f;
        }
        width = scale * (size * 13.0f);
        if (rightAlign) {
            x -= width;
        }
        if ((u32)digit < 10) {
            Text_DrawTileGrid(sprites, digit, x, y, size, scaleY, scaled);
        }
        if (!rightAlign) {
            x += width;
        }
    }
release:
    Cache_UnlockResource(0, (struct CacheResourceNode *)sprites);
}

void OnScreen_SetupTextRendering(void) {
    u8 *texture;

    texture = OnScreen_GetFontTexture();
    if (texture != 0) {

        {
            Gfx *cmd;
            cmd = g_displayListCursor++;
            gDPPipeSync(cmd);
            cmd = g_displayListCursor++;
            gDPSetCycleType(cmd, G_CYC_2CYCLE);
        }

        Geometry_SetCombineMode(26);
        Geometry_SetModePreset(21);

        g_creditsTextDrawingEnabled = 0;
        {
        Gfx *cmd;
        cmd = g_displayListCursor++;
        gSPTexture(cmd, 32768, 32768, 0, 0, G_ON);
        cmd = g_displayListCursor++;
        gDPSetTextureLUT(cmd, G_TT_NONE);
        cmd = g_displayListCursor++;
        gDPSetTexturePersp(cmd, G_TP_NONE);
        cmd = g_displayListCursor++;
        gDPSetTextureFilter(cmd, G_TF_BILERP);
        cmd = g_displayListCursor++;
        gDPSetTextureImage(cmd, G_IM_FMT_I, G_IM_SIZ_16b, 1, texture);
        cmd = g_displayListCursor++;
        gDPSetTile(cmd, G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP, 0, 0, G_TX_WRAP, 0, 0);
        cmd = g_displayListCursor++;
        gDPLoadSync(cmd);
        cmd = g_displayListCursor++;
        gDPLoadBlock(cmd, G_TX_LOADTILE, 0, 0, 143, 2048);
        cmd = g_displayListCursor++;
        gDPPipeSync(cmd);
        cmd = g_displayListCursor++;
        gDPSetTile(cmd, G_IM_FMT_I, G_IM_SIZ_4b, 2, 0, G_TX_RENDERTILE, 0, G_TX_WRAP, 0, 0, G_TX_WRAP, 0, 0);
        cmd = g_displayListCursor++;
        gDPSetTileSize(cmd, G_TX_RENDERTILE, 0, 0, 92, 92);
        cmd = g_displayListCursor++;
        gDPSetTile(cmd, G_IM_FMT_I, G_IM_SIZ_4b, 0, 0, 1, 0, G_TX_WRAP, 0, 0, G_TX_WRAP, 0, 0);
        cmd = g_displayListCursor++;
        gDPSetTileSize(cmd, 1, 0, 0, 60, 60);
        }

        OnScreen_SetTextColors(140, 140, 140, 140, 140, 140);
        OnScreen_SetTextScale(g_onscreenDefaultTextScale, g_onscreenDefaultTextScale);
        g_tutorialStatusBars.shadowX = 2;
        g_tutorialStatusBars.shadowY = 2;
    }
}

void OnScreen_LoadTextTileModeOne(void) {
    Gfx *cmd;
    u8 *v0;

    v0 = OnScreen_GetFontTexture();
    if (v0 != 0) {
        g_creditsTextDrawingEnabled = 1;
        cmd = g_displayListCursor++;
        gDPSetTextureImage(cmd, G_IM_FMT_I, G_IM_SIZ_16b, 1, v0);
        cmd = g_displayListCursor++;
        gDPSetTile(cmd, G_IM_FMT_I, G_IM_SIZ_16b, 0, 256, G_TX_LOADTILE, 0, G_TX_WRAP, 3, 0, G_TX_WRAP, 4, 0);
        cmd = g_displayListCursor++;
        gDPLoadSync(cmd);
        cmd = g_displayListCursor++;
        gDPLoadBlock(cmd, G_TX_LOADTILE, 0, 0, 31, 2048);
        cmd = g_displayListCursor++;
        gDPPipeSync(cmd);
        cmd = g_displayListCursor++;
        gDPSetTile(cmd, G_IM_FMT_I, G_IM_SIZ_4b, 1, 256, G_TX_RENDERTILE, 0, G_TX_WRAP, 3, 0, G_TX_WRAP, 4, 0);
        cmd = g_displayListCursor++;
        gDPSetTileSize(cmd, G_TX_RENDERTILE, 0, 0, 60, 28);
    }
}

void OnScreen_LoadTextTileModeTwo(void) {
    Gfx *cmd;
    u8 *v0;

    v0 = OnScreen_GetFontTexture();
    if (v0 != 0) {
        g_creditsTextDrawingEnabled = 2;
        cmd = g_displayListCursor++;
        gDPSetTextureImage(cmd, G_IM_FMT_I, G_IM_SIZ_16b, 1, v0);
        cmd = g_displayListCursor++;
        gDPSetTile(cmd, G_IM_FMT_I, G_IM_SIZ_16b, 0, 256, G_TX_LOADTILE, 0, G_TX_WRAP, 3, 0, G_TX_WRAP, 4, 0);
        cmd = g_displayListCursor++;
        gDPLoadSync(cmd);
        cmd = g_displayListCursor++;
        gDPLoadBlock(cmd, G_TX_LOADTILE, 0, 0, 31, 2048);
        cmd = g_displayListCursor++;
        gDPPipeSync(cmd);
        cmd = g_displayListCursor++;
        gDPSetTile(cmd, G_IM_FMT_I, G_IM_SIZ_4b, 1, 256, G_TX_RENDERTILE, 0, G_TX_WRAP, 3, 0, G_TX_WRAP, 4, 0);
        cmd = g_displayListCursor++;
        gDPSetTileSize(cmd, G_TX_RENDERTILE, 0, 0, 60, 28);
    }
}
