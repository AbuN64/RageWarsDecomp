#include "include_asm.h"

#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/FONT_STYLE_AND_GLYPH_OPERATIONS.H"
#include "COMMON/MENURECAT20V1.H"
#include "MULTI/SETUP_SETUPNAMESPINNER.H"
#include "TYPES.H"
#include "GFX/TEXT/ONSCREEN_DRAWSCALEDMASKEDTILEGRID.H"

/* Draws a menu spinner: during the first half of its blink period (the timer of its g_multiplayerNameEntryStates entry up to the float after g_multiplayerNameEntryTimingLimits) it fills a two-pixel white bar under the digit its value selects, placed from the item's x at 0x14 by the character width Menu_GetWidgetStyle_EncodedDrawtextentrycursor reports scaled to the screen, with the style's alpha at 0x30 and 0x34, through OnScreen_SetupFillMode and OnScreen_DrawBevelBox; then draws the item through Menu_DrawLocalizedMenuItemText. */








extern Spinner g_multiplayerNameEntryStates[];



extern s32 Player_GetPlayerIndex(char *, s32);
extern PaddedFloatView *Menu_GetWidgetStyle(void *, s32);

extern void Menu_DrawLocalizedMenuItemText(struct Field *object, s32 second, s32 third, s32 fourth);

void Setup_DrawNameCursor(void *menu, MenuLocalizedTextItemView *item, void *third, StyleMultiDrawNameCursor *style) {
    s32 i;
    f32 width;
    f32 alpha;
    s32 x;
    unsigned int bits;

    i = Player_GetPlayerIndex(&g_playerViewRenderContext, style->id);
    if (g_multiplayerNameEntryStates[i].timer <= *(&g_multiplayerNameEntryTimingLimits + 1)) {
        width = Menu_GetWidgetStyle(menu, 0)->value * (f32)g_hudReferenceViewportWidth * g_multiplayerNameCursorWidthScale;
        x = (f32)item->x + (f32)g_multiplayerNameEntryStates[i].value * width;
        g_multiplayerItemRenderState = -1;
        alpha = style->alpha * (style->fade * (64.0f));
        OnScreen_SetupFillMode();
        OnScreen_DrawBevelBox(x, item->y - 2, (f32)x + width, item->y, 0, 0, 0xFF, 0xFF, 0xFF,
                      (u8)(bits = !((2147483648.0f) <= alpha) ? (s32)alpha : (bits = (s32)(alpha - (2147483648.0f))) | 0x80000000));
    }
    Menu_DrawLocalizedMenuItemText(menu, item, third, style);
}
