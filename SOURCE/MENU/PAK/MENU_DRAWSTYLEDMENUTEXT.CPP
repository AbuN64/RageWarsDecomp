#include "COMMON/TEXTLAYERMETRICS.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/LONE/HUD_REFERENCE_VIEWPORT_HEIGHT.H"
#include "MENU/OPTION_AND_TEXT_LAYER_VIEWS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/FONT_STYLE_AND_GLYPH_OPERATIONS.H"
#include "COMMON/MENU_UI_PROVIDERS.H"
#include "TYPES.H"
#include "GFX/TEXT/ONSCREEN_DRAWSCALEDMASKEDTILEGRID.H"

/* Chooses a text style, updates its colours and scale, then draws the text. */
/* The values Menu_DrawStyledMenuText loads by address:
 * 0x800E2490 = 1.25 (float, k_menuTextSelectedColorScale in this cartridge's tables)
 * 0x800E2494 = 0.9 (float, unnamed in this cartridge's tables)
 * 0x800E2498 = 0.25 (float, k_menuTextDimColorScale in this cartridge's tables)
 * 0x800E28D0 = 4.48e-43 (float, g_hudReferenceViewportWidth in this cartridge's tables; not a literal: a variable, its value in the image, since g_hudReferenceViewportWidth: `sw` at %lo(g_hudReferenceViewportWidth) in Frontend_ApplyVideoMode.s)
 * 0x800E28D4 = 3.36e-43 (float, g_hudReferenceViewportHeight in this cartridge's tables)
 * 0x800E249C = 0.0035211267 (float, k_menuTextViewportWidthScale in this cartridge's tables)
 * 0x800E24A0 = 0.0045045046 (float, k_menuTextViewportHeightScale in this cartridge's tables)
 * 0x800E24A4 = 255.0 (float, k_menuTextAlphaMax in this cartridge's tables)
 * 0x800E24A8 = 1.0 (float, k_menuTextDrawScale in this cartridge's tables)
 */
u32 Defs_GetMemorySize(void);

int SetN64_IsModeThirteen(void);

void Menu_DrawMenuPanel(StyledMenuTextPanel *menu, TextBoundsText *text, s32 relative);

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#endif



                          /* unable to generate initializer: unknown type */





extern CMenuFontInfo g_menuFontStyles[];

void Onscrn_SetupSpriteMode(s32);

void OnScreen_SetupFillMode(void);

/* unable to generate initializer: unknown type */

void Menu_DrawStyledMenuText(MenuTextOwnerView *option, StyledMenuTextEntryView *entry, s32 unusedDirection, StyledMenuTextPanel *menu, void *text, s32 forceTileMode) {
    f32 colorScale;
    s32 scaledRed;
    s32 scaledGreen;
    s32 scaledBlue;
    s32 scaledShadowRed;
    s32 unusedScaledShadowGreen;
    s32 unusedScaledShadowBlue;
    s32 styleIndex;
    s32 red;
    s32 green;
    s32 blue;
    s32 shadowRed;
    s32 renderMode;
    u32 styleFlags;
    u8 shadowOffset;
    CMenuFontInfo *fontInfo;

    shadowOffset = 1;
    if ((SetN64_IsModeThirteen() == 0) || !(option->flags & 0x40000000)) {
        if (g_frontendScreenStatus.settings.local != 0) {
            if (option->flags < 0) {
                if (Defs_GetMemorySize() == 0x400000) {
                    goto block_5;
                }
            }
        }
    } else {
block_5:
        menu->shadowEnabled = 0;
    }
    if (option->flags & 0x08000000) {
        if (menu->shadowClearRequest != 0) {
            menu->shadowEnabled = 0;
        }
        Menu_DrawMenuPanel(menu, (TextBoundsText *)option, 1);
        Menu_DrawMenuPanel(menu, (TextBoundsText *)option, 0);
        shadowOffset = 0;
    }
    if (menu->shadowEnabled == 0) {
        shadowOffset = 0;
    }
    styleFlags = option->flags & 0x3FE0;
    styleIndex = 0;
    switch (styleFlags) {
    case 32: styleIndex = 0; break;
    case 64: styleIndex = 1; break;
    case 128: styleIndex = 2; break;
    case 0x100: styleIndex = 3; break;
    case 0x200: styleIndex = 4; break;
    case 0x400: styleIndex = 5; break;
    case 0x800: styleIndex = 6; break;
    case 0x1000: styleIndex = 7; break;
    case 0x2000: styleIndex = 8; break;
    default: styleIndex = 0; break;
    }
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    styleIndex += g_languageIndex * 9;
#endif
    fontInfo = &g_menuFontStyles[styleIndex];
    renderMode = fontInfo->kind;
    if (forceTileMode != 0) {
        renderMode = 6;
    }
    if (g_multiplayerItemRenderState != renderMode) {
        switch (renderMode) {                           /* irregular */
        case 0:
            OnScreen_SetupTextRendering();
            break;
        case 1:
            OnScreen_SetupTextRendering();
            OnScreen_LoadTextTileModeOne();
            break;
        case 2:
            OnScreen_SetupTextRendering();
            OnScreen_LoadTextTileModeTwo();
            break;
        case 6:
            OnScreen_SetupTextRendering();
            OnScreen_LoadTextTileModeOne();
            g_creditsTextDrawingEnabled = 1;
            break;
        }
        g_multiplayerItemRenderState = renderMode;
    }
    if (entry->index == menu->selectedIndex) {
        colorScale = 1.25f;
    } else if (!(option->flags & 0x01000000)) {
        colorScale = 0.25f;
    } else {
        colorScale = 0.9f;
    }
    scaledRed = (s32) ((f32) fontInfo->color0 * colorScale);
    red = 0xFF;
    if (scaledRed < 256) {
        red = scaledRed;
    }
    scaledGreen = (s32) ((f32) fontInfo->color1 * colorScale);
    green = 0xFF;
    if (scaledGreen < 256) {
        green = scaledGreen;
    }
    scaledBlue = (s32) ((f32) fontInfo->color2 * colorScale);
    blue = 0xFF;
    if (scaledBlue < 256) {
        blue = scaledBlue;
    }
    scaledShadowRed = (s32) ((f32) fontInfo->color3 * colorScale);
    shadowRed = 0xFF;
    if (scaledShadowRed < 256) {
        shadowRed = scaledShadowRed;
    }
    OnScreen_SetTextColors(red, green, blue, shadowRed,
        (s32)((f32)fontInfo->color4 * colorScale) > 0xFF ? 0xFF : (s32)((f32)fontInfo->color4 * colorScale),
        (s32)((f32)fontInfo->color5 * colorScale) > 0xFF ? 0xFF : (s32)((f32)fontInfo->color5 * colorScale));
    g_tutorialStatusBars.shadowX = (s32) fontInfo->shadowOffset;
    g_tutorialStatusBars.shadowY = (s32) fontInfo->shadowOffset;
    OnScreen_SetTextScale(fontInfo->scaleX * (f32) (g_hudReferenceViewportWidth) * 0.0035211267f, fontInfo->scaleY * (f32) (g_hudReferenceViewportHeight) * 0.0045045046f);
    if (shadowOffset != 0) {
        shadowOffset = fontInfo->shadowOffset;
    }
    Onscrn_DrawText(text, entry->x, entry->y, (s32) (menu->alpha * (menu->fade * 255.0f)), 0, (s32) shadowOffset, 1.0f, 1.0f);
}

void Menu_DrawMenuOptionSprite(MenuOption *option, MenuOptionBox *box, s32 dir, MenuOptionFade *fadeState) {
    s32 boxAlpha;
    f32 right;
    f32 bottom;
    f32 width;
    f32 height;
    s32 *active;

    if (((SetN64_IsModeThirteen() != 0) && (option->flags & 0x40000000)) || ((g_frontendScreenStatus.settings.local != 0) && (option->flags < 0) && (Defs_GetMemorySize() == 0x400000))) {
        fadeState->highlighted = 1;
        if (g_multiplayerItemRenderState != 3) {
            g_multiplayerItemRenderState = 3;
        }
        OnScreen_SetupFillMode();
        width = (f32)box->width * box->scaleX;
        height = (f32)box->height * box->scaleY;
        bottom = (f32)box->top;
        right = (f32)box->left;
        right += width;
        bottom += height;
        active = &g_frontendScreenStatus.status[7];
        if (*active != 0) {
            if (g_frontendScreenStatus.settings.local == 0) {
                boxAlpha = 128;
            } else if (option->flags < 0) {
                boxAlpha = 0xFF;
            } else {
                boxAlpha = 192;
            }
        } else {
            boxAlpha = 128;
        }
        OnScreen_DrawBevelBox(box->left, box->top, (s32)right, (s32)bottom, 1, 0, 0, 0, 0, boxAlpha);
        return;
    }
    if (g_multiplayerItemRenderState != 3) {
        g_multiplayerItemRenderState = 3;
        Onscrn_SetupSpriteMode((s32) (fadeState->fade * (fadeState->alpha * g_menuSpriteAlphaScale)));
    }
    OnScreen_DrawSpriteResource(option->resource, 0, (s16)box->left, (s16)box->top, box->scaleX, box->scaleY, 1);
}
